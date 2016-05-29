/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/filesystem/fstream.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-22
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_FILESYSTEM_FSTREAM_HPP
#define UFC_FILESYSTEM_FSTREAM_HPP

#include <ufc/base/config.hpp>
#include <ufc/string/string.hpp>
#include <ufc/filesystem/file.hpp>
#include <ufc/filesystem/path.hpp>
#include <fstream>
#include <streambuf>
#include <iosfwd>
#include <ios>
#include <cstdarg>

namespace ufc {
    
    /**
     *  If a file is already open, this function immediately fails.
     *  Otherwise it tries to open the file named @a s using the flags
     *  given in @a mode.
     *
     *  Table 92, adapted here, gives the relation between openmode
     *  combinations and the equivalent fopen() flags.
     *  (NB: lines app, in|out|app, in|app, binary|app, binary|in|out|app,
     *  and binary|in|app per DR 596)
     *  +---------------------------------------------------------+
     *  | ios_base Flag combination            stdio equivalent   |
     *  |binary  in  out  trunc  app                              |
     *  +---------------------------------------------------------+
     *  |             +                        "w"                |
     *  |             +           +            "a"                |
     *  |                         +            "a"                |
     *  |             +     +                  "w"                |
     *  |         +                            "r"                |
     *  |         +   +                        "r+"               |
     *  |         +   +     +                  "w+"               |
     *  |         +   +           +            "a+"               |
     *  |         +               +            "a+"               |
     *  +---------------------------------------------------------+
     *  |   +         +                        "wb"               |
     *  |   +         +           +            "ab"               |
     *  |   +                     +            "ab"               |
     *  |   +         +     +                  "wb"               |
     *  |   +     +                            "rb"               |
     *  |   +     +   +                        "r+b"              |
     *  |   +     +   +     +                  "w+b"              |
     *  |   +     +   +           +            "a+b"              |
     *  |   +     +               +            "a+b"              |
     *  +---------------------------------------------------------+
     */
    template <class CharT> 
    class basic_filebuf: virtual public object, public std::basic_filebuf<CharT, std::char_traits<CharT> >
    {
    public:
        typedef CharT                                 char_type;
        typedef char_traits<CharT>                    traits_type;
        typedef typename traits_type::int_type        int_type;
        typedef typename traits_type::pos_type        pos_type;
        typedef typename traits_type::off_type        off_type;
        typedef typename traits_type::state_type      state_type;
        typedef basic_string<char_type>               string_type;

        typedef typename std::basic_filebuf<char_type, std::char_traits<char_type> >     super_type;
        typedef basic_filebuf<char_type>                                filebuf_type;

    public:
        basic_filebuf();
        virtual ~basic_filebuf();

        filebuf_type* open(const char*   __path, std::ios::openmode __mode);
        filebuf_type* open(const string& __path, std::ios::openmode __mode);
        filebuf_type* open(const file&   __path, std::ios::openmode __mode);
        filebuf_type* open(const path&   __path, std::ios::openmode __mode);
    };

    template <class CharT> 
    class basic_ifstream: virtual public object, public std::basic_ifstream<CharT, std::char_traits<CharT> >
    {
    public:
        typedef CharT                                 char_type;
        typedef char_traits<CharT>                    traits_type;
        typedef typename traits_type::int_type        int_type;
        typedef typename traits_type::pos_type        pos_type;
        typedef typename traits_type::off_type        off_type;
        typedef typename traits_type::state_type      state_type;
        typedef basic_string<char_type>               string_type;

        typedef typename std::basic_ifstream<char_type, std::char_traits<char_type> >    super_type;
        typedef basic_ifstream<char_type>                  stream_type;

    public:
        basic_ifstream();
        basic_ifstream(const char*   __path, 
                       std::ios::openmode __mode = std::ios::in | std::ios::binary);
        basic_ifstream(const string& __path, 
                       std::ios::openmode __mode = std::ios::in | std::ios::binary);
        basic_ifstream(const file&   __path, 
                       std::ios::openmode __mode = std::ios::in | std::ios::binary);
        basic_ifstream(const path&   __path, 
                       std::ios::openmode __mode = std::ios::in | std::ios::binary);
        virtual ~basic_ifstream();

        void open(const char*   __path, std::ios::openmode __mode = std::ios::in | std::ios::binary);
        void open(const string& __path, std::ios::openmode __mode = std::ios::in | std::ios::binary);
        void open(const file&   __path, std::ios::openmode __mode = std::ios::in | std::ios::binary);
        void open(const path&   __path, std::ios::openmode __mode = std::ios::in | std::ios::binary);

        stream_type& getline(char_type* __s, std::streamsize __n, char_type __delim);
        stream_type& getline(char_type* __s, std::streamsize __n);
        stream_type& getline(string_type& __str, char_type __delim);
        stream_type& getline(string_type& __str);
        string_type  getline();

