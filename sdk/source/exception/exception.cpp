/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : exception/exception.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/exception/exception.hpp"

namespace ufc {

    exception::exception(int32_t __code)
        : _code(__code)
    {
    }

    exception::exception(const string& __msg, int32_t __code)
        : _code(__code)
        , _msg(__msg)
    {
    }

    exception::exception(const string& __msg, const string& __arg, int32_t __code)
        : _code(__code)
        , _msg(__msg)
    {
        if (!__arg.empty())
        {
            _msg.append(": ");
            _msg.append(__arg);
        }
    }

    exception::exception(const exception& __rhs)
        : _code(__rhs._code)
        , _msg(__rhs._msg)
    {
    }

    exception::~exception() throw()
    {
    }

    exception& exception::operator = (const exception& __rhs)
    {
        if (this != &__rhs)
        {
            _code = __rhs._code;
            _msg = __rhs._msg;
        }
        return *this;
    }

    int32_t exception::code() const
    {
        return _code;
    }

    const string& exception::message() const
    {
        return _msg;
    }

    string exception::display_text() const
    {
        string __result = name();
        if (!_msg.empty())
        {
            __result.append(": ");
            __result.append(_msg);
        }
        return __result;
    }

    const char* exception::what() const throw()
    {
        return name();
    }

    const char* exception::name() const
    {
        return "exception";
    }

    void exception::rethrow() const
    {
        throw *this;
    }

    ///
    /// @standard exception classes
    ///
    ufc_implement_exception(logic_error,                      exception,        "logic error")
    ufc_implement_exception(runtime_error,                    exception,        "runtime error")

    ufc_implement_exception(assertion_violation_error,        logic_error,      "assertion violation")
    ufc_implement_exception(null_pointer_error,               logic_error,      "null pointer")
    ufc_implement_exception(invalid_argument_error,           logic_error,      "invalid argument")
    ufc_implement_exception(not_implemented_error,            logic_error,      "not implemented")
    ufc_implement_exception(range_error,                      logic_error,      "out of range")
    ufc_implement_exception(signal_error,                     logic_error,      "signal received")

    ufc_implement_exception(system_error,                     runtime_error,    "system error")
    ufc_implement_exception(not_found_error,                  runtime_error,    "not found")
    ufc_implement_exception(exists_error,                     runtime_error,    "exists")
    ufc_implement_exception(timeout_error,                    runtime_error,    "timeout")
    ufc_implement_exception(io_error,                         runtime_error,    "i/o error")
    ufc_implement_exception(data_error,                       runtime_error,    "data error")
    ufc_implement_exception(lirary_load_error,                runtime_error,    "cannot load library")
    ufc_implement_exception(lirary_already_loaded_error,      runtime_error,    "library already loaded")
    ufc_implement_exception(no_thread_available_error,        runtime_error,    "no thread available")
    ufc_implement_exception(no_permission_error,              runtime_error,    "no permission")
    ufc_implement_exception(out_of_memory_error,              runtime_error,    "out of memory")
    ufc_implement_exception(mq_error,                         runtime_error,    "IBM Websphere MQ error")
    ufc_implement_exception(database_error,                   runtime_error,    "database error")

    ufc_implement_exception(regular_expression_error,         data_error,       "error in regular expression")
    ufc_implement_exception(data_format_error,                data_error,       "bad data format")
    ufc_implement_exception(syntax_error,                     data_error,       "syntax error")

    ufc_implement_exception(path_syntax_error,                syntax_error,     "bad path syntax")

    ufc_implement_exception(protocol_error,                   io_error,         "protocal error")
    ufc_implement_exception(file_error,                       io_error,         "file access error")

    ufc_implement_exception(file_exists_error,                file_error,       "file exists")
    ufc_implement_exception(file_not_found_error,             file_error,       "file not found")
    ufc_implement_exception(path_not_found_error,             file_error,       "path not found")
    ufc_implement_exception(file_read_only_error,             file_error,       "file is read-only")
    ufc_implement_exception(file_access_denied_error,         file_error,       "access to file denied")
    ufc_implement_exception(create_file_error,                file_error,       "cannot create file")
    ufc_implement_exception(open_file_error,                  file_error,       "cannot open file")
    ufc_implement_exception(write_file_error,                 file_error,       "cannot write file")
    ufc_implement_exception(read_file_error,                  file_error,       "cannot read file")

}//namespace ufc
