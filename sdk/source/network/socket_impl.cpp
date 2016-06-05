/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : network/socket_impl.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-05
  Description: 
  History    : 
*******************************************************************************/

#include "network/socket_impl.hpp"

namespace ufc {
    
    socket_impl::socket_impl():
        _sockfd(ufc_invalid_socket),
        _blocking(true)
    {
    }
    
    
    socket_impl::socket_impl(socket_t sockfd):
        _sockfd(sockfd),
        _blocking(true)
    {
    }
    
    
    socket_impl::~socket_impl()
    {
        close();
    }
    
        
    socket_impl* socket_impl::accept_connection(socket_address& __client_address)
    {
        if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
    
        char buffer[socket_address::max_address_length];
        struct sockaddr* pSA = reinterpret_cast<struct sockaddr*>(buffer);
        socklen_t saLen = sizeof(buffer);
        socket_t sd;
        do
        {
            sd = ::accept(_sockfd, pSA, &saLen);
        }
        while (sd == ufc_invalid_socket && last_error() == ufc_eintr);
        if (sd != ufc_invalid_socket)
        {
            __client_address = socket_address(pSA, saLen);
            return new StreamSocketImpl(sd);
        }
        error(); // will throw
        return 0;
    }
    
    
    void socket_impl::connect(const socket_address& __address)
    {
        if (_sockfd == ufc_invalid_socket)
        {
            init(__address.af());
        }
        int __rc;
        do
        {
#if defined(ufc_vxworks)
            __rc = ::connect(_sockfd, (sockaddr*) __address.addr(), __address.length());
#else
            __rc = ::connect(_sockfd, __address.addr(), __address.length());
#endif
        }
        while (__rc != 0 && last_error() == ufc_eintr);
        if (__rc != 0) 
        {
            int err = last_error();
            error(err, __address.to_string());
        }
    }
    
    
    void socket_impl::connect(const socket_address& __address, const Timespan& timeout)
    {
        if (_sockfd == ufc_invalid_socket)
        {
            init(__address.af());
        }
        set_blocking(false);
        try
        {
#if defined(ufc_vxworks)
            int __rc = ::connect(_sockfd, (sockaddr*) __address.addr(), __address.length());
#else
            int __rc = ::connect(_sockfd, __address.addr(), __address.length());
#endif
            if (__rc != 0)
            {
                int err = last_error();
                if (err != ufc_einprogress && err != ufc_ewouldblock)
                    error(err, __address.to_string());
                if (!poll(timeout, select_read | select_write | select_error))
                    throw timeout_error("connect timed out", __address.to_string());
                err = socketError();
                if (err != 0) error(err);
            }
        }
        catch (exception&)
        {
            set_blocking(true);
            throw;
        }
        set_blocking(true);
    }
    
    
    void socket_impl::connect_nb(const socket_address& __address)
    {
        if (_sockfd == ufc_invalid_socket)
        {
            init(__address.af());
        }
        set_blocking(false);
#if defined(ufc_vxworks)
        int __rc = ::connect(_sockfd, (sockaddr*) __address.addr(), __address.length());
#else
        int __rc = ::connect(_sockfd, __address.addr(), __address.length());
#endif
        if (__rc != 0)
        {
            int err = last_error();
            if (err != ufc_EINPROGRESS && err != ufc_EWOULDBLOCK)
                error(err, __address.to_string());
        }
    }
    
    
    void socket_impl::bind(const socket_address& __address, bool __reuse_address)
    {
        if (_sockfd == ufc_invalid_socket)
        {
            init(__address.af());
        }
        if (__reuse_address)
        {
            set_reuse_address(true);
            set_reuse_port(true);
        }
#if defined(ufc_vxworks)
        int __rc = ::bind(_sockfd, (sockaddr*) __address.addr(), __address.length());
#else
        int __rc = ::bind(_sockfd, __address.addr(), __address.length());
#endif
        if (__rc != 0) error(__address.to_string());
    }
    
    
    void socket_impl::bind6(const socket_address& __address, bool __reuse_address, bool __ipv6_only)
    {
#if defined(ufc_have_ipv6)
        if (__address.family() != ip_address::ipv6)
            throw InvalidArgumentException("socket_address must be an IPv6 __address");
            
        if (_sockfd == ufc_invalid_socket)
        {
            init(__address.af());
        }
        set_option(IPPROTO_IPV6, IPV6_V6ONLY, __ipv6_only ? 1 : 0);
        if (__reuse_address)
        {
            set_reuse_address(true);
            set_reuse_port(true);
        }
        int __rc = ::bind(_sockfd, __address.addr(), __address.length());
        if (__rc != 0) error(__address.to_string());
#else
        throw not_implemented_error("No IPv6 support available");
#endif
    }
    
        
    void socket_impl::listen(int backlog)
    {
        if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
        
        int __rc = ::listen(_sockfd, backlog);
        if (__rc != 0) error();
    }
    
    
    void socket_impl::close()
    {
        if (_sockfd != ufc_invalid_socket)
        {
        #ifdef ufc_os_family_windows
            closesocket(_sockfd);
        #else
            ::close(_sockfd);
        #endif
            _sockfd = ufc_invalid_socket;
        }
    }
    
    
    void socket_impl::shutdown_receive()
    {
        if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
    
        int __rc = ::shutdown(_sockfd, 0);
        if (__rc != 0) error();
    }
    
        
    void socket_impl::shutdown_send()
    {
        if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
    
        int __rc = ::shutdown(_sockfd, 1);
        if (__rc != 0) error();
    }
    
        
    void socket_impl::shutdown()
    {
        if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
    
        int __rc = ::shutdown(_sockfd, 2);
        if (__rc != 0) error();
    }
    
    
    int socket_impl::send_bytes(const void* buffer, int length, int flags)
    {
#if defined(ufc_broken_timeouts)
        if (_sndTimeout.totalMicroseconds() != 0)
        {
            if (!poll(_sndTimeout, SELECT_WRITE))
                throw timeout_error();
        }
#endif
    
        int __rc;
        do
        {
            if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
            __rc = ::send(_sockfd, reinterpret_cast<const char*>(buffer), length, flags);
        }
        while (__rc < 0 && last_error() == ufc_eintr);
        if (__rc < 0) error();
        return __rc;
    }
    
    
    int socket_impl::receive_bytes(void* buffer, int length, int flags)
    {
#if defined(ufc_broken_timeouts)
        if (_recv_timeout.get_total_microseconds() != 0)
        {
            if (!poll(_recv_timeout, select_read))
                throw timeout_error();
        }
#endif
        
        int __rc;
        do
        {
            if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
            __rc = ::recv(_sockfd, reinterpret_cast<char*>(buffer), length, flags);
        }
        while (__rc < 0 && last_error() == ufc_eintr);
        if (__rc < 0) 
        {
            int err = last_error();
            if (err == ufc_eagain || err == ufc_etimedout)
                throw timeout_error();
            else
                error(err);
        }
        return __rc;
    }
    
    
    int socket_impl::send_to(const void* buffer, int length, const socket_address& __address, int flags)
    {
        int __rc;
        do
        {
            if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
#if defined(ufc_vxworks)
            __rc = ::sendto(_sockfd, (char*) buffer, length, flags, (sockaddr*) __address.addr(), __address.length());
#else
            __rc = ::sendto(_sockfd, reinterpret_cast<const char*>(buffer), length, flags, __address.addr(), __address.length());
#endif
        }
        while (__rc < 0 && last_error() == ufc_eintr);
        if (__rc < 0) error();
        return __rc;
    }
    
    
    int socket_impl::receive_from(void* buffer, int length, socket_address& __address, int flags)
    {
#if defined(ufc_broken_timeouts)
        if (_recv_timeout.totalMicroseconds() != 0)
        {
            if (!poll(_recv_timeout, select_read))
                throw timeout_error();
        }
#endif
        
        char abuffer[socket_address::max_address_length];
        struct sockaddr* pSA = reinterpret_cast<struct sockaddr*>(abuffer);
        socklen_t saLen = sizeof(abuffer);
        int __rc;
        do
        {
            if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
            __rc = ::recvfrom(_sockfd, reinterpret_cast<char*>(buffer), length, flags, pSA, &saLen);
        }
        while (__rc < 0 && last_error() == ufc_eintr);
        if (__rc >= 0)
        {
            __address = socket_address(pSA, saLen);
        }
        else
        {
            int err = last_error();
            if (err == ufc_eagain || err == ufc_etimedout)
                throw timeout_error();
            else
                error(err);
        }
        return __rc;
    }
    
    
    void socket_impl::send_urgent(unsigned char data)
    {
        if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
    
        int __rc = ::send(_sockfd, reinterpret_cast<const char*>(&data), sizeof(data), MSG_OOB);
        if (__rc < 0) error();
    }
    
    
    int socket_impl::available()
    {
        int result;
        ioctl(FIONREAD, result);
        return result;
    }
    
    
    bool socket_impl::secure() const
    {
        return false;
    }
    
    
    bool socket_impl::poll(const timespan& timeout, int mode)
    {
        socket_t sockfd = _sockfd;
        if (sockfd == ufc_invalid_socket) throw invalid_socket_error();
    
#if defined(ufc_have_fd_epoll)
    
        int epollfd = epoll_create(1);
        if (epollfd < 0)
        {
            char buf[1024];
            strerror_r(errno, buf, sizeof(buf));
            error(std::string("Can't create epoll queue: ") + buf);
        }
    
        struct epoll_event evin;
        memset(&evin, 0, sizeof(evin));
    
        if (mode & SELECT_READ)
            evin.events |= EPOLLIN;
        if (mode & SELECT_WRITE)
            evin.events |= EPOLLOUT;
        if (mode & SELECT_ERROR)
            evin.events |= EPOLLERR;
    
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &evin) < 0)
        {
            char buf[1024];
            strerror_r(errno, buf, sizeof(buf));
            ::close(epollfd);
            error(std::string("Can't insert socket to epoll queue: ") + buf);
        }
    
        timespan remainingTime(timeout);
        int __rc;
        do
        {
            struct epoll_event evout;
            memset(&evout, 0, sizeof(evout));
    
            timestamp start;
            __rc = epoll_wait(epollfd, &evout, 1, remainingTime.totalMilliseconds());
            if (__rc < 0 && last_error() == ufc_eintr)
            {
                Timestamp end;
                Timespan waited = end - start;
                if (waited < remainingTime)
                    remainingTime -= waited;
                else
                    remainingTime = 0;
            }
        }
        while (__rc < 0 && last_error() == ufc_eintr);
    
        ::close(epollfd);
        if (__rc < 0) error();
        return __rc > 0; 
    
