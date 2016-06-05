/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/filesystem/detail/file_win32.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-05
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_FILESYSTEM_DETAIL_FILE_WIN32_HPP
#define UFC_FILESYSTEM_DETAIL_FILE_WIN32_HPP

#include <ufc/base/config.hpp>
#include <ufc/string/string.hpp>
#include <ufc/datetime/timestamp.hpp>

namespace ufc {
namespace detail {

    class file_impl: virtual public object
    {
    protected:
        file_impl();
        file_impl(const string& __path);
        virtual ~file_impl();

        void set_path_impl(const string& __path);
        const string& get_path_impl() const;

        bool exists_impl() const;

        bool can_read_impl() const;
        bool can_write_impl() const;
        bool can_execute_impl() const;

        bool is_file_impl() const;
        bool is_directory_impl() const;
        bool is_link_impl() const;
        bool is_device_impl() const;
        bool is_hidden_impl() const;

        timestamp created_impl() const;

        timestamp get_last_modified_impl() const;
        void set_last_modified_impl(const timestamp& __ts);

        int64_t get_size_impl() const;
        void set_size_impl(int64_t __size);
        
        void set_writeable_impl(bool __flag = true);
        void set_executable_impl(bool __flag = true);
        
        void copy_to_impl(const string& __path) const;
        void rename_to_impl(const string& __path);
        void remove_impl();
        bool create_file_impl();
        bool mkdir_impl();
        void list_impl(string_vec& __files) const;

    protected:
        static void handle_last_error_impl(const string& __path);

    private:
        string _path;
    };

}//namespace detail
}//namespace ufc

#endif//UFC_FILESYSTEM_DETAIL_FILE_WIN32_HPP