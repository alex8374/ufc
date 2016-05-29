/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : system/environment_unix.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef SYSTEM_ENVIRONMENT_UNIX_HPP
#define SYSTEM_ENVIRONMENT_UNIX_HPP

#include "ufc/system/environment.hpp"
#include "ufc/container/buffer.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/thread/mutex.hpp"
#include "ufc/filesystem/path.hpp"
#include <map>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/param.h>
#include <cstring>
#include <errno.h>
#if defined(__NetBSD__) || defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__APPLE__) || defined(__TOS_MACOS__)
#include <sys/sysctl.h>
#elif defined(hpux) || defined(_hpux)
#include <pthread.h>
#endif

#if defined(__NetBSD__) || defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__APPLE__) || defined(__TOS_MACOS__)
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <net/if_dl.h>

#elif defined(__CYGWIN__) || defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__)
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#ifndef __CYGWIN__
#include <net/if_arp.h>
#else // workaround for Cygwin, which does not have if_arp.h 
#define ARPHRD_ETHER 1 /* Ethernet 10Mbps */
#endif 
#include <arpa/inet.h>
#include <unistd.h>

#else
#include <sys/ioctl.h>
#if defined(sun) || defined(__sun)
#include <sys/sockio.h>
#endif
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <unistd.h>
#endif

namespace ufc {

    class environment_impl
    {
    public:    
        static string get(const string& __name)
        {
            const char* __val = getenv(__name.c_str());
            if (__val)
                return string(__val);
            else
                throw not_found_error(__name);
        }

        static bool has(const string& __name)
        {
            return (getenv(__name.c_str()) != NULL);
        }

        static void set(const string& __name, const string& __value)
        {
            string __var = __name + "=" + __value;
            if (putenv(const_cast<char*>(__var.c_str())))
            {
                throw system_error("cannot set environment variable: " + __name);
            }
        }

        static string expand(const string& __str)
        {
            string __result;
            string::const_iterator __it  = __str.begin();
            string::const_iterator __end = __str.end();
            if (__it != __end && *__it == '~')
            {
                ++__it;
                if (__it != __end && *__it == '/')
                {
                    __result += path::home(); ++__it;
                }
                else 
                {
                    __result += '~';
                }
            }
            while (__it != __end)
            {
                if (*__it == '$')
                {
                    string __var;
                    ++__it;
                    if (__it != __end && *__it == '{')
                    {
                        ++__it;
                        while (__it != __end && *__it != '}') 
                        {
                            __var += *__it++;
                        }
                        if (__it != __end) 
                        {
                            ++__it;
                        }
                    }
                    else if (__it != __end && *__it == '(')
                    {
                        ++__it;
                        while (__it != __end && *__it != ')')
                        {
                            __var += *__it++;
                        }
                        if (__it != __end)
                        {
                            ++__it;
                        }
                    }
                    else
                    {
                        while (__it != __end && (isalnum(*__it) || *__it == '_')) 
                        {
                            __var += *__it++;
                        }
                    }
                    char* __val = getenv(__var.c_str());
                    if (__val) 
                    {
                        __result += __val;
                    }
                }
                else 
                {
                    __result += *__it++;
                }
            }
            return __result;
        }

        static string os_name()
        {
            struct utsname __uts;
            uname(&__uts);
            return __uts.sysname;
        }

        static string os_display_name()
        {
            return os_name();
        }

        static string os_version()
        {
            struct utsname __uts;
            uname(&__uts);
            return __uts.release;
        }

        static string os_architecture()
        {
            struct utsname __uts;
            uname(&__uts);
            return __uts.machine;
        }

        static string node_name()
        {
            struct utsname __uts;
            uname(&__uts);
            return __uts.nodename;
        }

