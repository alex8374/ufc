/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/network/host_entry.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-04
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_NETWORK_HOST_ENTRY_HPP
#define UFC_NETWORK_HOST_ENTRY_HPP

#include <ufc/network/socketdefs.hpp>
#include <ufc/network/ip_address.hpp>

namespace ufc {

    ///
    /// @breif: This class stores information about a host such as host name, 
    ///         alias names and a list of IP addresses.
    ///
    class ufc_api host_entry: virtual public object
    {
    public:
        typedef vector<string>         alias_list;
        typedef vector<ip_address>     address_list;
        
        ///
        /// @breif: Creates an empty host_entry.
        ///
        host_entry();

        ///
        /// @breif: Creates the host_entry from the data in a hostent structure.
        ///
        host_entry(struct hostent* __entry);

#if defined(ufc_have_ipv6) || defined(ufc_have_addrinfo)
        ///
        /// @breif: Creates the host_entry from the data in an addrinfo structure.
        ///
        host_entry(struct addrinfo* __info);
#endif

        ///
        /// @breif: Creates the host_entry by copying another one.
        ///
        host_entry(const host_entry& __entry);

        ///
        /// @breif: Destroys the host_entry.
        ///
        virtual ~host_entry();

        ///
        /// @breif: Assigns another host_entry.
        ///
        host_entry& operator = (const host_entry& __entry);

        ///
        /// @breif: Swaps the host_entry with another one.   
        ///
        void swap(host_entry& __entry);

        ///
        /// @breif: Returns the canonical host name.
        ///
        const string& name() const;

        ///
        /// @breif: Returns a vector containing alias names for the host name.
        ///
        const alias_list& aliases() const;

        ///
        /// @breif: Returns a vector containing the IPAddresses for the host.
        ///
        const address_list& addresses() const;

    private:
        string       _name;
        alias_list   _aliases;
        address_list _addresses;
    };

}//namespace ufc

#endif//UFC_NETWORK_HOST_ENTRY_HPP
