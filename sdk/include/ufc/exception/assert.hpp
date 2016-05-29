/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/exception/assert.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_EXCEPTION_ASSERT_HPP
#define UFC_EXCEPTION_ASSERT_HPP

#include <ufc/base/config.hpp>

namespace ufc {

    /// 
    /// @breif: This class provides some static methods that are
    ///         used by the ufc_assert() and ufc_check_ptr() macros. 
    ///         You should not invoke these methods
    ///         directly. Use the macros instead, as they
    ///         automatically provide useful context information.
    /// 
    class ufc_api assertion: virtual public object
    {
    public:
        /// 
		/// @breif: An assertion failed. Break into the debugger, if
		///         possible, then throw an assertion_violation_error.
        /// 
        static void assert_(bool        __condition, 
                            const char* __description, 
                            const char* __file, 
                            uint32_t    __line)
        {
            if (__condition) 
            {
                throw_assert_(__description, __file, __line);
            }
        }

        /// 
		/// @breif: An null pointer was encountered. Break into the debugger, if
		///         possible, then throw an null_pointer_error.
        /// 
        static void check_ptr_(bool        __condition, 
                               const char* __description, 
                               const char* __file, 
                               uint32_t    __line)
        {
            if (__condition)
            {
                throw_check_ptr_(__description, __file, __line);
            }
        }

    private:
        static void throw_assert_(const char* __description, 
                                  const char* __file, 
                                  uint32_t    __line);

        static void throw_check_ptr_(const char* __description, 
                                     const char* __file, 
                                     uint32_t    __line);
    };

}//namespace ufc

//
// useful macros (these automatically supply line number and file name)
//
#define ufc_static_assert(__cond)     \
    typedef char ufc_join(__ufc_static_assertion, __LINE__)[(__cond)? 1: -1]

#define ufc_assert(__cond)            \
    ufc::assertion::assert_(!(__cond), ufc_string(__cond), __FILE__, __LINE__)

#define ufc_check_ptr(__ptr)        \
    ufc::assertion::check_ptr_(!(__ptr), ufc_string(__ptr), __FILE__, __LINE__)

#endif//UFC_EXCEPTION_ASSERT_HPP