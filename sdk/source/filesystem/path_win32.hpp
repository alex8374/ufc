/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : filesystem/path_win32.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef FILESYSTEM_PATH_WIN32_HPP
#define FILESYSTEM_PATH_WIN32_HPP

#include "ufc/filesystem/path.hpp"
#include "ufc/filesystem/file.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/string/string_tokenizer.hpp"
#include "ufc/system/environment.hpp"
#include "ufc/container/buffer.hpp"
#include <algorithm>
#include <Windows.h>

namespace ufc {

    class path::private_t
    {
    public:
        static string current()
        {
            char __buffer[MAX_PATH];
            DWORD __n = GetCurrentDirectoryA(sizeof(__buffer), __buffer);
            if (__n > 0 && __n < sizeof(__buffer))
            {
                string __result(__buffer, __n);
                if (__result[__n - 1] != '\\')
                    __result.append("\\");
                return __result;
            }
            else throw system_error("Cannot get current directory");
        }

        static string home()
        {
            string __result = environment::get("HOMEDRIVE");
            __result.append(environment::get("HOMEPATH"));
            string::size_type __n = __result.size();
            if (__n > 0 && __result[__n - 1] != '\\')
                __result.append("\\");
            return __result;
        }

        static string temp()
        {
            char __buffer[MAX_PATH];
            DWORD __n = GetTempPathA(sizeof(__buffer), __buffer);
            if (__n > 0 && __n < sizeof(__buffer))
            {
                __n = GetLongPathNameA(__buffer, __buffer, static_cast<DWORD>(sizeof __buffer));
                if (__n <= 0) throw system_error("Cannot get temporary directory long __path name");
                string __result(__buffer, __n);
                if (__result[__n - 1] != '\\')
                    __result.append("\\");
                return __result;
            }
            else throw system_error("Cannot get temporary directory");
        }

        static string null()
        {
            return "NUL:";
        }

        static void list_roots(string_vec& __roots)
        {
            __roots.clear();
            char __buffer[128];
            DWORD __n = GetLogicalDriveStrings(sizeof(__buffer) - 1, __buffer);
            char* __it = __buffer;
            char* end = __buffer + (__n > sizeof(__buffer) ? sizeof(__buffer) : __n);
            while (__it < end)
            {
                string dev;
                while (__it < end && *__it) dev += *__it++;
                __roots.push_back(dev);
                ++__it;
            }
        }

        static char separator_char()
        {
            return '\\';
        }

        static string separator()
        {
            return "\\";
        }

        static char path_separator_char()
        {
            return ';';
        }

        static string path_separator()
        {
            return ";";
        }

        static string get_library_path_list()
        {
            return environment::get("PATH", "");
        }

        static void parse(path& __path, const string& __str)
        {
            __path.clear();

            string::const_iterator __it  = __str.begin();
            string::const_iterator __end = __str.end();

            if (__it != __end)
            {
                if (*__it == '\\' || *__it == '/') 
                { 
                    __path._absolute = true; 
                    ++__it; 
                }
                if (__path._absolute && __it != __end && (*__it == '\\' || *__it == '/')) // UNC
                {
                    ++__it;
                    while (__it != __end && *__it != '\\' && *__it != '/') 
                    {
                        *__it++;
                    }
                    if (__it != __end) 
                    {
                        ++__it;
                    }
                }
                else if (__it != __end)
                {
                    char __d = *__it++;
                    if (__it != __end && *__it == ':') // drive letter
                    {
                        if (__path._absolute || !((__d >= 'a' && __d <= 'z') || (__d >= 'A' && __d <= 'Z')))
                        {
                            throw path_syntax_error(__path);
                        }
                        __path._absolute = true;
                        __path._device += __d;
                        ++__it;
                        if (__it == __end || (*__it != '\\' && *__it != '/')) 
                        {
                            throw path_syntax_error(__path);
                        }
                        ++__it;
                    }
                    else
                    {
                        --__it;
                    }
                }
                while (__it != __end)
                {
                    string __name;
                    while (__it != __end && *__it != '\\' && *__it != '/') __name += *__it++;
                    if (__it != __end)
                        __path.push_directory(__name);
                    else
                        __path._name = __name;
                    if (__it != __end) 
                    {
                        ++__it;
                    }
                }
            }
            if (__path._dirs.empty() && !__path._name.empty())
            {
                __path.make_directory();
            }
        }

        static void to_string(const path& __path, string& __str)
        {
            __str.clear();
            if (!__path._device.empty())
            {
                __str.append(__path._device);
                __str.append(":\\");
            }
            else if (__path._absolute)
            {
                __str.append("\\");
            }
            for (string_vec::const_iterator __it = __path._dirs.begin(); __it != __path._dirs.end(); ++__it)
            {
                __str.append(*__it);
                __str.append("\\");
            }
            __str.append(__path._name);
        }
    };

}//namespace ufc

#endif//FILESYSTEM_PATH_WIN32_HPP
