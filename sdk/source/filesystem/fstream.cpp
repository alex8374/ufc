/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : filesystem/fstream.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-23
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/filesystem/fstream.hpp"

namespace ufc {

    template <class stream_type>
    stream_type& __build_in_getfull(stream_type& __sstr, typename stream_type::string_type& __str)
    {
        typename stream_type::char_type __c;

        typename stream_type::pos_type __pos = __sstr.tellg();
        __sstr.seekg(0, std::ios_base::beg);

        __str.clear();
        for (;;)
        {
            __c = __sstr.get();
            if (__c == stream_type::traits_type::eof())
            {
                break;
            }
            __str += __c;
        }
        __sstr.seekg(__pos, std::ios_base::beg);

        return __sstr;
    }

    template <class stream_type>
    stream_type& __build_in_getline(stream_type& __sstr, 
                                    typename stream_type::string_type& __str,
                                    typename stream_type::char_type __delim)
    {
        typename stream_type::char_type __c;

        __str.clear();
        for (;;)
        {
            __c = __sstr.get();
            if ((__c == __delim) || (__c == stream_type::traits_type::eof()))
            {
                break;
            }
            __str += __c;
        }
        return __sstr;
    }

    template <class stream_type>
    std::streamsize __build_in_size(stream_type& __sstr)
    {
        typename stream_type::pos_type __pos  = __sstr.tellg();
        __sstr.seekg(0, std::ios_base::end);
        typename stream_type::pos_type __size = __sstr.tellg();
        __sstr.seekg(__pos);
        return __size;
    }
    ////////////////////////////////////////////////////////////////////

    template <> basic_filebuf<char>::basic_filebuf()
    {
    }

    template <> basic_filebuf<char>::~basic_filebuf()
    {
    }

    template <> basic_filebuf<char>::filebuf_type* basic_filebuf<char>::open(const char_type* __path, std::ios_base::openmode __mode) 
    {
        return super_type::open(__path, __mode)? this : 0;
    }

    template <> basic_filebuf<char>::filebuf_type* basic_filebuf<char>::open(const string& __path, std::ios_base::openmode __mode) 
    {
        return super_type::open(__path.c_str(), __mode)? this : 0;
    }

    template <> basic_filebuf<char>::filebuf_type* basic_filebuf<char>::open(const file& __path, std::ios_base::openmode __mode)
    {
        return super_type::open(__path.get_path().c_str(), __mode)? this : 0;
    }

    template <> basic_filebuf<char>::filebuf_type* basic_filebuf<char>::open(const path& __path, std::ios_base::openmode __mode)
    {
        return super_type::open(__path.to_string().c_str(), __mode)? this : 0;
    }

    template <> basic_filebuf<wchar_t>::basic_filebuf()
    {
    }

    template <> basic_filebuf<wchar_t>::~basic_filebuf()
    {
    }

    template <> basic_filebuf<wchar_t>::filebuf_type* basic_filebuf<wchar_t>::open(const char* __path, std::ios_base::openmode __mode) 
    {
        return super_type::open(__path, __mode)? this : 0;
    }

    template <> basic_filebuf<wchar_t>::filebuf_type* basic_filebuf<wchar_t>::open(const string& __path, std::ios_base::openmode __mode) 
    {
        return super_type::open(__path.c_str(), __mode)? this : 0;
    }

    template <> basic_filebuf<wchar_t>::filebuf_type* basic_filebuf<wchar_t>::open(const file& __path, std::ios_base::openmode __mode)
    {
        return super_type::open(__path.get_path().c_str(), __mode)? this : 0;
    }

    template <> basic_filebuf<wchar_t>::filebuf_type* basic_filebuf<wchar_t>::open(const path& __path, std::ios_base::openmode __mode)
    {
        return super_type::open(__path.to_string().c_str(), __mode)? this : 0;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <> basic_ifstream<char>::basic_ifstream()
    {
    }

    template <> basic_ifstream<char>::basic_ifstream(const char* __path, std::ios_base::openmode __mode)
        : super_type(__path, __mode)
    {
    }

    template <> basic_ifstream<char>::basic_ifstream(const string& __path, std::ios_base::openmode __mode)
        : super_type(__path.c_str(), __mode)
    {
    }

    template <> basic_ifstream<char>::basic_ifstream(const file& __path, std::ios_base::openmode __mode)
        : super_type(__path.get_path().c_str(), __mode)
    {
    }

    template <> basic_ifstream<char>::basic_ifstream(const path& __path, std::ios_base::openmode __mode)
        : super_type(__path.to_string().c_str(), __mode)
    {
    }

    template <> basic_ifstream<char>::~basic_ifstream()
    {
    }

    template <> void basic_ifstream<char>::open(const char* __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path, __mode);
    }

