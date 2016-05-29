/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/filesyteam/file.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_FILESYTEAM_FILE_HPP
#define UFC_FILESYTEAM_FILE_HPP

#include <ufc/string/string.hpp>
#include <ufc/datetime/timestamp.hpp>
#include <ufc/filesystem/path.hpp>
#include <ufc/container/vector.hpp>

namespace ufc {

    /// 
    /// @brief: the file class provides methods for working with a file.
    ///
    class ufc_api file: virtual public object
    {
    public:
        typedef vector<file> file_vec;

        file();
        file(const string& __path);
        file(const char* __path);
        file(const path& __path);
        file(const file& __file);
        virtual ~file();

        file& operator = (const file& __file);
        file& operator = (const string& __path);
        file& operator = (const char* __path);
        file& operator = (const path& __path);

        const string& get_path() const;

        bool exists() const;

        bool can_read() const;
        bool can_write() const;
        bool can_execute() const;

        bool is_file() const;
        bool is_link() const;
        bool is_directory() const;
        bool is_device() const;
        bool is_hidden() const;

        timestamp created() const;

        timestamp get_last_modified() const;
        file& set_last_modified(const timestamp& __ts);

        int64_t get_size() const;
        file& set_size(int64_t __size);

        file& set_writeable(bool __flag = true);
        file& set_read_only(bool __flag = true);
        file& set_executable(bool __flag = true);

        void copy_to(const string& __path) const;
        void move_to(const string& __path);
        void rename_to(const string& __path);
        void remove(bool __recursive = false);

        bool create_file();
        bool mkdir();
        void mkdirs();

        void list(string_vec& __files) const;
        void list(file_vec& __files) const;

        bool operator == (const file& __file) const;
        bool operator != (const file& __file) const;
        bool operator <  (const file& __file) const;
        bool operator <= (const file& __file) const;
        bool operator >  (const file& __file) const;
        bool operator >= (const file& __file) const;

        static void handle_last_error(const string& __path);

    private:
        class private_t;
        private_t* _impl;
    };

}//namespace ufc

#endif//UFC_FILESYTEAM_FILE_HPP