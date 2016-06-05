/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/exception/exception.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_EXCEPTION_EXCEPTION_HPP
#define UFC_EXCEPTION_EXCEPTION_HPP

#include <ufc/base/config.hpp>
#include <ufc/string/string.hpp>
#include <stdexcept>

#define ufc_declare_exception_ex(__cls, __base, __default_code)                                         \
    class ufc_api __cls: public __base                                                                  \
    {                                                                                                   \
    public:                                                                                             \
        explicit __cls(ufc::int32_t __code = __default_code);                                           \
        __cls(const ufc::string& __msg, ufc::int32_t __code = __default_code);                          \
        __cls(const ufc::string& __msg, const ufc::string& __arg, ufc::int32_t __code = __default_code);\
        __cls(const __cls& __rhs);                                                                      \
        virtual ~__cls() throw();                                                                       \
        __cls& operator = (const __cls& __rhs);                                                         \
        virtual const char* name() const;                                                               \
        virtual void rethrow() const;                                                                   \
    };

#define ufc_declare_exception(__cls, __base)                                                            \
    ufc_declare_exception_ex(__cls, __base, 0)

#define ufc_implement_exception(__cls, __base, __name)                                                  \
    __cls::__cls(ufc::int32_t __code)                                                                   \
        : __base(__code)                                                                                \
    {                                                                                                   \
    }                                                                                                   \
    __cls::__cls(const ufc::string& __msg, ufc::int32_t __code)                                         \
        : __base(__msg, __code)                                                                         \
    {                                                                                                   \
    }                                                                                                   \
    __cls::__cls(const ufc::string& __msg, const ufc::string& __arg, ufc::int32_t __code)               \
        : __base(__msg, __arg, __code)                                                                  \
    {                                                                                                   \
    }                                                                                                   \
    __cls::__cls(const __cls& __rhs)                                                                    \
        : __base(__rhs)                                                                                 \
    {                                                                                                   \
    }                                                                                                   \
    __cls::~__cls() throw()                                                                             \
    {                                                                                                   \
    }                                                                                                   \
    __cls& __cls::operator = (const __cls& __rhs)                                                       \
    {                                                                                                   \
        __base::operator = (__rhs);                                                                     \
        return *this;                                                                                   \
    }                                                                                                   \
    const char* __cls::name() const                                                                     \
    {                                                                                                   \
        return __name;                                                                                  \
    }                                                                                                   \
    void __cls::rethrow() const                                                                         \
    {                                                                                                   \
        throw *this;                                                                                    \
    }

namespace ufc {

    ///
    /// @breif: exception basic class
    ///
    class ufc_api exception: public std::exception, virtual public object
    {
    public:
        exception(const string& __msg, int32_t __code = 0);
        exception(const string& __msg, const string& __arg, int32_t __code = 0);
        exception(const exception& __rhs);
        virtual ~exception() throw();

        exception& operator = (const exception& __rhs);

        int32_t code() const;
        const string& message() const;
        string display_text() const;

        virtual const char* what() const throw();
        virtual const char* name() const;
        virtual void rethrow() const;

    protected:
        explicit exception(int32_t __code = 0);

    private:
        int32_t _code;
        string  _msg;
    };

    //
    // standard exception classes
    //
    ufc_declare_exception(logic_error,                      exception)
    ufc_declare_exception(runtime_error,                    exception)

    ufc_declare_exception(assertion_violation_error,        logic_error)
    ufc_declare_exception(null_pointer_error,               logic_error)
    ufc_declare_exception(invalid_argument_error,           logic_error)
    ufc_declare_exception(not_implemented_error,            logic_error)
    ufc_declare_exception(range_error,                      logic_error)
    ufc_declare_exception(signal_error,                     logic_error)

    ufc_declare_exception(system_error,                     runtime_error)
    ufc_declare_exception(not_found_error,                  runtime_error)
    ufc_declare_exception(exists_error,                     runtime_error)
    ufc_declare_exception(timeout_error,                    runtime_error)
    ufc_declare_exception(io_error,                         runtime_error)
    ufc_declare_exception(data_error,                       runtime_error)
    ufc_declare_exception(lirary_load_error,                runtime_error)
    ufc_declare_exception(lirary_already_loaded_error,      runtime_error)
    ufc_declare_exception(no_thread_available_error,        runtime_error)
    ufc_declare_exception(no_permission_error,              runtime_error)
    ufc_declare_exception(out_of_memory_error,              runtime_error)
    ufc_declare_exception(mq_error,                         runtime_error)
    ufc_declare_exception(database_error,                   runtime_error)

    ufc_declare_exception(regular_expression_error,         data_error)
    ufc_declare_exception(data_format_error,                data_error)
    ufc_declare_exception(syntax_error,                     data_error)

    ufc_declare_exception(path_syntax_error,                syntax_error)

    ufc_declare_exception(protocol_error,                   io_error)
    ufc_declare_exception(file_error,                       io_error)

    ufc_declare_exception(file_exists_error,                file_error)
    ufc_declare_exception(file_not_found_error,             file_error)
    ufc_declare_exception(path_not_found_error,             file_error)
    ufc_declare_exception(file_read_only_error,             file_error)
    ufc_declare_exception(file_access_denied_error,         file_error)
    ufc_declare_exception(create_file_error,                file_error)
    ufc_declare_exception(open_file_error,                  file_error)
    ufc_declare_exception(write_file_error,                 file_error)
    ufc_declare_exception(read_file_error,                  file_error)

}//namespace ufc

#endif//UFC_EXCEPTION_EXCEPTION_HPP
