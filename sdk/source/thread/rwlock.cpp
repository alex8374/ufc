/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/rwlock.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-21
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/thread/rwlock.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/exception/exception.hpp"
#if defined(ufc_os_family_windows)
#include "thread/rwlock_win32.hpp"
#else
#include "thread/rwlock_posix.hpp"
#endif

namespace ufc {

    rwlock::scoped_rwlock::scoped_rwlock(rwlock& __rwl, bool __write)
        : _rwl(__rwl)
    {
        if (__write)
            _rwl.write_lock();
        else
            _rwl.read_lock();
    }

    rwlock::scoped_rwlock::~scoped_rwlock()
    {
        _rwl.unlock();
    }
    
    rwlock::scoped_read_rwlock::scoped_read_rwlock(rwlock& __rwl)
        : scoped_rwlock(__rwl, false)
    {
    }

    rwlock::scoped_read_rwlock::~scoped_read_rwlock()
    {
    }

    rwlock::scoped_write_rwlock::scoped_write_rwlock(rwlock& __rwl)
        : scoped_rwlock(__rwl, true)
    {
    }

    rwlock::scoped_write_rwlock::~scoped_write_rwlock()
    {
    }
    
    rwlock::rwlock()
        : _impl(new private_t())
    {
        ufc_check_ptr(_impl);
    }
    
    rwlock::~rwlock()
    {
        memory::delete_ptr(_impl);
    }
    
    void rwlock::read_lock()
    {
        _impl->read_lock();
    }

    bool rwlock::try_read_lock()
    {
        return _impl->try_read_lock();
    }

    void rwlock::write_lock()
    {
        _impl->write_lock();
    }

    bool rwlock::try_write_lock()
    {
        return _impl->try_write_lock();
    }

    void rwlock::unlock()
    {
        _impl->unlock();
    }

}//namespace ufc
