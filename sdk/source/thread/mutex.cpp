/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/mutex.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/thread/mutex.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/exception/exception.hpp"
#if defined(ufc_os_family_windows)
#include "thread/mutex_win32.hpp"
#else
#include "thread/mutex_posix.hpp"
#endif

namespace ufc {

    mutex::scoped_lock::scoped_lock(mutex& __mutex)
        : _mutex(__mutex)
    {
        _mutex.lock();
    }

    mutex::scoped_lock::scoped_lock(mutex& __mutex, long_t __milliseconds)
        : _mutex(__mutex)
    {
        _mutex.lock(__milliseconds);
    }

    mutex::scoped_lock::~scoped_lock()
    {
        _mutex.unlock();
    }

    mutex::scoped_unlock::scoped_unlock(mutex& __mutex, bool __unlock_now)
        : _mutex(__mutex)
    {
        if (__unlock_now)
        {
            _mutex.unlock();
        }
    }
    
    mutex::scoped_unlock::~scoped_unlock()
    {
        _mutex.lock();
    }

    mutex::mutex()
        : _impl(new private_t())
    {
        ufc_check_ptr(_impl);
    }

    mutex::~mutex()
    {
        memory::delete_ptr(_impl);
    }

    void mutex::lock()
    {
        _impl->lock();
    }

    void mutex::lock(long_t __milliseconds)
    {
        if (!_impl->try_lock(__milliseconds))
        {
            throw timeout_error();
        }
    }

    bool mutex::try_lock()
    {
        return _impl->try_lock();
    }

    bool mutex::try_lock(long_t __milliseconds)
    {
        return _impl->try_lock(__milliseconds);
    }

    void mutex::unlock()
    {
        _impl->unlock();
    }

}//namespace ufc
