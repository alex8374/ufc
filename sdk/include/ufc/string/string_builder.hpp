/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/string/string_builder.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_STRING_STRING_BUILDER_HPP
#define UFC_STRING_STRING_BUILDER_HPP

#include <ufc/string/string.hpp>

namespace ufc {

    ///
    /// @breif: String construction class. Provide some methods for accumulating a string. 
    ///
    class ufc_api string_builder: virtual public object
    {
    public:
        string_builder();
        virtual ~string_builder();

        const string& operator [] (uint32_t __pos) const;
        string& operator [] (uint32_t __pos);

        uint32_t size() const;
        void     clear();

        string_builder& add(const string& __s);
        string_builder& add(const char* __s);
        string_builder& add(char __c);

        string_builder& add_format(const char* __format, ...);
        string_builder& add_vfromat(const char* __format, va_list __args);

        string to_string(const string& __delims = "") const;

    private:
        string_vec _datas;
    };

}//namespace ufc

#endif//UFC_STRING_STRING_BUILDER_HPP