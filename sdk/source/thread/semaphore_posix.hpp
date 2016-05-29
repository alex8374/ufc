/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/semaphore_posix.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_SEMAPHORE_POSIX_HPP
#define THREAD_SEMAPHORE_POSIX_HPP

#include "ufc/thread/semaphore.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>

namespace ufc {

    class semaphore::private_t
    {
    public:
    	private_t(int n, int max): _n(n), _max(max)
        {
        	ufc_assert (n >= 0 && max > 0 && n <= max);

        	if (pthread_mutex_init(&_mutex, NULL))
        		throw system_error("cannot create semaphore (mutex)");
        	if (pthread_cond_init(&_cond, NULL))
        		throw system_error("cannot create semaphore (condition)");
        }		

        ~private_t()
        {
        	pthread_cond_destroy(&_cond);
        	pthread_mutex_destroy(&_mutex);
        }

    	void set()
        {
        	if (pthread_mutex_lock(&_mutex))	
        		throw system_error("cannot signal semaphore (lock)");
        	if (_n < _max)
        	{
        		++_n;
        	}
        	else
        	{
        		pthread_mutex_unlock(&_mutex);
        		throw system_error("cannot signal semaphore: count would exceed maximum");
        	}	
        	if (pthread_cond_signal(&_cond))
        	{
        		pthread_mutex_unlock(&_mutex);
        		throw system_error("cannot signal semaphore");
        	}
        	pthread_mutex_unlock(&_mutex);
        }

        void wait()
        {
        	if (pthread_mutex_lock(&_mutex))
        		throw system_error("wait for semaphore failed (lock)"); 
        	while (_n < 1) 
        	{
        		if (pthread_cond_wait(&_cond, &_mutex))
        		{
        			pthread_mutex_unlock(&_mutex);
        			throw system_error("wait for semaphore failed");
        		}
        	}
        	--_n;
        	pthread_mutex_unlock(&_mutex);
        }

        bool wait(long __milliseconds)
        {
        	int rc = 0;
        	struct timespec __abstime;

#if defined(__VMS)
        	struct timespec __delta;
        	__delta.tv_sec  = __milliseconds / 1000;
        	__delta.tv_nsec = (__milliseconds % 1000)*1000000;
        	pthread_get_expiration_np(&__delta, &__abstime);
#else
        	struct timeval __tv;
        	gettimeofday(&__tv, NULL);
        	__abstime.tv_sec  = __tv.tv_sec + __milliseconds / 1000;
        	__abstime.tv_nsec = __tv.tv_usec*1000 + (__milliseconds % 1000)*1000000;
        	if (__abstime.tv_nsec >= 1000000000)
        	{
        		__abstime.tv_nsec -= 1000000000;
        		__abstime.tv_sec++;
        	}
#endif

        	if (pthread_mutex_lock(&_mutex) != 0)
        		throw system_error("wait for semaphore failed (lock)"); 
        	while (_n < 1) 
        	{
        		if ((rc = pthread_cond_timedwait(&_cond, &_mutex, &__abstime)))
        		{
        			if (rc == ETIMEDOUT) break;
        			pthread_mutex_unlock(&_mutex);
        			throw system_error("cannot wait for semaphore");
        		}
        	}
        	if (rc == 0) --_n;
        	pthread_mutex_unlock(&_mutex);
        	return rc == 0;
        }
    	
    private:
    	volatile int    _n;
    	int             _max;
    	pthread_mutex_t _mutex;
    	pthread_cond_t  _cond;
    };

}//namespace ufc

#endif//THREAD_SEMAPHORE_POSIX_HPP
