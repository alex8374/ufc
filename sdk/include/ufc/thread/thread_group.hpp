/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/thread_group.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_THREAD_GROUP_HPP
#define UFC_THREAD_THREAD_GROUP_HPP

#include <ufc/thread/thread.hpp>
#include <ufc/container/ptr_array.hpp>

namespace ufc {

    class ufc_api thread_group: virtual public object
    {
    public:
        thread_group(uint32_t __n = 0, uint32_t __stack_size = 0);
        virtual ~thread_group();

        void start(runnable& __target);
        void join();
        void housekeep();

        void add(uint32_t __n);
        uint32_t size() const;
        uint32_t get_stack_size() const;

    private:
        ptr_array<thread> _threads;
        runnable*         _target;
        uint32_t          _stack_size;
    };

}//namespace ufc

#endif//UFC_THREAD_THREAD_GROUP_HPP
