/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/posix/mutex.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_POSIX_MUTEX_HPP
#define THREAD_POSIX_MUTEX_HPP

#include "ufc/thread/mutex.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/datetime/timestamp.hpp"
#include <pthread.h>
#include <cerrno>
#include <cstring>
#include <sys/time.h>

namespace ufc {
    
    class mutex::private_t
    {
    public:
        explicit private_t()
        {
            pthread_mutexattr_t __attr;
            pthread_mutexattr_init(&__attr);
#if defined(PTHREAD_MUTEX_RECURSIVE_NP)
            pthread_mutexattr_settype_np(&__attr, PTHREAD_MUTEX_NORMAL_NP);
#elif !defined(UFC_VXWORKS)
            pthread_mutexattr_settype(&__attr, PTHREAD_MUTEX_NORMAL);
#endif
            if (pthread_mutex_init(&_mutex, &__attr))
            {
                pthread_mutexattr_destroy(&__attr);
                throw system_error("cannot create mutex");
            }
            pthread_mutexattr_destroy(&__attr);
        }

        inline ~private_t()
        {
            pthread_mutex_destroy(&_mutex);
        }

        inline void lock()
        {
            if (pthread_mutex_lock(&_mutex)) 
            {
                throw system_error("cannot lock mutex");
            }
        }

        inline bool try_lock()
        {
            int __rc = pthread_mutex_trylock(&_mutex);
            if (__rc == 0)
                return true;
            else if (__rc == EBUSY)
                return false;
            else
                throw system_error("cannot lock mutex");
        }

        inline bool try_lock(long __milliseconds)
        {
            struct timespec __abstime;
            struct timeval  __tv;
            gettimeofday(&__tv, NULL);
            int __rc;
            do
            {
                __abstime.tv_sec  = __tv.tv_sec + __milliseconds / 1000;
                __abstime.tv_nsec = __tv.tv_usec*1000 + (__milliseconds % 1000)*1000000;
                if (__abstime.tv_nsec >= 1000000000)
                {
                    __abstime.tv_nsec -= 1000000000;
                    __abstime.tv_sec++;
                }
                __rc = pthread_mutex_timedlock(&_mutex, &__abstime);
            }
            while (__rc != 0 && errno == EINTR);

            if (__rc == 0)
                return true;
            else if (__rc == ETIMEDOUT)
                return false;
            else
                throw system_error("cannot lock mutex");
        }

        inline void unlock()
        {
            if (pthread_mutex_unlock(&_mutex))
                throw system_error("cannot unlock mutex");
        }

    private:
        pthread_mutex_t _mutex;
    };

}//namespace ufc

#endif//THREAD_POSIX_MUTEX_HPP
