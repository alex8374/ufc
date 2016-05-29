/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : system/atomic_counter_posix.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef SYSTEM_ATOMIC_COUNTER_POSIX_HPP
#define SYSTEM_ATOMIC_COUNTER_POSIX_HPP

#include "ufc/system/atomic_counter.hpp"
#include "ufc/thread/mutex.hpp"

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
            mutex::scoped_lock __lock(_mutex);
            _value = __value;
        }

        inline int32_t get_value() const
        {
            int32_t __result;
            {
                mutex::scoped_lock __lock(_mutex);
                __result = _value;
            }
            return __result;
        }

        inline int32_t increment_prefix()
        {
            int32_t __result;
            {
                mutex::scoped_lock __lock(_mutex);
                __result = ++_value;
            }
            return __result;
        }

        inline int32_t increment_suffix()
        {
            int32_t __result;
            {
                mutex::scoped_lock __lock(_mutex);
                __result = _value++;
            }
            return __result;
        }

        inline int32_t decrement_prefix()
        {
            int32_t __result;
            {
                mutex::scoped_lock __lock(_mutex);
                __result = --_value;
            }
            return __result;
        }

        inline int32_t decrement_suffix()
        {
            int32_t __result;
            {
                mutex::scoped_lock __lock(_mutex);
                __result = _value--;
            }
            return __result;
        }

    private:
        mutable mutex  _mutex;
        volatile int32_t _value;
    };

}//namespace ufc

#endif//SYSTEM_ATOMIC_COUNTER_POSIX_HPP
