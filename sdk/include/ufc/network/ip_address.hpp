/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/network/ip_address.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-04
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_NETWORK_IP_ADDRESS_HPP
#define UFC_NETWORK_IP_ADDRESS_HPP

#include <ufc/network/socketdefs.hpp>

namespace ufc {

    ///
    /// @breif: This class represents an internet (IP) host
    ///         address. The address can belong either to the
    ///         ipv4 or the ipv6 address family.
    ///
    ///         Relational operators (==, !=, <, <=, >, >=) are
    ///         supported. However, you must not interpret any
    ///         special meaning into the result of these 
    ///         operations, other than that the results are
    ///         consistent.
    ///
    ///         Especially, an ipv4 address is never equal to
    ///         an ipv6 address, even if the ipv6 address is
    ///         ipv4 compatible and the addresses are the same.
    ///
    ///         ipv6 addresses are supported only if the target platform
    ///         supports ipv6.
    ///
    class ufc_api ip_address: virtual public object
    {
        class private_t;
        class private4_t;
        class private6_t;

    public:
        ///
        /// @breif: Possible address families for IP addresses.
        ///
        enum family_t
        {
            ipv4,
            ipv6
        };
        
        ///
        /// @breif: Creates a wildcard (zero) ipv4 ip_address.
        ///
        ip_address();

        ///
        /// @breif: Creates an ip_address by copying another one.
        ///
        ip_address(const ip_address& __addr);

        ///
        /// @breif: Creates a wildcard (zero) ip_address for the given address family.
        ///
        explicit ip_address(family_t __family);

        ///
        /// @breif: Creates an ip_address from the string containing
        ///         an IP address in presentation format (dotted decimal
        ///         for ipv4, hex string for ipv6).
        /// 
        ///         Depending on the format of addr, either an ipv4 or
        ///         an ipv6 address is created.
        ///
        ///         See to_string() for details on the supported formats.
        ///
        ///         Throws an invalid_address_error if the address cannot be parsed.
        ///
        explicit ip_address(const string& __addr);

        ///
        /// @breif: Creates an ip_address from the string containing
        ///         an IP address in presentation format (dotted decimal
        ///         for ipv4, hex string for ipv6).
        ///
        ip_address(const string& __addr, family_t __family);

        ///
        /// @breif: Creates an ip_address from a native internet address.
        ///         A pointer to a in_addr or a in6_addr structure may be 
        ///         passed.
        ///
        ip_address(const void* __addr, socklen_t __length);

        ///
        /// @breif: Creates an ip_address from a native internet address.
        ///         A pointer to a in_addr or a in6_addr structure may be 
        ///         passed. Additionally, for an ipv6 address, a scope ID
        ///         may be specified. The scope ID will be ignored if an ipv4
        ///         address is specified.
        ///
        ip_address(const void* __addr, socklen_t __length, uint32_t __scope);

        ///
        /// @breif: Destroys the ip_address.
        ///
        virtual ~ip_address();

        ///
        /// @breif: Assigns an ip_address.
        ///
        ip_address& operator = (const ip_address& __addr);

        ///
        /// @breif: Swaps the ip_address with another one.
        ///
        void swap(ip_address& __addr);

        ///
        /// @breif: Returns the address family (ipv4 or ipv6) of the address.
        ///
        family_t family() const;

        ///
        /// @breif: Returns the ipv6 scope identifier of the address. Returns 0 if
        ///         the address is an ipv4 address, or the address is an
        ///         ipv6 address but does not have a scope identifier.
        ///
        uint32_t scope() const;

