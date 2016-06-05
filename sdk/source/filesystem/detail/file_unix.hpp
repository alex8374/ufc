/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : filesystem/file_unix.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-05
  Description: 
  History    : 
*******************************************************************************/
    
#include "ufc/filesystem/detail/file_unix.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/container/buffer.hpp"
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <utime.h>
#include <cstring>
#include <dirent.h>

namespace ufc {
namespace detail {

    file_impl::file_impl()
    {
    }

    file_impl::file_impl(const string& __path)
    {
        set_path_impl(__path);
    }

    file_impl::~file_impl()
    {
    }

    void file_impl::set_path_impl(const string& __path)
    {
        _path = __path;
        string::size_type __n = _path.size();
        if (__n > 1 && _path[__n - 1] == '/')
        {
            _path.resize(__n - 1);
        }
    }

    const string& file_impl::get_path_impl() const
    {
        return _path;
    }

    bool file_impl::exists_impl() const
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        return stat(_path.c_str(), &__st) == 0;
    }

    bool file_impl::can_read_impl() const
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        if (stat(_path.c_str(), &__st) == 0)
        {
            if (geteuid() == 0)
                return true;
            else if (__st.st_uid == geteuid())
                return (__st.st_mode & S_IRUSR) != 0;
            else if (__st.st_gid == getegid())
                return (__st.st_mode & S_IRGRP) != 0;
            else
                return (__st.st_mode & S_IROTH) != 0;
        }
        else handle_last_error_impl(_path);
        return false;
    }

    bool file_impl::can_write_impl() const
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        if (stat(_path.c_str(), &__st) == 0)
        {
            if (geteuid() == 0)
                return true;
            else if (__st.st_uid == geteuid())
                return (__st.st_mode & S_IWUSR) != 0;
            else if (__st.st_gid == getegid())
                return (__st.st_mode & S_IWGRP) != 0;
            else
                return (__st.st_mode & S_IWOTH) != 0;
        }
        else handle_last_error_impl(_path);
        return false;
    }

    bool file_impl::can_execute_impl() const
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        if (stat(_path.c_str(), &__st) == 0)
        {
            if (__st.st_uid == geteuid() || geteuid() == 0)
                return (__st.st_mode & S_IXUSR) != 0;
            else if (__st.st_gid == getegid())
                return (__st.st_mode & S_IXGRP) != 0;
            else
                return (__st.st_mode & S_IXOTH) != 0;
        }
        else handle_last_error_impl(_path);
        return false;
    }

    bool file_impl::is_file_impl() const
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        if (stat(_path.c_str(), &__st) == 0)
            return S_ISREG(__st.st_mode);
        else
            handle_last_error_impl(_path);
        return false;
    }

    bool file_impl::is_directory_impl() const
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        if (stat(_path.c_str(), &__st) == 0)
            return S_ISDIR(__st.st_mode);
        else
            handle_last_error_impl(_path);
        return false;
    }

    bool file_impl::is_link_impl() const
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        if (lstat(_path.c_str(), &__st) == 0)
            return S_ISLNK(__st.st_mode);
        else
            handle_last_error_impl(_path);
        return false;
    }

    bool file_impl::is_device_impl() const
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        if (stat(_path.c_str(), &__st) == 0)
            return S_ISCHR(__st.st_mode) || S_ISBLK(__st.st_mode);
        else
            handle_last_error_impl(_path);
        return false;
    }

    bool file_impl::is_hidden_impl() const
    {
        ufc_assert (!_path.empty());
        path p(_path);
        p.make_file();

        return p.get_file_name().start_with('.');
    }

    timestamp file_impl::created_impl() const
    {
        ufc_assert (!_path.empty());

#if defined(__APPLE__) && defined(st_birthtime) && !defined(UFC_NO_STAT64) // st_birthtime is available only on 10.5
        struct stat64 __st;
        if (stat64(_path.c_str(), &__st) == 0)
            return timestamp::from_epoch_time(__st.st_birthtime);
#elif defined(__FreeBSD__)
        struct stat __st;
        if (stat(_path.c_str(), &__st) == 0)
            return timestamp::from_epoch_time(__st.st_birthtime);
#else
        struct stat __st;
        if (stat(_path.c_str(), &__st) == 0)
            return timestamp::from_epoch_time(__st.st_ctime);
#endif 
        else
            handle_last_error_impl(_path);
        return 0;
    }

    timestamp file_impl::get_last_modified_impl() const
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        if (stat(_path.c_str(), &__st) == 0)
            return timestamp::from_epoch_time(__st.st_mtime);
        else
            handle_last_error_impl(_path);
        return 0;
    }

    void file_impl::set_last_modified_impl(const timestamp& __ts)
    {
        ufc_assert (!_path.empty());

        struct utimbuf __tb;
        __tb.actime  = __ts.epoch_time();
        __tb.modtime = __ts.epoch_time();
        if (utime(_path.c_str(), &__tb) != 0)
            handle_last_error_impl(_path);
    }

    int64_t file_impl::get_size_impl() const
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        if (stat(_path.c_str(), &__st) == 0)
            return __st.st_size;
        else
            handle_last_error_impl(_path);
        return 0;
    }

    void file_impl::set_size_impl(int64_t __size)
    {
        ufc_assert (!_path.empty());

        if (truncate(_path.c_str(), __size) != 0)
            handle_last_error_impl(_path);
    }

    void file_impl::set_writeable_impl(bool __flag)
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        if (stat(_path.c_str(), &__st) != 0) 
            handle_last_error_impl(_path);
        mode_t __mode;
        if (__flag)
        {
            __mode = __st.st_mode | S_IWUSR;
        }
        else
        {
            mode_t wmask = S_IWUSR | S_IWGRP | S_IWOTH;
            __mode = __st.st_mode & ~wmask;
        }
        if (chmod(_path.c_str(), __mode) != 0) 
            handle_last_error_impl(_path);
    }

    void file_impl::set_executable_impl(bool __flag)
    {
        ufc_assert (!_path.empty());

        struct stat __st;
        if (stat(_path.c_str(), &__st) != 0) 
            handle_last_error_impl(_path);
        mode_t __mode;
        if (__flag)
        {
            __mode = __st.st_mode | S_IXUSR;
        }
        else
        {
            mode_t wmask = S_IXUSR | S_IXGRP | S_IXOTH;
            __mode = __st.st_mode & ~wmask;
        }
        if (chmod(_path.c_str(), __mode) != 0) 
            handle_last_error_impl(_path);
    }

    void file_impl::copy_to_impl(const string& __path) const
    {
        ufc_assert (!_path.empty());

        int __sd = open(_path.c_str(), O_RDONLY);
        if (__sd == -1) handle_last_error_impl(_path);

        struct stat __st;
        if (fstat(__sd, &__st) != 0) 
        {
            close(__sd);
            handle_last_error_impl(_path);
        }
        const long __block_size = __st.st_blksize;

        int __dd = open(__path.c_str(), O_CREAT | O_TRUNC | O_WRONLY, __st.st_mode & S_IRWXU);
        if (__dd == -1)
        {
            close(__sd);
            handle_last_error_impl(__path);
        }
        buffer<char> __buffer(__block_size);
        try
        {
            int n;
            while ((n = read(__sd, __buffer.get(), __block_size)) > 0)
            {
                if (write(__dd, __buffer.get(), n) != n) 
                    handle_last_error_impl(__path);
            }
            if (n < 0)
                handle_last_error_impl(_path);
        }
        catch (...)
        {
            close(__sd);
            close(__dd);
            throw;
        }
        close(__sd);
        if (fsync(__dd) != 0) 
        {
            close(__dd);
            handle_last_error_impl(__path);
        }
        if (close(__dd) != 0)
            handle_last_error_impl(__path);
    }

    void file_impl::rename_to_impl(const string& __path)
    {
        ufc_assert (!_path.empty());

        if (rename(_path.c_str(), __path.c_str()) != 0)
            handle_last_error_impl(_path);
    }

    void file_impl::remove_impl()
    {
        ufc_assert (!_path.empty());

        int rc;
        if (!is_link_impl() && is_directory_impl())
            rc = rmdir(_path.c_str());
        else
            rc = unlink(_path.c_str());
        if (rc) handle_last_error_impl(_path);
    }

    bool file_impl::create_file_impl()
    {
        ufc_assert (!_path.empty());

        int n = open(_path.c_str(), O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        if (n != -1)
        {
            close(n);
            return true;
        }
        if (n == -1 && errno == EEXIST)
            return false;
        else
            handle_last_error_impl(_path);
        return false;
    }

    bool file_impl::mkdir_impl()
    {
        ufc_assert (!_path.empty());

        if (exists_impl() && is_directory_impl())
            return false;
        if (::mkdir(_path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) != 0) 
            handle_last_error_impl(_path);
        return true;
    }

    void file_impl::list_impl(string_vec& __files) const
    {
        __files.clear();

        ufc_assert (!_path.empty());

        DIR* __dir = opendir(_path.c_str());
        if (!__dir) 
            handle_last_error_impl(_path);
        for (;;)
        {
            struct dirent* pEntry = readdir(__dir);
            if (!pEntry) break;
            string name = pEntry->d_name;
            if (name != "." && name != "..")
            {
                __files.push_back(name);
            }
        }
        closedir(__dir);
    }

    void file_impl::handle_last_error_impl(const string& __path)
    {
        switch (errno)
        {
        case EIO:
            throw io_error(__path);
        case EPERM:
            throw file_access_denied_error("insufficient permissions", __path);
        case EACCES:
            throw file_access_denied_error(__path);
        case ENOENT:
            throw file_not_found_error(__path);
        case ENOTDIR:
            throw open_file_error("not a directory", __path);
        case EISDIR:
            throw open_file_error("not a file", __path);
        case EROFS:
            throw file_read_only_error(__path);
        case EEXIST:
            throw file_exists_error(__path);
        case ENOSPC:
            throw file_error("no space left on device", __path);
        case EDQUOT:
            throw file_error("disk quota exceeded", __path);
#if !defined(_AIX)
        case ENOTEMPTY:
            throw file_error("directory not empty", __path);
#endif
        case ENAMETOOLONG:
            throw path_syntax_error(__path);
        case ENFILE:
        case EMFILE:
            throw file_error("too many open __files", __path);
        default:
            throw file_error(std::strerror(errno), __path);
        }
    }

}//namespace detail
}//namespace ufc
