/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : system/atomic_counter_win32.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef SYSTEM_ATOMIC_COUNTER_WIN32_HPP
#define SYSTEM_ATOMIC_COUNTER_WIN32_HPP

#include "ufc/system/atomic_counter.hpp"
#include <Windows.h>

namespace ufc {

    class atomic_counter::private_t
    {
    public:
        inline private_t(int32_t __initial_value)
            : _value(__initial_value)
        {
        }

        inline ~private_t()
        {
        }

        inline void set_value(int32_t __value)
        {
            InterlockedExchange(&_value, __value);
        }

        inline int32_t get_value() const
        {
            return _value;
        }

        inline int32_t increment_prefix()
        {
            return InterlockedIncrement(&_value);
        }

        inline int32_t increment_suffix()
        {
            int32_t __result = InterlockedIncrement(&_value);
            return --__result;
        }

        inline int32_t decrement_prefix()
        {
            return InterlockedDecrement(&_value);
        }

        inline int32_t decrement_suffix()
        {
            int32_t __result = InterlockedDecrement(&_value);
            return --__result;
        }

    private:
        volatile LONG _value;
    };

}//namespace ufc

#endif//SYSTEM_ATOMIC_COUNTER_WIN32_HPP
