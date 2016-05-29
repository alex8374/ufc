/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/thread_group.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-22
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/thread/thread_group.hpp"

namespace ufc {

    thread_group::thread_group(uint32_t __n, uint32_t __stack_size)
    {
        add(__n);
    }

    thread_group::~thread_group()
    {
    }

    void thread_group::start(runnable& __target)
    {
        _target = &__target;
        for (uint32_t __i = 0; __i < _threads.size(); __i++)
        {
            if (!_threads[__i]->is_running())
            {
                _threads[__i]->start(__target);
            }
        }
    }

    void thread_group::join()
    {
        for (unsigned int i = 0; i < _threads.size(); i++)
        {
            _threads[i]->join();
        }
    }

    void thread_group::housekeep()
    {
        if (_target)
        {
            for (uint32_t __i = 0; __i < _threads.size(); __i++)
            {
                if (!_threads[__i]->is_running())
                {
                    _threads[__i]->start(*_target);
                }
            }
        }
    }

    void thread_group::add(uint32_t __n)
    {
        for (uint32_t __i = 0; __i < __n; __i++)
        {
            _threads.append(new thread());
        }
    }

    uint32_t thread_group::size() const
    {
        return _threads.size();
    }

    uint32_t thread_group::get_stack_size() const
    {
        return _stack_size;
    }

}//namespace ufc
