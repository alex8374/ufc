/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : filesystem/path_unix.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef FILESYSTEM_PATH_UNIX_HPP
#define FILESYSTEM_PATH_UNIX_HPP

#include "ufc/filesystem/path.hpp"
#include "ufc/filesystem/file.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/string/string_tokenizer.hpp"
#include "ufc/system/environment.hpp"
#include "ufc/container/buffer.hpp"
#include <algorithm>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <climits>

namespace ufc {

    class path::private_t
    {
    public:
        static string current()
        {
            string __path;
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)))
                __path = cwd;
            else
                throw system_error("cannot get current directory");
            string::size_type __n = __path.size();
            if (__n > 0 && __path[__n - 1] != '/') __path.append("/");
            return __path;
        }

        static string home()
        {
            string __path;
            struct passwd* pwd = getpwuid(getuid());
            if (pwd)
                __path = pwd->pw_dir;
            else
            {
                pwd = getpwuid(geteuid());
                if (pwd)
                    __path = pwd->pw_dir;
                else
                    __path = environment::get("HOME");
            }
            string::size_type __n = __path.size();
            if (__n > 0 && __path[__n - 1] != '/') __path.append("/");
            return __path;
        }

        static string temp()
        {
            string __path;
            char* tmp = getenv("TMPDIR");
            if (tmp)
            {
                __path = tmp;
                string::size_type __n = __path.size();
                if (__n > 0 && __path[__n - 1] != '/') __path.append("/");
            }
            else
            {
                __path = "/tmp/";
            }
            return __path;
        }

        static string null()
        {
            return "/dev/null";
        }

        static void list_roots(string_vec& __roots)
        {
            __roots.clear();
            __roots.push_back("/");
        }

        static char separator_char()
        {
            return '/';
        }

        static string separator()
        {
            return "/";
        }

        static char path_separator_char()
        {
            return ':';
        }

        static string path_separator()
        {
            return ":";
        }

        static string get_library_path_list()
        {
            string __result = environment::get("LD_LIBRARY_PATH", "");
            if (environment::system_bits() == 64)
                __result += ":/usr/lib64:/lib64:/usr/local/lib64/";
            else
                __result += ":/usr/lib:/lib:/usr/local/lib/";
            return __result;
        }

        static void parse(path& __path, const string& __str)
        {
            __path.clear();

            string::const_iterator __it  = __str.begin();
            string::const_iterator __end = __str.end();

            if (__it != __end)
            {
                if (*__it == '/') 
                {
                    __path._absolute = true; 
                    ++__it;
                }
                else if (*__it == '~')
                {
                    ++__it;
                    if (__it == __end || *__it == '/')
                    {
                        path __cwd(home());
                        __path._dirs     = __cwd._dirs;
                        __path._absolute = true;
                    }
                    else 
                    {
                        --__it;
                    }
                }

                while (__it != __end)
                {
                    string __name;
                    while (__it != __end && *__it != '/') __name += *__it++;
                    if (__it != __end)
                    {
                        if (__path._dirs.empty())
                        {
                            if (!__name.empty() && *(__name.rbegin()) == ':')
                            {
                                __path._absolute = true;
                                __path._device.assign(__name, 0, __name.length() - 1);
                            }
                            else
                            {
                                __path.push_directory(__name);
                            }
                        }
                        else 
                        {
                            __path.push_directory(__name);
                        }
                    }
                    else 
                    {
                        __path._name = __name;
                    }
                    if (__it != __end) 
    				{
    	                ++__it;
    				}
                }
            }
        }

        static void to_string(const path& __path, string& __str)
        {
            __str.clear();
            if (!__path._device.empty())
            {
                __str.append("/");
                __str.append(__path._device);
                __str.append(":/");
            }
            else if (__path._absolute)
            {
                __str.append("/");
            }
            for (string_vec::const_iterator __it = __path._dirs.begin(); __it != __path._dirs.end(); ++__it)
            {
                __str.append(*__it);
                __str.append("/");
            }
            __str.append(__path._name);
        }
    };

}//namespace ufc

#endif//FILESYSTEM_PATH_UNIX_HPP
