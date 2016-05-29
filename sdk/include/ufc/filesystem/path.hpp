/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/filesyteam/path.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_FILESYTEAM_PATH_HPP
#define UFC_FILESYTEAM_PATH_HPP

#include <ufc/string/string.hpp>

namespace ufc {

    /// 
	/// @breif: This class represents filesystem paths in a platform-independent manner.
	///         Unix, Windows and OpenVMS all use a different syntax for filesystem paths.
	///         This class can work with all three formats.
	///         A path is made up of an optional node name(only Windows and OpenVMS), an optional
	///         device name (also only Windows and OpenVMS), a list of directory names and an optional
	///         filename.
    /// 
    class ufc_api path: virtual public object
    {
        class private_t;
        friend class path::private_t;

    public:
        path();
        path(bool __absolute);
        path(const char* __path);
        path(const string& __path);
        path(const path& __path);
        path(const path& __parent, const string& __filename);
        path(const path& __parent, const char* __filename);
        path(const path& __parent, const path& __relative);
        virtual ~path();

        path& operator = (const path& __path);
        path& operator = (const string& __path);
        path& operator = (const char* __path);

        void swap(path& __path);

        path& assign(const path& __path);
        path& assign(const string& __path);
        path& assign(const char* __path);

        string to_string() const;

        path& parse(const string& __path);
        bool  try_parse(const string& __path);
        path& parse_directory(const string& __path);

        path& make_directory();
        path& make_file();
        path& make_parent();
        path& make_absolute();
        path& make_absolute(const path& __base_path);

        path& append(const path& __path);

        path& resolve(const path& __path);

        bool is_absolute() const;
        bool is_relative() const;
        bool is_directory() const;
        bool is_file() const;

        uint32_t depth() const;

        const string& directory(uint32_t __n) const;
        const string& operator [] (uint32_t __n) const;

        path& push_directory(const string& __dir);
        path& pop_directory();
        path& pop_front_directory();

        path& set_device(const string& __device);
        const string& get_device() const;

        path& set_file_name(const string& __name);
        const string& get_file_name() const;

        path&  set_base_name(const string& __name);
        string get_base_name() const;

        path&  set_extension(const string& __extension);
        string get_extension() const;

        path parent() const;
        path absolute() const;
        path absolute(const path& __base_path) const;

        path& clear();

    public:
        static char   separator_char();
        static string separator();

        static char   path_separator_char();
        static string path_separator();

        static path   for_directory(const string& __path);

        static string current();
        static string home();
        static string temp();
        static string null();

        static void list_roots(string_vec& __roots);
        static bool find(const string& __name, path& __path, string __path_list = "");

        static string convert_native_path(const string& __path);

        static string get_library_path_list();

    private:
        string     _device;
        string_vec _dirs;
        string     _name;
        bool       _absolute;
    };

}//namespace ufc

#endif//UFC_FILESYTEAM_PATH_HPP