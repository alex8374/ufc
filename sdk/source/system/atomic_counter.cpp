/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : system/atomic_counter.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/system/atomic_counter.hpp"
#include "ufc/exception/assert.hpp"
#if defined(ufc_os_family_windows)
#include "system/atomic_counter_win32.hpp"
#else
#include "system/atomic_counter_unix.hpp"
#endif

namespace ufc {

    atomic_counter::atomic_counter()
        : _impl(new private_t(0))
    {
        ufc_check_ptr(_impl);
    }

    atomic_counter::atomic_counter(const atomic_counter& __counter)
        : _impl(new private_t(__counter._impl->get_value()))
    {
        ufc_check_ptr(_impl);
    }

    atomic_counter::atomic_counter(int32_t __initial_value)
        : _impl(new private_t(__initial_value))
    {
        ufc_check_ptr(_impl);
    }

    atomic_counter::~atomic_counter()
    {
        memory::delete_ptr(_impl);
    }

    atomic_counter& atomic_counter::operator = (const atomic_counter& __counter)
    {
        _impl->set_value(__counter._impl->get_value());
        return *this;
    }

    atomic_counter& atomic_counter::operator = (int32_t __value)
    {
        _impl->set_value(__value);
        return *this;
    }

    atomic_counter::operator int32_t () const
    {
        return _impl->get_value();
    }

    int32_t atomic_counter::value() const
    {
        return _impl->get_value();
    }

    int32_t atomic_counter::operator ++ ()     // prefix    
    {
        return _impl->increment_prefix();
    }

    int32_t atomic_counter::operator ++ (int)    // postfix    
    {
        return _impl->increment_suffix();
    }

    int32_t atomic_counter::operator -- ()     // prefix         
    {
        return _impl->decrement_prefix();
    }

    int32_t atomic_counter::operator -- (int)    // postfix
    {
        return _impl->decrement_suffix();
    }

    bool atomic_counter::operator ! () const
    {
        return _impl->get_value() == 0;
    }

}//namespace ufc
