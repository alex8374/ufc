/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/thread_local.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-22
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/thread/thread_local.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/exception/exception.hpp"
#if defined(ufc_os_family_windows)
#include "thread/thread_local_win32.hpp"
#else
#include "thread/thread_local_posix.hpp"
#endif

namespace ufc {

    tls_abstract_slot::tls_abstract_slot()
    {
    }

    tls_abstract_slot::~tls_abstract_slot()
    {
    }

    thread_local_storage::thread_local_storage()
        : _impl(new private_t)
    {
        ufc_check_ptr(_impl);
    }

    thread_local_storage::~thread_local_storage()
    {
        memory::delete_ptr(_impl);
    }

    void thread_local_storage::set(tls_abstract_slot* __value)
    {
        _impl->set(__value);
    }

    tls_abstract_slot* thread_local_storage::get() const
    {
        return _impl->get();
    }

}//namespace ufc
