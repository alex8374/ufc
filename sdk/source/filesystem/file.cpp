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
#if defined(_WIN32) || defined(WIN32)
#include "filesystem/file_win32.hpp"
#else
#include "filesystem/file_unix.hpp"
#endif

namespace ufc {

    file::file()
        : _impl(new private_t)
    {
        ufc_check_ptr(_impl);
    }

    file::file(const string& __path)
        : _impl(new private_t(__path))
    {
        ufc_check_ptr(_impl);
    }

    file::file(const char* __path)
        : _impl(new private_t(__path))
    {
        ufc_check_ptr(_impl);
    }

    file::file(const path& __path)
        : _impl(new private_t(__path.to_string()))
    {
        ufc_check_ptr(_impl);
    }   

    file::file(const file& __file)
        : _impl(new private_t(__file.get_path()))
    {
        ufc_check_ptr(_impl);
    }

    file::~file()
    {
        memory::delete_ptr(_impl);
    }

    file& file::operator = (const file& __file)
    {
        _impl->set_path(__file.get_path());
        return *this;
    }

    file& file::operator = (const string& __path)
    {
        _impl->set_path(__path);
        return *this;
    }

    file& file::operator = (const char* __path)
    {
        _impl->set_path(__path);
        return *this;
    }

    file& file::operator = (const path& __path)
    {
        _impl->set_path(__path.to_string());
        return *this;
    }

    const string& file::get_path() const
    {
        return _impl->get_path();
    }

    bool file::exists() const
    {
        return _impl->exists();
    }

    bool file::can_read() const
    {
        return _impl->can_read();
    }

    bool file::can_write() const
    {
        return _impl->can_write();
    }

    bool file::can_execute() const
    {
        return _impl->can_execute();
    }

    bool file::is_file() const
    {
        return _impl->is_file();
    }

    bool file::is_link() const
    {
        return _impl->is_link();
    }

    bool file::is_directory() const
    {
        return _impl->is_directory();
    }

    bool file::is_device() const
    {
        return _impl->is_device();
    }

    bool file::is_hidden() const
    {
        return _impl->is_hidden();
    }

    timestamp file::created() const
    {
        return _impl->created();
    }

    timestamp file::get_last_modified() const
    {
        return _impl->get_last_modified();
    }

    file& file::set_last_modified(const timestamp& __ts)
    {
        _impl->set_last_modified(__ts);
        return *this;
    }

    int64_t file::get_size() const
    {
        return _impl->get_size();
    }

    file& file::set_size(int64_t __size)
    {
        _impl->set_size(__size);
        return *this;
    }

    file& file::set_writeable(bool __flag)
    {
        _impl->set_writeable(__flag);
        return *this;
    }

    file& file::set_read_only(bool __flag)
    {
        _impl->set_writeable(!__flag);
        return *this;
    }

    file& file::set_executable(bool __flag)
    {
        _impl->set_executable(__flag);
        return *this;
    }

    void file::copy_to(const string& __path) const
    {
        path __src(_impl->get_path());
        path __dest(__path);
        file __dest_file(__path);
        if ((__dest_file.exists() && __dest_file.is_directory()) || __dest.is_directory())
        {
            __dest.make_directory();
            __dest.set_file_name(__src.get_file_name());
        }
        if (is_directory())
        {
            file __target(__path);
            __target.mkdirs();

            path src(_impl->get_path());
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
            _impl->copy_to(__dest.to_string());
        }
    }

    void file::move_to(const string& __path)
    {
        copy_to(__path);
        remove(true);
        _impl->set_path(__path);
    }

    void file::rename_to(const string& __path)
    {
        _impl->rename_to(__path);
        _impl->set_path(__path);
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
        _impl->remove();
    }

    bool file::create_file()
    {
        return _impl->create_file();
    }

    bool file::mkdir()
    {
        return _impl->mkdir();
    }

    void file::mkdirs()
    {
        if (!exists())
        {
            path __p(_impl->get_path());
            __p.make_directory();
            if (__p.depth() > 1)
            {
                __p.make_parent();
                file __f(__p.to_string());
                __f.mkdirs();
            }
            _impl->mkdir();
        }
    }

    void file::list(string_vec& __files) const
    {
        _impl->list(__files);
    }

    void file::list(file_vec& __files) const
    {
        __files.clear();

        string_vec __tmp_files;
        list(__tmp_files);
        for (string_vec::const_iterator it = __tmp_files.begin(); it != __tmp_files.end(); it++)
        {
            __files.push_back(file(_impl->get_path() + path::separator() + *it));
        }
    }

    bool file::operator == (const file& __file) const
    {
        return get_path() == __file.get_path();
    }

    bool file::operator != (const file& __file) const
    {
        return get_path() != __file.get_path();
    }

    bool file::operator <  (const file& __file) const
    {
        return get_path() < __file.get_path();
    }

    bool file::operator <= (const file& __file) const
    {
        return get_path() <= __file.get_path();
    }

    bool file::operator >  (const file& __file) const
    {
        return get_path() > __file.get_path();
    }

    bool file::operator >= (const file& __file) const
    {
        return get_path() >= __file.get_path();
    }

    void file::handle_last_error(const string& __path)
    {
        file::private_t::handle_last_error(__path);
    }

}//namespace ufc
