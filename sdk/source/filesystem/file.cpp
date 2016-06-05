/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : filesystem/file.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/filesystem/file.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/exception/exception.hpp"
#if defined(ufc_os_family_windows)
#include <filesystem/detail/file_win32.hpp>
#else
#include <filesystem/detail/file_unix.hpp>
#endif

namespace ufc {

    file::file()
    {
    }

    file::file(const string& __path)
        : detail::file_impl(__path)
    {
    }

    file::file(const char* __path)
        : detail::file_impl(__path)
    {
    }

    file::file(const path& __path)
        : detail::file_impl(__path.to_string())
    {
    }   

    file::file(const file& __file)
        : detail::file_impl(__file.get_path_impl())
    {
    }

    file::~file()
    {
    }

    file& file::operator = (const file& __file)
    {
        set_path_impl(__file.get_path_impl());
        return *this;
    }

    file& file::operator = (const string& __path)
    {
        set_path_impl(__path);
        return *this;
    }

    file& file::operator = (const char* __path)
    {
        set_path_impl(__path);
        return *this;
    }

    file& file::operator = (const path& __path)
    {
        set_path_impl(__path.to_string());
        return *this;
    }

    const string& file::get_path() const
    {
        return get_path_impl();
    }

    bool file::exists() const
    {
        return exists_impl();
    }

    bool file::can_read() const
    {
        return can_read_impl();
    }

    bool file::can_write() const
    {
        return can_write_impl();
    }

    bool file::can_execute() const
    {
        return can_execute_impl();
    }

    bool file::is_file() const
    {
        return is_file_impl();
    }

    bool file::is_link() const
    {
        return is_link_impl();
    }

    bool file::is_directory() const
    {
        return is_directory_impl();
    }

    bool file::is_device() const
    {
        return is_device_impl();
    }

    bool file::is_hidden() const
    {
        return is_hidden_impl();
    }

    timestamp file::created() const
    {
        return created_impl();
    }

    timestamp file::get_last_modified() const
    {
        return get_last_modified_impl();
    }

    file& file::set_last_modified(const timestamp& __ts)
    {
        set_last_modified_impl(__ts);
        return *this;
    }

    int64_t file::get_size() const
    {
        return get_size_impl();
    }

    file& file::set_size(int64_t __size)
    {
        set_size_impl(__size);
        return *this;
    }

    file& file::set_writeable(bool __flag)
    {
        set_writeable_impl(__flag);
        return *this;
    }

    file& file::set_read_only(bool __flag)
    {
        set_writeable_impl(!__flag);
        return *this;
    }

    file& file::set_executable(bool __flag)
    {
        set_executable_impl(__flag);
        return *this;
    }

    void file::copy_to(const string& __path) const
    {
        path __src(get_path_impl());
        path __dest(__path);
        file __dest_file(__path);
        if ((__dest_file.exists() && __dest_file.is_directory()) || __dest.is_directory())
        {
            __dest.make_directory();
            __dest.set_file_name(__src.get_file_name());
        }
        if (is_directory_impl())
        {
            file __target(__path);
            __target.mkdirs();

            path src(get_path_impl());
            src.make_file();
            file::file_vec __files;
            list(__files);
            for (file::file_vec::iterator it = __files.begin(); it != __files.end(); it++)
            {
                it->copy_to(__path);
            }
        }
        else
        {
            copy_to_impl(__dest.to_string());
        }
    }

    void file::move_to(const string& __path)
    {
        copy_to_impl(__path);
        remove(true);
        set_path_impl(__path);
    }

    void file::rename_to(const string& __path)
    {
        rename_to_impl(__path);
        set_path_impl(__path);
    }

    void file::remove(bool __recursive)
    {
        if (__recursive && !is_link() && is_directory())
        {
            file_vec __files;
            list(__files);
            for (file_vec::iterator it = __files.begin(); it != __files.end(); ++it)
            {
                it->remove(true);
            }
        }
        remove_impl();
    }

    bool file::create_file()
    {
        return create_file_impl();
    }

    bool file::mkdir()
    {
        return mkdir_impl();
    }

    void file::mkdirs()
    {
        if (!exists_impl())
        {
            path __p(get_path_impl());
            __p.make_directory();
            if (__p.depth() > 1)
            {
                __p.make_parent();
                file __f(__p.to_string());
                __f.mkdirs();
            }
            mkdir_impl();
        }
    }

    void file::list(string_vec& __files) const
    {
        list_impl(__files);
    }

    void file::list(file_vec& __files) const
    {
        __files.clear();

        string_vec __tmp_files;
        list_impl(__tmp_files);
        for (string_vec::const_iterator it = __tmp_files.begin(); it != __tmp_files.end(); it++)
        {
            __files.push_back(file(get_path_impl() + path::separator() + *it));
        }
    }

    bool file::operator == (const file& __file) const
    {
        return get_path_impl() == __file.get_path_impl();
    }

    bool file::operator != (const file& __file) const
    {
        return get_path_impl() != __file.get_path_impl();
    }

    bool file::operator <  (const file& __file) const
    {
        return get_path_impl() < __file.get_path_impl();
    }

    bool file::operator <= (const file& __file) const
    {
        return get_path_impl() <= __file.get_path_impl();
    }

    bool file::operator >  (const file& __file) const
    {
        return get_path_impl() > __file.get_path_impl();
    }

    bool file::operator >= (const file& __file) const
    {
        return get_path_impl() >= __file.get_path_impl();
    }

    void file::handle_last_error(const string& __path)
    {
        handle_last_error_impl(__path);
    }

}//namespace ufc
