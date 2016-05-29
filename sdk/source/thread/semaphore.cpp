/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/semaphore.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-21
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/thread/semaphore.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#if defined(_WIN32) || defined(WIN32)
#include "thread/semaphore_win32.hpp"
#else
#include "thread/semaphore_posix.hpp"
#endif

namespace ufc {

    semaphore::semaphore(int32_t __n)
        : _impl(new private_t(__n, __n))
    {
        ufc_check_ptr(_impl);
    }

    semaphore::semaphore(int32_t __n, int32_t __max)
        : _impl(new private_t(__n, __max))
    {
        ufc_check_ptr(_impl);
    }

    semaphore::~semaphore()
    {
        memory::delete_ptr(_impl);
    }

    inline void semaphore::set()
    {
    	_impl->set();
    }

    void semaphore::wait()
    {
    	_impl->wait();
    }

    void semaphore::wait(long_t __milliseconds)
    {
    	if (!_impl->wait(__milliseconds))
    		throw timeout_error();
    }

    bool semaphore::try_wait(long_t __milliseconds)
    {
    	return _impl->wait(__milliseconds);
    }

}//namespace ufc
