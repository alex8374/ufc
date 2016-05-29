/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : system/environment_win32.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef SYSTEM_ENVIRONMENT_WIN32_HPP
#define SYSTEM_ENVIRONMENT_WIN32_HPP

#include "ufc/system/environment.hpp"
#include "ufc/container/buffer.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/thread/mutex.hpp"
#include "ufc/filesystem/path.hpp"
#include <Windows.h>
#include <sstream>
#include <cstring>
#include <iphlpapi.h>

namespace ufc {

    class environment_impl
    {
    public:    
        static string get(const string& __name)
        {
            DWORD __length = GetEnvironmentVariableA(__name.c_str(), 0, 0);
            if (__length == 0) 
            {
                throw not_found_error(__name);
            }

            buffer<char> __buffer(__length);
            GetEnvironmentVariableA(__name.c_str(), __buffer.get(), __length);
            return string(__buffer.get());
        }

        static bool has(const string& __name)
        {
            return (GetEnvironmentVariableA(__name.c_str(), 0, 0) > 0);
        }

        static void set(const string& __name, const string& __value)
        {
            if (SetEnvironmentVariableA(__name.c_str(), __value.c_str()) == 0)
            {
                throw system_error("cannot set environment variable: " + __name);
            }
        }

        static string expand(const string& __str)
        {
            char __buffer[102400+1];
            DWORD __n = ExpandEnvironmentStringsA(__str.c_str(), __buffer, sizeof(__buffer));
            if (__n > 0 && __n < sizeof(__buffer))
                return string(__buffer, __n - 1);
            else
                return __str;
        }

        static string os_name()
        {
            OSVERSIONINFO __vi;
            __vi.dwOSVersionInfoSize = sizeof(__vi);
            if (GetVersionEx(&__vi) == 0) 
            {
                throw system_error("Cannot get OS version information");
            }
            switch (__vi.dwPlatformId)
            {
            case VER_PLATFORM_WIN32s:
                return "Windows 3.x";
            case VER_PLATFORM_WIN32_WINDOWS:
                return __vi.dwMinorVersion == 0 ? "Windows 95" : "Windows 98";
            case VER_PLATFORM_WIN32_NT:
                return "Windows NT";
            default:
                return "Unknown";
            }
        }

        static string os_display_name()
        {
            OSVERSIONINFO __vi;
            __vi.dwOSVersionInfoSize = sizeof(__vi);
            if (GetVersionEx(&__vi) == 0) 
            {
                throw system_error("Cannot get OS version information");
            }
            switch(__vi.dwMajorVersion)
            {
            case 6:
                switch (__vi.dwMinorVersion)
                {
                case 0:
                    return "Windows Vista/Server 2008";
                case 1:
                    return "Windows 7/Server 2008 SP2";
                case 2:
                    return "Windows 8/Server 2008 SP1";
                default:
                    return "Unknown";
                }
            case 5:
                switch (__vi.dwMinorVersion)
                {
                case 0:
                    return "Windows 2000";
                case 1:
                    return "Windows XP";
                case 2:
                    return "Windows Server 2003/Windows Server 2003 R2";
                default:
                    return "Unknown";
                }
            case 4:
                switch (__vi.dwMinorVersion)
                {
                case 0:
                    return "Windows 95/Windows NT 4.0";
                case 10:
                    return "Windows 98";
                case 90:
                    return "Windows ME";
                default:
                    return "Unknown";
                }
            default:
                return "Unknown";
            }
        }

        static string os_version()
        {
            OSVERSIONINFO __vi;
            __vi.dwOSVersionInfoSize = sizeof(__vi);
            if (GetVersionEx(&__vi) == 0) 
            {
                throw system_error("Cannot get OS version information");
            }
            std::ostringstream __str;
            __str << __vi.dwMajorVersion << "." << __vi.dwMinorVersion << " (Build " << (__vi.dwBuildNumber & 0xFFFF);
            if (__vi.szCSDVersion[0]) 
            {
                __str << ": " << __vi.szCSDVersion;
            }
            __str << ")";
            return __str.__str();
        }

        static string os_architecture()
        {
            SYSTEM_INFO __si;
            GetSystemInfo(&__si);
            switch (__si.wProcessorArchitecture)
            {
            case PROCESSOR_ARCHITECTURE_INTEL:
                return "IA32";
            case PROCESSOR_ARCHITECTURE_MIPS:
                return "MIPS";
            case PROCESSOR_ARCHITECTURE_ALPHA:
                return "ALPHA";
            case PROCESSOR_ARCHITECTURE_PPC:
                return "PPC";
            case PROCESSOR_ARCHITECTURE_IA64:
                return "IA64";
#ifdef PROCESSOR_ARCHITECTURE_IA32_ON_WIN64
            case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
                return "IA64/32";
#endif
#ifdef PROCESSOR_ARCHITECTURE_AMD64
            case PROCESSOR_ARCHITECTURE_AMD64:
                return "AMD64";
#endif
            default:
                return "Unknown";
            }
        }

        static string node_name()
        {
            char __name[MAX_COMPUTERNAME_LENGTH + 1];
            DWORD size = sizeof(__name);
            if (GetComputerNameA(__name, &size) == 0) 
            {
                throw system_error("Cannot get computer __name");
            }
            return std::string(__name);
        }

        static void node_id(environment::node_id_t& __id)
        {
            std::memset(&__id, 0, sizeof(__id));

            PIP_ADAPTER_INFO __adapter_info;
            PIP_ADAPTER_INFO __adapter = 0;
            ULONG __length    = sizeof(IP_ADAPTER_INFO);
            buffer<char> __buffer(__length);
            __adapter_info = reinterpret_cast<IP_ADAPTER_INFO*>(__buffer.get());
            // Make an initial call to GetAdaptersInfo to get
            // the necessary size into __length
            DWORD __rc = GetAdaptersInfo(__adapter_info, &__length);
            if (__rc == ERROR_BUFFER_OVERFLOW) 
            {
                __buffer.resize(__length);
                __adapter_info = reinterpret_cast<IP_ADAPTER_INFO*>(__buffer.get());
            }
            else if (__rc != ERROR_SUCCESS)
            {
                return;
            }
            if (GetAdaptersInfo(__adapter_info, &__length) == NO_ERROR) 
            {
                __adapter = __adapter_info;
                bool __found = false;
                while (__adapter && !__found) 
                {
                    if (__adapter->Type == MIB_IF_TYPE_ETHERNET && __adapter->AddressLength == sizeof(__id))
                    {
                        __found = true;
                        std::memcpy(&__id, __adapter->Address, __adapter->AddressLength);
                    }
                    __adapter = __adapter->Next;
                }
            }
        }

        static uint32_t processor_count()
        {
            SYSTEM_INFO __si;
            GetSystemInfo(&__si);
            return __si.dwNumberOfProcessors;
        }
    };

}//namespace ufc

#endif//SYSTEM_ENVIRONMENT_WIN32_HPP
