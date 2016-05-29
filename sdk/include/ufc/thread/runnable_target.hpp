/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/runnable_target.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_RUNNABLE_TARGET_HPP
#define UFC_THREAD_RUNNABLE_TARGET_HPP

#include <ufc/thread/runnable.hpp>

namespace ufc {

    ///
    /// @breif: This target simplifies using ordinary methods as
    /// targets for threads.
    /// Usage:
    ///    runnable_target ra(&MyObject::do_something));
    ///    thread thr;
    ///    thr.start(ra);
    ///
    /// For using a freestanding or static member function as a thread
    /// target, please see the ThreadTarget class.
    ///
    class ufc_api runnable_target: public runnable
    {
    public:
        typedef void (*callback)();

        explicit runnable_target(callback __method);
        runnable_target(const runnable_target& __ra);
        virtual ~runnable_target();

        runnable_target& operator = (const runnable_target& __ra);

        void run();

    private:
        runnable_target();

        callback _method;
    };

}//namespace ufc

#endif//UFC_THREAD_RUNNABLE_TARGET_HPP
