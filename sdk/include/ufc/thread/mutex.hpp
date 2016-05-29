/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/mutex.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_MUTEX_HPP
#define UFC_THREAD_MUTEX_HPP

#include <ufc/base/config.hpp>

namespace ufc {

	/// 
	/// @breif: Exclusive classes, in order to share data to provide multi thread 
	///         synchronization mechanism.
	///
	class ufc_api mutex: virtual public object
	{
	public:
		/// 
		/// @breif: This kind of simplification of a mutual exclusion of 
	    ///         multi thread synchronization (lock / unlock). 
		/// 
		class ufc_api scoped_lock: virtual public object
		{
		public:
			explicit scoped_lock(mutex& __mtx);
			scoped_lock(mutex& __mutex, long_t __milliseconds);
			virtual ~scoped_lock();

		private:
			mutex& _mutex;
		};

		/// 
		/// @breif: This kind of simplification of a mutual exclusion of 
	    ///         multi thread synchronization (unlock / lock). 
		/// 
		class ufc_api scoped_unlock: virtual public object
		{
		public:
			scoped_unlock(mutex& __mutex, bool __unlock_now = true);
			virtual ~scoped_unlock();

		private:
			mutex& _mutex;
		};

	public:
		mutex();
		virtual ~mutex();

        ///
		/// @breif: Locks the mutex. Blocks if the mutex
		///         is held by another thread.
        ///
		void lock();

        ///
		/// @breif: Locks the mutex. Blocks up to the given number of milliseconds
		///         if the mutex is held by another thread. Throws a timeout_error
		///         if the mutex can not be locked within the given timeout.
        ///
		void lock(long_t __milliseconds);

        ///
		/// @breif: Tries to lock the mutex. Returns false immediately
		///         if the mutex is already held by another thread.
		///         Returns true if the mutex was successfully locked.
        ///
		bool try_lock();

        ///
		/// @breif: Locks the mutex. Blocks up to the given number of milliseconds
		///         if the mutex is held by another thread.
		///         Returns true if the mutex was successfully locked.
        ///
		bool try_lock(long_t __milliseconds);

        ///
		/// @breif: Unlocks the mutex so that it can be acquired by other threads.
        ///
		void unlock();

	private:
		class private_t;
		private_t* _impl;
	};

}//namespace ufc

#endif//UFC_THREAD_MUTEX_HPP
