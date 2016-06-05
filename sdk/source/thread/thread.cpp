/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/thread.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-22
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/thread/thread.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/exception/exception.hpp"
#if defined(ufc_os_family_windows)
#include "thread/thread_win32.hpp"
#else
#include "thread/thread_posix.hpp"
#endif

namespace ufc {

    thread::thread()
        : _impl(new private_t(this, ""))
    {
        ufc_check_ptr(_impl);
    }

    thread::thread(const string& __name)
        : _impl(new private_t(this, __name))
    {
        ufc_check_ptr(_impl);
    }

    thread::~thread()
    {
        memory::delete_ptr(_impl);
    }

    void thread::start(runnable& __target)
    {
        _impl->start(__target);
    }

    void thread::join()
    {
        _impl->join();
    }

    void thread::join(long_t __milliseconds)
    {
        if (_impl->join(__milliseconds))
        {
            throw timeout_error();
        }
    }

    bool thread::try_join(long_t __milliseconds)
    {
        return _impl->join(__milliseconds);
    }

    bool thread::is_running() const
    {
        return _impl->is_running();
    }

    int32_t thread::id() const
    {
        return _impl->id();
    }

    int32_t thread::tid() const
    {
        return _impl->tid();
    }

    string thread::get_name() const
    {
        return _impl->get_name();
    }

    void thread::set_name(const string& __name)
    {
        _impl->set_name(__name);
    }

    void thread::set_priority(priority __prio)
    {
        _impl->set_priority(__prio);
    }

    thread::priority thread::get_priority() const
    {
        return (priority)_impl->get_priority();
    }

    void thread::set_os_priority(int32_t __prio)
    {
        _impl->set_os_priority(__prio);
    }

    int32_t thread::get_os_priority() const
    {
        return _impl->get_os_priority();
    }

    void thread::set_stack_size(int32_t __size)
    {
        _impl->set_stack_size(__size);
    }

    int32_t thread::get_stack_size() const
    {
        return _impl->get_stack_size();
    }

    void thread::sleep(long_t __milliseconds)
    {
        private_t::sleep(__milliseconds);
    }

    void thread::usleep(long_t __microseconds)
    {
        private_t::usleep(__microseconds);
    }

    void thread::yield()
    {
        private_t::yield();
    }

    thread* thread::current()
    {
        return private_t::current();
    }

    int32_t thread::current_tid()
    {
        return private_t::current_tid();
    }

    int32_t thread::get_min_os_priority()
    {
        return private_t::get_min_os_priority();
    }

    int32_t thread::get_max_os_priority()
    {
        return private_t::get_max_os_priority();
    }
        
}//namespace ufc