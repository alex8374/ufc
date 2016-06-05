/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : network/ip_address.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-04
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/network/ip_address.hpp"
#include "ufc/system/ref_counted_object.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/string/string_util.hpp"
#include <cstring>

namespace ufc {

    class ip_address::private_t: public ref_counted_object
    {
    public:
    	virtual string to_string() const = 0;
    	virtual socklen_t length() const = 0;
    	virtual const void* addr() const = 0;
    	virtual ip_address::family_t family() const = 0;
    	virtual int32_t af() const = 0;
    	virtual uint32_t scope() const = 0;
    	virtual bool is_wildcard() const	= 0;
    	virtual bool is_broadcast() const = 0;
    	virtual bool is_loopback() const = 0;
    	virtual bool is_multicast() const = 0;
    	virtual bool is_link_local() const = 0;
    	virtual bool is_site_local() const = 0;
    	virtual bool is_ipv4_mapped() const = 0;
    	virtual bool is_ipv4_compatible() const = 0;
    	virtual bool is_well_known_mc() const = 0;
    	virtual bool is_node_local_mc() const = 0;
    	virtual bool is_link_local_mc() const = 0;
    	virtual bool is_site_local_mc() const = 0;
    	virtual bool is_org_local_mc() const = 0;
    	virtual bool is_global_mc() const = 0;
    	virtual void mask(const private_t* __mask, const private_t* __set) = 0;
    	virtual private_t* clone() const = 0;

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
    
    class ip_address::private4_t: public ip_address::private_t
    {
    public:
    	private4_t()
    	{
    		std::memset(&_addr, 0, sizeof(_addr));
    	}
    	
    	private4_t(const void* __addr)
    	{
    		std::memcpy(&_addr, __addr, sizeof(_addr));
    	}
    	
    	string to_string() const
    	{
    		const uint8_t* __bytes = reinterpret_cast<const uint8_t*>(&_addr);
    		string __result;
    		__result.reserve(16);
            __result += string_util::format(__bytes[0]);
            __result += ".";
            __result += string_util::format(__bytes[1]);
            __result += ".";
            __result += string_util::format(__bytes[2]);
            __result += ".";
            __result += string_util::format(__bytes[3]);
    		return __result;
    	}

    	socklen_t length() const
    	{
    		return sizeof(_addr);
    	}
    	
    	const void* addr() const
    	{
    		return &_addr;
    	}
    	
    	ip_address::family_t family() const
    	{
    		return ip_address::ipv4;
    	}
    	
    	int32_t af() const
    	{
    		return AF_INET;
    	}
    	
    	uint32_t scope() const
    	{
    		return 0;
    	}
    	
    	bool is_wildcard() const
    	{
    		return _addr.s_addr == INADDR_ANY;
    	}
    	
    	bool is_broadcast() const
    	{
    		return _addr.s_addr == INADDR_NONE;
    	}
    	
    	bool is_loopback() const
    	{
    		return (ntohl(_addr.s_addr) & 0xFF000000) == 0x7F000000; // 127.0.0.1 to 127.255.255.255
    	}
    	
    	bool is_multicast() const
    	{
    		return (ntohl(_addr.s_addr) & 0xF0000000) == 0xE0000000; // 224.0.0.0/24 to 239.0.0.0/24
    	}
    		
    	bool is_link_local() const
    	{
    		return (ntohl(_addr.s_addr) & 0xFFFF0000) == 0xA9FE0000; // 169.254.0.0/16
    	}
    	
    	bool is_site_local() const
    	{
    		uint32_t __addr = ntohl(_addr.s_addr);
    		return (__addr & 0xFF000000) == 0x0A000000 ||        // 10.0.0.0/24
    		       (__addr & 0xFFFF0000) == 0xC0A80000 ||        // 192.68.0.0/16
    		       (__addr >= 0xAC100000 && __addr <= 0xAC1FFFFF); // 172.16.0.0 to 172.31.255.255
    	}
    	
    	bool is_ipv4_compatible() const
    	{
    		return true;
    	}

    	bool is_ipv4_mapped() const
    	{
    		return true;
    	}

    	bool is_well_known_mc() const
    	{
    		return (ntohl(_addr.s_addr) & 0xFFFFFF00) == 0xE0000000; // 224.0.0.0/8
    	}
    	
    	bool is_node_local_mc() const
    	{
    		return false;
    	}
    	
    	bool is_link_local_mc() const
    	{
    		return (ntohl(_addr.s_addr) & 0xFF000000) == 0xE0000000; // 244.0.0.0/24
    	}
    	