        ///
        /// @breif: Returns a string containing a representation of the address
        ///         in presentation format.
        ///
        ///         For ipv4 addresses the result will be in dotted-decimal(d.d.d.d) notation.
        ///
        ///         Textual representation of ipv6 address is one of the following forms:
        ///
        ///         The preferred form is x:x:x:x:x:x:x:x, where the 'x's are the hexadecimal 
        ///         values of the eight 16-bit pieces of the address. This is the full form.
        ///         Example: 1080:0:0:0:8:600:200A:425C
        ///
        ///         It is not necessary to write the leading zeros in an individual field. 
        ///         However, there must be at least one numeral in every field, except as described below.
        /// 
        ///         It is common for ipv6 addresses to contain long strings of zero bits. 
        ///         In order to make writing addresses containing zero bits easier, a special syntax is 
        ///         available to compress the zeros. The use of "::" indicates multiple groups of 16-bits of zeros. 
        ///         The "::" can only appear once in an address. The "::" can also be used to compress the leading 
        ///         and/or trailing zeros in an address. Example: 1080::8:600:200A:425C
        ///
        ///         For dealing with ipv4 compatible addresses in a mixed environment,
        ///         a special syntax is available: x:x:x:x:x:x:d.d.d.d, where the 'x's are the 
        ///         hexadecimal values of the six high-order 16-bit pieces of the address, 
        ///         and the 'd's are the decimal values of the four low-order 8-bit pieces of the 
        ///         standard ipv4 representation address. Example: ::FFFF:192.168.1.120
        ///
        ///         If an ipv6 address contains a non-zero scope identifier, it is added
        ///         to the string, delimited by a percent character. On Windows platforms,
        ///         the numeric value (which specifies an interface index) is directly
        ///         appended. On Unix platforms, the name of the interface corresponding
        ///         to the index (interpretation of the scope identifier) is added.
        ///
        string to_string() const;

        ///
        /// @breif: Returns true iff the address is a wildcard (all zero) address.
        ///
        bool is_wildcard() const;

        ///
        /// @breif: Returns true iff the address is a broadcast address.
        ///
        ///         Only ipv4 addresses can be broadcast addresses. In a broadcast
        ///         address, all bits are one.
        ///
        ///         For a ipv6 address, returns always false.
        ///
        bool is_broadcast() const;

        ///
        /// @breif: Returns true iff the address is a loopback address.
        ///         For ipv4, the loopback address is 127.0.0.1.
        ///         For ipv6, the loopback address is ::1.
        ///
        bool is_loopback() const;

        ///
        /// @breif: Returns true iff the address is a multicast address.
        ///         ipv4 multicast addresses are in the 224.0.0.0 to 239.255.255.255 range
        ///         (the first four bits have the value 1110).
        ///         ipv6 multicast addresses are in the FFxx:x:x:x:x:x:x:x range.
        ///
        bool is_multicast() const;

        ///
        /// @breif: Returns true iff the address is a unicast address.
        ///         An address is unicast if it is neither a wildcard, broadcast or multicast address.
        ///
        bool is_unicast() const;

        ///
        /// @breif: Returns true iff the address is a link local unicast address.
        ///         ipv4 link local addresses are in the 169.254.0.0/16 range, according to RFC 3927.
        ///         ipv6 link local addresses have 1111 1110 10 as the first 10 bits, followed by 54 zeros.
        ///
        bool is_link_local() const;

        ///
        /// @breif: Returns true iff the address is a site local unicast address.
        ///         ipv4 site local addresses are in on of the 10.0.0.0/24, 192.168.0.0/16 or 172.16.0.0 to 172.31.255.255 ranges.
        ///         ipv6 site local addresses have 1111 1110 11 as the first 10 bits, followed by 38 zeros.
        ///
        bool is_site_local() const;

        ///
        /// @breif: Returns true iff the address is ipv4 compatible.
        ///         For ipv4 addresses, this is always true.
        ///         For ipv6, the address must be in the ::x:x range (the first 96 bits are zero).
        ///
        bool is_ipv4_compatible() const;

        ///
        /// @breif: Returns true iff the address is an ipv4 mapped ipv6 address.
        ///         For ipv4 addresses, this is always true.
        ///         For ipv6, the address must be in the ::FFFF:x:x range.
        ///
        bool is_ipv4_mapped() const;

        ///
        /// @breif: Returns true iff the address is a well-known multicast address.
        ///         For ipv4, well-known multicast addresses are in the 224.0.0.0/8 range.
        ///         For ipv6, well-known multicast addresses are in the FF0x:x:x:x:x:x:x:x range.
        ///
        bool is_well_known_mc() const;

