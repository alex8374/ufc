/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/string/string_tokenizer.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_STRING_STRING_TOKENIZER_HPP
#define UFC_STRING_STRING_TOKENIZER_HPP

#include <ufc/string/string.hpp>
#include <ufc/container/vector.hpp>

namespace ufc {

    ///
	/// @breif: A simple tokenizer that splits a string into
	/// tokens, which are separated by separator characters.
	/// An iterator is used to iterate over all tokens.
    ///
    template <class CharT>
    class basic_string_tokenizer: virtual public object
    {
        typedef basic_string<CharT> string_type;
        typedef vector<string_type> string_vector;
 
    public:
        enum options_t
        {
            tok_ignore_empty = 0x01,    /// ignore empty tokens
            tok_trim         = 0x02,    /// remove leading and trailing whitespace from tokens
            tok_return_delim = 0x04     /// return separator
        };

        typedef typename string_vector::const_iterator iterator;

        basic_string_tokenizer(const string_type& __source, const string_type& __delims, int32_t __options = 0);

        virtual ~basic_string_tokenizer()
        {
        }

        inline const string_type& operator [] (uint32_t __pos) const
        {
            return _tokens[__pos];
        }

        inline string_type& operator [] (uint32_t __pos)
        {
            return _tokens[__pos];
        }

        inline uint32_t size() const
        {
            return _tokens.size();
        }

        inline iterator begin() const
        {
            return _tokens.begin();
        }

        inline iterator end() const
        {
            return _tokens.end();
        }

    private:
        string_vector _tokens;
    };

    typedef basic_string_tokenizer<char>    string_tokenizer;
    typedef basic_string_tokenizer<wchar_t> wstring_tokenizer;

}//namespace ufc

#endif//UFC_STRING_STRING_TOKENIZER_HPP