/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : string/string_builder.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/string/string_builder.hpp"
#include "ufc/string/string_util.hpp"

namespace ufc {

    string_builder::string_builder()
    {
        clear();
    }
    
    string_builder::~string_builder()
    {
    }

    const string& string_builder::operator [] (uint32_t __pos) const
    {
    }
    
    string& string_builder::operator [] (uint32_t __pos)
    {
    }

    uint32_t string_builder::size() const
    {
        return _datas.size();
    }
 
    void string_builder::clear()
    {
        _datas.clear();
    }

    string_builder& string_builder::add(const string& __s)
    {
        _datas.push_back(__s);
    }
    
    string_builder& string_builder::add(const char* __s)
    {
        _datas.push_back(__s);
    }
    
    string_builder& string_builder::add(char __c)
    {
        _datas.push_back(string(1, __c));
    }

    string_builder& string_builder::add_format(const char* __format, ...)
    {
        va_list __args;
        va_start(__args, __format);
        _datas.push_back(string().vformat(__format, __args));
        va_end(__args);
        return *this;
    }
    
    string_builder& string_builder::add_vfromat(const char* __format, va_list __args)
    {
        _datas.push_back(string().vformat(__format, __args));
    }

    string string_builder::to_string(const string& __delims) const
    {
        string __result;
        for (int32_t __i = 0; __i < int32_t(_datas.size() - 1); __i++)
        {
            __result += _datas[__i];
            __result += __delims;
        }
        if (!_datas.empty())
        {
            __result += _datas[_datas.size() - 1];
        }
        return __result;
    }

}//namespace ufc
