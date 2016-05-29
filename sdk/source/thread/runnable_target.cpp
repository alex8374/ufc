/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/runnable_target.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/thread/runnable_target.hpp"

namespace ufc {

    runnable_target::runnable_target(callback __method)
        : _method(__method)
    {
    }

    runnable_target::runnable_target(const runnable_target& __ra)
        : _method(__ra._method)
    {
    }

    runnable_target::~runnable_target()
    {
    }

    runnable_target& runnable_target::operator = (const runnable_target& __ra)
    {
        _method = __ra._method;
        return *this;
    }

    void runnable_target::run()
    {
        (*_method)();
    }

}//namespace ufc
