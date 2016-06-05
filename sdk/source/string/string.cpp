/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : string/string.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-21
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/string/string.hpp"
#include "ufc/string/codecvt.hpp"
#include "ufc/exception/exception.hpp"
#include <cctype>
#include <cstring>
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include <cwchar>
#include <cwctype>
#include <sstream>
#include <iomanip>
#include <locale>
#include <cstdio>
#include <cstdlib>

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

    template <> const char_traits<char>::char_type char_traits<char>::space_char = ' ';

    template <> int char_traits<char>::icompare(const char_type* __s1, const char_type* __s2)
    {
#if defined(ufc_os_family_windows)
        return stricmp(__s1, __s2);
#else
        return strcasecmp(__s1, __s2);
#endif
    }

    template <> int char_traits<char>::icompare(const char_type* __s1, const char_type* __s2, std::size_t __n)
    {
#if defined(ufc_os_family_windows)
        return strnicmp(__s1, __s2, __n);
#else
        return strncasecmp(__s1, __s2, __n);
#endif
    }

    template <> bool char_traits<char>::is_alnum(char_type __c)
    {
        return isalnum(__c);
    }

    template <> bool char_traits<char>::is_alpha(char_type __c)
    {
        return isalpha(__c);
    }

    template <> bool char_traits<char>::is_cntrl(char_type __c)
    {
        return iscntrl(__c);
    }

    template <> bool char_traits<char>::is_digit(char_type __c)
    {
        return isdigit(__c);
    }

    template <> bool char_traits<char>::is_xdigit(char_type __c)
    {
        return isxdigit(__c);
    }

    template <> bool char_traits<char>::is_graph(char_type __c)
    {
        return isgraph(__c);
    }

    template <> bool char_traits<char>::is_lower(char_type __c)
    {
        return islower(__c);
    }

    template <> bool char_traits<char>::is_print(char_type __c)
    {
        return isprint(__c);
    }

    template <> bool char_traits<char>::is_punct(char_type __c)
    {
        return ispunct(__c);
    }

    template <> bool char_traits<char>::is_space(char_type __c)
    {
        return isspace(__c);
    }

    template <> bool char_traits<char>::is_upper(char_type __c)
    {
        return isupper(__c);
    }

    template <> bool char_traits<char>::is_blank(char_type __c)
    {
        return isblank(__c);
    }

    template <> bool char_traits<char>::is_boolean(const char_type* __s)
    {
        if (icompare(__s, "true") == 0)
            return true;
        else if (icompare(__s, "yes") == 0)
            return true;
        else if (icompare(__s, "on") == 0)
            return true;
        else if (icompare(__s, "false") == 0)
            return true;
        else if (icompare(__s, "no") == 0)
            return true;
        else if (icompare(__s, "off") == 0)
            return true;
        else
            return false;
    }

    template <> bool char_traits<char>::is_decimal(const char_type* __s)
    {
        if (__s && __s[0] != 0)
        {
            bool __dot_flag = false;
            if (*__s == '+' || *__s == '-') ++__s;
            if (*__s == '.')
            {
                ++__s;
                if (!isdigit(*__s)) return false;
                __dot_flag = true;
            }
            for (; *__s; ++__s)
            {
                if (!isdigit(*__s) && *__s != '.')
                {
                    return false;
                }
                if (*__s == '.' && __dot_flag)
                {
                    if (__dot_flag) return false;
                    __dot_flag = true;
                }
            }
            return true;
        }
        return false;
    }

    template <> char_traits<char>::char_type char_traits<char>::to_lower(char_type __c)
    {
        return tolower(__c);
    }

    template <> char_traits<char>::char_type char_traits<char>::to_upper(char_type __c)
    {
        return toupper(__c);
    }

    template <> bool char_traits<char>::as_boolean(const char_type* __s)
    {
        if (icompare(__s, "true") == 0)
            return true;
        else if (icompare(__s, "yes") == 0)
            return true;
        else if (icompare(__s, "on") == 0)
            return true;
        else if (icompare(__s, "false") == 0)
            return false;
        else if (icompare(__s, "no") == 0)
            return false;
        else if (icompare(__s, "off") == 0)
            return false;
        else
            throw syntax_error("Not a valid boolean", __s);
    }

    template <> int char_traits<char>::as_int32(const char_type* __s)
    {
        int __v = 0;
        char __c;
        if (std::sscanf(__s, "%d%c", &__v, &__c) != 1)
        {
            throw syntax_error("Not a valid integer", __s);
        }
        return __v;
    }

    template <> unsigned char_traits<char>::as_uint32(const char_type* __s)
    {
        unsigned __v = 0;
        char __c;
        if (std::sscanf(__s, "%u%c", &__v, &__c) != 1)
        {
            throw syntax_error("Not a valid unsigned integer", __s);
        }
        return __v;
    }

    template <> unsigned char_traits<char>::as_hex32(const char_type* __s)
    {
        unsigned __v = 0;
        char __c;
        if (std::sscanf(__s, "%x%c", &__v, &__c) != 1)
        {
		    throw syntax_error("Not a valid hexadecimal integer", __s);
        }
        return __v;
    }

    template <> int64_t char_traits<char>::as_int64(const char_type* __s)
    {
        int64_t __v = 0;
        char __c;
        if (std::sscanf(__s, "%"I64_FMT"d%c", &__v, &__c) != 1)
        {
            throw syntax_error("Not a valid integer", __s);
        }
        return __v;
    }

    template <> uint64_t char_traits<char>::as_uint64(const char_type* __s)
    {
        uint64_t __v = 0;
        char __c;
        if (std::sscanf(__s, "%"I64_FMT"u%c", &__v, &__c) != 1)
        {
            throw syntax_error("Not a valid unsigned integer", __s);
        }
        return __v;
    }

    template <> uint64_t char_traits<char>::as_hex64(const char_type* __s)
    {
        uint64_t __v = 0;
        char __c;
        if (std::sscanf(__s, "%"I64_FMT"x%c", &__v, &__c) != 1)
        {
		    throw syntax_error("Not a valid hexadecimal integer", __s);
        }
        return __v;
    }

    template <> double char_traits<char>::as_double(const char_type* __s)
    {
        double __v = 0.00;
    	std::stringstream __istr(__s);
    	__istr.imbue(std::locale::classic());
    	__istr >> __v;
        if (!__istr.eof() || __istr.fail())
        {
		    throw syntax_error("Not a valid floating-point number", __s);
        }
        return __v;
    }

    template <> int char_traits<char>::scanf (const char_type* __s, const char_type* __fmt, ...)
    {
        int __r;
        va_list __args;
        va_start(__args, __fmt);
        __r = vsscanf(__s, __fmt, __args);
        va_end(__args);
        return __r;
    }

    template <> int char_traits<char>::vscanf(const char_type* __s, const char_type* __fmt, va_list __args)
    {
#if defined(ufc_os_family_windows)
        return vsscanf(__s, __fmt, __args);
#else
        va_list __copy_args;
        va_copy(__copy_args, __args);
        return vsscanf(__s, __fmt, __copy_args);
#endif
    }

    template <> int char_traits<char>::printf (char_type* __buf, std::size_t __n, const char_type* __fmt, ...)
    {
        int __r;
        va_list __args;
        va_start(__args, __fmt);
        __r = vsnprintf(__buf, __n, __fmt, __args);
        va_end(__args);
        return __r;
    }

    template <> int char_traits<char>::vprintf(char_type* __buf, std::size_t __n, const char_type* __fmt, va_list __args)
    {
#if defined(ufc_os_family_windows)
        return vsnprintf(__buf, __n, __fmt, __args);
#else
        va_list __copy_args;
        va_copy(__copy_args, __args);
        return vsnprintf(__buf, __n, __fmt, __copy_args);
#endif
    }
    ///////////////////////////////////////////////////////////////////////////////////////

    template <> const char_traits<wchar_t>::char_type char_traits<wchar_t>::space_char = L' ';


    template <> int char_traits<wchar_t>::icompare(const char_type* __s1, const char_type* __s2)
    {
#if defined(ufc_os_family_windows)
        return wcsicmp(__s1, __s2);
#else
        return wcscasecmp(__s1, __s2);
#endif
    }

    template <> int char_traits<wchar_t>::icompare(const char_type* __s1, const char_type* __s2, std::size_t __n)
    {
#if defined(ufc_os_family_windows)
        return wcsnicmp(__s1, __s2, __n);
#else
        return wcsncasecmp(__s1, __s2, __n);
#endif
    }

    template <> bool char_traits<wchar_t>::is_alnum(char_type __c)
    {
        return iswalnum(__c);
    }

    template <> bool char_traits<wchar_t>::is_alpha(char_type __c)
    {
        return iswalpha(__c);
    }

    template <> bool char_traits<wchar_t>::is_cntrl(char_type __c)
    {
        return iswcntrl(__c);
    }

    template <> bool char_traits<wchar_t>::is_digit(char_type __c)
    {
        return iswdigit(__c);
    }

    template <> bool char_traits<wchar_t>::is_xdigit(char_type __c)
    {
        return iswxdigit(__c);
    }

    template <> bool char_traits<wchar_t>::is_graph(char_type __c)
    {
        return iswgraph(__c);
    }

    template <> bool char_traits<wchar_t>::is_lower(char_type __c)
    {
        return iswlower(__c);
    }

    template <> bool char_traits<wchar_t>::is_print(char_type __c)
    {
        return iswprint(__c);
    }

    template <> bool char_traits<wchar_t>::is_punct(char_type __c)
    {
        return iswpunct(__c);
    }

    template <> bool char_traits<wchar_t>::is_space(char_type __c)
    {
        return iswspace(__c);
    }

    template <> bool char_traits<wchar_t>::is_upper(char_type __c)
    {
        return iswupper(__c);
    }

    template <> bool char_traits<wchar_t>::is_blank(char_type __c)
    {
        return iswblank(__c);
    }

    template <> bool char_traits<wchar_t>::is_boolean(const char_type* __s)
    {
        if (icompare(__s, L"true") == 0)
            return true;
        else if (icompare(__s, L"yes") == 0)
            return true;
        else if (icompare(__s, L"on") == 0)
            return true;
        else if (icompare(__s, L"false") == 0)
            return true;
        else if (icompare(__s, L"no") == 0)
            return true;
        else if (icompare(__s, L"off") == 0)
            return true;
        else
            return false;
    }

    template <> bool char_traits<wchar_t>::is_decimal(const char_type* __s)
    {
        if (__s && __s[0] != 0)
        {
            bool __dot_flag = false;
            if (*__s == L'+' || *__s == L'-') ++__s;
            if (*__s == L'.')
            {
                ++__s;
                if (!isdigit(*__s)) return false;
                __dot_flag = true;
            }
            for (; *__s; ++__s)
            {
                if (!iswdigit(*__s) && *__s != L'.')
                {
                    return false;
                }
                if (*__s == L'.' && __dot_flag)
                {
                    if (__dot_flag) return false;
                    __dot_flag = true;
                }
            }
            return true;
        }
        return false;
    }

    template <> char_traits<wchar_t>::char_type char_traits<wchar_t>::to_lower(char_type __c)
    {
        return towlower(__c);
    }

    template <> char_traits<wchar_t>::char_type char_traits<wchar_t>::to_upper(char_type __c)
    {
        return towupper(__c);
    }

    template <> bool char_traits<wchar_t>::as_boolean(const char_type* __s)
    {
        if (icompare(__s, L"true") == 0)
            return true;
        else if (icompare(__s, L"yes") == 0)
            return true;
        else if (icompare(__s, L"on") == 0)
            return true;
        else if (icompare(__s, L"false") == 0)
            return false;
        else if (icompare(__s, L"no") == 0)
            return false;
        else if (icompare(__s, L"off") == 0)
            return false;
        else
            throw syntax_error("Not a valid boolean", codecvt::instance().wcstombs(__s));
    }

    template <> int char_traits<wchar_t>::as_int32(const char_type* __s)
    {
        int __v = 0;
        char __c;
        if (std::swscanf(__s, L"%d%c", &__v, &__c) != 1)
        {
            throw syntax_error("Not a valid integer", codecvt::instance().wcstombs(__s));
        }
        return __v;
    }

    template <> unsigned char_traits<wchar_t>::as_uint32(const char_type* __s)
    {
        unsigned __v = 0;
        char __c;
        if (std::swscanf(__s, L"%u%c", &__v, &__c) != 1)
        {
            throw syntax_error("Not a valid unsigned integer", codecvt::instance().wcstombs(__s));
        }
        return __v;
    }

    template <> unsigned char_traits<wchar_t>::as_hex32(const char_type* __s)
    {
        unsigned __v = 0;
        char __c;
        if (std::swscanf(__s, L"%x%c", &__v, &__c) != 1)
        {
		    throw syntax_error("Not a valid hexadecimal integer", codecvt::instance().wcstombs(__s));
        }
        return __v;
    }

    template <> int64_t char_traits<wchar_t>::as_int64(const char_type* __s)
    {
        int64_t __v = 0;
        char __c;
        if (std::swscanf(__s, L"%"I64_FMT"d%c", &__v, &__c) != 1)
        {
            throw syntax_error("Not a valid integer", codecvt::instance().wcstombs(__s));
        }
        return __v;
    }

    template <> uint64_t char_traits<wchar_t>::as_uint64(const char_type* __s)
    {
        uint64_t __v = 0;
        char __c;
        if (std::swscanf(__s, L"%"I64_FMT"u%c", &__v, &__c) != 1)
        {
            throw syntax_error("Not a valid unsigned integer", codecvt::instance().wcstombs(__s));
        }
        return __v;
    }

    template <> uint64_t char_traits<wchar_t>::as_hex64(const char_type* __s)
    {
        uint64_t __v = 0;
        char __c;
        if (std::swscanf(__s, L"%"I64_FMT"x%c", &__v, &__c) != 1)
        {
		    throw syntax_error("Not a valid hexadecimal integer", codecvt::instance().wcstombs(__s));
        }
        return __v;
    }

    template <> double char_traits<wchar_t>::as_double(const char_type* __s)
    {
        double __v = 0.00;
    	std::wstringstream __istr(__s);
    	__istr.imbue(std::locale::classic());
    	__istr >> __v;
        if (!__istr.eof() || __istr.fail())
        {
		    throw syntax_error("Not a valid floating-point number", codecvt::instance().wcstombs(__s));
        }
        return __v;
    }

    template <> int char_traits<wchar_t>::scanf (const char_type* __s, const char_type* __fmt, ...)
    {
        int __r;
        va_list __args;
        va_start(__args, __fmt);
        __r = vswscanf(__s, __fmt, __args);
        va_end(__args);
        return __r;
    }

    template <> int char_traits<wchar_t>::vscanf(const char_type* __s, const char_type* __fmt, va_list __args)
    {
#if defined(ufc_os_family_windows)
        return vswscanf(__s, __fmt, __args);
#else
        va_list __copy_args;
        va_copy(__copy_args, __args);
        return vswscanf(__s, __fmt, __copy_args);
#endif
    }

    template <> int char_traits<wchar_t>::printf (char_type* __buf, std::size_t __n, const char_type* __fmt, ...)
    {
        int __r;
        va_list __args;
        va_start(__args, __fmt);
        __r = vswprintf(__buf, __n, __fmt, __args);
        va_end(__args);
        return __r;
    }

    template <> int char_traits<wchar_t>::vprintf(char_type* __buf, std::size_t __n, const char_type* __fmt, va_list __args)
    {
#if defined(ufc_os_family_windows)
        return vswprintf(__buf, __n, __fmt, __args);
#else
        va_list __copy_args;
        va_copy(__copy_args, __args);
        return vswprintf(__buf, __n, __fmt, __copy_args);
#endif
    }
    ///////////////////////////////////////////////////////////////////////////////////////

    template <class CharT>
    basic_string<CharT>& __build_in_replace(basic_string<CharT>& __str, 
                                            typename basic_string<CharT>::value_type __oldc, 
                                            typename basic_string<CharT>::value_type __newc, 
                                            typename basic_string<CharT>::size_type& __rc)
    {
        __rc = 0;
        for (typename basic_string<CharT>::iterator __it = __str.begin(); 
            __it != __str.end(); __it++)
        {
            if (*__it == __oldc)
            {
                *__it = __newc;
                ++__rc;
            }
        }
    }

    template <class CharT>
    basic_string<CharT>& __build_in_replace(basic_string<CharT>& __str, 
                                            typename basic_string<CharT>::super_type __oldstr, 
                                            typename basic_string<CharT>::super_type __newstr, 
                                            typename basic_string<CharT>::size_type& __rc)
    {
        __rc = 0;
        if (!__oldstr.empty())
        {
            basic_string<CharT> __tmpstr(__str);
            __str.clear();

            typename basic_string<CharT>::size_type __pos = 0, __begpos = 0;
            do 
            {
                __pos = __tmpstr.find(__oldstr, __begpos);
                if (__pos != basic_string<CharT>::npos)
                {
                    __str += __tmpstr.substr(__begpos, __pos - __begpos);
                    __str += __newstr;

                    __begpos = __pos + __oldstr.length();
                    __rc++;
                }
            } 
            while (__pos != basic_string<CharT>::npos);

            if (__begpos < (__tmpstr.length() + 1))
            {
                __str += __tmpstr.substr(__begpos, __tmpstr.length() - __begpos);
            }
        }
        return __str;
    }

    template <class CharT>
    basic_string<CharT>& __build_in_make_upper(basic_string<CharT>& __str)
    {
        typename basic_string<CharT>::iterator __it  = __str.begin();
        typename basic_string<CharT>::iterator __end = __str.end();
        for (; __it != __end; ++__it)
        {
            *__it = basic_string<CharT>::traits_type::to_upper(*__it);
        }
        return __str;
    }

    template <class CharT>
    basic_string<CharT>& __build_in_make_lower(basic_string<CharT>& __str)
    {
        typename basic_string<CharT>::iterator __it  = __str.begin();
        typename basic_string<CharT>::iterator __end = __str.end();
        for (; __it != __end; ++__it)
        {
            *__it = basic_string<CharT>::traits_type::to_lower(*__it);
        }
        return __str;
    }

    template <class CharT>
    basic_string<CharT>& __build_in_make_reverse(basic_string<CharT>& __str)
    {
        typename basic_string<CharT>::size_type __n = __str.length();
        typename basic_string<CharT>::size_type __m = __n / 2;
        for (typename basic_string<CharT>::size_type __i = 0; __i < __m; __i++)
        {
            std::swap(__str[__i], __str[__n - __i - 1]);
        }
        return __str;
    }

    template <class CharT>
    basic_string<CharT>& __build_in_remove_extra_space(basic_string<CharT>& __str)
    {
        __str.trim();

        basic_string<CharT> __tmp(__str);
        __str.clear();

        bool __space_flag = false;
        typename basic_string<CharT>::const_iterator __it  = __tmp.begin();
        typename basic_string<CharT>::const_iterator __end = __tmp.end();
        for (;__it != __end; __it++)
        {
            if (basic_string<CharT>::traits_type::is_space(*__it))
            {
                if (!__space_flag)
                {
                    __space_flag = true;
                    __str.append(1, basic_string<CharT>::traits_type::space_char);
                }
            }
            else
            {
                __space_flag = false;
                __str.append(1, *__it);
            }
        }
        return __str;
    }

    template <class CharT>
    basic_string<CharT>& __build_in_trim_left(basic_string<CharT>& __str)
    {
        typename basic_string<CharT>::iterator __it  = __str.begin();
        typename basic_string<CharT>::iterator __end = __str.end();
        while (__it != __end 
            && basic_string<CharT>::traits_type::is_space(*__it)) 
        {
            ++__it;
        }
        __str.erase(__str.begin(), __it);
        return __str;
    }

    template <class CharT>
    basic_string<CharT>& __build_in_trim_right(basic_string<CharT>& __str)
    {
        int __pos = __str.length() - 1;
        while (__pos >= 0 && basic_string<CharT>::traits_type::is_space(__str[__pos]))
        {
            --__pos;
        }
        __str.resize(__pos + 1);
        return __str;
    }

    template <class CharT>
    basic_string<CharT>& __build_in_vprintf(basic_string<CharT>& __str, 
                                            typename basic_string<CharT>::const_pointer __fmt, 
                                            va_list __args)
    {
        __str.clear();
        if (__fmt && __fmt[0] != '\0')
        {
            typename basic_string<CharT>::super_type __tmp;
            __tmp.reserve(1024);
            for (;;)
            {
                int __r = basic_string<CharT>::traits_type::vprintf(const_cast<typename basic_string<CharT>::pointer>(__tmp.data()), __tmp.capacity(), __fmt, __args);
                if (__r >= 0 && __r < (int)__tmp.capacity())
                {
                    __str.assign(__tmp.data(), __r);
                    break;
                }
                else if (__r >= (int)__tmp.capacity())
                    __tmp.reserve(__r + 1);
                else
                    __tmp.reserve(__tmp.capacity() * 2 + 1);
            }
        }
        return __str;
    }

    template <class CharT>
    int __build_in_vscanf(const basic_string<CharT>& __str, 
                          typename basic_string<CharT>::const_pointer __fmt, 
                          va_list __args)
    {
        return basic_string<CharT>::traits_type::vscanf(__str.c_str(), __fmt, __args);
    }

    template <class CharT>
    typename basic_string<CharT>::size_type __build_in_count(const basic_string<CharT>& __str, 
                                                             typename basic_string<CharT>::value_type __c)
    {
        typename basic_string<CharT>::size_type __result = 0;
        typename basic_string<CharT>::const_iterator __it  = __str.begin();
        typename basic_string<CharT>::const_iterator __end = __str.end();
        for (; __it != __end; __it++)
        {
            if (__c == *__it)
            {
                ++__result;
            }
        }
        return __result;
    }

    template <class CharT>
    typename basic_string<CharT>::size_type __build_in_count(const basic_string<CharT>& __str, 
                                                             typename basic_string<CharT>::super_type __substr)
    {
        typename basic_string<CharT>::size_type __res = 0;
        typename basic_string<CharT>::size_type __pos = 0;
        for (;;)
        {
            __pos = __str.find(__substr, __pos);
            if (__pos != basic_string<CharT>::npos)
            {
                __res ++;
                __pos += 1;
            }
        }
        return __res;
    }

    template <class CharT>
    bool __build_in_is_digit(const basic_string<CharT>& __str)
    {
        if (!__str.empty())
        {
            typename basic_string<CharT>::const_iterator __it  = __str.begin();
            typename basic_string<CharT>::const_iterator __end = __str.end();
            for (; __it != __end; __it++)
            {
                if (!basic_string<CharT>::traits_type::is_digit(*__it))
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    template <class CharT>
    bool __build_in_is_xdigit(const basic_string<CharT>& __str)
    {
        if (!__str.empty())
        {
            typename basic_string<CharT>::const_iterator __it  = __str.begin();
            typename basic_string<CharT>::const_iterator __end = __str.end();
            for (; __it != __end; __it++)
            {
                if (!basic_string<CharT>::traits_type::is_xdigit(*__it))
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    template <class CharT>
    bool __build_in_is_decimal(const basic_string<CharT>& __str)
    {
        if (!__str.empty())
        {
            return basic_string<CharT>::traits_type::is_decimal(__str.c_str());
        }
        return false;
    }

    template <class CharT>
    bool __build_in_is_boolean(const basic_string<CharT>& __str)
    {
        if (!__str.empty())
        {
            if (__str.is_digit())
                return true;
            else if (__str.is_xdigit())
                return true;
            else
                return basic_string<CharT>::traits_type::is_boolean(__str.c_str());
        }
        return false;
    }

    template <class CharT>
    int __build_in_as_int32(const basic_string<CharT>& __str)
    {
        return basic_string<CharT>::traits_type::as_int32(__str.c_str());
    }

    template <class CharT>
    unsigned __build_in_as_uint32(const basic_string<CharT>& __str)
    {
        return basic_string<CharT>::traits_type::as_uint32(__str.c_str());
    }

    template <class CharT>
    unsigned __build_in_as_hex32(const basic_string<CharT>& __str)
    {
        return basic_string<CharT>::traits_type::as_hex32(__str.c_str());
    }

    template <class CharT>
    int64_t __build_in_as_int64(const basic_string<CharT>& __str)
    {
        return basic_string<CharT>::traits_type::as_int64(__str.c_str());
    }

    template <class CharT>
    uint64_t __build_in_as_uint64(const basic_string<CharT>& __str)
    {
        return basic_string<CharT>::traits_type::as_uint64(__str.c_str());
    }

    template <class CharT>
    uint64_t __build_in_as_hex64(const basic_string<CharT>& __str)
    {
        return basic_string<CharT>::traits_type::as_hex64(__str.c_str());
    }

    template <class CharT>
    double __build_in_as_double(const basic_string<CharT>& __str)
    {
        return basic_string<CharT>::traits_type::as_double(__str.c_str());
    }

    template <class CharT>
    bool __build_in_as_boolean(const basic_string<CharT>& __str)
    {
        if (__str.is_digit())
            return (__str.as_int32() != 0);
        else if (__str.is_xdigit())
            return (__str.as_hex32() != 0);
        else
            return basic_string<CharT>::traits_type::as_boolean(__str.c_str());
    }
    ///////////////////////////////////////////////////////////////////////////////////////


    template <> basic_string<char>& basic_string<char>::replace(value_type __oldc, value_type __newc, size_type& __rc)
    {
        return __build_in_replace(*this, __oldc, __newc, __rc);
    }

    template <> basic_string<wchar_t>& basic_string<wchar_t>::replace(value_type __oldc, value_type __newc, size_type& __rc)
    {
        return __build_in_replace(*this, __oldc, __newc, __rc);
    }

    template <> basic_string<char>& basic_string<char>::replace(const super_type& __oldstr, const super_type& __newstr, size_type& __rc)
    {
        return __build_in_replace(*this, __oldstr, __newstr, __rc);
    }

    template <> basic_string<wchar_t>& basic_string<wchar_t>::replace(const super_type& __oldstr, const super_type& __newstr, size_type& __rc)
    {
        return __build_in_replace(*this, __oldstr, __newstr, __rc);
    }

    template <> basic_string<char>& basic_string<char>::make_upper()
    {
        return __build_in_make_upper(*this);
    }
    
    template <> basic_string<wchar_t>& basic_string<wchar_t>::make_upper()
    {
        return __build_in_make_upper(*this);
    }
    
    template <> basic_string<char>& basic_string<char>::make_lower()
    {
        return __build_in_make_lower(*this);
    }

    template <> basic_string<wchar_t>& basic_string<wchar_t>::make_lower()
    {
        return __build_in_make_lower(*this);
    }

    template <> basic_string<char>& basic_string<char>::make_reverse()
    {
        return __build_in_make_reverse(*this);
    }

    template <> basic_string<wchar_t>& basic_string<wchar_t>::make_reverse()
    {
        return __build_in_make_reverse(*this);
    }

    template <> basic_string<char>& basic_string<char>::remove_extra_space()
    {
        return __build_in_remove_extra_space(*this);
    }

    template <> basic_string<wchar_t>& basic_string<wchar_t>::remove_extra_space()
    {
        return __build_in_remove_extra_space(*this);
    }

    template <> basic_string<char>& basic_string<char>::trim_right()
    {
        return __build_in_trim_right(*this);
    }
 
    template <> basic_string<wchar_t>& basic_string<wchar_t>::trim_right()
    {
        return __build_in_trim_right(*this);
    }

    template <> basic_string<char>& basic_string<char>::trim_left()
    {
        return __build_in_trim_left(*this);
    }

    template <> basic_string<wchar_t>& basic_string<wchar_t>::trim_left()
    {
        return __build_in_trim_left(*this);
    }
 
    template <> int basic_string<char>::vscanf(const_pointer __fmt, va_list __args) const
    {
        return __build_in_vscanf(*this, __fmt, __args);
    }

    template <> int basic_string<wchar_t>::vscanf(const_pointer __fmt, va_list __args) const
    {
        return __build_in_vscanf(*this, __fmt, __args);
    }

    template <> basic_string<char>& basic_string<char>::vprintf(const_pointer __fmt, va_list __args)
    {
        return __build_in_vprintf(*this, __fmt, __args);
    }
 
    template <> basic_string<wchar_t>& basic_string<wchar_t>::vprintf(const_pointer __fmt, va_list __args)
    {
        return __build_in_vprintf(*this, __fmt, __args);
    }

    template <> basic_string<char>::size_type basic_string<char>::count(value_type __c) const
    {
        return __build_in_count(*this, __c);
    }

    template <> basic_string<wchar_t>::size_type basic_string<wchar_t>::count(value_type __c) const
    {
        return __build_in_count(*this, __c);
    }

    template <> basic_string<char>::size_type basic_string<char>::count(const super_type& __substr) const
    {
        return __build_in_count(*this, __substr);
    }

    template <> basic_string<wchar_t>::size_type basic_string<wchar_t>::count(const super_type& __substr) const
    {
        return __build_in_count(*this, __substr);
    }

    template <> bool basic_string<wchar_t>::has(const super_type& __str, size_type __pos) const
    {
        return super_type::find(__str, __pos) != npos;
    }

    template <> bool basic_string<wchar_t>::has(const value_type& __c, size_type __pos) const
    {
        return super_type::find(__c, __pos) != npos;
    }

    template <> bool basic_string<char>::has(const super_type& __str, size_type __pos) const
    {
        return super_type::find(__str, __pos) != npos;
    }

    template <> bool basic_string<char>::has(const value_type& __c, size_type __pos) const
    {
        return super_type::find(__c, __pos) != npos;
    }

    template <> bool basic_string<char>::is_digit() const
    {
        return __build_in_is_digit(*this);
    }

    template <> bool basic_string<wchar_t>::is_digit() const
    {
        return __build_in_is_digit(*this);
    }

    template <> bool basic_string<char>::is_xdigit() const
    {
        return __build_in_is_xdigit(*this);
    }

    template <> bool basic_string<wchar_t>::is_xdigit() const
    {
        return __build_in_is_xdigit(*this);
    }

    template <> bool basic_string<char>::is_decimal() const
    {
        return __build_in_is_decimal(*this);
    }

    template <> bool basic_string<wchar_t>::is_decimal() const
    {
        return __build_in_is_decimal(*this);
    }

    template <> bool basic_string<char>::is_boolean() const
    {
        return __build_in_is_boolean(*this);
    }

    template <> bool basic_string<wchar_t>::is_boolean() const
    {
        return __build_in_is_boolean(*this);
    }

    template <> int basic_string<char>::as_int32() const
    {
        return __build_in_as_int32(*this);
    }

    template <> int basic_string<wchar_t>::as_int32() const
    {
        return __build_in_as_int32(*this);
    }

    template <> unsigned basic_string<char>::as_uint32() const
    {
        return __build_in_as_uint32(*this);
    }

    template <> unsigned basic_string<wchar_t>::as_uint32() const
    {
        return __build_in_as_uint32(*this);
    }

    template <> unsigned basic_string<char>::as_hex32() const
    {
        return __build_in_as_hex32(*this);
    }

    template <> unsigned basic_string<wchar_t>::as_hex32() const
    {
        return __build_in_as_hex32(*this);
    }

    template <> int64_t basic_string<char>::as_int64() const
    {
        return __build_in_as_int64(*this);
    }

    template <> int64_t basic_string<wchar_t>::as_int64() const
    {
        return __build_in_as_int64(*this);
    }

    template <> uint64_t basic_string<char>::as_uint64() const
    {
        return __build_in_as_uint64(*this);
    }

    template <> uint64_t basic_string<wchar_t>::as_uint64() const
    {
        return __build_in_as_uint64(*this);
    }

    template <> uint64_t basic_string<char>::as_hex64() const
    {
        return __build_in_as_hex64(*this);
    }

    template <> uint64_t basic_string<wchar_t>::as_hex64() const
    {
        return __build_in_as_hex64(*this);
    }

    template <> double basic_string<char>::as_double() const
    {
        return __build_in_as_double(*this);
    }

    template <> double basic_string<wchar_t>::as_double() const
    {
        return __build_in_as_double(*this);
    }

    template <> bool basic_string<char>::as_boolean() const
    {
        return __build_in_as_boolean(*this);
    }

    template <> bool basic_string<wchar_t>::as_boolean() const
    {
        return __build_in_as_boolean(*this);
    }

}//namespace ufc
