/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/semaphore.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_SEMAPHORE_HPP
#define UFC_THREAD_SEMAPHORE_HPP

#include <ufc/base/config.hpp>

namespace ufc {

    ///
    /// @breif: A semaphore is a synchronization object with the following  characteristics:
    ///         A semaphore has a value that is constrained to be a non-negative
    ///         integer and two atomic operations. The allowable operations are V 
    ///         (here called set()) and P (here called wait()). A V (set()) operation 
    ///         increases the value of the semaphore by one. 
    ///         A P (wait()) operation decreases the value of the semaphore by one, 
    ///         provided that can be done without violating the constraint that the 
    ///         value be non-negative. A P (wait()) operation that is initiated when 
    ///         the value of the semaphore is 0 suspends the calling thread. 
    ///         The calling thread may continue when the value becomes positive again.
    ///
    class ufc_api semaphore: virtual public object
    {
    public:
        ///
        /// @breif: Creates the semaphore. The current value of the semaphore is given in n. The
        ///         maximum value of the semaphore is given in max.
        ///         If only n is given, it must be greater than zero.
        ///         If both n and max are given, max must be greater than zero, n must be greater than
        ///         or equal to zero and less than or equal to max.
        ///
        semaphore(int32_t __n);
        semaphore(int32_t __n, int32_t __max);
            
        ///
        /// @breif: Destroys the semaphore.
        ///
        virtual ~semaphore();
    
        ///
        /// @breif: Increments the semaphore's value by one and thus signals the semaphore. Another thread
        ///         waiting for the semaphore will be able to continue.
        ///
        void set();

        ///
        /// @breif: Waits for the semaphore to become signalled.
        ///         To become signalled, a semaphore's value must be greater than zero. 
        ///         Decrements the semaphore's value by one.
        ///
        void wait();

        ///
        /// @breif: Waits for the semaphore to become signalled.
        ///         To become signalled, a semaphore's value must be greater than zero.
        ///         Throws a timeout_error if the semaphore does not become signalled within the specified time interval.
        ///         Decrements the semaphore's value by one if successful.
        ///
        void wait(long_t __milliseconds);

        ///
        /// @breif: Waits for the semaphore to become signalled.
        ///         To become signalled, a semaphore's value must be greater than zero.
        ///         Returns true if the semaphore became signalled within the specified time interval, false otherwise.
        ///         Decrements the semaphore's value by one if successful.
        ///
        bool try_wait(long_t __milliseconds);

    private:
        class private_t;
        private_t* _impl;
    };

}//namespace ufc

#endif//UFC_THREAD_SEMAPHORE_HPP
