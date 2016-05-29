/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : system/environment.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/system/environment.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/thread/mutex.hpp"
#if defined(_WIN32) || defined(WIN32)
#include "system/environment_win32.hpp"
#else
#include "system/environment_unix.hpp"
#endif

namespace ufc {

    static mutex  __s_mutex;
    static string __s_engine_path = "";

    string environment::get(const string& __name)
    {
        return environment_impl::get(__name);
    }

    string environment::get(const string& __name, const string& __default_value)
    {
        if (environment_impl::has(__name))
            return environment_impl::get(__name);
        else
            return __default_value;
    }

    bool environment::has(const string& __name)
    {
        return environment_impl::has(__name);
    }

    void environment::set(const string& __name, const string& __value)
    {
        environment_impl::set(__name, __value);
    }

    string environment::expand(const string& __str)
    {
        return environment_impl::expand(__str);
    }

    string environment::os_name()
    {
        return environment_impl::os_name();
    }

    string environment::os_display_name()
    {
        return environment_impl::os_display_name();
    }

    string environment::os_version()
    {
        return environment_impl::os_version();
    }

    string environment::os_architecture()
    {
        return environment_impl::os_architecture();
    }

    string environment::node_name()
    {
        return environment_impl::node_name();
    }

    void environment::node_id(node_id_t& __id)
    {
        environment_impl::node_id(__id);
    }

    string environment::node_id()
    {
        node_id_t __id;
        node_id(__id);
        char __result[18] = {0};
        return string::format("%02x:%02x:%02x:%02x:%02x:%02x",
            __id[0],
            __id[1],
            __id[2],
            __id[3],
            __id[4],
            __id[5]);
    }

    uint32_t environment::processor_count()
    {
        return environment_impl::processor_count();
    }

    uint32_t environment::system_bits()
    {
        return (sizeof(void*) * 8);
    }

    void environment::set_engine_path(const string& __path)
    {
        mutex::scoped_lock __lock(__s_mutex);
        __s_engine_path = __path;
        if (!__s_engine_path.end_with(path::separator_char()))
        {
            __s_engine_path += path::separator();
        }
    }

    string environment::get_engine_path()
    {
        if (__s_engine_path.empty())
        {
            mutex::scoped_lock __lock(__s_mutex);
            if (__s_engine_path.empty())
            {
                __s_engine_path = environment::get("UFC_ENGINE_PATH", "." + path::separator() + "engine" + path::separator());
                if (!__s_engine_path.end_with(path::separator_char()))
                {
                    __s_engine_path += path::separator();
                }
            }
        }
        return __s_engine_path;
    }

}//namespace ufc