    	bool is_site_local_mc() const
    	{
    		return (ntohl(_addr.s_addr) & 0xFFFF0000) == 0xEFFF0000; // 239.255.0.0/16
    	}
    	
    	bool is_org_local_mc() const
    	{
    		return (ntohl(_addr.s_addr) & 0xFFFF0000) == 0xEFC00000; // 239.192.0.0/16
    	}
    	
    	bool is_global_mc() const
    	{
    		uint32_t __addr = ntohl(_addr.s_addr);
    		return __addr >= 0xE0000100 && __addr <= 0xEE000000; // 224.0.1.0 to 238.255.255.255
    	}

    	static private4_t* parse(const string& __addr)
    	{
    		if (__addr.empty()) return 0;		
#if defined(ufc_os_family_windows) 
    		struct in_addr __ia;
    		__ia.s_addr = inet_addr(__addr.c_str());
    		if (__ia.s_addr == INADDR_NONE && __addr != "255.255.255.255")
    			return 0;
    		else
    			return new private4_t(&__ia);
#else
#if __GNUC__ < 3 || defined(ufc_vxworks)
    		struct in_addr __ia;
    		__ia.s_addr = inet_addr(const_cast<char*>(__addr.c_str()));
    		if (__ia.s_addr == INADDR_NONE && __addr != "255.255.255.255")
    			return 0;
    		else
    			return new private4_t(&__ia);
#else
    		struct in_addr __ia;
    		if (inet_aton(__addr.c_str(), &__ia))
    			return new private4_t(&__ia);
    		else
    			return 0;
#endif
#endif
    	}
    	
    	void mask(const ip_address::private_t* __mask, const ip_address::private_t* __set)
    	{
    		ufc_assert (__mask->af() == AF_INET && __set->af() == AF_INET);
    		
    		_addr.s_addr &= static_cast<const private4_t*>(__mask)->_addr.s_addr;
    		_addr.s_addr |= static_cast<const private4_t*>(__set)->_addr.s_addr & ~static_cast<const private4_t*>(__mask)->_addr.s_addr;
    	}
    	
    	ip_address::private_t* clone() const
    	{
    		return new private4_t(&_addr);
    	}
    		
    private:
    	struct in_addr _addr;	
    };


#if defined(ufc_have_ipv6)

    class ip_address::private6_t: public ip_address::private_t
    {
    public:
    	private6_t()
            : _scope(0)
    	{
    		std::memset(&_addr, 0, sizeof(_addr));
    	}

    	private6_t(const void* __addr)
            : _scope(0)
    	{
    		std::memcpy(&_addr, __addr, sizeof(_addr));
    	}

    	private6_t(const void* __addr, uint32_t scope)
            : _scope(0)
    	{
    		std::memcpy(&_addr, __addr, sizeof(_addr));
    	}

    	string to_string() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		if (is_ipv4_compatible() || is_ipv4_mapped())
    		{
    			string __result;
    			__result.reserve(24);
    			if (__words[5] == 0)
    				__result.append("::");
    			else
    				__result.append("::FFFF:");
    			const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&_addr);
                __result += string_util::format(bytes[12]);
                __result += ".";
                __result += string_util::format(bytes[13]);
                __result += ".";
                __result += string_util::format(bytes[14]);
                __result += ".";
                __result += string_util::format(bytes[15]);
    			return __result;
    		}
    		else
    		{
    			string __result;
    			__result.reserve(64);
    			bool __zero_sequence = false;
    			int32_t __i = 0;
    			while (__i < 8)
    			{
    				if (!__zero_sequence && __words[__i] == 0)
    				{
    					int32_t __zi = __i;
    					while (__zi < 8 && __words[__zi] == 0) 
                        {
                            ++__zi;
                        }               
    					if (__zi > __i + 1)
    					{
    						__i = __zi;
    						__result.append(":");
    						__zero_sequence = true;
    					}
    				}
    				if (__i > 0) 
                    {            
                        __result.append(":");
    				}
                    if (__i < 8)
                    {
                        __result += string_util::format_hex(ntohs(__words[__i++]));
                    }
    			}
    			if (_scope > 0)
    			{
    				__result.append("%");
#if defined(ufc_os_family_windows)
                    __result += string_util::format(_scope);
#else
    				char __buffer[IFNAMSIZ];
    				if (if_indextoname(_scope, __buffer))
    				{
    					__result.append(__buffer);
    				}
    				else
    				{
                        __result += string_util::format(_scope);
    				}
#endif
    			}
    			return __result;
    		}
    	}
    	
