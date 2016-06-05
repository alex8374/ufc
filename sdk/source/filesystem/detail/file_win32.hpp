/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : filesystem/file_win32.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-05
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/filesystem/detail/file_win32.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#include <Windows.h>

namespace ufc {
namespace detail {

    class file_handle
    {
    public:
        file_handle(const string& __path, DWORD access, DWORD share, DWORD disp)
        {
            _h = CreateFileA(__path.c_str(), access, share, 0, disp, 0, 0);
            if (_h == INVALID_HANDLE_VALUE)
            {
                file::private_t::handle_last_error(__path);
            }
        }

        ~file_handle()
        {
            if (_h != INVALID_HANDLE_VALUE) CloseHandle(_h);
        }

        HANDLE get() const
        {
            return _h;
        }

    private:
        HANDLE _h;
    };

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
        if (__n > 1 && (_path[__n - 1] == '\\' || _path[__n - 1] == '/') && !((__n == 3 && _path[1]==':')))
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

        DWORD attr = GetFileAttributes(_path.c_str());
        if (attr == 0xFFFFFFFF)
        {
            switch (GetLastError())
            {
            case ERROR_FILE_NOT_FOUND:
            case ERROR_PATH_NOT_FOUND:
            case ERROR_NOT_READY:
            case ERROR_INVALID_DRIVE:
                return false;
            default:
                handle_last_error(_path);
            }
        }
        return true;
    }

    bool file_impl::can_read_impl() const
    {
        ufc_assert (!_path.empty());

        DWORD attr = GetFileAttributes(_path.c_str());
        if (attr == 0xFFFFFFFF)
        {
            switch (GetLastError())
            {
            case ERROR_ACCESS_DENIED:
                return false;
            default:
                handle_last_error(_path);
            }
        }
        return true;
    }

    bool file_impl::can_write_impl() const
    {
        ufc_assert (!_path.empty());

        DWORD attr = GetFileAttributes(_path.c_str());
        if (attr == 0xFFFFFFFF)
            handle_last_error(_path);
        return (attr & FILE_ATTRIBUTE_READONLY) == 0;
    }

    bool file_impl::can_execute_impl() const
    {
        path p(_path);
        return p.get_extension().icompare("exe") == 0;
    }

    bool file_impl::is_file_impl() const
    {
        return !is_directory() && !is_device();
    }

    bool file_impl::is_directory_impl() const
    {
        ufc_assert (!_path.empty());

        DWORD attr = GetFileAttributes(_path.c_str());
        if (attr == 0xFFFFFFFF)
            handle_last_error(_path);
        return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
    }

    bool file_impl::is_link_impl() const
    {
        return false;
    }

    bool file_impl::is_device_impl() const
    {
        ufc_assert (!_path.empty());

        file_handle __fh(_path, GENERIC_READ, 0, OPEN_EXISTING);
        DWORD type = GetFileType(__fh.get());
        if (type == FILE_TYPE_CHAR)
            return true;
        else if (type == FILE_TYPE_UNKNOWN && GetLastError() != NO_ERROR)
            handle_last_error(_path);
        return false;
    }

    bool file_impl::is_hidden_impl() const
    {
        ufc_assert (!_path.empty());

        DWORD attr = GetFileAttributes(_path.c_str());
        if (attr == 0xFFFFFFFF)
            handle_last_error(_path);
        return (attr & FILE_ATTRIBUTE_HIDDEN) != 0;
    }

