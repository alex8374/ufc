/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/posix/rwlock.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-21
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_POSIX_RWLOCK_HPP
#define THREAD_POSIX_RWLOCK_HPP

#include "ufc/thread/rwlock.hpp"
#include "ufc/exception/exception.hpp"
#include <pthread.h>
#include <errno.h>

namespace ufc {

    class rwlock::private_t
    {
    public:
    	private_t()
        {
        	if (pthread_rwlock_init(&_rwl, NULL))
        		throw system_error("cannot create reader/writer lock");
        }

    	~private_t()
        {
        	pthread_rwlock_destroy(&_rwl);
        }

        void read_lock()
        {
        	if (pthread_rwlock_rdlock(&_rwl)) 
        		throw system_error("cannot lock reader/writer lock");
        }

    	bool try_read_lock()
        {
        	int rc = pthread_rwlock_tryrdlock(&_rwl);
        	if (rc == 0)
        		return true;
        	else if (rc == EBUSY)
        		return false;
        	else
        		throw system_error("cannot lock reader/writer lock");

        }

    	void write_lock()
        {
        	if (pthread_rwlock_wrlock(&_rwl)) 
        		throw system_error("cannot lock reader/writer lock");
        }

        bool try_write_lock()
        {
        	int rc = pthread_rwlock_trywrlock(&_rwl);
        	if (rc == 0)
        		return true;
        	else if (rc == EBUSY)
        		return false;
        	else
        		throw system_error("cannot lock reader/writer lock");

        }

    	void unlock()
        {
        	if (pthread_rwlock_unlock(&_rwl))
        		throw system_error("cannot unlock mutex");
        }

    private:
	    pthread_rwlock_t _rwl;
    };

}//namespace ufc

#endif//THREAD_POSIX_RWLOCK_HPP