    	socklen_t length() const
    	{
    		return sizeof(_addr);
    	}

    	const void* addr() const
    	{
    		return &_addr;
    	}

    	ip_address::family_t family() const
    	{
    		return ip_address::ipv6;
    	}

    	int32_t af() const
    	{
    		return AF_INET6;
    	}
    	
    	uint32_t scope() const
    	{
    		return _scope;
    	}

    	bool is_wildcard() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return __words[0] == 0 && 
                   __words[1] == 0 && 
                   __words[2] == 0 && 
                   __words[3] == 0 && 
    		       __words[4] == 0 && 
    		       __words[5] == 0 && 
    		       __words[6] == 0 && 
    		       __words[7] == 0;
    	}
    	
    	bool is_broadcast() const
    	{
    		return false;
    	}
    	
    	bool is_loopback() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return __words[0] == 0 && 
                   __words[1] == 0 && 
                   __words[2] == 0 && 
                   __words[3] == 0 && 
    		       __words[4] == 0 && 
    		       __words[5] == 0 && 
    		       __words[6] == 0 && 
    		       ntohs(__words[7]) == 0x0001;
    	}
    	
    	bool is_multicast() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return (ntohs(__words[0]) & 0xFFE0) == 0xFF00;
    	}
    		
    	bool is_link_local() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return (ntohs(__words[0]) & 0xFFE0) == 0xFE80;
    	}
    	
    	bool is_site_local() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return (ntohs(__words[0]) & 0xFFE0) == 0xFEC0;
    	}
    	
    	bool is_ipv4_compatible() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return __words[0] == 0 && 
                   __words[1] == 0 && 
                   __words[2] == 0 && 
                   __words[3] == 0 && 
                   __words[4] == 0 && 
                   __words[5] == 0;
    	}

    	bool is_ipv4_mapped() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return __words[0] == 0 && 
                   __words[1] == 0 && 
                   __words[2] == 0 && 
                   __words[3] == 0 && 
                   __words[4] == 0 && 
                   ntohs(__words[5]) == 0xFFFF;
    	}

    	bool is_well_known_mc() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return (ntohs(__words[0]) & 0xFFF0) == 0xFF00;
    	}
    	
    	bool is_node_local_mc() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return (ntohs(__words[0]) & 0xFFEF) == 0xFF01;
    	}
    	
    	bool is_link_local_mc() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return (ntohs(__words[0]) & 0xFFEF) == 0xFF02;
    	}
    	
    	bool is_site_local_mc() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return (ntohs(__words[0]) & 0xFFEF) == 0xFF05;
    	}
    	
    	bool is_org_local_mc() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return (ntohs(__words[0]) & 0xFFEF) == 0xFF08;
    	}
    	
    	bool is_global_mc() const
    	{
    		const uint16_t* __words = reinterpret_cast<const uint16_t*>(&_addr);
    		return (ntohs(__words[0]) & 0xFFEF) == 0xFF0F;
    	}

    	static private6_t* parse(const string& __addr)
    	{
    		if (__addr.empty()) return 0;
#if defined(ufc_os_family_windows)
    		struct addrinfo* __ai;
    		struct addrinfo __hints;
    		std::memset(&__hints, 0, sizeof(__hints));
    		__hints.ai_flags = AI_NUMERICHOST;
    		int32_t __rc = getaddrinfo(__addr.c_str(), NULL, &__hints, &__ai);
    		if (__rc == 0)
    		{
    			private6_t* __result = new private6_t(&reinterpret_cast<struct sockaddr_in6*>(__ai->ai_addr)->sin6_addr, static_cast<int32_t>(reinterpret_cast<struct sockaddr_in6*>(__ai->ai_addr)->sin6_scope_id));
    			freeaddrinfo(__ai);
    			return __result;
    		}
    		else 
                return 0;
#else
    		struct in6_addr __ia;
    		string::size_type __pos = __addr.find('%');
    		if (string::npos != __pos)
    		{
    			string::size_type __startpos = ('[' == __addr[0]) ? 1 : 0;
    			string __unscopedAddr(__addr, __startpos, __pos - __startpos);
    			string __scope(__addr, __pos + 1, __addr.size() - __startpos - __pos);
    			uint32_t __scopeId(0);
    			if (!(__scopeId = if_nametoindex(__scope.c_str())))
    				return 0;
    			if (inet_pton(AF_INET6, __unscopedAddr.c_str(), &__ia) == 1)
    				return new private6_t(&__ia, __scopeId);
    			else
    				return 0;
    		}
    		else
    		{
    			if (inet_pton(AF_INET6, __addr.c_str(), &__ia) == 1)
    				return new private6_t(&__ia);
    			else
    				return 0;
    		}
#endif
    	}
    	
    	void mask(const ip_address::private_t* __mask, const ip_address::private_t* __set)
    	{
    		throw not_implemented_error("mask() is only supported for ipv4 addresses");
    	}

    	ip_address::private_t* clone() const
    	{
    		return new private6_t(&_addr, _scope);
    	}

    private:
    	struct in6_addr _addr;	
    	uint32_t        _scope;
    };

