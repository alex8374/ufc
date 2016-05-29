/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : filesystem/file_win32.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef FILESYSTEM_FILE_WIN32_HPP
#define FILESYSTEM_FILE_WIN32_HPP

#include "ufc/filesystem/file.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/container/buffer.hpp"
#include <Windows.h>

namespace ufc {

    class file::private_t
    {
    private:
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

    public:
        private_t()
        {
        }

        private_t(const string& __path)
        {
            set_path(__path);
        }

        ~private_t()
        {
        }

        void set_path(const string& __path)
        {
            _path = __path;
            string::size_type __n = _path.size();
            if (__n > 1 && (_path[__n - 1] == '\\' || _path[__n - 1] == '/') && !((__n == 3 && _path[1]==':')))
            {
                _path.resize(__n - 1);
            }
        }

        const string& get_path() const
        {
            return _path;
        }

        bool exists() const
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

        bool can_read() const
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

        bool can_write() const
        {
            ufc_assert (!_path.empty());

            DWORD attr = GetFileAttributes(_path.c_str());
            if (attr == 0xFFFFFFFF)
                handle_last_error(_path);
            return (attr & FILE_ATTRIBUTE_READONLY) == 0;
        }

        bool can_execute() const
        {
            path p(_path);
            return p.get_extension().icompare("exe") == 0;
        }

        bool is_file() const
        {
            return !is_directory() && !is_device();
        }

        bool is_directory() const
        {
            ufc_assert (!_path.empty());

            DWORD attr = GetFileAttributes(_path.c_str());
            if (attr == 0xFFFFFFFF)
                handle_last_error(_path);
            return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
        }

        bool is_link() const
        {
            return false;
        }

        bool is_device() const
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

        bool is_hidden() const
        {
            ufc_assert (!_path.empty());

            DWORD attr = GetFileAttributes(_path.c_str());
            if (attr == 0xFFFFFFFF)
                handle_last_error(_path);
            return (attr & FILE_ATTRIBUTE_HIDDEN) != 0;
        }

        timestamp created() const
        {
            ufc_assert (!_path.empty());

            WIN32_FILE_ATTRIBUTE_DATA fad;
            if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &fad) == 0) 
                handle_last_error(_path);
            return timestamp::from_file_time_np(fad.ftCreationTime.dwLowDateTime, fad.ftCreationTime.dwHighDateTime);
        }

        timestamp get_last_modified() const
        {
            ufc_assert (!_path.empty());

            WIN32_FILE_ATTRIBUTE_DATA fad;
            if (GetFileAttributesEx(_path.c_str(), GetFileExInfoStandard, &fad) == 0) 
                handle_last_error(_path);
            return timestamp::from_file_time_np(fad.ftLastWriteTime.dwLowDateTime, fad.ftLastWriteTime.dwHighDateTime);
        }

        void set_last_modified(const timestamp& __ts)
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

        int64_t get_size() const
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

        void set_size(int64_t __size)
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

        void set_writeable(bool __flag = true)
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

        void set_executable(bool __flag = true)
        {

        }

        void copy_to(const string& __path) const
        {
            ufc_assert (!_path.empty());

            if (CopyFileA(_path.c_str(), __path.c_str(), FALSE) != 0) 
            {
                private_t copy(__path);
                copy.set_writeable(true);
            }
            else 
                handle_last_error(_path);
        }

        void rename_to(const string& __path)
        {
            ufc_assert (!_path.empty());

            if (MoveFileA(_path.c_str(), __path.c_str()) == 0) 
                handle_last_error(_path);
        }

        void remove()
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

        bool create_file()
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

        bool mkdir()
        {
            ufc_assert (!_path.empty());

            if (exists() && is_directory())
                return false;
            if (CreateDirectoryA(_path.c_str(), 0) == 0)
                handle_last_error(_path);
            return true;
        }

        void list(string_vec& __files) const
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

        static void handle_last_error(const string& __path)
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

    private:
        string _path;
    };

}//namespace ufc

#endif//FILESYSTEM_FILE_WIN32_HPP
