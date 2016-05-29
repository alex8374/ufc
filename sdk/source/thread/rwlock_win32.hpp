/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/win32/rwlock.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-21
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_WIN32_RWLOCK_HPP
#define THREAD_WIN32_RWLOCK_HPP

#include "ufc/thread/rwlock.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#include <Windows.h>

namespace ufc {

    class rwlock::private_t
    {
    public:
    	private_t()
            : _readers(0), _writers_waiting(0), _writers(0)
        {
        	_mutex = CreateMutexW(NULL, FALSE, NULL);
        	if (_mutex == NULL)
        		throw system_error("cannot create reader/writer lock");

        	_read_evt = CreateEventW(NULL, TRUE, TRUE, NULL);
        	if (_read_evt == NULL)
        		throw system_error("cannot create reader/writer lock");

        	_write_evt = CreateEventW(NULL, TRUE, TRUE, NULL);
        	if (_write_evt == NULL)
        		throw system_error("cannot create reader/writer lock");
        }
    	~private_t()
        {
            CloseHandle(_mutex);
            CloseHandle(_read_evt);
            CloseHandle(_write_evt);
        }

        void read_lock()
        {
        	HANDLE __h[2];
        	__h[0] = _mutex;
        	__h[1] = _read_evt;
        	switch (WaitForMultipleObjects(2, __h, TRUE, INFINITE))
        	{
        	case WAIT_OBJECT_0:
        	case WAIT_OBJECT_0 + 1:
        		++_readers;
        		ResetEvent(_write_evt);
        		ReleaseMutex(_mutex);
        		ufc_assert(_writers == 0);
        		break;
        	default:
        		throw system_error("cannot lock reader/writer lock");
        	}
        }

    	bool try_read_lock()
        {
        	for (;;)
        	{
        		if (_writers != 0 || _writers_waiting != 0)
        			return false;

        		DWORD __result = try_read_lock_once();
        		switch (__result)
        		{
        		case WAIT_OBJECT_0:
        		case WAIT_OBJECT_0 + 1:
        			return true;
        		case WAIT_TIMEOUT:
        			continue; // try again
        		default:
        			throw system_error("cannot lock reader/writer lock");
        		}
        	}
        }

    	void write_lock()
        {
        	add_writer();
        	HANDLE __h[2];
        	__h[0] = _mutex;
        	__h[1] = _write_evt;
        	switch (WaitForMultipleObjects(2, __h, TRUE, INFINITE))
        	{
        	case WAIT_OBJECT_0:
        	case WAIT_OBJECT_0 + 1:
        		--_writers_waiting;
        		++_readers;
        		++_writers;
        		ResetEvent(_read_evt);
        		ResetEvent(_write_evt);
        		ReleaseMutex(_mutex);
        		ufc_assert(_writers == 1);
        		break;
        	default:
        		remove_writer();
        		throw system_error("cannot lock reader/writer lock");
        	}
        }

    	bool try_write_lock()
        {
        	add_writer();
        	HANDLE __h[2];
        	__h[0] = _mutex;
        	__h[1] = _write_evt;
        	switch (WaitForMultipleObjects(2, __h, TRUE, 1))
        	{
        	case WAIT_OBJECT_0:
        	case WAIT_OBJECT_0 + 1:
        		--_writers_waiting;
        		++_readers;
        		++_writers;
        		ResetEvent(_read_evt);
        		ResetEvent(_write_evt);
        		ReleaseMutex(_mutex);
        		ufc_assert(_writers == 1);
        		return true;
        	case WAIT_TIMEOUT:
        		remove_writer();
        		return false;
        	default:
        		remove_writer();
        		throw system_error("cannot lock reader/writer lock");
        	}
        }

        void unlock()
        {
        	switch (WaitForSingleObject(_mutex, INFINITE))
        	{
        	case WAIT_OBJECT_0:
        		_writers = 0;
        		if (_writers_waiting == 0) SetEvent(_read_evt);
        		if (--_readers == 0) SetEvent(_write_evt);
        		ReleaseMutex(_mutex);
        		break;
        	default:
        		throw system_error("cannot unlock reader/writer lock");
        	}
        }

    private:
        void add_writer()
        {
        	switch (WaitForSingleObject(_mutex, INFINITE))
        	{
        	case WAIT_OBJECT_0:
        		if (++_writers_waiting == 1) ResetEvent(_read_evt);
        		ReleaseMutex(_mutex);
        		break;
        	default:
        		throw system_error("cannot lock reader/writer lock");
        	}
        }

        void remove_writer()
        {
        	switch (WaitForSingleObject(_mutex, INFINITE))
        	{
        	case WAIT_OBJECT_0:
        		if (--_writers_waiting == 0 && _writers == 0) SetEvent(_read_evt);
        		ReleaseMutex(_mutex);
        		break;
        	default:
        		throw system_error("cannot lock reader/writer lock");
        	}
        }

        DWORD try_read_lock_once()
        {
        	HANDLE __h[2];
        	__h[0] = _mutex;
        	__h[1] = _read_evt;
        	DWORD __result = WaitForMultipleObjects(2, __h, TRUE, 1); 
        	switch (__result)
        	{
        	case WAIT_OBJECT_0:
        	case WAIT_OBJECT_0 + 1:
        		++_readers;
        		ResetEvent(_write_evt);
        		ReleaseMutex(_mutex);
        		ufc_assert(_writers == 0);
        		return __result;
        	case WAIT_TIMEOUT:
        		return __result;
        	default:
        		throw system_error("cannot lock reader/writer lock");
        	}
        }

    private:
        HANDLE   _mutex;
        HANDLE   _read_evt;
        HANDLE   _write_evt;
        unsigned _readers;
        unsigned _writers_waiting;
        unsigned _writers;
    };

}//namespace ufc

#endif//THREAD_WIN32_RWLOCK_HPP
