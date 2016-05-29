/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/base/sourceinfo.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-17
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_BASE_SOURCEINFO_HPP
#define UFC_BASE_SOURCEINFO_HPP

#include <ufc/base/config.hpp>

namespace ufc {

    class ufc_api source_info: virtual public object
    {
    public:
        source_info(const source_info& rhs);
        source_info(const char* file, uint32_t line, const char* function);
        virtual ~source_info();

        source_info& operator = (const source_info& rhs);

        const char* file() const;
        uint32_t    line() const;
        const char* function() const;

    private:
        source_info();

        void init();

    private:
        char     _file[260+1];
        uint32_t _line;
        char     _function[260+1];
    };

}//namespace ufc

#if defined(__GNUC__)
    #define ufc_sourceinfo      ufc::source_info(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#elif defined(__BORLANDC__)
    #define ufc_sourceinfo      ufc::source_info(__FILE__, __LINE__, __FUNC__)
#else
    #define ufc_sourceinfo      ufc::source_info(__FILE__, __LINE__, __FUNCTION__)
#endif

#endif//UFC_BASE_SOURCEINFO_HPP
