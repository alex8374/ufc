/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/network/dns.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-04
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_NETWORK_DNS_HPP
#define UFC_NETWORK_DNS_HPP

#include <ufc/network/host_entry.hpp>

namespace ufc {
    
    ///
    /// @breif: This class provides an interface to the domain name service.
    ///
    ///         An internal dns cache is used to speed up name lookups.
    ///
    class ufc_api dns
    {
    public:
        ///
        /// @breif: Returns a host_entry object containing the dns information
        ///         for the host with the given name.
        ///
        ///         Throws a host_not_found_error if a host with the given name cannot be found.
        ///         Throws a no_address_found_error if no address can be found for the hostname.
        ///         Throws a dns_error in case of a general dns error.
        ///         Throws an io_error in case of any other error.
        ///
        static host_entry host_by_name(const string& __hostname);

        ///
        /// @breif: Returns a host_entry object containing the dns information
        ///         for the host with the given IP address.
        ///
        ///         Throws a host_not_found_error if a host with the given name cannot be found.
        ///         Throws a dns_error in case of a general dns error.
        ///         Throws an io_error in case of any other error.
        ///
        static host_entry host_by_address(const ip_address& __address);

        ///
        /// @breif: Returns a host_entry object containing the dns information
        ///         for the host with the given IP address or host name.
        ///
        ///         Throws a host_not_found_error if a host with the given name cannot be found.
        ///         Throws a no_address_found_error if no address can be found for the hostname.
        ///         Throws a dns_error in case of a general dns error.
        ///         Throws an io_error in case of any other error.
        ///
        static host_entry resolve(const string& __address);

        ///
        /// @breif: Convenience method that calls resolve(address) and returns 
        ///         the first address from the HostInfo.
        ///
        static ip_address resolve_one(const string& __address);

        ///
        /// @breif: Returns a host_entry object containing the dns information for this host.
        ///
        ///         Throws a host_not_found_error if dns information for this host cannot be found.
        ///         Throws a no_address_found_error if no address can be found for this host.
        ///         Throws a dns_error in case of a general dns error.
        ///         Throws an io_error in case of any other error.
        ///
        static host_entry this_host();

        ///
        /// @breif: Flushes the internal dns cache.
        ///         As of 1.4.2, the dns cache is no longer used and this method does not do anything.
        ///
        static void flush_cache();

        ///
        /// @breif: Returns the host name of this host.
        ///
        static string host_name();

    protected:
        ///
        /// @breif: Returns the code of the last error.
        ///
        static int32_t last_error();

        ///
        /// @breif: Throws an exception according to the error code.
        ///
        static void error(int32_t __code, const string& __arg);

        ///
        /// @breif: Throws an exception according to the getaddrinfo() error code.
        ///
        static void aierror(int32_t __code, const string& __arg);
    };

}//namespace ufc

#endif//UFC_NETWORK_DNS_HPP
