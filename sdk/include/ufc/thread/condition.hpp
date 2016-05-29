/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/condition.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_CONDITION_HPP
#define UFC_THREAD_CONDITION_HPP

#include <ufc/thread/mutex.hpp>
#include <ufc/thread/event.hpp>
#include <deque>

namespace ufc {

    ///
    /// @breif: A condition is a synchronization object used to block a thread 
    ///         until a particular condition is met. 
    ///         A condition object is always used in conjunction with a mutex object.
    ///
    ///         condition objects are similar to POSIX condition variables, which the
    ///         difference that condition is not subject to spurious wakeups.
    ///
    ///         Threads waiting on a condition are resumed in FIFO order.
    ///
    class ufc_api condition: virtual public object
    {
    public:
        ///
        /// @breif: Creates the condition.
        ///
        condition();
        
        ///
        /// @breif: Destroys the condition.
        ///
        virtual ~condition();

        ///
        /// @breif: Unlocks the mutex (which must be locked upon calling
        ///         wait()) and waits until the condition is signalled.
        ///
        ///         The given mutex will be locked again upon 
        ///         leaving the function, even in case of an exception.
        ///
        void wait(mutex& __mutex);

        ///
        /// @breif: unlocks the mutex (which must be locked upon calling
        ///         wait()) and waits for the given time until the condition is signalled.
        ///
        ///         The given mutex will be locked again upon successfully leaving the 
        ///         function, even in case of an exception.
        ///
        ///         Throws a timeout_error if the condition is not signalled
        ///         within the given time interval.
        ///
        void wait(mutex& __mutex, long_t __milliseconds);
        
        ///
        /// @breif: Unlocks the mutex (which must be locked upon calling
        ///         try_wait()) and waits for the given time until the condition is signalled.
        ///
        ///         The given mutex will be locked again upon leaving the 
        ///         function, even in case of an exception.
        ///
        ///         Returns true if the condition has been signalled
        ///         within the given time interval, otherwise false.
        ///
        bool try_wait(mutex& __mutex, long_t __milliseconds);
        
        ///
        /// @breif: Signals the condition and allows one waiting thread to continue execution.
        ///
        void signal();

        ///
        /// @breif: Signals the condition and allows all waiting threads to continue their execution.
        ///
        void broadcast();
    
    protected:
        void enqueue(event& __event);
        void dequeue();
        void dequeue(event& __event);
        
    private:        
        typedef std::deque<event*> wait_queue;
        
        mutex       _mutex;
        wait_queue  _wait_queue;
    };

}//namespace ufc

#endif//UFC_THREAD_CONDITION_HPP
