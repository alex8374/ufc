/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/string/codecvt.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-21
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_STRING_CODECVT_HPP
#define UFC_STRING_CODECVT_HPP

#include <ufc/string/string.hpp>

namespace ufc {

    class ufc_api codecvt: virtual public object
    {
    public:
        codecvt();
        codecvt(const codecvt& __other);
        explicit codecvt(const string& __code_page);
        virtual ~codecvt();

        codecvt& operator = (const codecvt& __other);

        codecvt& set_code_page(const string& __code_page);
        const string& get_code_page() const;

        string  wcstombs(const wstring& __wcs);
        wstring mbstowcs(const string& __str);

    public:
        static codecvt& instance();

    public:
        static void mbscvt(const string& __from_code, 
                           const string& __from,
                           const string& __to_code,
                           string&       __to);
    private:
        string _code_page;
    };

}//namespace ufc

#endif//UFC_STRING_CODECVT_HPP
