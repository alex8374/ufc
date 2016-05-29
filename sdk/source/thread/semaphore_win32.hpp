/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/semaphore_win32.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_SEMAPHORE_WIN32_HPP
#define THREAD_SEMAPHORE_WIN32_HPP

#include "ufc/thread/semaphore.hpp"
#include "ufc/exception/exception.h"
#include "ufc/exception/assert.h"
#include <Windows.h>

namespace ufc {
    
    class semaphore::private_t
    {
    public:
        private_t(int n, int max)
        {
        	ufc_assert (n >= 0 && max > 0 && n <= max);

        	_sema = CreateSemaphoreW(NULL, n, max, NULL);
        	if (!_sema)
        	{
        		throw system_error("cannot create semaphore");
        	}
        }    

        ~private_t()
        {
        	CloseHandle(_sema);
        }

        void set()
        {
        	if (!ReleaseSemaphore(_sema, 1, NULL))
        	{
        		throw system_error("cannot signal semaphore");
        	}
        }

        void wait()
        {
        	switch (WaitForSingleObject(_sema, INFINITE))
        	{
        	case WAIT_OBJECT_0:
        		return;
        	default:
        		throw system_error("wait for semaphore failed");
        	}
        }

        bool wait(long __milliseconds)
        {
        	switch (WaitForSingleObject(_sema, __milliseconds + 1))
        	{
        	case WAIT_TIMEOUT:
        		return false;
        	case WAIT_OBJECT_0:
        		return true;
        	default:
        		throw system_error("wait for semaphore failed");		
        	}
        }

    private:
        HANDLE _sema;
    };

}//namespace ufc

#endif//THREAD_SEMAPHORE_WIN32_HPP
