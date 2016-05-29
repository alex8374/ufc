/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/win32/mutex.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_WIN32_MUTEX_HPP
#define THREAD_WIN32_MUTEX_HPP

#include "ufc/thread/mutex.hpp"
#include "ufc/exception/exception.hpp"
#include <Windows.h>

namespace ufc {

    class mutex::private_t
    {
    public:
        explicit private_t()
        {
            InitializeCriticalSectionAndSpinCount(&_cs, 4000);
        }

        inline ~private_t()
        {
            DeleteCriticalSection(&_cs);
        }

        inline void lock()
        {
            try
            {
                EnterCriticalSection(&_cs);
            }
            catch (...)
            {
                throw system_error("cannot lock mutex");
            }
        }

        inline bool try_lock()
        {
            try
            {
                return TryEnterCriticalSection(&_cs) != 0;
            }
            catch (...)
            {
            }
            throw system_error("cannot lock mutex");
        }

        inline bool try_lock(long __milliseconds)
        {
            timestamp now;
            time_t __diff(time_t(__milliseconds)*1000);
            do
            {
                try
                {
                    if (TryEnterCriticalSection(&_cs) == TRUE)
                        return true;
                }
                catch (...)
                {
                    throw system_error("cannot lock mutex");
                }
                Sleep(5);
            }
            while (!now.is_elapsed(__diff));
            return false;
        }

        inline void unlock()
        {
            LeaveCriticalSection(&_cs);
        }

    private:
        CRITICAL_SECTION _cs;
    };

}//namespace ufc

#endif//THREAD_WIN32_MUTEX_HPP
