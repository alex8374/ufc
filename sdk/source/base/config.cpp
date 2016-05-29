/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : base/object.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/base/config.hpp"
#include "ufc/thread/mutex.hpp"
#include "ufc/string/string.hpp"
#include <cctype>
#include <map>
#include <deque>
#include <cstring>

namespace ufc {

    static string parse_class_name(const string& __class_name)
    {
        std::deque<string> __class_name_queue;
        for (std::size_t i = 0; i < __class_name.length();)
        {
            int nLen = 0;
            for (; i < __class_name.length() && isdigit(__class_name[i]); i++)
            {
                nLen = nLen * 10 + (__class_name[i] - '0');
            }

            if (nLen == 0) break;

            __class_name_queue.push_back(__class_name.substr(i, nLen));
            i += nLen;        
        }

        string strResultClassName;
        for (;;)
        {
            if (__class_name_queue.empty()) break;

            if (!strResultClassName.empty())
                strResultClassName += "::";
            strResultClassName += __class_name_queue.front();
            __class_name_queue.pop_front();
        }        

        return strResultClassName;
    }

	const char* object::get_class_name(const std::type_info& __typeinfo)
    {
        typedef std::map<string, string> string_map;

        static mutex      __s_mutex;
        static string_map __s_nameMap;

        mutex::scoped_lock lock(__s_mutex);

        string __raw_name(__typeinfo.name());
        string_map::const_iterator it = __s_nameMap.find(__raw_name);
        if (it == __s_nameMap.end())
        {
            string __new_name;
            if (__raw_name.start_with_ignore_case("class "))
                __new_name = __raw_name.substr(6);
            else if (__raw_name.start_with_ignore_case("struct "))
                __new_name = __raw_name.substr(7);
            else
            {
                if (__raw_name.start_with('N') && __raw_name.length() >= 5 && isdigit(__raw_name[1]))
                {
                    __new_name = parse_class_name(__raw_name.substr(1));
                }
                else if (__raw_name.start_with("PKN") && __raw_name.length() >= 5 && isdigit(__raw_name[3]))
                {
                    __new_name = parse_class_name(__raw_name.substr(3));
                }
                else
                {
                    __new_name = parse_class_name(__raw_name);
                }
            }

            if (__new_name.end_with('*'))
            {
                __new_name = __new_name.substr(0, __new_name.length() - 1);
            }

            __new_name.trim();

            __s_nameMap.insert(std::make_pair(__raw_name, __new_name));
        }

        return __s_nameMap[__raw_name].c_str();
    }

    object::object()
    {
    }

    object::object(const object&)
    {
    }

    object::~object()
    {
    }

    object& object::operator = (const object&)
    {
        return *this;
    }

    intptr_t object::hash_code() const
    {
        return reinterpret_cast<intptr_t>(this);
    }

}//namespace ufc