#endif // UFC_HAS_IPv6

    const int32_t ip_address::max_address_length = 
#if defined(ufc_have_ipv6)
			sizeof(struct in6_addr);
#else
			sizeof(struct in_addr);
#endif

    ip_address::ip_address()
        : _impl(new private4_t)
    {
    }

    ip_address::ip_address(const ip_address& __addr)
        : _impl(__addr._impl)
    {
    	_impl->duplicate();
    }

    ip_address::ip_address(family_t __family)
        : _impl(0)
    {
    	if (__family == ipv4)
    		_impl = new private4_t();
#if defined(ufc_have_ipv6)
    	else if (__family == ipv6)
    		_impl = new private6_t();
#endif
    	else
    		throw invalid_argument_error("Invalid or unsupported address family passed to ip_address()");
    }

    ip_address::ip_address(const string& __addr)
        : _impl(0)
    {
    	_impl = private4_t::parse(__addr);
#if defined(ufc_have_ipv6)
    	if (!_impl)
    		_impl = private6_t::parse(__addr);
#endif
    	if (!_impl) 
            throw invalid_address_error(__addr);
    }

    ip_address::ip_address(const string& __addr, family_t __family)
        : _impl(0)
    {
    	if (__family == ipv4)
    		_impl = private4_t::parse(__addr);
#if defined(ufc_have_ipv6)
    	else if (__family == ipv6)
    		_impl = private6_t::parse(__addr);
#endif
    	else 
            throw invalid_argument_error("Invalid or unsupported address family passed to ip_address()");
    	if (!_impl) 
            throw invalid_address_error(__addr);
    }

    ip_address::ip_address(const void* __addr, socklen_t __length)
    {
    	if (__length == sizeof(struct in_addr))
    		_impl = new private4_t(__addr);
#if defined(ufc_have_ipv6)
    	else if (__length == sizeof(struct in6_addr))
    		_impl = new private6_t(__addr);
#endif
    	else 
            throw invalid_argument_error("Invalid address length passed to ip_address()");
    }

    ip_address::ip_address(const void* __addr, socklen_t __length, uint32_t __scope)
    {
    	if (__length == sizeof(struct in_addr))
    		_impl = new private4_t(__addr);
#if defined(ufc_have_ipv6)
    	else if (__length == sizeof(struct in6_addr))
    		_impl = new private6_t(__addr, __scope);
#endif
    	else 
            throw invalid_argument_error("Invalid address length passed to ip_address()");
    }

    ip_address::~ip_address()
    {
    	_impl->release();
    }

    ip_address& ip_address::operator = (const ip_address& __addr)
    {
    	if (&__addr != this)
    	{
    		_impl->release();
    		_impl = __addr._impl;
    		_impl->duplicate();
    	}
    	return *this;
    }

    void ip_address::swap(ip_address& address)
    {
    	std::swap(_impl, address._impl);
    }

    ip_address::family_t ip_address::family() const
    {
    	return _impl->family();
    }

    uint32_t ip_address::scope() const
    {
    	return _impl->scope();
    }

    string ip_address::to_string() const
    {
    	return _impl->to_string();
    }


    bool ip_address::is_wildcard() const
    {
    	return _impl->is_wildcard();
    }
    	
    bool ip_address::is_broadcast() const
    {
    	return _impl->is_broadcast();
    }

    bool ip_address::is_loopback() const
    {
    	return _impl->is_loopback();
    }

    bool ip_address::is_multicast() const
    {
    	return _impl->is_multicast();
    }
    	
    bool ip_address::is_unicast() const
    {
    	return !is_wildcard() && !is_broadcast() && !is_multicast();
    }
    	
    bool ip_address::is_link_local() const
    {
    	return _impl->is_link_local();
    }

    bool ip_address::is_site_local() const
    {
    	return _impl->is_site_local();
    }

    bool ip_address::is_ipv4_compatible() const
    {
    	return _impl->is_ipv4_compatible();
    }

    bool ip_address::is_ipv4_mapped() const
    {
    	return _impl->is_ipv4_mapped();
    }

    bool ip_address::is_well_known_mc() const
    {
    	return _impl->is_well_known_mc();
    }

    bool ip_address::is_node_local_mc() const
    {
    	return _impl->is_node_local_mc();
    }

    bool ip_address::is_link_local_mc() const
    {
    	return _impl->is_link_local_mc();
    }

    bool ip_address::is_site_local_mc() const
    {
    	return _impl->is_site_local_mc();
    }

    bool ip_address::is_org_local_mc() const
    {
    	return _impl->is_org_local_mc();
    }

    bool ip_address::is_global_mc() const
    {
    	return _impl->is_global_mc();
    }

    bool ip_address::operator == (const ip_address& __addr) const
    {
    	socklen_t __l1 = length();
    	socklen_t __l2 = __addr.length();
    	if (__l1 == __l2)
    		return std::memcmp(addr(), __addr.addr(), __l1) == 0;
    	else
    		return false;
    }

    bool ip_address::operator != (const ip_address& __addr) const
    {
    	socklen_t __l1 = length();
    	socklen_t __l2 = __addr.length();
    	if (__l1 == __l2)
    		return std::memcmp(addr(), __addr.addr(), __l1) != 0;
    	else
    		return true;
    }

    bool ip_address::operator < (const ip_address& __addr) const
    {
    	socklen_t __l1 = length();
    	socklen_t __l2 = __addr.length();
    	if (__l1 == __l2)
    		return std::memcmp(addr(), __addr.addr(), __l1) < 0;
    	else
    		return __l1 < __l2;
    }

    bool ip_address::operator <= (const ip_address& __addr) const
    {
    	socklen_t __l1 = length();
    	socklen_t __l2 = __addr.length();
    	if (__l1 == __l2)
    		return std::memcmp(addr(), __addr.addr(), __l1) <= 0;
    	else
    		return __l1 < __l2;
    }

    bool ip_address::operator > (const ip_address& __addr) const
    {
    	socklen_t __l1 = length();
    	socklen_t __l2 = __addr.length();
    	if (__l1 == __l2)
    		return std::memcmp(addr(), __addr.addr(), __l1) > 0;
    	else
    		return __l1 > __l2;
    }

    bool ip_address::operator >= (const ip_address& __addr) const
    {
    	socklen_t __l1 = length();
    	socklen_t __l2 = __addr.length();
    	if (__l1 == __l2)
    		return std::memcmp(addr(), __addr.addr(), __l1) >= 0;
    	else
    		return __l1 > __l2;
    }

    socklen_t ip_address::length() const
    {
    	return _impl->length();
    }

    const void* ip_address::addr() const
    {
    	return _impl->addr();
    }

    int32_t ip_address::af() const
    {
    	return _impl->af();
    }

    void ip_address::init(private_t* __impl)
    {
    	_impl->release();
    	_impl = __impl;
    }

    ip_address ip_address::parse(const string& __addr)
    {
    	return ip_address(__addr);
    }

    bool ip_address::try_parse(const string& __addr, ip_address& __result)
    {
    	private_t* __impl   = private4_t::parse(__addr);
#if defined(ufc_have_ipv6)
    	if (!__impl) __impl = private6_t::parse(__addr);
#endif
    	if (__impl)
    	{
    		__result.init(__impl);
    		return true;
    	}
    	else 
            return false;
    }

    void ip_address::mask(const ip_address& __mask)
    {
    	private_t* __clone = _impl->clone();
    	_impl->release();
    	_impl = __clone;
    	ip_address __nulladdr;
    	_impl->mask(__mask._impl, __nulladdr._impl);
    }

    void ip_address::mask(const ip_address& __mask, const ip_address& __set)
    {
    	private_t* __clone = _impl->clone();
    	_impl->release();
    	_impl = __clone;
    	_impl->mask(__mask._impl, __set._impl);
    }

    ip_address ip_address::wildcard(family_t family)
    {
    	return ip_address(family);
    }

    ip_address ip_address::broadcast()
    {
    	struct in_addr __ia;
    	__ia.s_addr = INADDR_NONE;
    	return ip_address(&__ia, sizeof(__ia));
    }

}//namespace ufc