    template <> void basic_ifstream<char>::open(const string& __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.c_str(), __mode);
    }

    template <> void basic_ifstream<char>::open(const file& __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.get_path().c_str(), __mode);
    }

    template <> void basic_ifstream<char>::open(const path& __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.to_string().c_str(), __mode);
    }

    template <> basic_ifstream<char>::stream_type& basic_ifstream<char>::getline(char_type* __s, std::streamsize __n, char_type __delim)
    {
        super_type::getline(__s, __n, __delim);
        return *this;
    }

    template <> basic_ifstream<char>::stream_type& basic_ifstream<char>::getline(char_type* __s, std::streamsize __n)
    {
        super_type::getline(__s, __n);
        return *this;
    }

    template <> basic_ifstream<char>::stream_type& basic_ifstream<char>::getline(string_type& __str, char_type __delim)
    {
        return __build_in_getline(*this, __str, __delim);
    }

    template <> basic_ifstream<char>::stream_type& basic_ifstream<char>::getline(string_type& __str)
    {
        return __build_in_getline(*this, __str, super_type::widen('\n'));
    }

    template <> basic_ifstream<char>::string_type basic_ifstream<char>::getline()
    {
        string_type __str;
        __build_in_getline(*this, __str, super_type::widen('\n'));
        return __str;
    }

    template <> basic_ifstream<char>::stream_type& basic_ifstream<char>::getfull(string_type& __str)
    {
        return __build_in_getfull(*this, __str);
    }

    template <> basic_ifstream<char>::string_type basic_ifstream<char>::getfull()
    {
        string_type __str;
        __build_in_getfull(*this, __str);
        return __str;
    }

    template <> basic_ifstream<char>::char_type basic_ifstream<char>::getch()
    {
        return super_type::get();
    }

    template <> std::streamsize basic_ifstream<char>::size()
    {
        return __build_in_size(*this);
    }

    template <> basic_ifstream<char>::pos_type basic_ifstream<char>::position()
    {
        return super_type::tellg();
    }
    ////
    
    template <> basic_ifstream<wchar_t>::basic_ifstream()
    {
    }

    template <> basic_ifstream<wchar_t>::basic_ifstream(const char* __path, std::ios_base::openmode __mode)
        : super_type(__path, __mode)
    {
    }

    template <> basic_ifstream<wchar_t>::basic_ifstream(const string& __path, std::ios_base::openmode __mode)
        : super_type(__path.c_str(), __mode)
    {
    }

    template <> basic_ifstream<wchar_t>::basic_ifstream(const file& __path, std::ios_base::openmode __mode)
        : super_type(__path.get_path().c_str(), __mode)
    {
    }

    template <> basic_ifstream<wchar_t>::basic_ifstream(const path& __path, std::ios_base::openmode __mode)
        : super_type(__path.to_string().c_str(), __mode)
    {
    }

    template <> basic_ifstream<wchar_t>::~basic_ifstream()
    {
    }

    template <> void basic_ifstream<wchar_t>::open(const char* __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path, __mode);
    }

    template <> void basic_ifstream<wchar_t>::open(const string& __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.c_str(), __mode);
    }

    template <> void basic_ifstream<wchar_t>::open(const file& __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.get_path().c_str(), __mode);
    }

    template <> void basic_ifstream<wchar_t>::open(const path& __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.to_string().c_str(), __mode);
    }

    template <> basic_ifstream<wchar_t>::stream_type& basic_ifstream<wchar_t>::getline(char_type* __s, std::streamsize __n, char_type __delim)
    {
        super_type::getline(__s, __n, __delim);
        return *this;
    }

    template <> basic_ifstream<wchar_t>::stream_type& basic_ifstream<wchar_t>::getline(char_type* __s, std::streamsize __n)
    {
        super_type::getline(__s, __n);
        return *this;
    }

    template <> basic_ifstream<wchar_t>::stream_type& basic_ifstream<wchar_t>::getline(string_type& __str, char_type __delim)
    {
        return __build_in_getline(*this, __str, __delim);
    }

    template <> basic_ifstream<wchar_t>::stream_type& basic_ifstream<wchar_t>::getline(string_type& __str)
    {
        return __build_in_getline(*this, __str, super_type::widen('\n'));
    }

    template <> basic_ifstream<wchar_t>::string_type basic_ifstream<wchar_t>::getline()
    {
        string_type __str;
        __build_in_getline(*this, __str, super_type::widen('\n'));
        return __str;
    }

    template <> basic_ifstream<wchar_t>::stream_type& basic_ifstream<wchar_t>::getfull(string_type& __str)
    {
        return __build_in_getfull(*this, __str);
    }

    template <> basic_ifstream<wchar_t>::string_type basic_ifstream<wchar_t>::getfull()
    {
        string_type __str;
        __build_in_getfull(*this, __str);
        return __str;
    }

    template <> basic_ifstream<wchar_t>::char_type basic_ifstream<wchar_t>::getch()
    {
        return super_type::get();
    }

    template <> std::streamsize basic_ifstream<wchar_t>::size()
    {
        return __build_in_size(*this);
    }

    template <> basic_ifstream<wchar_t>::pos_type basic_ifstream<wchar_t>::position()
    {
        return super_type::tellg();
    }
    /////////////////////////////////
    
    template <> basic_ofstream<char>::basic_ofstream()
    {
    }

    template <> basic_ofstream<char>::basic_ofstream(const char*   __path, std::ios_base::openmode __mode)
        : super_type(__path, __mode)
    {
    }

    template <> basic_ofstream<char>::basic_ofstream(const string& __path, std::ios_base::openmode __mode)
        : super_type(__path.c_str(), __mode)
    {
    }

    template <> basic_ofstream<char>::basic_ofstream(const file&   __path, std::ios_base::openmode __mode)
        : super_type(__path.get_path().c_str(), __mode)
    {
    }

    template <> basic_ofstream<char>::basic_ofstream(const path&   __path, std::ios_base::openmode __mode)
        : super_type(__path.to_string().c_str(), __mode)
    {
    }

    template <> basic_ofstream<char>::~basic_ofstream()
    {
    }

    template <> void basic_ofstream<char>::open(const char*   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path, __mode);
    }

    template <> void basic_ofstream<char>::open(const string& __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.c_str(), __mode);
    }

    template <> void basic_ofstream<char>::open(const file&   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.get_path().c_str(), __mode);
    }

    template <> void basic_ofstream<char>::open(const path&   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.to_string().c_str(), __mode);
    }

    template <> basic_ofstream<char>::stream_type& basic_ofstream<char>::vprintf(const char_type* __fmt, va_list __args)
    {
        string_type __str;
        __str.vprintf(__fmt, __args);
        super_type::write(__str.c_str(), __str.length());
        //super_type::operator << (string_type::vformat(__fmt, __args).c_str());
        return *this;
    }

    template <> basic_ofstream<char>::stream_type& basic_ofstream<char>::printf(const char_type* __fmt, ...)
    {
        va_list __args;
        va_start(__args, __fmt);
        this->vprintf(__fmt, __args);
        va_end(__args);
        return *this;
    }

    template <> basic_ofstream<wchar_t>::basic_ofstream()
    {
    }

    template <> basic_ofstream<wchar_t>::basic_ofstream(const char*   __path, std::ios_base::openmode __mode)
        : super_type(__path, __mode)
    {
    }

    template <> basic_ofstream<wchar_t>::basic_ofstream(const string& __path, std::ios_base::openmode __mode)
        : super_type(__path.c_str(), __mode)
    {
    }

    template <> basic_ofstream<wchar_t>::basic_ofstream(const file&   __path, std::ios_base::openmode __mode)
        : super_type(__path.get_path().c_str(), __mode)
    {
    }

    template <> basic_ofstream<wchar_t>::basic_ofstream(const path&   __path, std::ios_base::openmode __mode)
        : super_type(__path.to_string().c_str(), __mode)
    {
    }

    template <> basic_ofstream<wchar_t>::~basic_ofstream()
    {
    }

    template <> void basic_ofstream<wchar_t>::open(const char*   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path, __mode);
    }

    template <> void basic_ofstream<wchar_t>::open(const string& __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.c_str(), __mode);
    }

    template <> void basic_ofstream<wchar_t>::open(const file&   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.get_path().c_str(), __mode);
    }

    template <> void basic_ofstream<wchar_t>::open(const path&   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.to_string().c_str(), __mode);
    }

    template <> basic_ofstream<wchar_t>::stream_type& basic_ofstream<wchar_t>::vprintf(const char_type* __fmt, va_list __args)
    {
        string_type __str;
        __str.vprintf(__fmt, __args);
        super_type::write(__str.c_str(), __str.length());
        //super_type::operator << (string_type::vformat(__fmt, __args).c_str());
        return *this;
    }

    template <> basic_ofstream<wchar_t>::stream_type& basic_ofstream<wchar_t>::printf(const char_type* __fmt, ...)
    {
        va_list __args;
        va_start(__args, __fmt);
        this->vprintf(__fmt, __args);
        va_end(__args);
        return *this;
    }
    //////////////////////////////////////////

    template <> basic_fstream<char>::basic_fstream()
    {
    }

    template <> basic_fstream<char>::basic_fstream(const char*   __path, std::ios_base::openmode __mode)
        : super_type(__path, __mode)
    {
    }

    template <> basic_fstream<char>::basic_fstream(const string& __path, std::ios_base::openmode __mode)
        : super_type(__path.c_str(), __mode)
    {
    }

    template <> basic_fstream<char>::basic_fstream(const file&   __path, std::ios_base::openmode __mode)
        : super_type(__path.get_path().c_str(), __mode)
    {
    }

    template <> basic_fstream<char>::basic_fstream(const path&   __path, std::ios_base::openmode __mode)
        : super_type(__path.to_string().c_str(), __mode)
    {
    }

    template <> basic_fstream<char>::~basic_fstream()
    {
    }

    template <> void basic_fstream<char>::open(const char*   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path, __mode);
    }

    template <> void basic_fstream<char>::open(const string& __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.c_str(), __mode);
    }

    template <> void basic_fstream<char>::open(const file&   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.get_path().c_str(), __mode);
    }

    template <> void basic_fstream<char>::open(const path&   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.to_string().c_str(), __mode);
    }

    template <> basic_fstream<char>::stream_type& basic_fstream<char>::getline(char_type* __s, std::streamsize __n, char_type __delim)
    {
        super_type::getline(__s, __n, __delim);
        return *this;
    }

    template <> basic_fstream<char>::stream_type& basic_fstream<char>::getline(char_type* __s, std::streamsize __n)
    {
        super_type::getline(__s, __n);
        return *this;
    }

    template <> basic_fstream<char>::stream_type& basic_fstream<char>::getline(string_type& __str, char_type __delim)
    {
        return __build_in_getline(*this, __str, __delim);
    }

    template <> basic_fstream<char>::stream_type& basic_fstream<char>::getline(string_type& __str)
    {
        return __build_in_getline(*this, __str, super_type::widen('\n'));
    }

    template <> basic_fstream<char>::string_type  basic_fstream<char>::getline()
    {
        string_type __str;
        __build_in_getline(*this, __str, super_type::widen('\n'));
        return __str;
    }

    template <> basic_fstream<char>::stream_type& basic_fstream<char>::getfull(string_type& __str)
    {
        return __build_in_getfull(*this, __str);
    }

    template <> basic_fstream<char>::string_type basic_fstream<char>::getfull()
    {
        string_type __str;
        __build_in_getfull(*this, __str);
        return __str;
    }

    template <> basic_fstream<char>::char_type basic_fstream<char>::getch()
    {
        return super_type::get();
    }

    template <> std::streamsize basic_fstream<char>::size()
    {
        return __build_in_size(*this);
    }

    template <> basic_fstream<char>::pos_type basic_fstream<char>::position()
    {
        return super_type::tellg();
    }

    template <> basic_fstream<char>::stream_type& basic_fstream<char>::vprintf(const char_type* __fmt, va_list __args)
    {
        string_type __str;
        __str.vprintf(__fmt, __args);
        super_type::write(__str.c_str(), __str.length());
        //super_type::operator << (string_type::vformat(__fmt, __args).c_str());
        return *this;
    }

    template <> basic_fstream<char>::stream_type& basic_fstream<char>::printf(const char_type* __fmt, ...)
    {
        va_list __args;
        va_start(__args, __fmt);
        this->vprintf(__fmt, __args);
        va_end(__args);
        return *this;
    }
    ///

    template <> basic_fstream<wchar_t>::basic_fstream()
    {
    }

    template <> basic_fstream<wchar_t>::basic_fstream(const char*   __path, std::ios_base::openmode __mode)
        : super_type(__path, __mode)
    {
    }

    template <> basic_fstream<wchar_t>::basic_fstream(const string& __path, std::ios_base::openmode __mode)
        : super_type(__path.c_str(), __mode)
    {
    }

    template <> basic_fstream<wchar_t>::basic_fstream(const file&   __path, std::ios_base::openmode __mode)
        : super_type(__path.get_path().c_str(), __mode)
    {
    }

    template <> basic_fstream<wchar_t>::basic_fstream(const path&   __path, std::ios_base::openmode __mode)
        : super_type(__path.to_string().c_str(), __mode)
    {
    }

    template <> basic_fstream<wchar_t>::~basic_fstream()
    {
    }

    template <> void basic_fstream<wchar_t>::open(const char*   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path, __mode);
    }

    template <> void basic_fstream<wchar_t>::open(const string& __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.c_str(), __mode);
    }

    template <> void basic_fstream<wchar_t>::open(const file&   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.get_path().c_str(), __mode);
    }

    template <> void basic_fstream<wchar_t>::open(const path&   __path, std::ios_base::openmode __mode)
    {
        super_type::open(__path.to_string().c_str(), __mode);
    }

    template <> basic_fstream<wchar_t>::stream_type& basic_fstream<wchar_t>::getline(char_type* __s, std::streamsize __n, char_type __delim)
    {
        super_type::getline(__s, __n, __delim);
        return *this;
    }

    template <> basic_fstream<wchar_t>::stream_type& basic_fstream<wchar_t>::getline(char_type* __s, std::streamsize __n)
    {
        super_type::getline(__s, __n);
        return *this;
    }

    template <> basic_fstream<wchar_t>::stream_type& basic_fstream<wchar_t>::getline(string_type& __str, char_type __delim)
    {
        return __build_in_getline(*this, __str, __delim);
    }

    template <> basic_fstream<wchar_t>::stream_type& basic_fstream<wchar_t>::getline(string_type& __str)
    {
        return __build_in_getline(*this, __str, super_type::widen('\n'));
    }

    template <> basic_fstream<wchar_t>::string_type  basic_fstream<wchar_t>::getline()
    {
        string_type __str;
        __build_in_getline(*this, __str, super_type::widen('\n'));
        return __str;
    }

    template <> basic_fstream<wchar_t>::stream_type& basic_fstream<wchar_t>::getfull(string_type& __str)
    {
        return __build_in_getfull(*this, __str);
    }

    template <> basic_fstream<wchar_t>::string_type basic_fstream<wchar_t>::getfull()
    {
        string_type __str;
        __build_in_getfull(*this, __str);
        return __str;
    }

    template <> basic_fstream<wchar_t>::char_type basic_fstream<wchar_t>::getch()
    {
        return super_type::get();
    }

    template <> std::streamsize basic_fstream<wchar_t>::size()
    {
        return __build_in_size(*this);
    }

    template <> basic_fstream<wchar_t>::pos_type basic_fstream<wchar_t>::position()
    {
        return super_type::tellg();
    }

    template <> basic_fstream<wchar_t>::stream_type& basic_fstream<wchar_t>::vprintf(const char_type* __fmt, va_list __args)
    {
        string_type __str;
        __str.vprintf(__fmt, __args);
        super_type::write(__str.c_str(), __str.length());
        //super_type::operator << (string_type::vformat(__fmt, __args).c_str());
        return *this;
    }

    template <> basic_fstream<wchar_t>::stream_type& basic_fstream<wchar_t>::printf(const char_type* __fmt, ...)
    {
        va_list __args;
        va_start(__args, __fmt);
        this->vprintf(__fmt, __args);
        va_end(__args);
        return *this;
    }

}//namespace ufc