    timestamp file_impl::created_impl() const
    {
        ufc_assert (!_path.empty());

        WIN32_FILE_ATTRIBUTE_DATA fad;
        if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &fad) == 0) 
            handle_last_error(_path);
        return timestamp::from_file_time_np(fad.ftCreationTime.dwLowDateTime, fad.ftCreationTime.dwHighDateTime);
    }

    timestamp file_impl::get_last_modified_impl() const
    {
        ufc_assert (!_path.empty());

        WIN32_FILE_ATTRIBUTE_DATA fad;
        if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &fad) == 0) 
            handle_last_error(_path);
        return timestamp::from_file_time_np(fad.ftLastWriteTime.dwLowDateTime, fad.ftLastWriteTime.dwHighDateTime);
    }

    void file_impl::set_last_modified_impl(const timestamp& __ts)
    {
        ufc_assert (!_path.empty());

        uint32_t low;
        uint32_t high;
        __ts.to_file_time_np(low, high);
        FILETIME ft;
        ft.dwLowDateTime  = low;
        ft.dwHighDateTime = high;
        file_handle __fh(_path, FILE_ALL_ACCESS, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
        if (SetFileTime(__fh.get(), 0, &ft, &ft) == 0)
            handle_last_error(_path);
    }

    int64_t file_impl::get_size_impl() const
    {
        ufc_assert (!_path.empty());

        WIN32_FILE_ATTRIBUTE_DATA fad;
        if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &fad) == 0) 
            handle_last_error(_path);
        LARGE_INTEGER li;
        li.LowPart  = fad.nFileSizeLow;
        li.HighPart = fad.nFileSizeHigh;
        return li.QuadPart;
    }

    void file_impl::set_size_impl(int64_t __size)
    {
        ufc_assert (!_path.empty());

        file_handle __fh(_path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
        LARGE_INTEGER li;
        li.QuadPart = __size;
        if (SetFilePointer(__fh.get(), li.LowPart, &li.HighPart, FILE_BEGIN) == -1)
            handle_last_error(_path);
        if (SetEndOfFile(__fh.get()) == 0) 
            handle_last_error(_path);
    }

    void file_impl::set_writeable_impl(bool __flag)
    {
        ufc_assert (!_path.empty());

        DWORD attr = GetFileAttributes(_path.c_str());
        if (attr == -1)
            handle_last_error(_path);
        if (__flag)
            attr &= ~FILE_ATTRIBUTE_READONLY;
        else
            attr |= FILE_ATTRIBUTE_READONLY;
        if (SetFileAttributes(_path.c_str(), attr) == 0)
            handle_last_error(_path);
    }

    void file_impl::set_executable_impl(bool __flag)
    {
    }

    void file_impl::copy_to_impl(const string& __path) const
    {
        ufc_assert (!_path.empty());

        if (CopyFileA(_path.c_str(), __path.c_str(), FALSE) != 0) 
        {
            file_impl copy(__path);
            copy.set_writeable(true);
        }
        else 
            handle_last_error(_path);
    }

    void file_impl::rename_to_impl(const string& __path)
    {
        ufc_assert (!_path.empty());

        if (MoveFileA(_path.c_str(), __path.c_str()) == 0) 
            handle_last_error(_path);
    }

    void file_impl::remove_impl()
    {
        ufc_assert (!_path.empty());

        if (is_directory())
        {
            if (RemoveDirectoryA(_path.c_str()) == 0) 
                handle_last_error(_path);
        }
        else
        {
            if (DeleteFileA(_path.c_str()) == 0)
                handle_last_error(_path);
        }
    }

    bool file_impl::create_file_impl()
    {
        ufc_assert (!_path.empty());

        HANDLE __file_handle = CreateFileA(_path.c_str(), GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0);
        if (__file_handle != INVALID_HANDLE_VALUE)
        {
            CloseHandle(__file_handle);
            return true;
        }
        else if (GetLastError() == ERROR_FILE_EXISTS)
            return false;
        else
            handle_last_error(_path);
        return false;
    }

    bool file_impl::mkdir_impl()
    {
        ufc_assert (!_path.empty());

        if (exists() && is_directory())
            return false;
        if (CreateDirectoryA(_path.c_str(), 0) == 0)
            handle_last_error(_path);
        return true;
    }

    void file_impl::list_impl(string_vec& __files) const
    {
        __files.clear();

        ufc_assert (!_path.empty());

        HANDLE          __fh;
        WIN32_FIND_DATA __fd;

        string __find_path = _path + "\\*";
        __fh = FindFirstFile(__find_path.c_str(), &__fd);
        if (__fh == INVALID_HANDLE_VALUE)
        {
            if (GetLastError() != ERROR_NO_MORE_FILES)
                handle_last_error(_path);
        }
        else
        {
            for (;;)
            {
                string name = __fd.cFileName;
                if (name != "." && name != "..")
                {
                    __files.push_back(name);
                }

                if (FindNextFile(__fh, &__fd) == FALSE)
                {
                    break;
                }
            }
            FindClose(__fh);
        }
    }

    void file_impl::handle_last_error_impl(const string& __path)
    {
        switch (GetLastError())
        {
        case ERROR_FILE_NOT_FOUND:
            throw file_not_found_error(__path);
        case ERROR_PATH_NOT_FOUND:
        case ERROR_BAD_NETPATH:
        case ERROR_CANT_RESOLVE_FILENAME:
        case ERROR_INVALID_DRIVE:
            throw PathNotFoundException(__path);
        case ERROR_ACCESS_DENIED:
            throw file_access_denied_error(__path);
        case ERROR_ALREADY_EXISTS:
        case ERROR_FILE_EXISTS:
            throw file_exists_error(__path);
        case ERROR_INVALID_NAME:
        case ERROR_DIRECTORY:
        case ERROR_FILENAME_EXCED_RANGE:
        case ERROR_BAD_PATHNAME:
            throw path_syntax_error(__path);
        case ERROR_FILE_READ_ONLY:
            throw file_read_only_error(__path);
        case ERROR_CANNOT_MAKE:
            throw CreateFileException(__path);
        case ERROR_DIR_NOT_EMPTY:
            throw file_error("directory not empty", __path);
        case ERROR_WRITE_FAULT:
            throw WriteFileException(__path);
        case ERROR_READ_FAULT:
            throw ReadFileException(__path);
        case ERROR_SHARING_VIOLATION:
            throw file_error("sharing violation", __path);
        case ERROR_LOCK_VIOLATION:
            throw file_error("lock violation", __path);
        case ERROR_HANDLE_EOF:
            throw ReadFileException("EOF reached", __path);
        case ERROR_HANDLE_DISK_FULL:
        case ERROR_DISK_FULL:
            throw WriteFileException("disk is full", __path);
        case ERROR_NEGATIVE_SEEK:
            throw file_error("negative seek", __path);
        default:
            throw file_error(__path);
        }
    }

}//namespace detail
}//namespace ufc

