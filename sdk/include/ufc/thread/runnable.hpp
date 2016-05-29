/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/runnable.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_RUNNABLE_HPP
#define UFC_THREAD_RUNNABLE_HPP

#include <ufc/base/config.hpp>

namespace ufc {

    ///
    /// @breif: The runnable interface with the run() method
    ///         must be implemented by classes that provide
    ///         an entry point for a thread.
    ///
    class ufc_api runnable: virtual public object
    {
    public: 
        runnable();
        virtual ~runnable();

        ///
        /// @breif: Do whatever the thread needs to do. Must
        ///         be overridden by subclasses.
        ///
        virtual void run() = 0;
    };

}//namespace ufc

#endif//UFC_THREAD_RUNNABLE_HPP
