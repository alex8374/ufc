/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/system/environment.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_SYSTEM_ENVIRONMENT_HPP
#define UFC_SYSTEM_ENVIRONMENT_HPP

#include <ufc/string/string.hpp>

namespace ufc {

    ///
    /// @breif: This class provides access to environment variables 
    ///         and some general system information.
    ///
    class ufc_api environment: virtual public object
    {
    public:
        typedef byte_t node_id_t[6]; /// Ethernet address.

        ///
        /// @breif: Returns the value of the environment variable
        ///         with the given name. Throws a not_found_error
        ///         if the variable does not exist.
        ///
        static string get(const string& __name);

        ///
        /// @breif: Returns the value of the environment variable
        ///         with the given name. If the environment variable
        ///         is undefined, returns __default_value instead.
        ///
        static string get(const string& __name, const string& __default_value);

        ///
        /// @breif: Returns true iff an environment variable
        ///         with the given name is defined.
        ///
        static bool has(const string& __name);

        ///
        /// @breif: Sets the environment variable with the given name to the given value.
        ///
        static void set(const string& __name, const string& __value);

        /// 
        /// @breif: Expand the environment variable in the string variable.
        ///
        static string expand(const string& __str);

        ///
        /// @breif: Returns the operating system name.
        ///
        static string os_name();

        ///
        /// @breif: Returns the operating system name in a "user-friendly" way.
        ///
        static string os_display_name();

        ///
        /// @breif: Returns the operating system version.
        ///
        static string os_version();

        ///
        /// @breif: Returns the operating system architecture.
        ///
        static string os_architecture();

        ///
        /// @breif: Returns the node (or host) name.
        ///
        static string node_name();

        ///
        /// @breif: Returns the Ethernet address of the first Ethernet adapter found on the system.
        ///         Throws a system_error if no Ethernet adapter is available.
        ///
        static void node_id(node_id_t& id);

        ///
        /// @breif: Returns the Ethernet address (format "xx:xx:xx:xx:xx:xx")
        ///         of the first Ethernet adapter found on the system.
        ///         Throws a system_error if no Ethernet adapter is available.
        ///
        static string node_id();

        ///
        /// @breif: Returns the number of processors installed in the system.
        ///         If the number of processors cannot be determined, returns 1.
        ///
        static uint32_t processor_count();

        ///
        /// @breif: Returns the number of the operating system bits.
        ///
        static uint32_t system_bits();

        ///
        /// @breif: Set the path of engine driven.
        ///
        static void set_engine_path(const string& path);

        ///
        /// @breif: Returns the path of engine driven.
        ///
        static string get_engine_path();
    };

}//namespace ufc

#endif//UFC_SYSTEM_ENVIRONMENT_HPP