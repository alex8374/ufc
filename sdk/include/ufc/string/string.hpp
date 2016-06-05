/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/string/string.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-21
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_STRING_STRING_HPP
#define UFC_STRING_STRING_HPP

#include <ufc/base/config.hpp>
#include <ufc/container/vector.hpp>
#include <string>
#include <cstdarg>

namespace ufc {

    template <class CharT>
    class char_traits: public std::char_traits<CharT>
    {
        typedef typename std::char_traits<CharT>    super_type;

    public:
        typedef typename super_type::char_type  char_type;
        typedef typename super_type::int_type   int_type;
        typedef typename super_type::off_type   off_type;
        typedef typename super_type::pos_type   pos_type;
        typedef typename super_type::state_type state_type;

        static bool is_alnum(char_type __c);
        static bool is_alpha(char_type __c);
        static bool is_cntrl(char_type __c);
        static bool is_digit(char_type __c);
        static bool is_xdigit(char_type __c);
        static bool is_graph(char_type __c);
        static bool is_lower(char_type __c);
        static bool is_print(char_type __c);
        static bool is_punct(char_type __c);
        static bool is_space(char_type __c);
        static bool is_upper(char_type __c);
        static bool is_blank(char_type __c);
        static bool is_boolean(const char_type* __s);
        static bool is_decimal(const char_type* __s);

        static char_type to_lower(char_type __c);
        static char_type to_upper(char_type __c);

        static bool     as_boolean(const char_type* __s);
        static int32_t  as_int32(const char_type* __s);
        static uint32_t as_uint32(const char_type* __s);
        static uint32_t as_hex32(const char_type* __s);
        static int64_t  as_int64(const char_type* __s);
        static uint64_t as_uint64(const char_type* __s);
        static uint64_t as_hex64(const char_type* __s);
        static double   as_double(const char_type* __s);

        static int32_t icompare(const char_type* __s1, const char_type* __s2);
        static int32_t icompare(const char_type* __s1, const char_type* __s2, std::size_t __n);

        static int32_t scanf (const char_type* __s, const char_type* __fmt, ...);
        static int32_t vscanf(const char_type* __s, const char_type* __fmt, va_list __args);

        static int32_t printf (char_type* __buf, std::size_t __n, const char_type* __fmt, ...);
        static int32_t vprintf(char_type* __buf, std::size_t __n, const char_type* __fmt, va_list __args);

        static const char_type space_char;
    };

