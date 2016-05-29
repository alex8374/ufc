/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/event.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/thread/event.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/exception/exception.hpp"
#if defined(_WIN32) || defined(WIN32)
#include "thread/event_win32.hpp"
#else
#include "thread/event_posix.hpp"
#endif

namespace ufc {

    event::event(bool __auto_reset)
        : _impl(new private_t(__auto_reset))
    {
        ufc_check_ptr(_impl);
    }

    event::~event()
    {
        memory::delete_ptr(_impl);
    }

    void event::set()
    {
        _impl->set();
    }

    void event::wait()
    {
        _impl->wait();
    }

    void event::wait(long_t __milliseconds)
    {
        if (!_impl->wait(__milliseconds))
        {
            throw timeout_error();
        }
    }

    bool event::try_wait(long_t __milliseconds)
    {
        return _impl->wait(__milliseconds);
    }

    void event::reset()
    {
        _impl->reset();
    }

}//namespace ufc