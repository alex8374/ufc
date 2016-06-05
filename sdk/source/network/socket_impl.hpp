/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : network/socket_impl.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-05
  Description: 
  History    : 
*******************************************************************************/
#ifndef NETWORK_SOCKET_IMPL_HPP
#define NETWORK_SOCKET_IMPL_HPP

#include "ufc/network/socketdefs.hpp"
#include "ufc/network/socket_address.hpp"
#include "ufc/network/ip_address.hpp"

namespace ufc {
    
    class socket_impl: public ref_counted_object
        /// This class encapsulates the Berkeley sockets API.
        /// 
        /// Subclasses implement specific socket types like
        /// stream or datagram sockets.
        ///
        /// You should not create any instances of this class.
    {
    public:
        enum select_mode_t
        {
            select_read  = 1,
            select_write = 2,
            select_error = 4
        };

        ///
        /// @breif: Get the next completed connection from the socket's completed connection queue.
        ///         If the queue is empty, waits until a connection request completes.
        ///         Returns a new TCP socket for the connection with the client.
        ///         The client socket's address is returned in __client_address.
        ///
        virtual socket_impl* accept_connection(socket_address& __client_address);

        ///
        /// @breif: Initializes the socket and establishes a connection to the TCP server at the given address.
        ///
        ///         Can also be used for UDP sockets. In this case, no
        ///         connection is established. Instead, incoming and outgoing
        ///         packets are restricted to the specified address.
        ///
        virtual void connect(const socket_address& __address);

        ///
        /// @breif: Initializes the socket, sets the socket __timeout and 
        ///         establishes a connection to the TCP server at the given address.
        ///
        virtual void connect(const socket_address& __address, const timespan& __timeout);

        ///
        /// @breif: Initializes the socket and establishes a connection to 
        ///         the TCP server at the given address. Prior to opening the
        ///         connection the socket is set to nonblocking mode.
        ///
        virtual void connect_nb(const socket_address& __address);

        ///
        /// @breif: Bind a local address to the socket.
        ///
        ///         This is usually only done when establishing a server
        ///         socket. TCP clients should not bind a socket to a
        ///         specific address.
        ///
        ///         If reuseAddress is true, sets the SO_REUSEADDR socket __option.
        ///
        virtual void bind(const socket_address& __address, bool __reuse_address = false);

        ///
        /// @breif: Bind a local IPv6 address to the socket.
        ///
        ///         This is usually only done when establishing a server
        ///         socket. TCP clients should not bind a socket to a
        ///         specific address.
        ///
        ///         If reuseAddress is true, sets the SO_REUSEADDR socket __option.
        ///
        ///         The given address must be an IPv6 address. The
        ///         IPPROTO_IPV6/IPV6_V6ONLY __option is set on the socket
        ///         according to the ipV6Only parameter.
        ///
        ///         If the library has not been built with IPv6 support,
        ///         a not_implemented_error will be thrown.
        ///
        virtual void bind6(const socket_address& __address, bool __reuse_address = false, bool __ipv6_only = false);

        ///
        /// @breif: Puts the socket into listening state.
        ///
        ///         The socket becomes a passive socket that
        ///         can accept incoming connection requests.
        ///
        ///         The backlog argument specifies the maximum
        ///         number of connections that can be queued
        ///         for this socket.
        ///
        virtual void listen(int32_t __backlog = 64);

        ///
        /// @breif: Close the socket.
        ///
        virtual void close();

        ///
        /// @breif: Shuts down the receiving part of the socket connection.
        ///
        virtual void shutdown_receive();

        ///
        /// @breif: Shuts down the sending part of the socket connection.
        ///
        virtual void shutdown_send();

        ///
        /// @breif: Shuts down both the receiving and the sending part
        ///         of the socket connection.
        ///
        virtual void shutdown();

        ///
        /// @breif: Sends the contents of the given __buffer through the socket.
        ///
        ///         Returns the number of bytes sent, which may be
        ///         less than the number of bytes specified.
        ///
        ///         Certain socket implementations may also return a negative
        ///         __valuee denoting a certain condition.
        ///
        virtual int32_t send_bytes(const void* __buffer, int32_t __length, int32_t __flags = 0);

        ///
        /// @breif: Receives data from the socket and stores it
        ///         in __buffer. Up to __length bytes are received.
        ///
        ///         Returns the number of bytes received.
        ///
        ///         Certain socket implementations may also return a negative
        ///         __valuee denoting a certain condition.
        ///
        virtual int32_t receive_bytes(void* __buffer, int32_t __length, int32_t __flags = 0);

        ///
        /// @breif: Sends the contents of the given __buffer through
        ///         the socket to the given address.
        ///
        ///         Returns the number of bytes sent, which may be
        ///         less than the number of bytes specified.
        ///
        virtual int32_t send_to(const void* __buffer, int32_t __length, const socket_address& __address, int32_t __flags = 0);

        ///
        /// @breif: Receives data from the socket and stores it
        ///         in __buffer. Up to __length bytes are received.
        ///         Stores the address of the sender in address.
        ///
        ///         Returns the number of bytes received.
        ///
        virtual int32_t receive_from(void* __buffer, int32_t __length, socket_address& __address, int32_t __flags = 0);

        ///
        /// @breif: Sends one byte of urgent data through the socket.
        ///
        ///         The data is sent with the MSG_OOB flag.
        ///
        ///         The preferred way for a socket to receive urgent data
        ///         is by enabling the SO_OOBINLINE __option.
        ///
        virtual void send_urgent(unsigned char data);

        ///
        /// @breif: Returns the number of bytes available that can be read
        ///         without causing the socket to block.
        ///
        virtual int32_t available();

        ///
        /// @breif: Determines the status of the socket, using a 
        ///         call to select().
        /// 
        ///         The mode argument is constructed by combining the values
        ///         of the SelectMode enumeration.
        ///
        ///         Returns true if the next operation corresponding to
        ///         mode will not block, false otherwise.
        ///
        virtual bool poll(const timespan& __timeout, int32_t __mode);

        ///
        /// @breif: Sets the size of the send __buffer.
        ///
        virtual void set_send_buffer_size(int32_t size);

        ///
        /// @breif: Returns the size of the send __buffer.
        ///
        virtual int32_t get_send_buffer_size();

        ///
        /// @breif: Sets the size of the receive __buffer.
        ///
        virtual void set_receive_buffer_size(int32_t size);

        ///
        /// @breif: Returns the size of the receive __buffer.
        ///
        virtual int32_t get_receive_buffer_size();

        ///
        /// @breif: Sets the send __timeout for the socket.
        ///
        virtual void set_send_timeout(const timespan& __timeout);

        ///
        /// @breif: Returns the send __timeout for the socket.
        ///
        virtual timespan get_send_timeout();

        ///
        /// @breif: Sets the send __timeout for the socket.
        ///
        ///         On systems that do not support SO_RCVTIMEO, a
        ///         workaround using poll() is provided.
        ///
        virtual void set_receive_timeout(const timespan& __timeout);

        ///
        /// @breif: Returns the receive __timeout for the socket.
        ///
        virtual timespan get_receive_timeout();

        ///
        /// @breif: Returns the IP address and port number of the socket.
        ///
        virtual socket_address address();

        ///
        /// @breif: Returns the IP address and port number of the peer socket.
        ///
        virtual socket_address peer_address();

        ///
        /// @breif: Sets the socket __option specified by __level and __option
        ///         to the given integer __valuee.
        ///
        void set_option(int32_t __level, int32_t __option, int32_t __valuee);

        ///
        /// @breif: Sets the socket __option specified by __level and __option
        ///         to the given integer __valuee.
        ///
        void set_option(int32_t __level, int32_t __option, unsigned __valuee);

        ///
        /// @breif: Sets the socket __option specified by __level and __option
        ///         to the given integer __valuee.
        ///
        void set_option(int32_t __level, int32_t __option, unsigned char __valuee);

        ///
        /// @breif: Sets the socket __option specified by __level and __option
        ///         to the given time __valuee.
        ///
        void set_option(int32_t __level, int32_t __option, const timespan& __valuee);

        ///
        /// @breif: Sets the socket __option specified by __level and __option
        ///         to the given time __valuee.
        ///
        void set_option(int32_t __level, int32_t __option, const ip_address& __valuee);

        ///
        /// @breif: Sets the socket __option specified by __level and __option
        ///         to the given time __valuee.
        ///
        virtual void set_raw_option(int32_t __level, int32_t __option, const void* __valuee, socklen_t __length);

        ///
        /// @breif: Returns the __valuee of the socket __option specified by __level and __option.
        ///
        void get_option(int32_t __level, int32_t __option, int32_t& __valuee);

        ///
        /// @breif: Returns the __valuee of the socket __option specified by __level and __option.
        ///
        void get_option(int32_t __level, int32_t __option, unsigned& __valuee);

        ///
        /// @breif: Returns the __valuee of the socket __option specified by __level and __option.
        ///
        void get_option(int32_t __level, int32_t __option, unsigned char& __valuee);

        ///
        /// @breif: Returns the __valuee of the socket __option specified by __level and __option.
        ///
        void get_option(int32_t __level, int32_t __option, timespan& __valuee);

        ///
        /// @breif: Returns the __valuee of the socket __option specified by __level and __option.
        ///
        void get_option(int32_t __level, int32_t __option, ip_address& __valuee);

        ///
        /// @breif: Returns the __valuee of the socket __option specified by __level and __option.  
        ///
        virtual void get_raw_option(int32_t __level, int32_t __option, void* __valuee, socklen_t& __length);

        ///
        /// @breif: Sets the __valuee of the SO_LINGER socket __option.
        ///
        void set_linger(bool __on, int32_t __seconds);

        ///
        /// @breif: Returns the __valuee of the SO_LINGER socket __option.
        ///
        void get_linger(bool& __on, int32_t& __seconds);

        ///
        /// @breif: Sets the __valuee of the TCP_NODELAY socket __option.
        ///
        void set_no_delay(bool __flag);

        ///
        /// @breif: Returns the __valuee of the TCP_NODELAY socket __option.
        ///
        bool get_no_delay();

        ///
        /// @breif: Sets the __valuee of the SO_KEEPALIVE socket __option.
        ///
        void set_keep_alive(bool __flag);

        ///
        /// @breif: Returns the __valuee of the SO_KEEPALIVE socket __option.
        ///
        bool get_keep_alive();

        ///
        /// @breif: Sets the __valuee of the SO_REUSEADDR socket __option.
        ///
        void set_reuse_address(bool __flag);

        ///
        /// @breif: Returns the __valuee of the SO_REUSEADDR socket __option.
        ///
        bool get_reuse_address();

        ///
        /// @breif: Sets the __valuee of the SO_REUSEPORT socket __option.
        ///         Does nothing if the socket implementation does not support SO_REUSEPORT.
        ///
        void set_reuse_port(bool __flag);

        ///
        /// @breif: Returns the __valuee of the SO_REUSEPORT socket __option.
        ///
        ///         Returns false if the socket implementation does not support SO_REUSEPORT.
        ///
        bool get_reuse_port();

        ///
        /// @breif: Sets the __valuee of the SO_OOBINLINE socket __option.
        ///
        void set_oob_inline(bool __flag);

        ///
        /// @breif: Returns the __valuee of the SO_OOBINLINE socket __option.
        ///
        bool get_oob_inline();

        ///
        /// @breif: Sets the __valuee of the SO_BROADCAST socket __option.
        ///
        void set_broadcast(bool __flag);

        ///
        /// @breif: Returns the __valuee of the SO_BROADCAST socket __option.
        ///
        bool get_broadcast();

        ///
        /// @breif: Sets the socket in blocking mode if flag is true, disables blocking mode if flag is false.
        ///
        virtual void set_blocking(bool __flag);

        ///
        /// @breif: Returns the blocking mode of the socket.
        ///         This method will only work if the blocking modes of 
        ///         the socket are changed via the setBlocking method!
        ///
        virtual bool get_blocking() const;

        ///
        /// @breif: Returns true iff the socket's connection is secure (using SSL or TLS).
        ///
        virtual bool secure() const;

        ///
        /// @breif: Returns the __valuee of the SO_ERROR socket __option.
        ///
        int32_t socket_error();

        ///
        /// @breif: Returns the socket descriptor for the underlying native socket.
        ///
        socket_t sockfd() const;

        ///
        /// @breif: A wrapper for the ioctl system call.
        ///
        void ioctl(ioctl_request_t __request, int32_t& __arg);

        ///
        /// @breif: A wrapper for the ioctl system call.
        ///
        void ioctl(ioctl_request_t __request, void* __arg);

        ///
        /// @breif: Returns true iff the underlying socket is initialized.
        ///
        bool initialized() const;

    protected:
        ///
        /// @breif: Creates a socket_impl.
        ///
        socket_impl();

        ///
        /// @breif: Creates a socket_impl using the given native socket.
        ///
        socket_impl(socket_t __sockfd);

        ///
        /// @breif: Destroys the socket_impl.
        ///         Closes the socket if it is still open.
        ///
        virtual ~socket_impl();

        ///
        /// @breif: Creates the underlying native socket.
        ///
        ///         Subclasses must implement this method so that it calls initSocket() with the
        ///         appropriate arguments.
        ///
        ///         The default implementation creates a stream socket.
        ///
        virtual void init(int32_t __af);

        ///
        /// @breif: Creates the underlying native socket.
        ///
        ///         The first argument, af, specifies the address family used by the socket, 
        ///         which should be either AF_INET or AF_INET6.
        ///
        ///         The second argument, type, specifies the type of the socket, which can be one of 
        ///         SOCK_STREAM, SOCK_DGRAM or SOCK_RAW.
        ///
        ///         The third argument, proto, is normally set to 0, except for raw sockets.
        ///
        void init_socket(int32_t __af, int32_t __type, int32_t __proto = 0);

        ///
        /// @breif: Allows subclasses to set the socket manually, iff no valid socket is set yet.
        ///
        void reset(socket_t __fd = ufc_invalid_socket);

        ///
        /// @breif: Returns the last error code.
        ///
        static int32_t last_error();

        ///
        /// @breif: Throws an appropriate exception for the last error.
        ///
        static void error();

        ///
        /// @breif: Throws an appropriate exception for the last error.
        ///
        static void error(const string& __arg);

        ///
        /// @breif: Throws an appropriate exception for the given error code.
        ///
        static void error(int32_t __code);

        ///
        /// Throws an appropriate exception for the given error code.
        ///
        static void error(int32_t __code, const string& __arg);
    
    private:        
        socket_t _sockfd;
#if defined(ufc_broken_timeouts)
        timespan _recv_timeout;
        timespan _send_timeout;
#endif
        bool     _blocking;
        detail::network_initialize __initialize;
    };

}//namespace ufc

#endif//NETWORK_SOCKET_IMPL_HPP