    template <class CharT>
    class basic_string
        : virtual public object
        , public std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT> >
    {
    public:
        typedef typename std::basic_string<CharT, std::char_traits<CharT>, std::allocator<CharT> > super_type;
        typedef typename super_type::allocator_type          allocator_type;
        typedef typename super_type::size_type               size_type;
        typedef typename super_type::difference_type         difference_type;
        typedef typename super_type::value_type              value_type;
        typedef typename super_type::pointer                 pointer;
        typedef typename super_type::const_pointer           const_pointer;
        typedef typename super_type::reference               reference;
        typedef typename super_type::const_reference         const_reference;
        typedef typename super_type::iterator                iterator;
        typedef typename super_type::const_iterator          const_iterator;
        typedef typename super_type::reverse_iterator        reverse_iterator;
        typedef typename super_type::const_reverse_iterator  const_reverse_iterator;
        typedef char_traits<CharT>                           traits_type;

        using super_type::npos;

    public:
        basic_string();
        basic_string(const basic_string& __str);
        basic_string(const basic_string& __str, size_type __pos, size_type __n = npos);
        basic_string(const super_type& __str);
        basic_string(const super_type& __str, size_type __pos, size_type __n = npos);
        basic_string(const_pointer __s, size_type __n);
        basic_string(const_pointer __s);
        basic_string(size_type __n, value_type __c);
        
        template<class InputIterator>
        basic_string(InputIterator __beg, InputIterator __end)
            : super_type(__beg, __end)
        {
        }

        virtual ~basic_string();

        basic_string& operator = (const basic_string& __str);
        basic_string& operator = (const super_type& __str);
        basic_string& operator = (const_pointer __s);
        basic_string& operator = (value_type __c);

        basic_string& operator += (const basic_string& __str);
        basic_string& operator += (const super_type& __str);
        basic_string& operator += (const_pointer __s);
        basic_string& operator += (value_type __c);

        const_reference operator[] (size_type __pos) const;
        reference operator[](size_type __pos);

        operator const_pointer() const;

        basic_string& append(const super_type& __str);
        basic_string& append(const super_type& __str, size_type __pos, size_type __n);
        basic_string& append(const_pointer __s, size_type __n);
        basic_string& append(const_pointer __s);
        basic_string& append(size_type __n, value_type __c);

        template<class InputIterator>
        basic_string& append(InputIterator __first, InputIterator __last)
        {
            super_type::append(__first, __last);
            return *this;
        }

        basic_string& assign(const super_type& __str);
        basic_string& assign(const super_type& __str, size_type __pos, size_type __n);
        basic_string& assign(const_pointer __s, size_type __n);
        basic_string& assign(const_pointer __s);
        basic_string& assign(size_type __n, value_type __c);

        template<class InputIterator>
        basic_string& assign(InputIterator __first, InputIterator __last)
        {
            super_type::assign(__first, __last);
            return *this;
        }

        void insert(iterator __p, size_type __n2, value_type __c2);

        template<class InputIterator>
        void insert(iterator __p, InputIterator __first, InputIterator __last)
        {
            super_type::insert(__p, __first, __last);
        }
        basic_string& insert(size_type __pos, const super_type& __str2);
        basic_string& insert(size_type __pos, const super_type& __str2, size_type __pos2, size_type __n2);
        basic_string& insert(size_type __pos, const_pointer __s2, size_type __n2);
        basic_string& insert(size_type __pos, const_pointer __s2);
        basic_string& insert(size_type __pos, size_type __n2, value_type __c2);
        iterator insert(iterator __p, value_type __c2);

        basic_string&  erase(size_type __pos = 0, size_type __n = npos);
        iterator erase(iterator __p);
        iterator erase(iterator __first, iterator __last);

        basic_string& replace(size_type __pos, size_type __n, const super_type& __str2);
        basic_string& replace(size_type __pos, size_type __n, const super_type& __str2, size_type __pos2, size_type __n2);
        basic_string& replace(size_type __pos, size_type __n, const_pointer __s2, size_type __n2);
        basic_string& replace(size_type __pos, size_type __n, const_pointer __s2);
        basic_string& replace(size_type __pos, size_type __n, size_type __n2, value_type __c2);
        basic_string& replace(iterator __beg, iterator __end, const super_type& __str2);
        basic_string& replace(iterator __beg, iterator __end, const_pointer __s2, size_type __n2);
        basic_string& replace(iterator __beg, iterator __end, const_pointer __s2);
        basic_string& replace(iterator __beg, iterator __end, size_type __n2, value_type __c2);
        basic_string& replace(iterator __beg, iterator __end, pointer __beg2, pointer __end2);
        basic_string& replace(iterator __beg, iterator __end, const_pointer __beg2, const_pointer __end2);
        basic_string& replace(iterator __beg, iterator __end, iterator __beg2, iterator __end2);
        basic_string& replace(iterator __beg, iterator __end, const_iterator __beg2, const_iterator __end2);

        template<class InputIterator>
        basic_string& replace(iterator __beg, iterator __end, InputIterator __beg2, InputIterator __end2)
        {
            super_type::replace(__beg, __end, __beg2, __end2);
            return *this;
        }
        basic_string& replace(value_type __oldc, value_type __newc);
        basic_string& replace(value_type __oldc, value_type __newc, size_type& __rc);                   // build-in
        basic_string& replace(const super_type& __oldstr, const super_type& __newstr);
        basic_string& replace(const super_type& __oldstr, const super_type& __newstr, size_type& __rc); // build-in

        size_type find_one_of(const super_type& __ctrls, size_type __pos = 0) const; // build-in

        basic_string substr(size_type __pos = 0, size_type __n = npos) const;
        basic_string left(size_type __n) const;
        basic_string right(size_type __n) const;

        int32_t icompare(const super_type& __str2) const;
        int32_t icompare(size_type __pos, size_type __n, const super_type& __str2) const;
        int32_t icompare(size_type __pos, size_type __n, const super_type& __str2, size_type __pos2, size_type __n2) const; // build-in
        int32_t icompare(const_pointer __s2) const;
        int32_t icompare(size_type __pos, size_type __n, const_pointer __s2) const;
        int32_t icompare(size_type __pos, size_type __n, const_pointer __s2, size_type __n2) const; // build-in

        bool start_with(const super_type& __prefix) const;
        bool start_with(value_type __prefix) const;
        bool start_with_ignore_case(const super_type& __prefix) const;
        bool start_with_ignore_case(value_type __prefix) const;

        bool end_with(const super_type& __suffix) const;
        bool end_with(value_type __suffix) const;
        bool end_with_ignore_case(const super_type& __suffix) const;
        bool end_with_ignore_case(value_type __suffix) const;

        basic_string& make_upper(); // build-in
        basic_string& make_lower(); // build-in
        basic_string& make_reverse(); // build-in

        basic_string upper() const;
        basic_string lower() const;
        basic_string reverse() const;

        basic_string& remove_extra_space(); // build-in

        basic_string& trim();
        basic_string& trim_right(); // build-in
        basic_string& trim_left(); // build-in

        int32_t scanf (const_pointer __fmt, ...) const;
        int32_t vscanf(const_pointer __fmt, va_list __args) const; // build-in

        basic_string& printf (const_pointer __fmt, ...);
        basic_string& vprintf(const_pointer __fmt, va_list __args); // build-in
        basic_string& cat_printf (const_pointer __fmt, ...);
        basic_string& cat_vprintf(const_pointer __fmt, va_list __args);

        size_type count(value_type __c) const; // build-in
        size_type count(const super_type& __substr) const; // build-in

        bool has(const super_type& __str, size_type __pos = 0) const;
        bool has(const value_type& __c, size_type __pos = 0) const;

        bool is_digit() const;
        bool is_xdigit() const;
        bool is_decimal() const;
        bool is_boolean() const;

        int32_t  as_int32() const;
        uint32_t as_uint32() const;
        uint32_t as_hex32() const;
        int64_t  as_int64() const;
        uint64_t as_uint64() const;
        uint64_t as_hex64() const;
        double   as_double() const;
        bool     as_boolean() const;

    public:
        static basic_string format (const_pointer __fmt, ...);
        static basic_string vformat(const_pointer __fmt, va_list __args);
    };

