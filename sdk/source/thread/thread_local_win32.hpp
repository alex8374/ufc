/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/win32/thread_local.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-22
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_WIN32_THREAD_LOCAL_HPP
#define THREAD_WIN32_THREAD_LOCAL_HPP

#include "ufc/thread/thread_local.hpp"
#include "ufc/exception/exception.hpp"
#include <Windows.h>

namespace ufc {

    class thread_local_storage::private_t
    {
    public:
        private_t()
            : _slot(TlsAlloc())
        {
            if (_slot == TLS_OUT_OF_INDEXES)
                throw system_error("cannot allocate thread context key");
        }

        ~private_t()
        {
            TlsFree(_slot);
        }

        void set(tls_abstract_slot* __value)
        {
            TlsSetValue(_slot, __value);
        }

        tls_abstract_slot* get() const
        {
            return reinterpret_cast<tls_abstract_slot*>(TlsGetValue(_slot));
        }

    private:
        DWORD _slot;
    };

}//namespace ufc

#endif//THREAD_WIN32_THREAD_LOCAL_HPP
