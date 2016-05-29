/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : string/string_util.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/string/string_util.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#include <sstream>
#include <iomanip>
#if !defined(ufc_no_locale)
#include <locale>
#endif
#include <cstdio>

#if defined(ufc_long_is_64_bit)
#define I64_FMT "l"
#elif defined(_MSC_VER)
#define I64_FMT "I64"
#elif defined(__APPLE__) 
#define I64_FMT "q"
#else
#define I64_FMT "ll"
#endif

namespace ufc {

    string string_util::format(bool __val, bool __digit_type_flag)
    {
        if (__digit_type_flag)
            return __val? "1": "0";
        else
            return __val? "true": "false";
    }

    string string_util::format(int8_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%d", __val);
        return __buffer;
    }

    string string_util::format(int8_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%*d", __width, __val);
        return __buffer;
    }

    string string_util::format0(int8_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*d", __width, __val);
        return __buffer;
    }

    string string_util::format_hex(int8_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%X", __val);
        return __buffer;
    }

    string string_util::format_hex(int8_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*X", __width, __val);
        return __buffer;
    }

    string string_util::format(uint8_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%u", __val);
        return __buffer;
    }

    string string_util::format(uint8_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%*u", __width, __val);
        return __buffer;
    }

    string string_util::format0(uint8_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*u", __width, __val);
        return __buffer;
    }

    string string_util::format_hex(uint8_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%X", __val);
        return __buffer;
    }

    string string_util::format_hex(uint8_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*X", __width, __val);
        return __buffer;
    }

    string string_util::format(int16_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%d", __val);
        return __buffer;
    }

    string string_util::format(int16_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%*d", __width, __val);
        return __buffer;
    }

    string string_util::format0(int16_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*d", __width, __val);
        return __buffer;
    }

    string string_util::format_hex(int16_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%X", __val);
        return __buffer;
    }

    string string_util::format_hex(int16_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*X", __width, __val);
        return __buffer;
    }

    string string_util::format(uint16_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%u", __val);
        return __buffer;
    }

    string string_util::format(uint16_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%*u", __width, __val);
        return __buffer;
    }

    string string_util::format0(uint16_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*u", __width, __val);
        return __buffer;
    }

    string string_util::format_hex(uint16_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%X", __val);
        return __buffer;
    }

    string string_util::format_hex(uint16_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*X", __width, __val);
        return __buffer;
    }

    string string_util::format(int32_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%d", __val);
        return __buffer;
    }

    string string_util::format(int32_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%*d", __width, __val);
        return __buffer;
    }

    string string_util::format0(int32_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*d", __width, __val);
        return __buffer;
    }

    string string_util::format_hex(int32_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%X", __val);
        return __buffer;
    }

    string string_util::format_hex(int32_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*X", __width, __val);
        return __buffer;
    }

    string string_util::format(uint32_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%u", __val);
        return __buffer;
    }

    string string_util::format(uint32_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%*u", __width, __val);
        return __buffer;
    }

    string string_util::format0(uint32_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*u", __width, __val);
        return __buffer;
    }

    string string_util::format_hex(uint32_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%X", __val);
        return __buffer;
    }

    string string_util::format_hex(uint32_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*X", __width, __val);
        return __buffer;
    }

#ifndef ufc_long_is_64_bit

    string string_util::format(long_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%ld", __val);
        return __buffer;
    }

    string string_util::format(long_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%*ld", __width, __val);
        return __buffer;
    }

    string string_util::format0(long_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*ld", __width, __val);
        return __buffer;
    }

    string string_util::format_hex(long_t value)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%lX", value);
        return __buffer;
    }

    string string_util::format_hex(long_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*lX", __width, __val);
        return __buffer;
    }

    string string_util::format(ulong_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%lu", __val);
        return __buffer;
    }

    string string_util::format(ulong_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%*lu", __width, __val);
        return __buffer;
    }

    string string_util::format0(ulong_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*lu", __width, __val);
        return __buffer;
    }

    string string_util::format_hex(ulong_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%lX", __val);
        return __buffer;
    }

    string string_util::format_hex(ulong_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*lX", __width, __val);
        return __buffer;
    }

#endif//ufc_long_is_64_bit

    string string_util::format(int64_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%"I64_FMT"d", __val);
        return __buffer;
    }

    string string_util::format(int64_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%*"I64_FMT"d", __width, __val);
        return __buffer;
    }

    string string_util::format0(int64_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*"I64_FMT"d", __width, __val);
        return __buffer;
    }

    string string_util::format_hex(int64_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%"I64_FMT"X", __val);
        return __buffer;
    }

    string string_util::format_hex(int64_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*"I64_FMT"X", __width, __val);
        return __buffer;
    }

    string string_util::format(uint64_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%"I64_FMT"u", __val);
        return __buffer;
    }

    string string_util::format(uint64_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%*"I64_FMT"u", __width, __val);
        return __buffer;
    }

    string string_util::format0(uint64_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*"I64_FMT"u", __width, __val);
        return __buffer;
    }

    string string_util::format_hex(uint64_t __val)
    {
        char __buffer[64];
        std::sprintf(__buffer, "%"I64_FMT"X", __val);
        return __buffer;
    }

    string string_util::format_hex(uint64_t __val, uint32_t __width)
    {
        ufc_assert (__width > 0 && __width < 64);

        char __buffer[64];
        std::sprintf(__buffer, "%0*"I64_FMT"X", __width, __val);
        return __buffer;
    }

    string string_util::format(float __val)
    {
        std::ostringstream ostr;
#if !defined(ufc_no_locale)
        ostr.imbue(std::locale::classic());
#endif
        ostr << std::setprecision(8) << __val;
        return ostr.str();
    }

    string string_util::format(double __val)
    {
        std::ostringstream ostr;
#if !defined(ufc_no_locale)
        ostr.imbue(std::locale::classic());
#endif
        ostr << std::setprecision(16) << __val;
        return ostr.str();
    }

    string string_util::format(double __val, uint32_t __precision)
    {
        ufc_assert (__precision >= 0 && __precision < 32);

        std::ostringstream ostr;
#if !defined(ufc_no_locale)
        ostr.imbue(std::locale::classic());
#endif
        ostr << std::fixed;
        if (__precision > 0) ostr << std::showpoint;
        ostr << std::setprecision(__precision) << __val;
        return ostr.str();
    }

    string string_util::format(double value, uint32_t __width, uint32_t __precision)
    {
        ufc_assert (__width > 0 && __width < 64 && __precision >= 0 && __precision < __width);

        std::ostringstream ostr;
#if !defined(ufc_no_locale)
        ostr.imbue(std::locale::classic());
#endif
        ostr << std::fixed;
        if (__precision > 0) ostr << std::showpoint;
        ostr << std::setw(__width) << std::setprecision(__precision) << value;
        return ostr.str();
    }

    string string_util::fill(const string& __s, string::size_type __width, alignment __align, string::value_type __fillc)
    {
        string::size_type __length = __s.length();
        if (__width > __length)
        {
            string __result;
            const int __remain_length = __width - __length;
            const int __middle_length = __remain_length / 2;
            switch (__align)
            {
            case al_right:
                __result.append(__fillc, __remain_length)
                        .append(__s);
                break;

            case al_middle:
                __result.append(__fillc, __middle_length)
                        .append(__s)
                        .append(__fillc, __remain_length - __middle_length);
                break;

            default:
                __result.append(__s)
                        .append(__fillc, __remain_length);
                break;
            }
            return __result;
        }
        else if (__width == __length)
            return __s;
        else
            return __s.left(__width);
    }

}//namespace ufc