/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/posix/thread.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-22
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_POSIX_THREAD_HPP
#define THREAD_POSIX_THREAD_HPP

#include "ufc/thread/thread.hpp"
#include "ufc/thread/mutex.hpp"
#include "ufc/thread/event.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/system/atomic_counter.hpp"
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#    include <time.h>
#if defined(__sun) && defined(__SVR4)
#    if !defined(__EXTENSIONS__)
#        define __EXTENSIONS__
#    endif
#endif

namespace ufc {

    class thread::private_t
    {
    public:
        private_t(thread* __parent, const string& __name)
            : _parent(__parent)
            , _id(uniqueid())
            , _name(__name.empty()? make_name(): __name)
            , _target(0)
            , _thread(0)
            , _prio(thread::prio_normal)
            , _os_prio(0)
            , _stack_size(0)
        {
        }

        ~private_t()
        {
            if (is_running())
                pthread_detach(_thread);
        }

        void start(runnable& __target)
        {
            if (_target)
                throw system_error("thread already running");

            pthread_attr_t __attr;
            pthread_attr_init(&__attr);

            if (_stack_size != 0)
            {
                if (0 != pthread_attr_setstacksize(&__attr, _stack_size))
                    throw system_error("cannot set thread stack size");
            }

            _target = &__target;
            if (pthread_create(&_thread, &__attr, runnable_entry, this))
            {
                _target = 0;
                throw system_error("cannot start thread");
            }

            if (_prio != thread::prio_normal)
            {
                struct sched_param __par;
                __par.sched_priority = map_prio(_prio);
                if (pthread_setschedparam(_thread, SCHED_OTHER, &__par))
                    throw system_error("cannot set thread priority");
            }
        }

        void join()
        {
            _done.wait();
            void* result;
            if (pthread_join(_thread, &result))
                throw system_error("cannot join thread"); 
        }

        bool join(long_t __milliseconds)
        {
            if (_done.try_wait(__milliseconds))
            {
                void* __result;
                if (pthread_join(_thread, &__result))
                    throw system_error("cannot join thread");
                return true;
            }
            else 
                return false;
        }

        bool is_running() const
        {
            return (_target != 0);
        }

        int32_t id() const
        {
            return _id;
        }

        int32_t tid() const
        {
            return _thread;
        }

        void set_name(const string& __name)
        {
            _name = __name;
        }

        const string& get_name() const
        {
            return _name;
        }

        void set_priority(int32_t __prio)
        {
            if (__prio != _prio)
            {
                _prio = __prio;
                if (is_running())
                {
                    struct sched_param __par;
                    __par.sched_priority = map_prio(_prio);
                    if (pthread_setschedparam(_thread, SCHED_OTHER, &__par))
                        throw system_error("cannot set thread priority");
                }
            }
        }

        int32_t get_priority() const
        {
            return _prio;
        }

        void set_os_priority(int32_t __prio)
        {
            if (__prio != _os_prio)
            {
                if (_target)
                {
                    struct sched_param __par;
                    __par.sched_priority = __prio;
                    if (pthread_setschedparam(_thread, SCHED_OTHER, &__par))
                        throw system_error("cannot set thread priority");
                }
                _prio   = reverse_map_prio(__prio);
                _os_prio = __prio;
            }
        }

        int32_t get_os_priority() const
        {
            return _os_prio;
        }

        void set_stack_size(int32_t __size)
        {
#ifndef PTHREAD_STACK_MIN
            _stack_size = 0;
#else
            if (__size != 0)
            {
#if defined(__APPLE__)
                // we must round up to a multiple of the memory page size
                const int32_t PAGE_SIZE = 4096;
                __size = ((__size + PAGE_SIZE - 1)/PAGE_SIZE)*PAGE_SIZE;
#endif
                if (__size < PTHREAD_STACK_MIN)
                    __size = PTHREAD_STACK_MIN;
            }
            _stack_size = __size;
#endif
        }

        int32_t get_stack_size() const
        {
            return _stack_size;
        }

    public:
        static int32_t get_min_os_priority()
        {
#if defined(__VMS) || defined(__digital__)
            return PRI_OTHER_MIN;
#else
            return sched_get_priority_min(SCHED_OTHER);
#endif
        }

