/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/thread_pool.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_THREAD_POOL_HPP
#define UFC_THREAD_THREAD_POOL_HPP

#include <ufc/thread/thread.hpp>
#include <ufc/thread/mutex.hpp>
#include <ufc/thread/runnable.hpp>
#include <ufc/string/string.hpp>
#include <ufc/container/vector.hpp>

namespace ufc {

    ///
    /// @breif: A thread pool always keeps a number of threads running, ready
    ///         to accept work.
    ///         Creating and starting a threads can impose a significant runtime
    ///         overhead to an application. A thread pool helps to improve
    ///         the performance of an application by reducing the number
    ///         of threads that have to be created (and destroyed again).
    ///         Threads in a thread pool are re-used once they become
    ///         available again.
    ///         The thread pool always keeps a minimum number of threads
    ///         running. If the demans for threads increases, additional
    ///         threads are created. Once the demand for threads sinks
    ///         again, no-longer used threads are stopped and removed
    ///         from the pool.
    ///
    class ufc_api thread_pool: virtual public object
    {
        class pool_thread;

    public:
        ///
        /// @breif: Creates a thread pool with __min_capacity threads.
        ///         If required, up to __max_capacity threads are created
        ///         a NoThreadAvailableException exception is thrown.
        ///         If a thread is running idle for more than __idle_time seconds,
        ///         and more than __min_capacity threads are running, the thread
        ///         is killed. Threads are created with given stack size.
        ///
        thread_pool(int32_t __min_capacity = 2,
                    int32_t __max_capacity = 16,
                    int32_t __idle_time = 60,
                    int32_t __stack_size = 0);

        ///
        /// @breif: Creates a thread pool with the given __name and __min_capacity threads.
        ///         If required, up to __max_capacity threads are created
        ///         a NoThreadAvailableException exception is thrown.
        ///         If a thread is running idle for more than __idle_time seconds,
        ///         and more than __min_capacity threads are running, the thread
        ///         is killed. Threads are created with given stack size.
        ///
        thread_pool(const string& __name,
                    int32_t __min_capacity = 2,
                    int32_t __max_capacity = 16,
                    int32_t __idle_time = 60,
                    int32_t __stack_size = 0);

        ///
        /// @breif: Currently running threads will remain active until they complete. 
        ///
        virtual ~thread_pool();

        ///
        /// @breif:Increases (or decreases, if n is negative) the maximum number of threads.
        ///
        void add_capacity(int32_t __n);

        ///
        /// @breif: Returns the maximum capacity of threads.
        ///
        int32_t capacity() const;

        ///
        /// @breif: Sets the stack size for threads.
        ///         New stack size applies only for newly created threads.
        ///
        void set_stack_size(int32_t __stack_size);

        ///
        /// @breif: Returns the stack size used to create new threads.
        ///
        int32_t get_stack_size() const;

        ///
        /// @breif: Returns the number of currently used threads.
        ///
        int32_t used() const;

        ///
        /// @breif: Returns the number of currently allocated threads.
        ///
        int32_t allocated() const;

        ///
        /// @breif: Returns the number available threads.
        ///
        int32_t available() const;

        ///
        /// @breif: Obtains a thread and starts the target.
        ///         Throws a no_thread_available_error if no more threads are available.
        ///
        void start(runnable& __target);

        ///
        /// @breif: Obtains a thread and starts the __target.
        ///         Assigns the given name to the thread.
        ///         Throws a no_thread_available_error if no more threads are available.
        ///
        void start(runnable& __target, const string& __name);

        ///
        /// @breif: Obtains a thread, adjusts the thread's priority, and starts the target.
        ///         Throws a no_thread_available_error if no more threads are available.
        ///
        void start_with_priority(thread::priority __priority, runnable& __target);

        ///
        /// @breif: Obtains a thread, adjusts the thread's priority, and starts the target.
        ///         Assigns the given name to the thread.
        ///         Throws a no_thread_available_error if no more threads are available.
        ///
        void start_with_priority(thread::priority __priority, runnable& __target, const string& __name);

        ///
        /// @breif: Stops all running threads and waits for their completion.
        ///
        ///         Will also delete all thread objects.
        ///         If used, this method should be the last action before
        ///         the thread pool is deleted.
        ///
        ///         Note: If a thread fails to stop within 10 seconds 
        ///         (due to a programming error, for example), the
        ///         underlying thread object will not be deleted and
        ///         this method will return anyway. This allows for a
        ///         more or less graceful shutdown in case of a misbehaving thread.
        ///
        void stop_all();

        ///
        /// @breif: Waits for all threads to complete.
        ///
        ///         Note that this will not actually join() the underlying
        ///         thread, but rather wait for the thread's runnables to finish.
        ///
        void join_all();

        ///
        /// @breif: Stops and removes no longer used threads from the
        ///         thread pool. Can be called at various times in an
        ///         application's life time to help the thread pool
        ///         manage its threads. Calling this method is optional,
        ///         as the thread pool is also implicitly managed in
        ///         calls to start(), addCapacity() and joinAll().
        ///
        void collect();

        ///
        /// @breif: Returns the name of the thread pool,
        ///         or an empty string if no name has been
        ///         specified in the constructor.
        ///
        const string& name() const;

        ///
        /// Returns a reference to the default thread pool.
        ///
        static thread_pool& default_pool();

    protected:
        pool_thread* get_thread();
        pool_thread* create_thread();

        void housekeep();

    private:
        typedef vector<pool_thread*> thread_vec;

        string  _name;
        int32_t _min_capacity;
        int32_t _max_capacity;
        int32_t _idle_time;
        int32_t _serial;
        int32_t _age;
        int32_t _stack_size;
        thread_vec    _threads;
        mutable mutex _mutex;
    };

}//namespace ufc

#endif//UFC_THREAD_THREAD_POOL_HPP
