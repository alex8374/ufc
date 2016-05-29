/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : system/ref_counted_object.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/system/ref_counted_object.hpp"

namespace ufc {

    ref_counted_object::ref_counted_object()
        : _counter(1)
    {
    }
    
    ref_counted_object::~ref_counted_object()
    {
    }
    
    void ref_counted_object::duplicate()
    {
        ++_counter;
    }
    
    void ref_counted_object::release()
    {
        if (--_counter == 0)
        {
            delete this;
        }
    }
    
    int32_t ref_counted_object::ref_count() const
    {
        return _counter.value();
    }

}//namespace ufc