        stream_type& getfull(string_type& __str);
        string_type  getfull();

        char_type    getch();

        std::streamsize size();
        pos_type        position();
    };

    template <class CharT> 
    class basic_ofstream: virtual public object, public std::basic_ofstream<CharT, std::char_traits<CharT> >
    {
    public:
        typedef CharT                                 char_type;
        typedef char_traits<CharT>                    traits_type;
        typedef typename traits_type::int_type        int_type;
        typedef typename traits_type::pos_type        pos_type;
        typedef typename traits_type::off_type        off_type;
        typedef typename traits_type::state_type      state_type;
        typedef basic_string<char_type>               string_type;

        typedef typename std::basic_ofstream<char_type, std::char_traits<char_type> >    super_type;
        typedef basic_ofstream<char_type>                  stream_type;

    public:
        basic_ofstream();
        basic_ofstream(const char*   __path, 
                       std::ios::openmode __mode = std::ios::out | std::ios::binary);
        basic_ofstream(const string& __path, 
                       std::ios::openmode __mode = std::ios::out | std::ios::binary);
        basic_ofstream(const file&   __path, 
                       std::ios::openmode __mode = std::ios::out | std::ios::binary);
        basic_ofstream(const path&   __path, 
                       std::ios::openmode __mode = std::ios::out | std::ios::binary);
        virtual ~basic_ofstream();

        void open(const char*   __path, std::ios::openmode __mode = std::ios::out | std::ios::binary);
        void open(const string& __path, std::ios::openmode __mode = std::ios::out | std::ios::binary);
        void open(const file&   __path, std::ios::openmode __mode = std::ios::out | std::ios::binary);
        void open(const path&   __path, std::ios::openmode __mode = std::ios::out | std::ios::binary);

        stream_type& printf(const char_type* __fmt, ...);
        stream_type& vprintf(const char_type* __fmt, va_list __args);
    };

    template <class CharT> 
    class basic_fstream: virtual public object, public std::basic_fstream<CharT, std::char_traits<CharT> >
    {
    public:
        typedef CharT                                 char_type;
        typedef char_traits<CharT>                    traits_type;
        typedef typename traits_type::int_type        int_type;
        typedef typename traits_type::pos_type        pos_type;
        typedef typename traits_type::off_type        off_type;
        typedef typename traits_type::state_type      state_type;
        typedef basic_string<char_type>               string_type;

        typedef typename std::basic_fstream<char_type, std::char_traits<char_type> >    super_type;
        typedef basic_fstream<char_type>                  stream_type;

    public:
        basic_fstream();
        basic_fstream(const char*   __path,
                      std::ios::openmode __mode = std::ios::in | std::ios::out | std::ios::binary);
        basic_fstream(const string& __path,
                      std::ios::openmode __mode = std::ios::in | std::ios::out | std::ios::binary);
        basic_fstream(const file&   __path,
                      std::ios::openmode __mode = std::ios::in | std::ios::out | std::ios::binary);
        basic_fstream(const path&   __path,
                      std::ios::openmode __mode = std::ios::in | std::ios::out | std::ios::binary);
        virtual ~basic_fstream();

        void open(const char*   __path, std::ios::openmode __mode = std::ios::in | std::ios::out | std::ios::binary);
        void open(const string& __path, std::ios::openmode __mode = std::ios::in | std::ios::out | std::ios::binary);
        void open(const file&   __path, std::ios::openmode __mode = std::ios::in | std::ios::out | std::ios::binary);
        void open(const path&   __path, std::ios::openmode __mode = std::ios::in | std::ios::out | std::ios::binary);

        stream_type& getline(char_type* __s, std::streamsize __n, char_type __delim);
        stream_type& getline(char_type* __s, std::streamsize __n);
        stream_type& getline(string_type& __str, char_type __delim);
        stream_type& getline(string_type& __str);
        string_type  getline();

        stream_type& getfull(string_type& __str);
        string_type  getfull();

        char_type    getch();

        std::streamsize size();
        pos_type        position();

        stream_type& printf(const char_type* __fmt, ...);
        stream_type& vprintf(const char_type* __fmt, va_list __args);
    };

    //--------------------------------------------------------------------------------------//
    //                                    typedefs                                          //
    //--------------------------------------------------------------------------------------//

    typedef basic_filebuf<char>     filebuf;
    typedef basic_ifstream<char>    ifstream;
    typedef basic_ofstream<char>    ofstream;
    typedef basic_fstream<char>     fstream;

    typedef basic_filebuf<wchar_t>  wfilebuf;
    typedef basic_ifstream<wchar_t> wifstream;
    typedef basic_ofstream<wchar_t> wofstream;
    typedef basic_fstream<wchar_t>  wfstream;

}//namespace ufc

#endif//UFC_FILESYSTEM_FSTREAM_HPP
