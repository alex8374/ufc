/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/string/string_util.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_STRING_STRING_UTIL_HPP
#define UFC_STRING_STRING_UTIL_HPP

#include <ufc/string/string.hpp>

namespace ufc {

    ///
    /// @breif: string helper class. provides static methods to parse strings 
    ///         for numeric types and to format numeric types for strings. 
    ///
    class ufc_api string_util: virtual public object
    {
    public:
        static string format(bool __val, bool __digit_type_flag = false);
        static string format(int8_t __val);
        static string format(int8_t __val, uint32_t __width);
        static string format0(int8_t __val, uint32_t __width);
        static string format_hex(int8_t __val);
        static string format_hex(int8_t __val, uint32_t __width);
        static string format(uint8_t __val);
        static string format(uint8_t __val, uint32_t __width);
        static string format0(uint8_t __val, uint32_t __width);
        static string format_hex(uint8_t __val);
        static string format_hex(uint8_t __val, uint32_t __width);

        static string format(int16_t __val);
        static string format(int16_t __val, uint32_t __width);
        static string format0(int16_t __val, uint32_t __width);
        static string format_hex(int16_t __val);
        static string format_hex(int16_t __val, uint32_t __width);
        static string format(uint16_t __val);
        static string format(uint16_t __val, uint32_t __width);
        static string format0(uint16_t __val, uint32_t __width);
        static string format_hex(uint16_t __val);
        static string format_hex(uint16_t __val, uint32_t __width);

        static string format(int32_t __val);
        static string format(int32_t __val, uint32_t __width);
        static string format0(int32_t __val, uint32_t __width);
        static string format_hex(int32_t __val);
        static string format_hex(int32_t __val, uint32_t __width);
        static string format(uint32_t __val);
        static string format(uint32_t __val, uint32_t __width);
        static string format0(uint32_t __val, uint32_t __width);
        static string format_hex(uint32_t __val);
        static string format_hex(uint32_t __val, uint32_t __width);

#ifndef ufc_long_is_64_bit
        static string format(long_t __val);
        static string format(long_t __val, uint32_t __width);
        static string format0(long_t __val, uint32_t __width);
        static string format_hex(long_t __val);
        static string format_hex(long_t __val, uint32_t __width);
        static string format(ulong_t __val);
        static string format(ulong_t __val, uint32_t __width);
        static string format0(ulong_t __val, uint32_t __width);
        static string format_hex(ulong_t __val);
        static string format_hex(ulong_t __val, uint32_t __width);
#endif//ufc_long_is_64_bit

        static string format(int64_t __val);
        static string format(int64_t __val, uint32_t __width);
        static string format0(int64_t __val, uint32_t __width);
        static string format_hex(int64_t __val);
        static string format_hex(int64_t __val, uint32_t __width);
        static string format(uint64_t __val);
        static string format(uint64_t __val, uint32_t __width);
        static string format0(uint64_t __val, uint32_t __width);
        static string format_hex(uint64_t __val);
        static string format_hex(uint64_t __val, uint32_t __width);

        static string format(float __val);
        static string format(double __val);
        static string format(double __val, uint32_t __precision);
        static string format(double __val, uint32_t __width, uint32_t __precision);

        static string fill(const string&      __str,
                           string::size_type  __width,
                           alignment          __align = al_left,
                           string::value_type __fillc = string::traits_type::space_char);
    };

}//namespace ufc

#endif//UFC_STRING_STRING_UTIL_HPP