        static int32_t get_max_os_priority()
        {
#if defined(__VMS) || defined(__digital__)
            return PRI_OTHER_MAX;
#else
            return sched_get_priority_max(SCHED_OTHER);
#endif
        }

        static void sleep(long_t __milliseconds)
        {
            ::usleep(__milliseconds * 1000);
        }

        static void usleep(long_t __microseconds)
        {
            ::usleep(__microseconds);
        }

        static void yield()
        {
            sched_yield();
        }

        static thread* current()
        {
            return __current_thread_holder.get();
        }

        static int32_t current_tid()
        {
            return pthread_self();
        }

    private:
        static void* runnable_entry(void* __data)
        {
            __current_thread_holder.set(reinterpret_cast<thread::private_t*>(__data)->_parent);

            sigset_t sset;
            sigemptyset(&sset);
            sigaddset(&sset, SIGQUIT);
            sigaddset(&sset, SIGTERM);
            sigaddset(&sset, SIGPIPE); 
            pthread_sigmask(SIG_BLOCK, &sset, 0);

            thread::private_t* __pthr = reinterpret_cast<thread::private_t*>(__data);
            try
            {
                __pthr->_target->run();
            }
            catch (exception& e)
            {
                //UFC_LOG_EXCEPTION(e);
            }
            catch (std::exception& e)
            {
                //UFC_LOG_EXCEPTION(e);
            }
            catch (...)
            {
                //UFC_LOG_EXCEPTION();
            }

            __pthr->_target = 0;
            __pthr->_done.set();
            return 0;
        }

        static int32_t map_prio(int32_t __prio)
        {
            int32_t __pmin = get_min_os_priority();
            int32_t __pmax = get_max_os_priority();

            switch (__prio)
            {
            case thread::prio_lowest:
                return __pmin;
            case thread::prio_low:
                return __pmin + (__pmax - __pmin)/4;
            case thread::prio_normal:
                return __pmin + (__pmax - __pmin)/2;
            case thread::prio_high:
                return __pmin + 3*(__pmax - __pmin)/4;
            case thread::prio_highest:
                return __pmax;
            default:
                throw invalid_argument_error("invalid thread priority");
            }
            return -1; // just to satisfy compiler - we'll never get here anyway
        }

        static int32_t reverse_map_prio(int32_t osPrio)
        {
            int32_t __pmin = get_min_os_priority();
            int32_t __pmax = get_max_os_priority();
            int32_t __pnormal = __pmin + (__pmax - __pmin)/2;
            if (osPrio == __pmax)
                return thread::prio_highest;
            if (osPrio > __pnormal)
                return thread::prio_high;
            else if (osPrio == __pnormal)
                return thread::prio_normal;
            else if (osPrio > __pmin)
                return thread::prio_low;
            else
                return thread::prio_lowest;
        }

        string make_name()
        {
            return string::format("#%d", _id);
        }

        static int32_t uniqueid()
        {
            static atomic_counter __counter;
            return ++__counter;
        }

    private:
    	class current_thread_holder
    	{
    	public:
    		current_thread_holder()
    		{
    			if (pthread_key_create(&_key, NULL))
    				throw system_error("cannot allocate thread context key");
    		}
    		~current_thread_holder()
    		{
    			pthread_key_delete(_key);
    		}
    		thread* get() const
    		{
    			return reinterpret_cast<thread*>(pthread_getspecific(_key));
    		}
    		void set(thread* __data)
    		{
    			pthread_setspecific(_key, __data);
    		}
    	
    	private:
    		pthread_key_t _key;
    	};

        thread*     _parent;
        int32_t     _id;
        string      _name;
        runnable*   _target;
        pthread_t   _thread;
        int32_t     _prio;
        int32_t     _os_prio;
        event       _done;
        std::size_t _stack_size;

        static current_thread_holder __current_thread_holder;
    };

    thread::private_t::current_thread_holder thread::private_t::__current_thread_holder;

}//namespace ufc

#endif//THREAD_POSIX_THREAD_HPP
