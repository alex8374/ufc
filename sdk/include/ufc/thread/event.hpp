/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/event.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_EVENT_HPP
#define UFC_THREAD_EVENT_HPP

#include <ufc/base/config.hpp>

namespace ufc {

    ///
    /// @breif: An event is a synchronization object that
    ///         allows one thread to signal one or more
    ///         other threads that a certain event
    ///         has happened.
    ///         Usually, one thread signals an event,
    ///         while one or more other threads wait
    ///         for an event to become signalled.
    ///
    class ufc_api event: virtual public object
    {
    public:
        ///
        /// @breif: Creates the event. If autoReset is true,
        ///         the event is automatically reset after
        ///         a wait() successfully returns.
        ///
        explicit event(bool __auto_reset = true);
            
        virtual ~event();
    
        ///
        /// @breif: Signals the event. If autoReset is true,
        ///         only one thread waiting for the event 
        ///         can resume execution.
        ///         If autoReset is false, all waiting threads
        ///         can resume execution.
        ///
        void set();

        ///
        /// @breif: Waits for the event to become signalled.
        ///
        void wait();
    
        ///
        /// @breif: Waits for the event to become signalled.
        ///         Throws a timeout_error if the event
        ///         does not become signalled within the specified
        ///         time interval.
        ///
        void wait(long_t __milliseconds);
    
        ///
        /// @breif: Waits for the event to become signalled.
        ///         Returns true if the event
        ///         became signalled within the specified
        ///         time interval, false otherwise.
        ///
        bool try_wait(long __milliseconds);
    
        ///
        /// @breif: Resets the event to unsignalled state.
        ///
        void reset();
        
    private:
        class private_t;
        private_t* _impl;
    };

}//namespace ufc

#endif//UFC_THREAD_EVENT_HPP
