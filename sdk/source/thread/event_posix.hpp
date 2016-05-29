/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/pthread/event.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_POSIX_EVENT_HPP
#define THREAD_POSIX_EVENT_HPP

#include "ufc/thread/event.hpp"
#include "ufc/exception/exception.hpp"
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>

namespace ufc {
    
    class event::private_t
    {
    public:
        private_t(bool __auto_reset): _auto(__auto_reset), _state(false)
        {
        	if (pthread_mutex_init(&_mutex, NULL))
        		throw system_error("cannot create event (mutex)");
        	if (pthread_cond_init(&_cond, NULL))
        		throw system_error("cannot create event (condition)");
        }      

        ~private_t()
        {
            pthread_cond_destroy(&_cond);
            pthread_mutex_destroy(&_mutex);
        }

        void set()
        {
        	if (pthread_mutex_lock(&_mutex))	
        		throw system_error("cannot signal event (lock)");
        	_state = true;
        	if (pthread_cond_broadcast(&_cond))
        	{
        		pthread_mutex_unlock(&_mutex);
        		throw system_error("cannot signal event");
        	}
        	pthread_mutex_unlock(&_mutex);
        }

        void wait()
        {
        	if (pthread_mutex_lock(&_mutex))
        		throw system_error("wait for event failed (lock)"); 
        	while (!_state) 
        	{
        		if (pthread_cond_wait(&_cond, &_mutex))
        		{
        			pthread_mutex_unlock(&_mutex);
        			throw system_error("wait for event failed");
        		}
        	}
        	if (_auto)
        		_state = false;
        	pthread_mutex_unlock(&_mutex);
        }

        bool wait(long __milliseconds)
        {
        	int __rc = 0;
        	struct timespec __abstime;
        	struct timeval  __tv;

        	gettimeofday(&__tv, NULL);
        	__abstime.tv_sec  = __tv.tv_sec + __milliseconds / 1000;
        	__abstime.tv_nsec = __tv.tv_usec*1000 + (__milliseconds % 1000)*1000000;
        	if (__abstime.tv_nsec >= 1000000000)
        	{
        		__abstime.tv_nsec -= 1000000000;
        		__abstime.tv_sec++;
        	}

        	if (pthread_mutex_lock(&_mutex) != 0)
        		throw system_error("wait for event failed (lock)"); 
        	while (!_state) 
        	{
        		if ((__rc = pthread_cond_timedwait(&_cond, &_mutex, &__abstime)))
        		{
        			if (__rc == ETIMEDOUT) break;
        			pthread_mutex_unlock(&_mutex);
        			throw system_error("cannot wait for event");
        		}
        	}
        	if (__rc == 0 && _auto) _state = false;
        	pthread_mutex_unlock(&_mutex);
        	return __rc == 0;
        }

        void reset()
        {
        	if (pthread_mutex_lock(&_mutex))	
        		throw system_error("cannot reset event");
        	_state = false;
        	pthread_mutex_unlock(&_mutex);
        }
        
    private:
        bool            _auto;
        volatile bool   _state;
        pthread_mutex_t _mutex;
        pthread_cond_t  _cond;
    };

}//namespace ufc

#endif//THREAD_POSIX_EVENT_HPP