        ///
        /// @breif: Returns true iff the address is a node-local multicast address.
        ///         ipv4 does not support node-local addresses, thus the result is always false for an ipv4 address.
        ///         For ipv6, node-local multicast addresses are in the FFx1:x:x:x:x:x:x:x range.
        ///
        bool is_node_local_mc() const;

        ///
        /// @breif: Returns true iff the address is a link-local multicast address.
        ///
        ///         For ipv4, link-local multicast addresses are in the 224.0.0.0/24 range.
        ///         Note that this overlaps with the range for well-known multicast addresses.
        ///
        ///         For ipv6, link-local multicast addresses are in the FFx2:x:x:x:x:x:x:x range.
        ///
        bool is_link_local_mc() const;

        ///
        /// @breif: Returns true iff the address is a site-local multicast address.
        ///         For ipv4, site local multicast addresses are in the 239.255.0.0/16 range.
        ///         For ipv6, site-local multicast addresses are in the FFx5:x:x:x:x:x:x:x range.
        ///
        bool is_site_local_mc() const;

        ///
        /// @breif: Returns true iff the address is a organization-local multicast address.
        ///         For ipv4, organization-local multicast addresses are in the 239.192.0.0/16 range.
        ///         For ipv6, organization-local multicast addresses are in the FFx8:x:x:x:x:x:x:x range.
        ///
        bool is_org_local_mc() const;

        ///
        /// @breif: Returns true iff the address is a global multicast address.
        ///         For ipv4, global multicast addresses are in the 224.0.1.0 to 238.255.255.255 range.
        ///         For ipv6, global multicast addresses are in the FFxF:x:x:x:x:x:x:x range.
        ///
        bool is_global_mc() const;

        bool operator == (const ip_address& __addr) const; 
        bool operator != (const ip_address& __addr) const;
        bool operator <  (const ip_address& __addr) const;
        bool operator <= (const ip_address& __addr) const;
        bool operator >  (const ip_address& __addr) const;
        bool operator >= (const ip_address& __addr) const;

        ///
        /// @breif: Returns the length in bytes of the internal socket address structure.   
        ///
        socklen_t length() const;

        ///
        /// @breif: Returns the internal address structure.
        ///
        const void* addr() const;

        ///
        /// @breif: Returns the address family (AF_INET or AF_INET6) of the address.
        ///
        int32_t af() const;

        ///
        /// @breif: Masks the IP address using the given netmask, which is usually
        ///         a ipv4 subnet mask. Only supported for ipv4 addresses.
        ///
        ///         The new address is (address & mask).
        ///
        void mask(const ip_address& __mask);

        ///
        /// @breif: Masks the IP address using the given netmask, which is usually
        /// a ipv4 subnet mask. Only supported for ipv4 addresses.
        ///
        /// The new address is (address & mask) | (set & ~mask).
        ///
        void mask(const ip_address& __mask, const ip_address& __set);

    public:
        ///
        /// @breif: Creates an ip_address from the string containing an IP address in presentation format (dotted decimal
        ///         for ipv4, hex string for ipv6).
        ///         Depending on the format of addr, either an ipv4 or an ipv6 address is created.
        ///         See to_string() for details on the supported formats.
        ///         Throws an invalid_address_error if the address cannot be parsed.
        ///
        static ip_address parse(const string& __addr);

        ///
        /// @breif: Tries to interpret the given address string as an IP address in presentation format (dotted decimal
        ///         for ipv4, hex string for ipv6).
        ///         Returns true and stores the ip_address in result if the string contains a valid address.
        ///         Returns false and leaves result unchanged otherwise.
        ///
        static bool try_parse(const string& __addr, ip_address& __result);

        ///
        /// @breif: Returns a wildcard ipv4 or ipv6 address (0.0.0.0).
        ///
        static ip_address wildcard(family_t __family = ipv4);

        ///
        /// @breif: Returns a broadcast ipv4 address (255.255.255.255).
        ///
        static ip_address broadcast();

        ///
        /// @breif: Maximum length in bytes of a socket address.
        ///
        static const int32_t max_address_length;

    private:
	    void init(private_t* __impl);

        private_t* _impl;
    };

}//namespace ufc

#endif//UFC_NETWORK_IP_ADDRESS_HPP