    typedef basic_string<char>      string;
    typedef basic_string<wchar_t>   wstring;

    typedef vector<string>          string_vec;
    typedef vector<string>          wstring_vec;
    ////////////////////////////////////////////////////////////////////////////

    template <class CharT>
    inline basic_string<CharT>::basic_string()
    {
    }

    template <class CharT>
    inline basic_string<CharT>::basic_string(const basic_string& __str)
        : super_type(__str)
    {
    }

    template <class CharT>
    inline basic_string<CharT>::basic_string(const basic_string& __str, size_type __pos, size_type __n)
        : super_type(__str, __pos, __n)
    {
    }

    template <class CharT>
    inline basic_string<CharT>::basic_string(const super_type& __str)
        : super_type(__str)
    {
    }

    template <class CharT>
    inline basic_string<CharT>::basic_string(const super_type& __str, size_type __pos, size_type __n)
        : super_type(__str, __pos, __n)
    {
    }

    template <class CharT>
    inline basic_string<CharT>::basic_string(const_pointer __s, size_type __n)
        : super_type(__s, __n)
    {
    }

    template <class CharT>
    inline basic_string<CharT>::basic_string(const_pointer __s)
        : super_type(__s)
    {
    }

    template <class CharT>
    inline basic_string<CharT>::basic_string(size_type __n, value_type __c)
        : super_type(__n, __c)
    {
    }

