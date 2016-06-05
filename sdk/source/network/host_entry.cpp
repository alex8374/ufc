/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : network/host_entry.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-04
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/network/host_entry.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#include <algorithm>

namespace ufc {

    host_entry::host_entry()
    {
    }

    host_entry::host_entry(struct hostent* __entry)
    {
        ufc_check_ptr (__entry);

        _name = __entry->h_name;  
        char** alias = __entry->h_aliases;
        if (alias)
        {
            while (*alias)
            {
                _aliases.push_back(string(*alias));
                ++alias;
            }
        }
        char** address = __entry->h_addr_list;
        if (address)
        {
            while (*address)
            {
                _addresses.push_back(ip_address(*address, __entry->h_length));
                ++address;
            }
        }
    }

#if defined(ufc_have_ipv6) || defined(ufc_have_addrinfo)

    host_entry::host_entry(struct addrinfo* __ainfo)
    {
        ufc_check_ptr (__ainfo);
        
        for (struct addrinfo* __ai = __ainfo; __ai; __ai = __ai->ai_next)
        {
            if (__ai->ai_canonname)
            {
                _name.assign(__ai->ai_canonname);
            }
            if (__ai->ai_addrlen && __ai->ai_addr)
            {
                switch (__ai->ai_addr->sa_family)
                {
                case AF_INET:
                    _addresses.push_back(ip_address(&reinterpret_cast<struct sockaddr_in*>(__ai->ai_addr)->sin_addr, sizeof(in_addr)));
                    break;
#if defined(ufc_have_ipv6)
                case AF_INET6:
                    _addresses.push_back(ip_address(&reinterpret_cast<struct sockaddr_in6*>(__ai->ai_addr)->sin6_addr, sizeof(in6_addr), reinterpret_cast<struct sockaddr_in6*>(__ai->ai_addr)->sin6_scope_id));
                    break;
#endif
                }
            }
        }
    }

#endif // ufc_have_ipv6

#if defined(ufc_vxworks)

    host_entry::host_entry(const string& __name, const ip_address& __addr)
        : _name(__name)
    {
        _addresses.push_back(__addr);
    }

#endif // ufc_vxworks

    host_entry::host_entry(const host_entry& __entry):
        _name(__entry._name),
        _aliases(__entry._aliases),
        _addresses(__entry._addresses)
    {
    }

    host_entry& host_entry::operator = (const host_entry& __entry)
    {
        if (&__entry != this)
        {
            _name          = __entry._name;
            _aliases       = __entry._aliases;
            _addresses     = __entry._addresses;
        }
        return *this;
    }

    void host_entry::swap(host_entry& __entry)
    {
        std::swap(_name, __entry._name);
        std::swap(_aliases, __entry._aliases);
        std::swap(_addresses, __entry._addresses);
    }

    host_entry::~host_entry()
    {
    }

    const string& host_entry::name() const
    {
        return _name;
    }

    const host_entry::alias_list& host_entry::aliases() const
    {
        return _aliases;
    }

    const host_entry::address_list& host_entry::addresses() const
    {
        return _addresses;
    }

}//namespace ufc
