/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/thread.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_THREAD_HPP
#define UFC_THREAD_THREAD_HPP

#include <ufc/thread/runnable.hpp>
#include <ufc/string/string.hpp>

namespace ufc {
    
    ///
    /// @breif: This class implements a platform-independent
    ///         wrapper to an operating system thread.
    ///
    ///         Every thread object gets a unique (within
    ///         its process) numeric thread ID.
    ///         Furthermore, a thread can be assigned a name.
    ///         The name of a thread can be changed at any time.
    ///
    class ufc_api thread: virtual public object
    {
    public:
        ///
        /// @breif: thread priorities.
        ///
        enum priority
        {
            prio_lowest, /// The lowest thread priority.
            prio_low,    /// A lower than normal thread priority.
            prio_normal, /// The normal thread priority.
            prio_high,   /// A higher than normal thread priority.
            prio_highest /// The highest thread priority.
        };

        ///
        /// @breif: Creates a thread. Call start() to start it.
        ///
        thread();

        ///
        /// @breif: Creates a named thread. Call start() to start it.
        ///
        thread(const string& __name);

        ///
        /// @breif: Destroys the thread.
        ///
        virtual ~thread();

        ///
        /// @breif: Starts the thread with the given target.
        ///
        void start(runnable& __target);

        ///
        /// @breif: Waits until the thread completes execution. 
        ///         If multiple threads try to join the same
        ///         thread, the result is undefined.
        ///
        void join();

        ///
        /// @breif: Waits for at most the given interval for the thread
        ///         to complete. Throws a timeout_error if the thread
        ///         does not complete within the specified time interval.
        ///
        void join(long_t __milliseconds);

        ///
        /// @breif: Waits for at most the given interval for the thread
        ///         to complete. Returns true if the thread has finished,
        ///         false otherwise.
        ///
        bool try_join(long_t __milliseconds);

        ///
        /// @breif: Returns true if the thread is running.
        ///
        bool is_running() const;

        ///
        /// @breif: Returns the unique thread ID of the thread.
        ///
        int32_t id() const;

        ///
        /// @breif: Returns the native thread ID of the thread.
        ///
        int32_t tid() const;

        ///
        /// @breif: Returns the name of the thread.
        ///
        string get_name() const;

        ///
        /// @breif: Sets the name of the thread.
        ///
        void set_name(const string& __name);

        ///
        /// @breif: Sets the thread's priority.
        ///
        ///         Some platform only allow changing a thread's priority
        ///         if the process has certain privileges.
        ///
        void set_priority(priority __prio);

        ///
        /// @breif: Returns the thread's priority.
        ///
        priority get_priority() const;

        ///
        /// @breif: Sets the thread's priority, using an operating system specific
        ///         priority value. Use get_min_os_priority() and get_max_os_priority() to
        ///         obtain mininum and maximum priority values.
        ///
        void set_os_priority(int32_t __prio);

        ///
        /// @breif: Returns the thread's priority, expressed as an operating system
        ///         specific priority value.
        ///
        ///         May return 0 if the priority has not been explicitly set.
        ///
        int32_t get_os_priority() const;

        ///
        /// @breif: Sets the thread's stack size in bytes.
        ///         Setting the stack size to 0 will use the default stack size.
        ///         Typically, the real stack size is rounded up to the nearest
        ///         page size multiple.
        ///
        void set_stack_size(int32_t __size);

        ///
        /// @breif: Returns the thread's stack size in bytes.
        ///         If the default stack size is used, 0 is returned.
        ///
        int32_t get_stack_size() const;
   
    public:
        ///
        /// @breif: Suspends the current thread for the specified amount of time.
        ///
        static void sleep(long_t __milliseconds);
        static void usleep(long_t __microseconds);

        ///
        /// @breif: Yields cpu to other threads.
        ///
        static void yield();

        ///
        /// @breif: Returns the thread object for the currently active thread.
        ///         If the current thread is the main thread, 0 is returned.
        ///
        static thread* current();

        ///
        /// @breif: Returns the native thread ID for the current thread.    
        ///
        static int32_t current_tid();

        ///
        /// @breif: Returns the mininum operating system-specific priority value,
        ///         which can be passed to set_os_priority().
        ///
        static int32_t get_min_os_priority();

        ///
        /// @breif: Returns the maximum operating system-specific priority value,
        ///         which can be passed to set_os_priority().
        ///
        static int32_t get_max_os_priority();

    protected:
        class private_t;
        private_t* _impl;
    };

}//namespace ufc

#endif//UFC_THREAD_THREAD_HPP