        static void node_id(environment::node_id_t& __id)
        {
#if defined(__NetBSD__) || defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__APPLE__) || defined(__TOS_MACOS__)

            std::memset(&__id, 0, sizeof(__id));
            struct ifaddrs* __ifaphead;
            int __rc = getifaddrs(&__ifaphead);
            if (__rc) return;

            for (struct ifaddrs* ifap = __ifaphead; ifap; ifap = ifap->ifa_next) 
            {
                if (ifap->ifa_addr && ifap->ifa_addr->sa_family == AF_LINK) 
                {
                    struct sockaddr_dl* sdl = reinterpret_cast<struct sockaddr_dl*>(ifap->ifa_addr);
                    caddr_t ap = (caddr_t) (sdl->sdl_data + sdl->sdl_nlen);
                    int alen = sdl->sdl_alen;
                    if (ap && alen > 0) 
                    {
                        std::memcpy(&__id, ap, sizeof(__id));
                        break;
                    }
                }
            }
            freeifaddrs(__ifaphead);

#elif defined(__CYGWIN__) || defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__)

            std::memset(&__id, 0, sizeof(__id));
            int __sock = socket(PF_INET, SOCK_DGRAM, 0);
            if (__sock == -1) return;

            // the following code is loosely based
            // on W. Richard Stevens, UNIX Network Programming, pp 434ff.
            int __last_len = 0;
            int __length = 100*sizeof(struct ifreq);
            struct ifconf __ifc;
            char* __buf = 0;
            for (;;)
            {
                __buf = new char[__length];
                __ifc.ifc_len = __length;
                __ifc.ifc_buf = __buf;
                if (::ioctl(__sock, SIOCGIFCONF, &__ifc) < 0)
                {
                    if (errno != EINVAL || __last_len != 0)
                    {
                        close(__sock);
                        delete [] __buf;
                        return;
                    }
                }
                else
                {
                    if (__ifc.ifc_len == __last_len)
                        break;
                    __last_len = __ifc.ifc_len;
                }
                __length += 10*sizeof(struct ifreq);
                delete [] __buf;
            }
            for (const char* ptr = __buf; ptr < __buf + __ifc.ifc_len;)
            {
                const struct ifreq* ifr = reinterpret_cast<const struct ifreq*>(ptr);        
                int __rc = ioctl(__sock, SIOCGIFHWADDR, ifr);
                if (__rc != -1)
                {
                    const struct sockaddr* sa = reinterpret_cast<const struct sockaddr*>(&ifr->ifr_hwaddr);
                    if (sa->sa_family == ARPHRD_ETHER)
                    {
                        std::memcpy(&__id, sa->sa_data, sizeof(__id));
                        break;
                    }
                }
                ptr += sizeof(struct ifreq);
            }
            close(__sock);
            delete [] __buf;

#else

            std::memset(&__id, 0, sizeof(__id));
            char __name[64];
            if (gethostname(__name, sizeof(__name)))
                return;

            struct hostent* __host = gethostbyname(__name);
            if (!__host) return;

            int __s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (__s == -1) return;

            struct arpreq __ar;
            std::memset(&__ar, 0, sizeof(__ar));
            struct sockaddr_in* __addr = reinterpret_cast<struct sockaddr_in*>(&__ar.arp_pa);
            __addr->sin_family = AF_INET;
            std::memcpy(&__addr->sin_addr, *__host->h_addr_list, sizeof(struct in_addr));
            int __rc = ioctl(__s, SIOCGARP, &__ar);
            close(__s);
            if (__rc < 0) return;
            std::memcpy(&__id, __ar.arp_ha.sa_data, sizeof(__id));
#endif
        }

        static uint32_t processor_count()
        {
#if defined(__NetBSD__) || defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__APPLE__) || defined(__TOS_MACOS__)
            uint32_t __count;
            std::size_t __size = sizeof(__count);
            if (sysctlbyname("hw.ncpu", &__count, &__size, 0, 0))
                return 1;
            else
                return __count;
#elif defined(hpux) || defined(_hpux)
            return pthread_num_processors_np();
#elif defined(_SC_NPROCESSORS_ONLN)
            int __count = sysconf(_SC_NPROCESSORS_ONLN);
            if (__count <= 0) __count = 1;
            return static_cast<uint32_t>(__count);
#else
            return 1;
#endif
        }
    };

}//namespace ufc

#endif//SYSTEM_ENVIRONMENT_UNIX_HPP
