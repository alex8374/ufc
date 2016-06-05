/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/network/socketdefs.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-05
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_NETWORK_SOCKETDEFS_HPP
#define UFC_NETWORK_SOCKETDEFS_HPP

#include "ufc/base/config.hpp"
#include <ufc/string/string.hpp>
#include <ufc/string/string_util.hpp>
#include <ufc/exception/exception.hpp>
#include <ufc/exception/assert.hpp>
#include <ufc/container/vector.hpp>
#include <ufc/system/atomic_counter.hpp>
#include <ufc/system/ref_counted_object.hpp>
#if defined(ufc_os_family_windows)
# include <Windows.h>
# include <winsock2.h>
# include <ws2tcpip.h>
# pragma comment(lib, "ws2_32.lib")
#elif defined(ufc_vxworks)
# include <hostLib.h>
# include <ifLib.h>
# include <inetLib.h>
# include <ioLib.h>
# include <resolvLib.h>
# include <types.h>
# include <socket.h>
# include <netinet/tcp.h>
#elif defined(ufc_os_family_unix) || defined(ufc_os_family_vms)
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# if ufc_os != ufc_os_hpux
#  include <sys/select.h>
# endif
# include <sys/ioctl.h>
# if defined(ufc_os_family_vms)
#  include <inet.h>
# else
#  include <arpa/inet.h>
# endif
# include <netinet/in.h>
# include <netinet/tcp.h>
# include <netdb.h>
# if defined(ufc_os_family_unix)
#  include <net/if.h>
# endif
# if defined(sun) || defined(__APPLE__)
#  include <sys/sockio.h>
#  include <sys/filio.h>
# endif
#endif

#if defined(ufc_os_family_windows)
# define ufc_invalid_socket  INVALID_SOCKET
# define ufc_eintr           WSAEINTR
# define ufc_eacces          WSAEACCES
# define ufc_efault          WSAEFAULT
# define ufc_einval          WSAEINVAL
# define ufc_emfile          WSAEMFILE
# define ufc_eagain          WSAEWOULDBLOCK
# define ufc_ewouldblock     WSAEWOULDBLOCK
# define ufc_einprogress     WSAEINPROGRESS
# define ufc_ealready        WSAEALREADY
# define ufc_enotsock        WSAENOTSOCK
# define ufc_edestaddrreq    WSAEDESTADDRREQ
# define ufc_emsgsize        WSAEMSGSIZE
# define ufc_eprototype      WSAEPROTOTYPE
# define ufc_enoprotoopt     WSAENOPROTOOPT
# define ufc_eprotonosupport WSAEPROTONOSUPPORT
# define ufc_esocktnosupport WSAESOCKTNOSUPPORT
# define ufc_enotsup         WSAEOPNOTSUPP
# define ufc_epfnosupport    WSAEPFNOSUPPORT
# define ufc_eafnosupport    WSAEAFNOSUPPORT
# define ufc_eaddrinuse      WSAEADDRINUSE
# define ufc_eaddrnotavail   WSAEADDRNOTAVAIL
# define ufc_enetdown        WSAENETDOWN
# define ufc_enetunreach     WSAENETUNREACH
# define ufc_enetreset       WSAENETRESET
# define ufc_econnaborted    WSAECONNABORTED
# define ufc_econnreset      WSAECONNRESET
# define ufc_enobufs         WSAENOBUFS
# define ufc_eisconn         WSAEISCONN
# define ufc_enotconn        WSAENOTCONN
# define ufc_eshutdown       WSAESHUTDOWN
# define ufc_etimedout       WSAETIMEDOUT
# define ufc_econnrefused    WSAECONNREFUSED
# define ufc_ehostdown       WSAEHOSTDOWN
# define ufc_ehostunreach    WSAEHOSTUNREACH
# define ufc_esysnotready    WSASYSNOTREADY
# define ufc_enotinit        WSANOTINITIALISED
# define ufc_host_not_found  WSAHOST_NOT_FOUND
# define ufc_try_again       WSATRY_AGAIN
# define ufc_no_recovery     WSANO_RECOVERY
# define ufc_no_data         WSANO_DATA
#elif defined(ufc_os_family_unix) || defined(ufc_os_family_vms) || defined(ufc_vxworks)
# define ufc_invalid_socket  -1
# define ufc_eintr           EINTR
# define ufc_eacces          EACCES
# define ufc_efault          EFAULT
# define ufc_einval          EINVAL
# define ufc_emfile          EMFILE
# define ufc_eagain          EAGAIN
# define ufc_ewouldblock     EWOULDBLOCK
# define ufc_einprogress     EINPROGRESS
# define ufc_ealready        EALREADY
# define ufc_enotsock        ENOTSOCK
# define ufc_edestaddrreq    EDESTADDRREQ
# define ufc_emsgsize        EMSGSIZE
# define ufc_eprototype      EPROTOTYPE
# define ufc_enoprotoopt     ENOPROTOOPT
# define ufc_eprotonosupport EPROTONOSUPPORT
# if defined(ESOCKTNOSUPPORT)
#  define ufc_esocktnosupport ESOCKTNOSUPPORT
# else
#  define ufc_esocktnosupport -1
# endif
# define ufc_enotsup         ENOTSUP
# define ufc_epfnosupport    EPFNOSUPPORT
# define ufc_eafnosupport    EAFNOSUPPORT
# define ufc_eaddrinuse      EADDRINUSE
# define ufc_eaddrnotavail   EADDRNOTAVAIL
# define ufc_enetdown        ENETDOWN
# define ufc_enetunreach     ENETUNREACH
# define ufc_enetreset       ENETRESET
# define ufc_econnaborted    ECONNABORTED
# define ufc_econnreset      ECONNRESET
# define ufc_enobufs         ENOBUFS
# define ufc_eisconn         EISCONN
# define ufc_enotconn        ENOTCONN
# if defined(ESHUTDOWN)
#  define ufc_eshutdown      ESHUTDOWN
# else
#  define ufc_eshutdown      -2
# endif
# define ufc_etimedout       ETIMEDOUT
# define ufc_econnrefused    ECONNREFUSED
# if defined(EHOSTDOWN)
#  define ufc_ehostdown      EHOSTDOWN
# else
#  define ufc_ehostdown      -3
# endif
# define ufc_ehostunreach    EHOSTUNREACH
# define ufc_esysnotready    -4
# define ufc_enotinit        -5
# define ufc_host_not_found  HOST_NOT_FOUND
# define ufc_try_again       TRY_AGAIN
# define ufc_no_recovery     NO_RECOVERY
# define ufc_no_data         NO_DATA
#endif

