/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : network/socketdefs.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-05
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/network/socketdefs.hpp"

namespace ufc {
namespace detail {

    atomic_counter network_initialize::_counter;
    
    network_initialize::network_initialize()
    {
#if defined(ufc_os_family_windows)
        if (++_counter == 1)
        {
            WORD    __version = MAKEWORD(2, 2);
            WSADATA __vdata;
            if (WSAStartup(__version, &__vdata) != 0)
            {   
                throw net_error("Failed to initialize network subsystem");
            }
        }
#endif // ufc_os_family_windows
    }

    network_initialize::~network_initialize()
    {
#if defined(ufc_os_family_windows)
        if (--_counter == 0)
        {
            WSACleanup();
        }
#endif // ufc_os_family_windows
    }

}//namespace detail
        
    ufc_implement_exception(net_error,                        io_error,         "network error")
    ufc_implement_exception(invalid_address_error,            net_error,        "invalid address")
    ufc_implement_exception(invalid_socket_error,             net_error,        "invalid socket")
    ufc_implement_exception(service_not_found_error,          net_error,        "service not found")
    ufc_implement_exception(connection_aborted_error,         net_error,        "software caused connection abort")
    ufc_implement_exception(connection_reset_error,           net_error,        "connection reset by peer")
    ufc_implement_exception(connection_refused_error,         net_error,        "connection refused")
    ufc_implement_exception(dns_error,                        net_error,        "dns error")
    ufc_implement_exception(ftp_error,                        net_error,        "ftp error")
    ufc_implement_exception(smtp_error,                       net_error,        "smtp error")

    ufc_implement_exception(host_not_found_error,             dns_error,        "host not found")
    ufc_implement_exception(no_address_found_error,           dns_error,        "no address found")

}//namespace ufc
