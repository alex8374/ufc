/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : string/codecvt.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-21
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/string/codecvt.hpp"

namespace ufc {

    codecvt::codecvt()
        : _code_page("gbk")
    {
    }

    codecvt::codecvt(const codecvt& __other)
        : _code_page(__other._code_page)
    {
    }

    codecvt::codecvt(const string& __code_page)
        : _code_page(__code_page)
    {
    }

    codecvt::~codecvt()
    {
    }

    codecvt& codecvt::operator = (const codecvt& __other)
    {
        _code_page = __other._code_page;
        return *this;
    }

    codecvt& codecvt::set_code_page(const string& __code_page)
    {
        _code_page = __code_page;
        return *this;
    }

    const string& codecvt::get_code_page() const
    {
        return _code_page;
    }

    string  codecvt::wcstombs(const wstring& __wcs)
    {
        return "";
    }

    wstring codecvt::mbstowcs(const string& __str)
    {
        return L"";
    }

    void codecvt::mbscvt(const string& __from_code, 
                         const string& __from,
                         const string& __to_code,
                         string&       __to)
    {
    }

    codecvt& codecvt::instance()
    {
        static codecvt __holder;
        return __holder;
    }

}//namespace ufc