#if defined(ufc_os_family_bsd) || (ufc_os == ufc_os_tru64) || (ufc_os == ufc_os_aix) || (ufc_os == ufc_os_irix) || (ufc_os == ufc_os_qnx) || (ufc_os == ufc_os_vxworks)
# define ufc_have_salen      1
#endif

#if ufc_os != ufc_os_vxworks
# define ufc_have_addrinfo   1
#endif

#if (ufc_os == ufc_os_hpux) || (ufc_os == ufc_os_solaris) || (ufc_os == ufc_os_windows_ce)
# define ufc_broken_timeouts 1
#endif

#if defined(ufc_have_addrinfo)
# if !defined(AI_ADDRCONFIG)
#  define AI_ADDRCONFIG 0
# endif
#endif

#if defined(ufc_have_salen)
# define ufc_set_sa_len(pSA, len) (pSA)->sa_len   = (len)
# define ufc_set_sin_len(pSA)     (pSA)->sin_len  = sizeof(struct sockaddr_in)
# if defined(ufc_have_ipv6)
#  define ufc_set_sin6_len(pSA)   (pSA)->sin6_len = sizeof(struct sockaddr_in6)
# endif
#else
# define ufc_set_sa_len(pSA, len) (void) 0
# define ufc_set_sin_len(pSA)     (void) 0
# define ufc_set_sin6_len(pSA)    (void) 0
#endif

#ifndef INADDR_NONE
# define INADDR_NONE 0xFFFFFFFF
#endif

#ifndef ufc_inaddr_none
# define ufc_inaddr_none INADDR_NONE
#endif//ufc_inaddr_none

namespace ufc {

#if defined(ufc_os_family_windows)    
    typedef SOCKET              socket_t;
    typedef int                 socklen_t;
    typedef int                 ioctl_request_t;
#else
    typedef int                 socket_t;
    //typedef int               socklen_t;
    typedef int                 ioctl_request_t;
    #if defined(ufc_os_family_bsd)
        #define ioctl_request_t unsigned long
    #else
        #define ioctl_request_t int
    #endif
#endif

    namespace detail {
    
        class network_initialize: virtual public object
        {
        public:
            network_initialize();

            virtual ~network_initialize();

        private:
            static atomic_counter _counter;
        };

    }//namespace detail

    ufc_declare_exception(net_error,                        io_error)
    ufc_declare_exception(invalid_address_error,            net_error)
    ufc_declare_exception(invalid_socket_error,             net_error)
    ufc_declare_exception(service_not_found_error,          net_error)
    ufc_declare_exception(connection_aborted_error,         net_error)
    ufc_declare_exception(connection_reset_error,           net_error)
    ufc_declare_exception(connection_refused_error,         net_error)
    ufc_declare_exception(dns_error,                        net_error)
    ufc_declare_exception(ftp_error,                        net_error)
    ufc_declare_exception(smtp_error,                       net_error)
    ufc_declare_exception(host_not_found_error,             dns_error)
    ufc_declare_exception(no_address_found_error,           dns_error)

}//namespace ufc

#endif//UFC_NETWORK_SOCKETDEFS_HPP
