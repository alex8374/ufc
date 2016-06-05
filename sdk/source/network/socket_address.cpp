/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : network/socket_address.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-04
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/network/socket_address.hpp"
#include "ufc/network/host_entry.hpp"
#include "ufc/network/dns.hpp"
#include "ufc/system/ref_counted_object.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/string/string_util.hpp"
#include <cstring>

namespace ufc {

    struct aflt
    {
    	bool operator () (const ip_address& __a1, const ip_address& __a2)
    	{
    		return __a1.af() < __a2.af();
    	}
    };

    //
    // socket_address::private_t
    //
    class socket_address::private_t: public ref_counted_object
    {
    public:
    	virtual ip_address host() const = 0;
    	virtual uint16_t port() const = 0;
    	virtual socklen_t length() const = 0;
    	virtual const struct sockaddr* addr() const = 0;
    	virtual int af() const = 0;
    	
    protected:
    	private_t()
    	{
    	}
    	
    	virtual ~private_t()
    	{
    	}
    	
    private:
        detail::network_initialize _initialize;
    };

    class socket_address::private4_t: public socket_address::private_t
    {
    public:
    	private4_t()
    	{
    		std::memset(&_addr, 0, sizeof(_addr));
    		_addr.sin_family = AF_INET;
    		ufc_set_sin_len(&_addr);
    	}
    	
    	private4_t(const struct sockaddr_in* __addr)
    	{
    		std::memcpy(&_addr, __addr, sizeof(_addr));
    	}
    	
    	private4_t(const void* __addr, uint16_t __port)
    	{
    		std::memset(&_addr, 0, sizeof(_addr));
    		_addr.sin_family = AF_INET;
    		std::memcpy(&_addr.sin_addr, __addr, sizeof(_addr.sin_addr));
    		_addr.sin_port = __port;
    	}

    	ip_address host() const
    	{
    		return ip_address(&_addr.sin_addr, sizeof(_addr.sin_addr));
    	}
    	
    	uint16_t port() const
    	{
    		return _addr.sin_port;
    	}

    	socklen_t length() const
    	{
    		return sizeof(_addr);
    	}
    	
    	const struct sockaddr* addr() const
    	{
    		return reinterpret_cast<const struct sockaddr*>(&_addr);
    	}
    	
    	int af() const
    	{
    		return _addr.sin_family;
    	}

    private:
    	struct sockaddr_in _addr;
    };

#if defined(ufc_have_ipv6)

    class socket_address::private6_t: public socket_address::private_t
    {
    public:
    	private6_t(const struct sockaddr_in6* __addr)
    	{
    		std::memcpy(&_addr, __addr, sizeof(_addr));
    	}
    	
    	private6_t(const void* __addr, uint16_t __port)
    	{
    		std::memset(&_addr, 0, sizeof(_addr));
    		_addr.sin6_family = AF_INET6;
    		ufc_set_sin6_len(&_addr);
    		std::memcpy(&_addr.sin6_addr, __addr, sizeof(_addr.sin6_addr));
    		_addr.sin6_port = __port;
    	}

    	private6_t(const void* __addr, uint16_t __port, uint32_t scope)
    	{
    		std::memset(&_addr, 0, sizeof(_addr));
    		_addr.sin6_family = AF_INET6;
    		ufc_set_sin6_len(&_addr);
    		std::memcpy(&_addr.sin6_addr, __addr, sizeof(_addr.sin6_addr));
    		_addr.sin6_port = __port;
    		_addr.sin6_scope_id = scope;
    	}

    	ip_address host() const
    	{
    		return ip_address(&_addr.sin6_addr, sizeof(_addr.sin6_addr), _addr.sin6_scope_id);
    	}
    	
    	uint16_t port() const
    	{
    		return _addr.sin6_port;
    	}

    	socklen_t length() const
    	{
    		return sizeof(_addr);
    	}
    	
    	const struct sockaddr* addr() const
    	{
    		return reinterpret_cast<const struct sockaddr*>(&_addr);
    	}

    	int af() const
    	{
    		return _addr.sin6_family;
    	}

    private:
    	struct sockaddr_in6 _addr;
    };

#endif // ufc_have_ipv6

    //
    // socket_address
    //
    socket_address::socket_address()
    {
    	_impl = new private4_t;
    }

    	
    socket_address::socket_address(const ip_address& __addr, uint16_t __port)
    {
    	init(__addr, __port);	
    }

    	
    socket_address::socket_address(const string& __addr, uint16_t __port)
    {
    	init(__addr, __port);
    }


