/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/rwlock.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_RWLOCK_HPP
#define UFC_THREAD_RWLOCK_HPP

#include <ufc/base/config.hpp>

namespace ufc {

    ///
    /// @breif: A reader writer lock allows multiple concurrent
    ///         readers or one exclusive writer.
    ///
    class ufc_api rwlock: virtual public object
    {
    public:
        ///
        /// A variant of ScopedLock for reader/writer locks.
        ///
        class ufc_api scoped_rwlock: virtual public object
        {
        public:
            scoped_rwlock(rwlock& __rwl, bool __write = false);
            virtual ~scoped_rwlock();
        
        private:
            rwlock& _rwl;
        };

        ///
        /// A variant of ScopedLock for reader locks.
        ///
        class ufc_api scoped_read_rwlock: public scoped_rwlock
        {
        public:
            scoped_read_rwlock(rwlock& __rwl);
            virtual ~scoped_read_rwlock();
        };

        ///        
        /// A variant of ScopedLock for writer locks.
        ///
        class ufc_api scoped_write_rwlock: public scoped_rwlock
        {
        public:
            scoped_write_rwlock(rwlock& __rwl);
            virtual ~scoped_write_rwlock();
        };

    public:
        ///
        /// @breif: Creates the Reader/Writer lock.
        ///
        rwlock();

        ///
        /// @breif: Destroys the Reader/Writer lock.
        ///
        virtual ~rwlock();

        ///
        /// @breif: Acquires a read lock. If another thread currently holds a write lock,
        ///         waits until the write lock is released.
        ///
        void read_lock();

        ///
        /// @breif: Tries to acquire a read lock. Immediately returns true if successful, or
        ///         false if another thread currently holds a write lock.
        ///
        bool try_read_lock();

        ///
        /// @breif: Acquires a write lock. If one or more other threads currently hold 
        ///         locks, waits until all locks are released. The results are undefined
        ///         if the same thread already holds a read or write lock
        ///
        void write_lock();

        ///
        /// @breif: Tries to acquire a write lock. Immediately returns true if successful,
        ///         or false if one or more other threads currently hold 
        ///         locks. The result is undefined if the same thread already
        ///         holds a read or write lock.
        ///
        bool try_write_lock();

        ///
        /// @breif: Releases the read or write lock.
        ///
        void unlock();
    
    private:
        class private_t;
        private_t* _impl;
    };

}//namespace ufc

#endif//UFC_THREAD_RWLOCK_HPP
