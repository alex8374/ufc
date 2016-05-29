/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/posix/thread_local.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-22
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_POSIX_THREAD_LOCAL_HPP
#define THREAD_POSIX_THREAD_LOCAL_HPP

#include "ufc/thread/thread_local.hpp"
#include "ufc/exception/exception.hpp"
#include <pthread.h>
#include <errno.h>

namespace ufc {

    class thread_local_storage::private_t
    {
    public:
        private_t()
        {
            if (pthread_key_create(&_key, NULL))
                throw system_error("cannot allocate thread context key");
        }

        ~private_t()
        {
            pthread_key_delete(_key);
        }

        void set(tls_abstract_slot* __value)
        {
            pthread_setspecific(_key, __value);
        }

        tls_abstract_slot* get() const
        {
            return reinterpret_cast<tls_abstract_slot*>(pthread_getspecific(_key));
        }

    private:
        pthread_key_t _key;
    };

}//namespace ufc

#endif//THREAD_POSIX_THREAD_LOCAL_HPP
