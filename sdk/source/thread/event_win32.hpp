/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/win32/event.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_WIN32_EVENT_HPP
#define THREAD_WIN32_EVENT_HPP

#include "ufc/thread/event.hpp"
#include "ufc/exception/exception.hpp"
#include <Windows.h>

namespace ufc {
    
    class event::private_t
    {
    public:
        private_t(bool __auto_reset)
        {
        	_event = CreateEvent(NULL, __auto_reset ? FALSE : TRUE, FALSE, NULL);
        	if (!_event)
        		throw SystemException("cannot create event");
        }     

        ~private_t()
        {
        	CloseHandle(_event);
        }

        void set()
        {
        	if (!SetEvent(_event))
        	{
        		throw SystemException("cannot signal event");
        	}
        }

        void wait()
        {
        	switch (WaitForSingleObject(_event, INFINITE))
        	{
        	case WAIT_OBJECT_0:
        		return;
        	default:
        		throw SystemException("wait for event failed");
        	}
        }

        bool wait(long __milliseconds)
        {
        	switch (WaitForSingleObject(_event, __milliseconds + 1))
        	{
        	case WAIT_TIMEOUT:
        		return false;
        	case WAIT_OBJECT_0:
        		return true;
        	default:
        		throw SystemException("wait for event failed");		
        	}
        }

        void reset()
        {
        	if (!ResetEvent(_event))
        	{
        		throw SystemException("cannot reset event");
        	}
        }
        
    private:
        HANDLE _event;
    };

}//namespace ufc

#endif//THREAD_WIN32_EVENT_HPP
