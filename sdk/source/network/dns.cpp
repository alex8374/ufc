/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : network/dns.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-04
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/network/dns.hpp"
#include "ufc/network/ip_address.hpp"
#include "ufc/network/socket_address.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/string/string_util.hpp"
#include <cstring>

namespace ufc {

    host_entry dns::host_by_name(const string& __hostname)
    {
        detail::network_initialize __initialize;
    	
#if defined(ufc_have_ipv6) || defined(ufc_have_addrinfo)
    	struct addrinfo* __ai;
    	struct addrinfo __hints;
    	std::memset(&__hints, 0, sizeof(__hints));
    	__hints.ai_flags = AI_CANONNAME | AI_ADDRCONFIG;
    	int32_t __rc = getaddrinfo(__hostname.c_str(), NULL, &__hints, &__ai); 
    	if (__rc == 0)
    	{
    		host_entry result(__ai);
    		freeaddrinfo(__ai);
    		return result;
    	}
    	else
    	{
    		aierror(__rc, __hostname);
    	}
#elif defined(ufc_vxworks)
    	int32_t __addr = hostGetByName(const_cast<char*>(__hostname.c_str()));
    	if (__addr != ERROR)
    	{
    		return host_entry(__hostname, ip_address(&__addr, sizeof(__addr)));
    	}
#else
    	struct hostent* __he = gethostbyname(__hostname.c_str());
    	if (__he)
    	{
    		return host_entry(__he);
    	}
#endif
    	error(last_error(), __hostname);      // will throw an appropriate exception
    	throw net_error(); // to silence compiler
    }


    host_entry dns::host_by_address(const ip_address& __address)
    {
        detail::network_initialize __initialize;

#if defined(ufc_have_ipv6) || defined(ufc_have_addrinfo)
    	socket_address __sa(__address, 0);
    	static char __fqname[1024];
    	int32_t __rc = getnameinfo(__sa.addr(), __sa.length(), __fqname, sizeof(__fqname), NULL, 0, NI_NAMEREQD); 
    	if (__rc == 0)
    	{
    		struct addrinfo* __ai;
    		struct addrinfo __hints;
    		std::memset(&__hints, 0, sizeof(__hints));
    		__hints.ai_flags = AI_CANONNAME | AI_ADDRCONFIG;
    		__rc = getaddrinfo(__fqname, NULL, &__hints, &__ai);
    		if (__rc == 0)
    		{
    			host_entry result(__ai);
    			freeaddrinfo(__ai);
    			return result;
    		}
    		else
    		{
    			aierror(__rc, __address.to_string());
    		}
    	}
    	else
    	{
    		aierror(__rc, __address.to_string());
    	}
#elif defined(ufc_vxworks)
    	char __name[MAXHOSTNAMELEN + 1];
    	if (hostGetByAddr(*reinterpret_cast<const int32_t*>(__address.addr()), __name) == OK)
    	{
    		return host_entry(string(__name), __address);
    	}
#else
    	struct hostent* __he = gethostbyaddr(reinterpret_cast<const char*>(__address.addr()), __address.length(), __address.af());
    	if (__he)
    	{
    		return host_entry(__he);
    	}
#endif
    	error(last_error(), __address.to_string());      // will throw an appropriate exception
    	throw net_error(); // to silence compiler
    }


    host_entry dns::resolve(const string& __address)
    {
        detail::network_initialize __initialize;

    	ip_address __ip;
    	if (ip_address::try_parse(__address, __ip))
    		return host_by_address(__ip);
    	else
    		return host_by_name(__address);
    }


    ip_address dns::resolve_one(const string& __address)
    {
        detail::network_initialize __initialize;

    	const host_entry& __entry = resolve(__address);
    	if (!__entry.addresses().empty())
    		return __entry.addresses()[0];
    	else
    		throw no_address_found_error(__address);
    }


    host_entry dns::this_host()
    {
    	return host_by_name(host_name());
    }


    void dns::flush_cache()
    {
    }

    string dns::host_name()
    {
        detail::network_initialize __initialize;

    	char __buffer[256];
    	int32_t __rc = gethostname(__buffer, sizeof(__buffer));
    	if (__rc == 0)
    		return string(__buffer);
    	else
    		throw net_error("Cannot get host name");
    }

    int32_t dns::last_error()
    {
#if defined(ufc_os_family_windows)
    	return GetLastError();
#elif defined(ufc_vxworks)
    	return errno;
#else
    	return h_errno;
#endif
    }

    void dns::error(int32_t __code, const string& __arg)
    {
    	switch (__code)
    	{
    	case ufc_esysnotready:
    		throw net_error("Net subsystem not ready");
    	case ufc_enotinit:
    		throw net_error("Net subsystem not initialized");
    	case ufc_host_not_found:
    		throw host_not_found_error(__arg);
    	case ufc_try_again:
    		throw dns_error("Temporary dns error while resolving", __arg);
    	case ufc_no_recovery:
    		throw dns_error("Non recoverable dns error while resolving", __arg);
    	case ufc_no_data:
    		throw no_address_found_error(__arg);
    	default:
    		throw io_error(string_util::format(__code));
    	}
    }

    void dns::aierror(int32_t __code, const string& __arg)
    {
#if defined(ufc_have_ipv6)
    	switch (__code)
    	{
    	case EAI_AGAIN:
    		throw dns_error("Temporary dns error while resolving", __arg);
    	case EAI_FAIL:
    		throw dns_error("Non recoverable dns error while resolving", __arg);
#if !defined(_WIN32) // EAI_NODATA and EAI_NONAME have the same value
    	case EAI_NODATA:
    		throw no_address_found_error(__arg);
#endif
    	case EAI_NONAME:
    		throw host_not_found_error(__arg);
#if defined(EAI_SYSTEM)
    	case EAI_SYSTEM:
    		error(last_error(), __arg);
    		break;
#endif
#if defined(ufc_os_family_windows)
    	case WSANO_DATA: // may happen on XP
    		throw host_not_found_error(__arg);
#endif
    	default:
    		throw dns_error("EAI", string_util::format(__code));
    	}
#endif // ufc_have_ipv6
    }

}//namespace ufc
