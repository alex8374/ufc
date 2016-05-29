/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : string/string_tokenizer.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/string/string_tokenizer.hpp"

namespace ufc {

    template <class CharT>
    void __build_in_strok(vector<basic_string<CharT> >& __tokens,
                          const basic_string<CharT>& __source, 
                          const basic_string<CharT>& __delims,
                          int32_t __options)
    {
        typedef basic_string<CharT>             string_type;
        typedef basic_string_tokenizer<CharT>   string_tokenizer_type;

        typename string_type::const_iterator __it  = __source.begin();
        typename string_type::const_iterator __end = __source.end();
        typename string_type::const_iterator __tmpit;

        __tokens.clear();
        while (__it != __end)
        {
            __tmpit = __it;
            while (__tmpit != __end && __delims.find(*__tmpit) == string_type::npos) ++__tmpit;

            string_type __tmpstr(__it, __tmpit);
            if (__options & string_tokenizer_type::tok_trim)
            {
                __tmpstr.trim();
            }

            if (__options & string_tokenizer_type::tok_ignore_empty)
            {
                if (!__tmpstr.empty())
                {
                    __tokens.push_back(__tmpstr);
                }
            }
            else
            {
                __tokens.push_back(__tmpstr);
            }

            if (__options & string_tokenizer_type::tok_return_delim && __tmpit != __end)
            {
                __tokens.push_back(string_type(1, *__tmpit));
            }

            __it = __tmpit;
            if (__it != __end)
            {
                ++__it;
            }
        }
    }

    template <> basic_string_tokenizer<char>::basic_string_tokenizer(const string_type& __source, 
                                                                     const string_type& __delims,
                                                                     int32_t __options)
    {
        __build_in_strok(_tokens, __source, __delims, __options);
    }

    template <> basic_string_tokenizer<wchar_t>::basic_string_tokenizer(const string_type& __source, 
                                                                        const string_type& __delims,
                                                                        int32_t __options)
    {
        __build_in_strok(_tokens, __source, __delims, __options);
    }

}//namespace ufc