    socket_address::socket_address(const string& __addr, const string& __port)
    {
    	init(__addr, resolve_service(__port));
    }


    socket_address::socket_address(const string& __host_and_port)
    {
    	ufc_assert (!__host_and_port.empty());
    	
    	string __host;
    	string __port;
    	string::const_iterator it  = __host_and_port.begin();
    	string::const_iterator end = __host_and_port.end();
    	if (*it == '[')
    	{
    		++it;
    		while (it != end && *it != ']') __host += *it++;
    		if (it == end) 
                throw invalid_argument_error("Malformed IPv6 address");
    		++it;
    	}
    	else
    	{
    		while (it != end && *it != ':') __host += *it++;
    	}
    	if (it != end && *it == ':')
    	{
    		++it;
    		while (it != end) __port += *it++;
    	}
    	else 
            throw invalid_argument_error("Missing port number");
    	init(__host, resolve_service(__port));
    }

    socket_address::socket_address(const socket_address& __addr)
    {
    	_impl = __addr._impl;
    	_impl->duplicate();
    }

    socket_address::socket_address(const struct sockaddr* __addr, socklen_t length)
    {
    	if (length == sizeof(struct sockaddr_in))
    		_impl = new private4_t(reinterpret_cast<const struct sockaddr_in*>(__addr));
#if defined(ufc_have_ipv6)
    	else if (length == sizeof(struct sockaddr_in6))
    		_impl = new private6_t(reinterpret_cast<const struct sockaddr_in6*>(__addr));
#endif
    	else
            throw invalid_argument_error("Invalid address length passed to socket_address()");
    }

    socket_address::~socket_address()
    {
    	_impl->release();
    }
    	
    socket_address& socket_address::operator = (const socket_address& __addr)
    {
    	if (&__addr != this)
    	{
    		_impl->release();
    		_impl = __addr._impl;
    		_impl->duplicate();
    	}
    	return *this;
    }

    void socket_address::swap(socket_address& __addr)
    {
    	std::swap(_impl, __addr._impl);
    }
    	
    ip_address socket_address::host() const
    {
    	return _impl->host();
    }
    	
    uint16_t socket_address::port() const
    {
    	return ntohs(_impl->port());
    }
    	
    socklen_t socket_address::length() const
    {
    	return _impl->length();
    }
    	
    const struct sockaddr* socket_address::addr() const
    {
    	return _impl->addr();
    }

    int socket_address::af() const
    {
    	return _impl->af();
    }

    string socket_address::to_string() const
    {
    	string __result;
    	if (host().family() == ip_address::ipv6)
    		__result.append("[");
    	__result.append(host().to_string());
    	if (host().family() == ip_address::ipv6)
    		__result.append("]");
    	__result.append(":");
        __result += string_util::format(port());
    	return __result;
    }

    void socket_address::init(const ip_address& __host, uint16_t __port)
    {
    	if (__host.family() == ip_address::ipv4)
    		_impl = new private4_t(__host.addr(), htons(__port));
#if defined(ufc_have_ipv6)
    	else if (__host.family() == ip_address::ipv6)
    		_impl = new private6_t(__host.addr(), htons(__port), __host.scope());
#endif
    	else 
            throw not_implemented_error("unsupported IP address family");
    }

    void socket_address::init(const string& __host, uint16_t __port)
    {
    	ip_address __ip;
    	if (ip_address::try_parse(__host, __ip))
    	{
    		init(__ip, __port);
    	}
    	else
    	{
    		host_entry __he = dns::host_by_name(__host);
    		host_entry::address_list __addresses = __he.addresses();
    		if (__addresses.size() > 0)
    		{
#if defined(ufc_have_ipv6)
    			// if we get both IPv4 and IPv6 addresses, prefer IPv4
    			std::sort(__addresses.begin(), __addresses.end(), aflt());
#endif
    			init(__addresses[0], __port);
    		}
    		else 
                throw host_not_found_error("No address found for __host", __host);
    	}
    }

    uint16_t socket_address::resolve_service(const string& __service)
    {
        if (__service.is_digit())
        {
            uint32_t __port = __service.as_uint32();
            if (__port <= 0xFFFF)
            {
                return __port;
            }
        }
        
#if defined(ufc_vxworks)
		throw service_not_found_error(__service);
#else
		struct servent* __se = getservbyname(__service.c_str(), NULL);
		if (__se)
			return ntohs(__se->s_port);
		else
			throw service_not_found_error(__service);
#endif
    }

}//namespace ufc
