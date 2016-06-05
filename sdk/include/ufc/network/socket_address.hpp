/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/network/socket_address.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-04
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_NETWORK_SOCKET_ADDRESS_HPP
#define UFC_NETWORK_SOCKET_ADDRESS_HPP

#include <ufc/network/ip_address.hpp>

namespace ufc {
    
    /// @breif: This class represents an internet (IP) endpoint/socket
    ///         address. The address can belong either to the
    ///         ipv4 or the ipv6 address family and consists of a
    ///         host address and a port number.
    class ufc_api socket_address: virtual public object
    {
        class private_t;
        class private4_t;
        class private6_t;

    public:
        ///
        /// @breif: Creates a wildcard (all zero) ipv4 socket_address.
        ///
        socket_address();

        ///
        /// @breif: Creates a socket_address from an IP address and a port number.
        ///
        socket_address(const ip_address& host, uint16_t port);

        ///
        /// @breif: Creates a socket_address from an IP address and a port number.
        ///
        ///         The IP address must either be a domain name, or it must
        ///         be in dotted decimal (ipv4) or hex string (ipv6) format.
        ///
        socket_address(const string& host, uint16_t port);

        ///
        /// @breif: Creates a socket_address from an IP address and a 
        ///         service name or port number.
        ///
        ///         The IP address must either be a domain name, or it must
        ///         be in dotted decimal (ipv4) or hex string (ipv6) format.
        ///
        ///         The given port must either be a decimal port number, or 
        ///         a service name.
        ///
        socket_address(const string& host, const string& port);

        ///
        /// @breif: Creates a socket_address from an IP address or host name and a
        ///         port number/service name. Host name/address and port number must
        ///         be separated by a colon. In case of an ipv6 address,
        ///         the address part must be enclosed in brackets.
        ///
        ///         Examples:
        ///             192.168.1.10:80 
        ///             [::FFFF:192.168.1.120]:2040
        ///             www.appinf.com:8080
        ///
        explicit socket_address(const string& __host_and_port);

        ///
        /// @breif: Creates a socket_address by copying another one.
        ///
        socket_address(const socket_address& __addr);

        ///
        /// @breif: Creates a socket_address from a native socket address.
        ///
        socket_address(const struct sockaddr* __addr, socklen_t __length);

        ///
        /// @breif: Destroys the socket_address.
        ///
        virtual ~socket_address();

        /// @breif: Assigns another socket_address.
        socket_address& operator = (const socket_address& __addr);

        ///
        /// @breif: Swaps the socket_address with another one.  
        ///
        void swap(socket_address& __addr); 

        ///
        /// @breif: Returns the host IP address.
        ///
        ip_address host() const;

        ///
        /// @breif: Returns the port number.
        ///
        uint16_t port() const;

        ///
        /// @breif: Returns the length of the internal native socket address.   
        ///
        socklen_t length() const;

        ///
        /// @breif: Returns a pointer to the internal native socket address.
        ///
        const struct sockaddr* addr() const;

        ///
        /// @breif: Returns the address family (AF_INET or AF_INET6) of the address.
        ///
        int af() const;

        ///
        /// @breif: Returns a string representation of the address.
        ///
        string to_string() const;

        ///
        /// Returns the address family of the host's address.
        ///
        ip_address::family_t family() const;

        bool operator == (const socket_address& __addr) const;
        bool operator != (const socket_address& __addr) const;

    public:
        ///
        /// @breif: Maximum length in bytes of a socket address.
        ///
        static const int32_t& max_address_length;

    protected:
        void init(const ip_address& __host, uint16_t __port);
        void init(const string& __host, uint16_t __port);
        uint16_t resolve_service(const string& __service);
    
    private:
        private_t* _impl;
    };

}//namespace ufc

#endif//UFC_NETWORK_SOCKET_ADDRESS_HPP