    template <class CharT>
    inline basic_string<CharT>::~basic_string()
    {
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::operator = (const basic_string& __str)        
    {
        if (super_type::c_str() != __str.c_str())
        {
            super_type::operator = (__str);
        }
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::operator = (const super_type& __str)
    {
        if (super_type::c_str() != __str.c_str())
        {
            super_type::operator = (__str);
        }
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::operator = (const_pointer __s)
    {
        if (super_type::c_str() != __s)
        {
            super_type::operator = (__s);
        }
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::operator = (value_type __c)
    {
        value_type __s[2] = {__c, 0};
        super_type::operator = (__s);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::operator += (const basic_string& __str)
    {
        super_type::operator += (__str);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::operator += (const super_type& __str)
    {
        super_type::operator += (__str);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::operator += (const_pointer __s)
    {
        super_type::operator += (__s);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::operator += (value_type __c)
    {
        value_type __s[2] = {__c, 0};
        super_type::operator += (__s);
        return *this;
    }

    template <class CharT>
    inline typename basic_string<CharT>::const_reference basic_string<CharT>::operator[] (size_type __pos) const
    {
        return super_type::operator[](__pos);
    }

    template <class CharT>
    inline typename basic_string<CharT>::reference basic_string<CharT>::operator[](size_type __pos)
    {
        return super_type::operator[](__pos);
    }

    template <class CharT>
    inline basic_string<CharT>::operator typename basic_string<CharT>::const_pointer() const
    {
        return super_type::c_str();
    }
    
    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::append(const super_type& __str)
    {
        super_type::append(__str);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::append(const super_type& __str, size_type __pos, size_type __n)
    {
        super_type::append(__str, __pos, __n);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::append(const_pointer __s, size_type __n)
    {
        super_type::append(__s, __n);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::append(const_pointer __s)
    {
        super_type::append(__s);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::append(size_type __n, value_type __c)
    {
        super_type::append(__n, __c);
        return *this;
    }
    
    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::assign(const super_type& __str)
    {
        super_type::assign(__str);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::assign(const super_type& __str, size_type __pos, size_type __n)
    {
        super_type::assign(__str, __pos, __n);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::assign(const_pointer __s, size_type __n)
    {
        super_type::assign(__s, __n);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::assign(const_pointer __s)
    {
        super_type::assign(__s);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::assign(size_type __n, value_type __c)
    {
        super_type::assign(__n, __c);
        return *this;
    }
    
    template <class CharT>
    inline void basic_string<CharT>::insert(iterator __p, size_type __n2, value_type __c2)
    {
        super_type::insert(__p, __n2, __c2);
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::insert(size_type __pos, const super_type& __str2)
    {
        super_type::insert(__pos, __str2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::insert(size_type __pos, const super_type& __str2, size_type __pos2, size_type __n2)
    {
        super_type::insert(__pos, __str2, __pos2, __n2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::insert(size_type __pos, const_pointer __s2, size_type __n2)
    {
        super_type::insert(__pos, __s2, __n2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::insert(size_type __pos, const_pointer __s2)
    {
        super_type::insert(__pos, __s2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::insert(size_type __pos, size_type __n2, value_type __c2)
    {
        super_type::insert(__pos, __n2, __c2);
        return *this;
    }

    template <class CharT>
    inline typename basic_string<CharT>::iterator basic_string<CharT>::insert(iterator __p, value_type __c2)
    {
        return super_type::insert(__p, __c2);
    }
    
    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::erase(size_type __pos, size_type __n)
    {
        super_type::erase(__pos, __n);
        return *this;
    }

    template <class CharT>
    inline typename basic_string<CharT>::iterator basic_string<CharT>::erase(iterator __p)
    {
        return super_type::erase(__p);
    }

    template <class CharT>
    inline typename basic_string<CharT>::iterator basic_string<CharT>::erase(iterator __first, iterator __last)
    {
        return super_type::erase(__first, __last);
    }
    
    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(size_type __pos, size_type __n, const super_type& __str2)
    {
        super_type::replace(__pos, __n, __str2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(size_type __pos, size_type __n, const super_type& __str2, size_type __pos2, size_type __n2)
    {
        super_type::replace(__pos, __n, __str2, __pos2, __n2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(size_type __pos, size_type __n, const_pointer __s2, size_type __n2)
    {
        super_type::replace(__pos, __n, __s2, __n2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(size_type __pos, size_type __n, const_pointer __s2)
    {
        super_type::replace(__pos, __n, __s2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(size_type __pos, size_type __n, size_type __n2, value_type __c2)
    {
        super_type::replace(__pos, __n, __n2, __c2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(iterator __beg, iterator __end, const super_type& __str2)
    {
        super_type::replace(__beg, __end, __str2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(iterator __beg, iterator __end, const_pointer __s2, size_type __n2)
    {
        super_type::replace(__beg, __end, __s2, __n2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(iterator __beg, iterator __end, const_pointer __s2)
    {
        super_type::replace(__beg, __end, __s2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(iterator __beg, iterator __end, size_type __n2, value_type __c2)
    {
        super_type::replace(__beg, __end, __n2, __c2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(iterator __beg, iterator __end, pointer __beg2, pointer __end2)
    {
        super_type::replace(__beg, __end, __beg2, __end2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(iterator __beg, iterator __end, const_pointer __beg2, const_pointer __end2)
    {
        super_type::replace(__beg, __end, __beg2, __end2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(iterator __beg, iterator __end, iterator __beg2, iterator __end2)
    {
        super_type::replace(__beg, __end, __beg2, __end2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(iterator __beg, iterator __end, const_iterator __beg2, const_iterator __end2)
    {
        super_type::replace(__beg, __end, __beg2, __end2);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(value_type __oldc, value_type __newc)
    {
        size_type __n;
        return this->replace(__oldc, __newc, __n);
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::replace(const super_type& __oldstr, const super_type& __newstr)
    {
        size_type __n;
        return this->replace(__oldstr, __newstr, __n);
    }

    template <class CharT>
    inline basic_string<CharT> basic_string<CharT>::substr(size_type __pos, size_type __n) const
    {
        return super_type::substr(__pos, __n);
    }

    template <class CharT>
    inline basic_string<CharT> basic_string<CharT>::left(size_type __n) const
    {
        if (__n >= super_type::length())
            return *this;
        else
            return super_type::substr(0, __n);
    }

    template <class CharT>
    inline basic_string<CharT> basic_string<CharT>::right(size_type __n) const
    {
        if (__n >= super_type::length())
            return *this;
        else
            return super_type::substr(super_type::length() - __n, __n);
    }

    template <class CharT>
    inline int32_t basic_string<CharT>::icompare(const super_type& __str2) const
    {
        return icompare(0, super_type::length(), __str2.c_str(), __str2.length());
    }

    template <class CharT>
    inline int32_t basic_string<CharT>::icompare(size_type __pos, size_type __n, const super_type& __str2) const
    {
        return icompare(__pos, __n, __str2.c_str(), __str2.length());
    }

    template <class CharT>
    inline int32_t basic_string<CharT>::icompare(const_pointer __s2) const
    {
        return traits_type::icompare(super_type::c_str(), __s2);
    }

    template <class CharT>
    inline int32_t basic_string<CharT>::icompare(size_type __pos, size_type __n, const_pointer __s2) const
    {
        return icompare(__pos, __n, __s2, __s2? traits_type::length(__s2): 0);
    }

    template <class CharT>
    inline bool basic_string<CharT>::start_with(const super_type& __prefix) const
    {
        if (__prefix.length() > super_type::length()) 
            return false;
        else
            return super_type::compare(0, __prefix.length(), __prefix.c_str(), __prefix.length()) == 0;
    }

    template <class CharT>
    inline bool basic_string<CharT>::start_with(value_type __prefix) const
    {
        if (super_type::empty())
            return false;
        else
            return super_type::at(0) == __prefix;
    }

    template <class CharT>
    inline bool basic_string<CharT>::start_with_ignore_case(const super_type& __prefix) const
    {
        if (__prefix.length() > super_type::length()) 
            return false;
        else
            return icompare(0, __prefix.length(), __prefix.c_str(), __prefix.length()) == 0;
    }

    template <class CharT>
    inline bool basic_string<CharT>::start_with_ignore_case(value_type __prefix) const
    {
        if (super_type::empty())
            return false;
        else
            return traits_type::to_lower(super_type::at(0)) == traits_type::to_lower(__prefix);
    }

    template <class CharT>
    inline bool basic_string<CharT>::end_with(const super_type& __suffix) const
    {
        size_type __len  = super_type::length();
        size_type __len2 = __suffix.length();
        if (__len2 > __len) 
            return false;
        else
            return super_type::compare(__len - __len2, __len2, __suffix.c_str(), __len2) == 0;
    }

    template <class CharT>
    inline bool basic_string<CharT>::end_with(value_type __suffix) const
    {
        if (super_type::empty())
            return false;
        else
            return super_type::at(super_type::length() - 1) == __suffix;
    }

    template <class CharT>
    inline bool basic_string<CharT>::end_with_ignore_case(const super_type& __suffix) const
    {
        size_type __len  = super_type::length();
        size_type __len2 = __suffix.length();
        if (__len2 > __len) 
            return false;
        else
            return icompare(__len - __len2, __len2, __suffix.c_str(), __len2) == 0;
    }

    template <class CharT>
    inline bool basic_string<CharT>::end_with_ignore_case(value_type __suffix) const
    {
        if (super_type::empty())
            return false;
        else
            return traits_type::to_lower(super_type::at(super_type::length() - 1)) == traits_type::to_lower(__suffix);
    }

    template <class CharT>
    inline basic_string<CharT> basic_string<CharT>::upper() const
    {
        return basic_string(*this).make_upper();
    }

    template <class CharT>
    inline basic_string<CharT> basic_string<CharT>::lower() const
    {
        return basic_string(*this).make_lower();
    }

    template <class CharT>
    inline basic_string<CharT> basic_string<CharT>::reverse() const
    {
        return basic_string(*this).make_reverse();
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::trim()
    {
        return trim_right().trim_left();
    }

    template <class CharT>
    inline int32_t basic_string<CharT>::scanf(const_pointer __fmt, ...) const
    {
        va_list __args;
        va_start(__args, __fmt);
        int32_t __res = this->vscanf(__fmt, __args);
        va_end(__args);
        return __res;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::printf (const_pointer __fmt, ...)
    {
        va_list __args;
        va_start(__args, __fmt);
        this->vprintf(__fmt, __args);
        va_end(__args);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::cat_printf (const_pointer __fmt, ...)
    {
        va_list __args;
        va_start(__args, __fmt);
        *this += string().vprintf(__fmt, __args);
        va_end(__args);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT>& basic_string<CharT>::cat_vprintf(const_pointer __fmt, va_list __args)
    {
        *this += basic_string().vprintf(__fmt, __args);
        return *this;
    }

    template <class CharT>
    inline basic_string<CharT> basic_string<CharT>::format(const_pointer __fmt, ...)
    {
        basic_string __res;
        va_list __args;
        va_start(__args, __fmt);
        __res.vprintf(__fmt, __args);
        va_end(__args);
        return __res;
    }

    template <class CharT>
    inline basic_string<CharT> basic_string<CharT>::vformat(const_pointer __fmt, va_list __args)
    {
        return basic_string().vprintf(__fmt, __args);
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template <class CharT>
    inline basic_string<CharT> operator + (const basic_string<CharT>& __lhs, const basic_string<CharT>& __rhs)
    {
        basic_string<CharT> __res(__lhs);
        __res += __rhs;
        return __res;
    }

    template <class CharT>
    inline basic_string<CharT> operator + (const basic_string<CharT>& __lhs, const typename basic_string<CharT>::super_type& __rhs)
    {
        basic_string<CharT> __res(__lhs);
        __res += __rhs;
        return __res;
    }

    template <class CharT>
    inline basic_string<CharT> operator + (const typename basic_string<CharT>::super_type& __lhs, const basic_string<CharT>& __rhs)
    {
        basic_string<CharT> __res(__lhs);
        __res += __rhs;
        return __res;
    }

    template <class CharT>
    inline basic_string<CharT> operator + (const basic_string<CharT>& __lhs, typename basic_string<CharT>::pointer __rhs)
    {
        basic_string<CharT> __res(__lhs);
        __res += __rhs;
        return __res;
    }

    template <class CharT>
    inline basic_string<CharT> operator + (typename basic_string<CharT>::pointer __lhs, const basic_string<CharT>& __rhs)
    {
        basic_string<CharT> __res(__lhs);
        __res += __rhs;
        return __res;
    }

    template <class CharT>
    inline basic_string<CharT> operator + (const basic_string<CharT>& __lhs, typename basic_string<CharT>::const_pointer __rhs)
    {
        basic_string<CharT> __res(__lhs);
        __res += __rhs;
        return __res;
    }

    template <class CharT>
    inline basic_string<CharT> operator + (typename basic_string<CharT>::const_pointer __lhs, const basic_string<CharT>& __rhs)
    {
        basic_string<CharT> __res(__lhs);
        __res += __rhs;
        return __res;
    }

    template <class CharT>
    inline basic_string<CharT> operator + (const basic_string<CharT>& __lhs, typename basic_string<CharT>::value_type __rhs)
    {
        basic_string<CharT> __res(__lhs);
        __res += __rhs;
        return __res;
    }

    template <class CharT>
    inline basic_string<CharT> operator + (typename basic_string<CharT>::value_type __lhs, const basic_string<CharT>& __rhs)
    {
        basic_string<CharT> __res(1, __lhs);
        __res += __rhs;
        return __res;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////

    template <class CharT>
    inline bool operator == (const basic_string<CharT>& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) == 0;
    }
    
    template <class CharT>
    inline bool operator == (const basic_string<CharT>& __lhs, const typename basic_string<CharT>::super_type& __rhs)
    {
        return __lhs.compare(__rhs) == 0;
    }
    
    template <class CharT>
    inline bool operator == (const typename basic_string<CharT>::super_type& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) == 0;
    }
    
    template <class CharT>
    inline bool operator == (const basic_string<CharT>& __lhs, typename basic_string<CharT>::const_pointer __rhs)
    {
        return __lhs.compare(__rhs) == 0;
    }
    
    template <class CharT>
    inline bool operator == (typename basic_string<CharT>::const_pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) == 0;
    }
    
    template <class CharT>
    inline bool operator == (const basic_string<CharT>& __lhs, typename basic_string<CharT>::pointer __rhs)
    {
        return __lhs.compare(__rhs) == 0;
    }
    
    template <class CharT>
    inline bool operator == (typename basic_string<CharT>::pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) == 0;
    }

    template <class CharT>
    inline bool operator != (const basic_string<CharT>& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) != 0;
    }

    template <class CharT>
    inline bool operator != (const basic_string<CharT>& __lhs, const typename basic_string<CharT>::super_type& __rhs)
    {
        return __lhs.compare(__rhs) != 0;
    }

    template <class CharT>
    inline bool operator != (const typename basic_string<CharT>::super_type& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) != 0;
    }

    template <class CharT>
    inline bool operator != (const basic_string<CharT>& __lhs, typename basic_string<CharT>::const_pointer __rhs)
    {
        return __lhs.compare(__rhs) != 0;
    }

    template <class CharT>
    inline bool operator != (typename basic_string<CharT>::const_pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) != 0;
    }

    template <class CharT>
    inline bool operator != (const basic_string<CharT>& __lhs, typename basic_string<CharT>::pointer __rhs)
    {
        return __lhs.compare(__rhs) != 0;
    }

    template <class CharT>
    inline bool operator != (typename basic_string<CharT>::pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) != 0;
    }

    template <class CharT>
    inline bool operator >  (const basic_string<CharT>& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) > 0;
    }

    template <class CharT>
    inline bool operator >  (const basic_string<CharT>& __lhs, const typename basic_string<CharT>::super_type& __rhs)
    {
        return __lhs.compare(__rhs) > 0;
    }

    template <class CharT>
    inline bool operator >  (const typename basic_string<CharT>::super_type& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) > 0;
    }

    template <class CharT>
    inline bool operator >  (const basic_string<CharT>& __lhs, typename basic_string<CharT>::const_pointer __rhs)
    {
        return __lhs.compare(__rhs) > 0;
    }

    template <class CharT>
    inline bool operator >  (typename basic_string<CharT>::const_pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) < 0;
    }

    template <class CharT>
    inline bool operator >  (const basic_string<CharT>& __lhs, typename basic_string<CharT>::pointer __rhs)
    {
        return __lhs.compare(__rhs) > 0;
    }

    template <class CharT>
    inline bool operator >  (typename basic_string<CharT>::pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) < 0;
    }

    template <class CharT>
    inline bool operator >= (const basic_string<CharT>& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) >= 0;
    }

    template <class CharT>
    inline bool operator >= (const basic_string<CharT>& __lhs, const typename basic_string<CharT>::super_type& __rhs)
    {
        return __lhs.compare(__rhs) >= 0;
    }

    template <class CharT>
    inline bool operator >= (const typename basic_string<CharT>::super_type& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) >= 0;
    }

    template <class CharT>
    inline bool operator >= (const basic_string<CharT>& __lhs, typename basic_string<CharT>::const_pointer __rhs)
    {
        return __lhs.compare(__rhs) >= 0;
    }

    template <class CharT>
    inline bool operator >= (typename basic_string<CharT>::const_pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) <= 0;
    }

    template <class CharT>
    inline bool operator >= (const basic_string<CharT>& __lhs, typename basic_string<CharT>::pointer __rhs)
    {
        return __lhs.compare(__rhs) >= 0;
    }

    template <class CharT>
    inline bool operator >= (typename basic_string<CharT>::pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) <= 0;
    }

    template <class CharT>
    inline bool operator <  (const basic_string<CharT>& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) < 0;
    }

    template <class CharT>
    inline bool operator <  (const basic_string<CharT>& __lhs, const typename basic_string<CharT>::super_type& __rhs)
    {
        return __lhs.compare(__rhs) < 0;
    }

    template <class CharT>
    inline bool operator <  (const typename basic_string<CharT>::super_type& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) < 0;
    }

    template <class CharT>
    inline bool operator <  (const basic_string<CharT>& __lhs, typename basic_string<CharT>::const_pointer __rhs)
    {
        return __lhs.compare(__rhs) < 0;
    }

    template <class CharT>
    inline bool operator <  (typename basic_string<CharT>::const_pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) > 0;
    }

    template <class CharT>
    inline bool operator <  (const basic_string<CharT>& __lhs, typename basic_string<CharT>::pointer __rhs)
    {
        return __lhs.compare(__rhs) < 0;
    }

    template <class CharT>
    inline bool operator <  (typename basic_string<CharT>::pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) > 0;
    }

    template <class CharT>
    inline bool operator <= (const basic_string<CharT>& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) <= 0;
    }

    template <class CharT>
    inline bool operator <= (const basic_string<CharT>& __lhs, const typename basic_string<CharT>::super_type& __rhs)
    {
        return __lhs.compare(__rhs) <= 0;
    }

    template <class CharT>
    inline bool operator <= (const typename basic_string<CharT>::super_type& __lhs, const basic_string<CharT>& __rhs)
    {
        return __lhs.compare(__rhs) <= 0;
    }

    template <class CharT>
    inline bool operator <= (const basic_string<CharT>& __lhs, typename basic_string<CharT>::const_pointer __rhs)
    {
        return __lhs.compare(__rhs) <= 0;
    }

    template <class CharT>
    inline bool operator <= (typename basic_string<CharT>::const_pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) >= 0;
    }

    template <class CharT>
    inline bool operator <= (const basic_string<CharT>& __lhs, typename basic_string<CharT>::pointer __rhs)
    {
        return __lhs.compare(__rhs) <= 0;
    }

    template <class CharT>
    inline bool operator <= (typename basic_string<CharT>::pointer __lhs, const basic_string<CharT>& __rhs)
    {
        return __rhs.compare(__lhs) >= 0;
    }

}//namespace ufc

#endif//UFC_STRING_STRING_HPP
