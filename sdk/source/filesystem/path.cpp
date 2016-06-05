/*******************************************************************************
       Copyright(C) 2016, Free software engineer and contributor
 ******************************************************************************
  Filename   : core/path.cpp
  Author     : lcq<lichangqing8374@hotmail.com>
  Date       : 2016-05-09
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/filesystem/path.hpp"
#include "ufc/filesystem/file.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/string/string_tokenizer.hpp"
#include "ufc/system/environment.hpp"
#include "ufc/container/buffer.hpp"
#include <algorithm>
#if defined(ufc_os_family_windows)
#include "filesystem/path_win32.hpp"
#else
#include "filesystem/path_unix.hpp"
#endif

namespace ufc {

    path::path()
        : _absolute(false)
    {
    }

    path::path(bool __absolute)
        : _absolute(__absolute)
    {
    }

    path::path(const char* __path)
    {
        ufc_check_ptr(__path);
        assign(__path);
    }

    path::path(const string& __path)
    {
        assign(__path);
    }

    path::path(const path& __path)
        : _device(__path._device)
        , _dirs(__path._dirs)
        , _name(__path._name)
        , _absolute(__path._absolute)
    {    
    }

    path::path(const path& parent, const string& fileName)
        : _device(parent._device)
        , _dirs(parent._dirs)
        , _name(parent._name)
        , _absolute(parent._absolute)
    {
        make_directory();
        _name = fileName;
    }

    path::path(const path& parent, const char* fileName)
        : _device(parent._device)
        , _dirs(parent._dirs)
        , _name(parent._name)
        , _absolute(parent._absolute)
    {
        make_directory();
        _name = fileName;
    }

    path::path(const path& parent, const path& relative)
        : _device(parent._device)
        , _dirs(parent._dirs)
        , _name(parent._name)
        , _absolute(parent._absolute)
    {
        resolve(relative);
    }

    path::~path()
    {
    }

    path& path::operator = (const path& __path)
    {
        return assign(__path);
    }

    path& path::operator = (const string& __path)
    {
        return assign(__path);
    }

    path& path::operator = (const char* __path)
    {
        return assign(__path);
    }

    void path::swap(path& __path)
    {
        std::swap(_device, __path._device);
        std::swap(_dirs, __path._dirs);
        std::swap(_name, __path._name);
        std::swap(_absolute, __path._absolute);
    }

    path& path::assign(const path& __path)
    {
        if (this != &__path)
        {
            _device = __path._device;
            _dirs   = __path._dirs;
            _name   = __path._name;
            _absolute = __path._absolute;
        }
        return *this;
    }

    path& path::assign(const string& __path)
    {
        private_t::parse(*this, __path);
        return *this;
    }

    path& path::assign(const char* __path)
    {
        ufc_check_ptr(__path);
        return assign(string(__path));
    }

    string path::to_string() const
    {
        string __result;
        private_t::to_string(*this, __result);
        return __result;
    }

    path& path::parse(const string& __path)
    {
        return assign(__path);
    }

    bool path::try_parse(const string& __path)
    {
        try
        {
            path __p;
            __p.parse(__path);
            assign(__p);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    path& path::parse_directory(const string& __path)
    {
        assign(__path);
        return make_directory();
    }

    path& path::make_directory()
    {
        push_directory(_name);
        _name.clear();
        return *this;
    }

    path& path::make_file()
    {
        if (!_dirs.empty() && _name.empty())
        {
            _name = _dirs.back();
            _dirs.pop_back();
        }
        return *this;
    }

    path& path::make_parent()
    {
        if (_name.empty())
        {
            if (_dirs.empty())
            {
                if (!_absolute)
                    _dirs.push_back("..");
            }
            else
            {
                if (_dirs.back() == "..")
                    _dirs.push_back("..");
                else
                    _dirs.pop_back();
            }
        }
        else
        {
            _name.clear();
        }
        return *this;
    }

    path& path::make_absolute()
    {
        return make_absolute(current());
    }

    path& path::make_absolute(const path& __base_path)
    {
        if (!_absolute)
        {
            path __tmp = __base_path;
            __tmp.make_directory();
            for (string_vec::const_iterator __it = _dirs.begin(); __it != _dirs.end(); ++__it)
            {
                __tmp.push_directory(*__it);
            }
            _device   = __tmp._device;
            _dirs     = __tmp._dirs;
            _absolute = __base_path._absolute;
        }
        return *this;
    }

    path& path::append(const path& __path)
    {
        make_directory();
        _dirs.insert(_dirs.end(), __path._dirs.begin(), __path._dirs.end());
        _name = __path._name;
        return *this;
    }

    path& path::resolve(const path& __path)
    {
        if (__path.is_absolute())
        {
            assign(__path);
        }
        else
        {
            for (uint32_t i = 0; i < __path.depth(); ++i)
            {
                push_directory(__path[i]);
            }
            _name = __path._name;
        }
        return *this;
    }

    bool path::is_absolute() const
    {
        return _absolute;
    }

    bool path::is_relative() const
    {
        return !_absolute;
    }

    bool path::is_directory() const
    {
        return _name.empty();
    }

    bool path::is_file() const
    {
        return !_name.empty();
    }

    path& path::set_device(const string& device)
    {
        _device   = device;
        _absolute = _absolute || !device.empty();
        return *this;
    }

    const string& path::get_device() const
    {
        return _device;
    }

    uint32_t path::depth() const
    {
        return _dirs.size();
    }

    const string& path::directory(uint32_t __depth) const
    {
        ufc_assert (0 <= __depth && __depth <= int(_dirs.size()));

        if (__depth < uint32_t(_dirs.size()))
            return _dirs[__depth];
        else
            return _name;    
    }

    const string& path::operator [] (uint32_t __depth) const
    {
        return directory(__depth);
    }

    path& path::push_directory(const string& __dir)
    {
        if (!__dir.empty() && __dir != ".")
        {
            if (__dir == "..")
            {
                if (!_dirs.empty() && _dirs.back() != "..")
                    _dirs.pop_back();
                else if (!_absolute)
                    _dirs.push_back(__dir);
            }
            else 
                _dirs.push_back(__dir);
        }
        return *this;
    }

    path& path::pop_directory()
    {
        ufc_assert (!_dirs.empty());

        _dirs.pop_back();
        return *this;
    }

    path& path::pop_front_directory()
    {
        ufc_assert (!_dirs.empty());

        string_vec::iterator __it = _dirs.begin();
        _dirs.erase(__it);
        return *this;
    }

    path& path::set_file_name(const string& __name)
    {
        _name = __name;
        return *this;
    }

    const string& path::get_file_name() const
    {
        return _name;
    }

    path& path::set_base_name(const string& __name)
    {
        string __ext = get_extension();
        _name = __name;
        if (!__ext.empty())
        {
            _name.append(".");
            _name.append(__ext);
        }
        return *this;
    }

    string path::get_base_name() const
    {
        string::size_type __pos = _name.rfind('.');
        if (__pos != string::npos)
            return _name.substr(0, __pos);
        else
            return _name;
    }

    path& path::set_extension(const string& __extension)
    {
        _name = get_base_name();
        if (!__extension.empty())
        {
            _name.append(".");
            _name.append(__extension);
        }
        return *this;
    }

    string path::get_extension() const
    {
        string::size_type __pos = _name.rfind('.');
        if (__pos != string::npos)
            return _name.substr(__pos + 1);
        else
            return string();
    }

    path& path::clear()
    {
        _device.clear();
        _name.clear();
        _dirs.clear();
        _absolute = false;
        return *this;
    }

    path path::parent() const
    {
        path __p(*this);
        return __p.make_parent();
    }

    path path::absolute() const
    {
        path __result(*this);
        if (!__result._absolute)
        {
            __result.make_absolute();
        }
        return __result;
    }

    path path::absolute(const path& __base_path) const
    {
        path __result(*this);
        if (!__result._absolute)
        {
            __result.make_absolute(__base_path);
        }
        return __result;
    }

    path path::for_directory(const string& __path)
    {
        path __p;
        return __p.parse_directory(__path);
    }

    string path::current()
    {
        return private_t::current();
    }

    string path::home()
    {
        return private_t::home();
    }

    string path::temp()
    {
        return private_t::temp();
    }

    string path::null()
    {
        return private_t::null();
    }

    void path::list_roots(string_vec& __roots)
    {
        __roots.clear();
        return private_t::list_roots(__roots);
    }

    bool path::find(const string& __name, path& __path, string __path_list)
    {
        if (__name.empty()) return false;

        if (__path_list.empty())
        {
            __path_list = environment::get("PATH");
        }

        string_tokenizer __st(__path_list, path_separator(), string_tokenizer::tok_ignore_empty + string_tokenizer::tok_trim);

        string_vec::const_iterator __it  = __st.begin();
        string_vec::const_iterator __end = __st.end();
        while (__it != __end)
        {
#if defined(ufc_os_family_windows)
            string __clean_path(*__it);
            if (__clean_path.size() > 1 && __clean_path[0] == '"' && __clean_path[__clean_path.size() - 1] == '"')
            {
                __clean_path = __clean_path.substr(1, __clean_path.size() - 2);
            }
            path __p(__clean_path);
#else
            path __p(*__it);
#endif
            __p.make_directory();
            __p.resolve(path(__name));
            file __f(__p);
            if (__f.exists() && (__f.is_file() || __f.is_link()))
            {
                __path = __p;
                return true;
            }
            ++__it;
        }
        return false;
    }

    string path::convert_native_path(const string& __path)
    {
        string __result;
        char   __peer_separator = separator_char() == '/'? '\\': '/';
        for (string::const_iterator __it = __path.begin(); __it != __path.end(); __it++)
        {
            if (*__it == __peer_separator)
                __result += separator();
            else
                __result += *__it;
        }
        return __result;
    }

    char path::separator_char()
    {
        return private_t::separator_char();
    }

    string path::separator()
    {
        return private_t::separator();
    }

    char path::path_separator_char()
    {
        return private_t::path_separator_char();
    }

    string path::path_separator()
    {
        return private_t::path_separator();
    }

    string path::get_library_path_list()
    {
        return private_t::get_library_path_list();
    }

}//namespace ufc