#else
    
        fd_set fdRead;
        fd_set fdWrite;
        fd_set fdExcept;
        FD_ZERO(&fdRead);
        FD_ZERO(&fdWrite);
        FD_ZERO(&fdExcept);
        if (mode & select_read)
        {
            FD_SET(sockfd, &fdRead);
        }
        if (mode & select_write)
        {
            FD_SET(sockfd, &fdWrite);
        }
        if (mode & select_error)
        {
            FD_SET(sockfd, &fdExcept);
        }
        timespan remainingTime(timeout);
        int __rc;
        do
        {
            struct timeval tv;
            tv.tv_sec  = (long) remainingTime.totalSeconds();
            tv.tv_usec = (long) remainingTime.useconds();
            timestamp start;
            __rc = ::select(int(sockfd) + 1, &fdRead, &fdWrite, &fdExcept, &tv);
            if (__rc < 0 && last_error() == ufc_eintr)
            {
                timestamp end;
                timespan waited = end - start;
                if (waited < remainingTime)
                    remainingTime -= waited;
                else
                    remainingTime = 0;
            }
        }
        while (__rc < 0 && last_error() == ufc_eintr);
        if (__rc < 0) error();
        return __rc > 0; 
    
#endif // ufc_HAVE_FD_EPOLL
    }
    
        
    void socket_impl::set_send_buffer_size(int size)
    {
        set_option(SOL_SOCKET, SO_SNDBUF, size);
    }
    
        
    int socket_impl::getSendBufferSize()
    {
        int result;
        get_option(SOL_SOCKET, SO_SNDBUF, result);
        return result;
    }
    
    
    void socket_impl::setReceiveBufferSize(int size)
    {
        set_option(SOL_SOCKET, SO_RCVBUF, size);
    }
    
        
    int socket_impl::getReceiveBufferSize()
    {
        int result;
        get_option(SOL_SOCKET, SO_RCVBUF, result);
        return result;
    }
    
    
    void socket_impl::setSendTimeout(const Timespan& timeout)
    {
#if defined(_WIN32) && !defined(ufc_BROKEN_TIMEOUTS)
        int value = (int) timeout.totalMilliseconds();
        set_option(SOL_SOCKET, SO_SNDTIMEO, value);
#elif defined(ufc_BROKEN_TIMEOUTS)
        _sndTimeout = timeout;
#else
        set_option(SOL_SOCKET, SO_SNDTIMEO, timeout);
#endif
    }
    
    
    Timespan socket_impl::getSendTimeout()
    {
        Timespan result;
#if defined(_WIN32) && !defined(ufc_BROKEN_TIMEOUTS)
        int value;
        get_option(SOL_SOCKET, SO_SNDTIMEO, value);
        result = Timespan::TimeDiff(value)*1000;
#elif defined(ufc_BROKEN_TIMEOUTS)
        result = _sndTimeout;
#else
        get_option(SOL_SOCKET, SO_SNDTIMEO, result);
#endif
        return result;
    }
    
    
    void socket_impl::setReceiveTimeout(const Timespan& timeout)
    {
#ifndef ufc_BROKEN_TIMEOUTS
#if defined(_WIN32)
        int value = (int) timeout.totalMilliseconds();
        set_option(SOL_SOCKET, SO_RCVTIMEO, value);
#else
      set_option(SOL_SOCKET, SO_RCVTIMEO, timeout);
#endif
#else
        _recv_timeout = timeout;
#endif
    }
    
    
    Timespan socket_impl::getReceiveTimeout()
    {
        Timespan result;
#if defined(_WIN32) && !defined(ufc_BROKEN_TIMEOUTS)
        int value;
        get_option(SOL_SOCKET, SO_RCVTIMEO, value);
        result = Timespan::TimeDiff(value)*1000;
#elif defined(ufc_BROKEN_TIMEOUTS)
        result = _recv_timeout;
#else
        get_option(SOL_SOCKET, SO_RCVTIMEO, result);
#endif
        return result;
    }
    
        
    socket_address socket_impl::address()
    {
        if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
        
        char buffer[socket_address::MAX_ADDRESS_LENGTH];
        struct sockaddr* pSA = reinterpret_cast<struct sockaddr*>(buffer);
        socklen_t saLen = sizeof(buffer);
        int __rc = ::getsockname(_sockfd, pSA, &saLen);
        if (__rc == 0)
            return socket_address(pSA, saLen);
        else 
            error();
        return socket_address();
    }
    
        
    socket_address socket_impl::peerAddress()
    {
        if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
        
        char buffer[socket_address::MAX_ADDRESS_LENGTH];
        struct sockaddr* pSA = reinterpret_cast<struct sockaddr*>(buffer);
        socklen_t saLen = sizeof(buffer);
        int __rc = ::getpeername(_sockfd, pSA, &saLen);
        if (__rc == 0)
            return socket_address(pSA, saLen);
        else 
            error();
        return socket_address();
    }
    
    
    void socket_impl::set_option(int level, int option, int value)
    {
        setRawOption(level, option, &value, sizeof(value));
    }
    
    
    void socket_impl::set_option(int level, int option, unsigned value)
    {
        setRawOption(level, option, &value, sizeof(value));
    }
    
    
    void socket_impl::set_option(int level, int option, unsigned char value)
    {
        setRawOption(level, option, &value, sizeof(value));
    }
    
    
    void socket_impl::set_option(int level, int option, const IPAddress& value)
    {
        setRawOption(level, option, value.addr(), value.length());
    }
    
    
    void socket_impl::set_option(int level, int option, const Timespan& value)
    {
        struct timeval tv;
        tv.tv_sec  = (long) value.totalSeconds();
        tv.tv_usec = (long) value.useconds();
        
        setRawOption(level, option, &tv, sizeof(tv));
    }
    
        
    void socket_impl::setRawOption(int level, int option, const void* value, socklen_t length)
    {
        if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
    
#if defined(ufc_vxworks)
        int __rc = ::setsockopt(_sockfd, level, option, (char*) value, length);
#else	
        int __rc = ::setsockopt(_sockfd, level, option, reinterpret_cast<const char*>(value), length);
#endif
        if (__rc == -1) error();
    }
    
    
    void socket_impl::get_option(int level, int option, int& value)
    {
        socklen_t len = sizeof(value);
        getRawOption(level, option, &value, len);
    }
    
    
    void socket_impl::get_option(int level, int option, unsigned& value)
    {
        socklen_t len = sizeof(value);
        getRawOption(level, option, &value, len);
    }
    
    
    void socket_impl::get_option(int level, int option, unsigned char& value)
    {
        socklen_t len = sizeof(value);
        getRawOption(level, option, &value, len);
    }
    
    
    void socket_impl::get_option(int level, int option, Timespan& value)
    {
        struct timeval tv;
        socklen_t len = sizeof(tv);
        getRawOption(level, option, &tv, len);
        value.assign(tv.tv_sec, tv.tv_usec);
    }
    
    
    void socket_impl::get_option(int level, int option, IPAddress& value)
    {
        char buffer[IPAddress::MAX_ADDRESS_LENGTH];
        socklen_t len = sizeof(buffer);
        getRawOption(level, option, buffer, len);
        value = IPAddress(buffer, len);
    }
    
    
    void socket_impl::getRawOption(int level, int option, void* value, socklen_t& length)
    {
        if (_sockfd == ufc_invalid_socket) throw invalid_socket_error();
        
        int __rc = ::getsockopt(_sockfd, level, option, reinterpret_cast<char*>(value), &length);
        if (__rc == -1) error();
    }
    
    
    void socket_impl::setLinger(bool on, int seconds)
    {
        struct linger l;
        l.l_onoff  = on ? 1 : 0;
        l.l_linger = seconds;
        setRawOption(SOL_SOCKET, SO_LINGER, &l, sizeof(l));
    }
    
        
    void socket_impl::getLinger(bool& on, int& seconds)
    {
        struct linger l;
        socklen_t len = sizeof(l);
        getRawOption(SOL_SOCKET, SO_LINGER, &l, len);
        on      = l.l_onoff != 0;
        seconds = l.l_linger;
    }
    
    
    void socket_impl::setNoDelay(bool flag)
    {
        int value = flag ? 1 : 0;
        set_option(IPPROTO_TCP, TCP_NODELAY, value);
    }
    
    
    bool socket_impl::getNoDelay()
    {
        int value(0);
        get_option(IPPROTO_TCP, TCP_NODELAY, value);
        return value != 0;
    }
    
    
    void socket_impl::setKeepAlive(bool flag)
    {
        int value = flag ? 1 : 0;
        set_option(SOL_SOCKET, SO_KEEPALIVE, value);
    }
    
    
    bool socket_impl::getKeepAlive()
    {
        int value(0);
        get_option(SOL_SOCKET, SO_KEEPALIVE, value);
        return value != 0;
    }
    
    
    void socket_impl::set_reuse_address(bool flag)
    {
        int value = flag ? 1 : 0;
        set_option(SOL_SOCKET, SO_REUSEADDR, value);
    }
    
    
    bool socket_impl::getReuseAddress()
    {
        int value(0);
        get_option(SOL_SOCKET, SO_REUSEADDR, value);
        return value != 0;
    }
    
    
    void socket_impl::set_reuse_port(bool flag)
    {
#ifdef SO_REUSEPORT
        try
        {
            int value = flag ? 1 : 0;
            set_option(SOL_SOCKET, SO_REUSEPORT, value);
        }
        catch (IOException&)
        {
            // ignore error, since not all implementations
            // support SO_REUSEPORT, even if the macro
            // is defined.
        }
#endif
    }
    
    
    bool socket_impl::getReusePort()
    {
#ifdef SO_REUSEPORT
        int value(0);
        get_option(SOL_SOCKET, SO_REUSEPORT, value);
        return value != 0;
#else
        return false;
#endif
    }
    
    
    void socket_impl::setOOBInline(bool flag)
    {
        int value = flag ? 1 : 0;
        set_option(SOL_SOCKET, SO_OOBINLINE, value);
    }
    
    
    bool socket_impl::getOOBInline()
    {
        int value(0);
        get_option(SOL_SOCKET, SO_OOBINLINE, value);
        return value != 0;
    }
    
    
    void socket_impl::setBroadcast(bool flag)
    {
        int value = flag ? 1 : 0;
        set_option(SOL_SOCKET, SO_BROADCAST, value);
    }
    
        
    bool socket_impl::getBroadcast()
    {
        int value(0);
        get_option(SOL_SOCKET, SO_BROADCAST, value);
        return value != 0;
    }
    
    
    void socket_impl::set_blocking(bool flag)
    {
        int arg = flag ? 0 : 1;
        ioctl(FIONBIO, arg);
        _blocking = flag;
    }
    
    
    int socket_impl::socketError()
    {
        int result(0);
        get_option(SOL_SOCKET, SO_ERROR, result);
        return result;
    }
    
    
    void socket_impl::init(int af)
    {
        initSocket(af, SOCK_STREAM);
    }
    
    
    void socket_impl::initSocket(int af, int type, int proto)
    {
        poco_assert (_sockfd == ufc_invalid_socket);
    
        _sockfd = ::socket(af, type, proto);
        if (_sockfd == ufc_invalid_socket)
            error();
    }
    
    
    void socket_impl::ioctl(poco_ioctl_request_t request, int& arg)
    {
#if defined(_WIN32)
        int __rc = ioctlsocket(_sockfd, request, reinterpret_cast<u_long*>(&arg));
#elif defined(ufc_vxworks)
        int __rc = ::ioctl(_sockfd, request, (int) &arg);
#else
        int __rc = ::ioctl(_sockfd, request, &arg);
#endif
        if (__rc != 0) error();
    }
    
    
    void socket_impl::ioctl(poco_ioctl_request_t request, void* arg)
    {
#if defined(_WIN32)
        int __rc = ioctlsocket(_sockfd, request, reinterpret_cast<u_long*>(arg));
#elif defined(ufc_vxworks)
        int __rc = ::ioctl(_sockfd, request, (int) arg);
#else
        int __rc = ::ioctl(_sockfd, request, arg);
#endif
        if (__rc != 0) error();
    }
    
    
    void socket_impl::reset(socket_t aSocket)
    {
        _sockfd = aSocket;
    }
    
    
    void socket_impl::error()
    {
        int err = last_error();
        std::string empty;
        error(err, empty);
    }
    
    
    void socket_impl::error(const std::string& arg)
    {
        error(last_error(), arg);
    }
    
    
    void socket_impl::error(int code)
    {
        std::string arg;
        error(code, arg);
    }
    
    
    void socket_impl::error(int code, const std::string& arg)
    {
        switch (code)
        {
        case ufc_ESYSNOTREADY:
            throw NetException("Net subsystem not ready");
        case ufc_ENOTINIT:
            throw NetException("Net subsystem not initialized");
        case ufc_eintr:
            throw IOException("Interrupted");
        case ufc_EACCES:
            throw IOException("Permission denied");
        case ufc_EFAULT:
            throw IOException("Bad __address");
        case ufc_EINVAL:
            throw InvalidArgumentException();
        case ufc_EMFILE:
            throw IOException("Too many open files");
        case ufc_EWOULDBLOCK:
            throw IOException("Operation would block");
        case ufc_EINPROGRESS:
            throw IOException("Operation now in progress");
        case ufc_EALREADY:
            throw IOException("Operation already in progress");
        case ufc_ENOTSOCK:
            throw IOException("Socket operation attempted on non-socket");
        case ufc_EDESTADDRREQ:
            throw NetException("Destination __address required");
        case ufc_EMSGSIZE:
            throw NetException("Message too long");
        case ufc_EPROTOTYPE:
            throw NetException("Wrong protocol type");
        case ufc_ENOPROTOOPT:
            throw NetException("Protocol not available");
        case ufc_EPROTONOSUPPORT:
            throw NetException("Protocol not supported");
        case ufc_ESOCKTNOSUPPORT:
            throw NetException("Socket type not supported");
        case ufc_ENOTSUP:
            throw NetException("Operation not supported");
        case ufc_EPFNOSUPPORT:
            throw NetException("Protocol family not supported");
        case ufc_EAFNOSUPPORT:
            throw NetException("Address family not supported");
        case ufc_EADDRINUSE:
            throw NetException("Address already in use", arg);
        case ufc_EADDRNOTAVAIL:
            throw NetException("Cannot assign requested __address", arg);
        case ufc_ENETDOWN:
            throw NetException("Network is down");
        case ufc_ENETUNREACH:
            throw NetException("Network is unreachable");
        case ufc_ENETRESET:
            throw NetException("Network dropped connection on reset");
        case ufc_ECONNABORTED:
            throw ConnectionAbortedException();
        case ufc_ECONNRESET:
            throw ConnectionResetException();
        case ufc_ENOBUFS:
            throw IOException("No buffer space available");
        case ufc_EISCONN:
            throw NetException("Socket is already connected");
        case ufc_ENOTCONN:
            throw NetException("Socket is not connected");
        case ufc_ESHUTDOWN:
            throw NetException("Cannot send after socket shutdown");
        case ufc_ETIMEDOUT:
            throw timeout_error();
        case ufc_ECONNREFUSED:
            throw ConnectionRefusedException(arg);
        case ufc_EHOSTDOWN:
            throw NetException("Host is down", arg);
        case ufc_EHOSTUNREACH:
            throw NetException("No route to host", arg);
        default:
            throw IOException(NumberFormatter::format(code), arg);
        }
    }

}//namespace ufc
