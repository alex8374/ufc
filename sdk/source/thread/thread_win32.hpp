/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/win32/thread.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-22
  Description: 
  History    : 
*******************************************************************************/
#ifndef THREAD_WIN32_THREAD_HPP
#define THREAD_WIN32_THREAD_HPP

#include "ufc/thread/thread.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/system/atomic_counter.hpp"
#include <Windows.h>

namespace ufc {

    class thread::private_t
    {
    public:    
#if defined(_DLL)
        typedef DWORD (WINAPI *Entry)(LPVOID);
#else
        typedef unsigned (__stdcall *Entry)(void*);
#endif

        private_t(thread* __parent, const string& __name)
            : _parent(__parent)
            , _id(uniqueid())
            , _name(__name.empty()? make_name(): __name)
            , _target(0)
            , _thread(0)
            , _tid(0)
            , _prio(THREAD_PRIORITY_NORMAL)
            , _stack_size(0)
        {
        }

        ~private_t()
        {
            if (_thread) CloseHandle(_thread);
        }

        void start(runnable& __target)
        {
            if (isRunning())
                throw system_error("thread already running");

            _target = &__target;

#if defined(_DLL)
            _thread = CreateThread(NULL, _stack_size, runnableEntry, this, 0, &_tid);
#else
            unsigned __tid;
            _thread = (HANDLE) _beginthreadex(NULL, _stack_size, runnableEntry, this, 0, &__tid);
            _tid = static_cast<DWORD>(__tid);
#endif
            if (!_thread)
                throw system_error("cannot create thread");
            if (_prio != THREAD_PRIORITY_NORMAL && !SetThreadPriority(_thread, _prio))
                throw system_error("cannot set thread priority");
        }

        void join()
        {
            if (!_thread) return;

            switch (WaitForSingleObject(_thread, INFINITE))
            {
            case WAIT_OBJECT_0:
                cleanup();
                return;
            default:
                throw system_error("cannot join thread");
            }
        }

        bool join(long_t __milliseconds)
        {
            if (!_thread) return true;

            switch (WaitForSingleObject(_thread, __milliseconds + 1))
            {
            case WAIT_TIMEOUT:
                return false;
            case WAIT_OBJECT_0:
                cleanup();
                return true;
            default:
                throw system_error("cannot join thread");
            }
        }

        bool is_running() const
        {
            if (_thread)
            {
                DWORD ec = 0;
                return GetExitCodeThread(_thread, &ec) && ec == STILL_ACTIVE;
            }
            return false;
        }

        int32_t id() const
        {
            return _id;
        }

        int32_t tid() const
        {
            return _tid;
        }

        void set_name(const string& name)
        {
            _name = name;
        }

        const string& get_name() const
        {
            return _name;
        }

        void set_priority(int32_t __prio)
        {
            switch ((thread::Priority)__prio)
            {
            case thread::prio_lowest:  set_os_priority(THREAD_PRIORITY_LOWEST); break;
            case thread::prio_low:     set_os_priority(THREAD_PRIORITY_BELOW_NORMAL); break;
            case thread::prio_normal:  set_os_priority(THREAD_PRIORITY_NORMAL); break;
            case thread::prio_high:    set_os_priority(THREAD_PRIORITY_ABOVE_NORMAL); break;
            case thread::prio_highest: set_os_priority(THREAD_PRIORITY_HIGHEST); break;
            default: throw invalid_argument_error();
            }
        }

        int32_t get_priority() const
        {
            switch (_prio)
            {
            case THREAD_PRIORITY_LOWEST:          return thread::prio_lowest;
            case THREAD_PRIORITY_BELOW_NORMAL:    return thread::prio_low;
            case THREAD_PRIORITY_ABOVE_NORMAL:    return thread::prio_high;
            case THREAD_PRIORITY_HIGHEST:         return thread::prio_highest;
            default:                              return thread::prio_normal;
            }
        }

        void set_os_priority(int32_t __prio)
        {
            if (__prio != _prio)
            {
                _prio = __prio;
                if (_thread)
                {
                    if (SetThreadPriority(_thread, _prio) == 0)
                        throw system_error("cannot set thread priority");
                }
            }
        }

        int32_t get_os_priority() const
        {
            return _prio;
        }

        void set_stack_size(int32_t __size)
        {
            _stack_size = __size;
        }

        int32_t get_stack_size() const
        {
            return _stack_size;
        }

    public:
        static int32_t get_min_os_priority()
        {
            return THREAD_PRIORITY_LOWEST;
        }

        static int32_t get_max_os_priority()
        {
            return THREAD_PRIORITY_HIGHEST;
        }

        static void sleep(long_t __milliseconds)
        {
            ::Sleep(__milliseconds);
        }

        static void usleep(long_t __microseconds)
        {
            ::Sleep(__microseconds / 1000);
        }

        static void yield()
        {
            ::Sleep(0);
        }

        static thread* current()
        {
            return _current_thread_holder.get();
        }

        static int32_t current_tid()
        {
            return GetCurrentThreadId();
        }

    private:
#ifdef _DLL
        static DWORD WINAPI runnableEntry(LPVOID __data)
#else
        static unsigned __stdcall runnableEntry(void* __data)
#endif
        {
            _current_thread_holder.set(reinterpret_cast<thread::private_t*>(__data)->_parent);
            try
            {
                reinterpret_cast<thread::private_t*>(__data)->_target->run();
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
            return 0;
        }

        void cleanup()
        {
            if (!_thread) return;
            if (CloseHandle(_thread)) _thread = 0;
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
    		current_thread_holder(): _slot(TlsAlloc())
    		{
    			if (_slot == TLS_OUT_OF_INDEXES)
    				throw system_error("cannot allocate thread context key");
    		}
    		~current_thread_holder()
    		{
    			TlsFree(_slot);
    		}
    		thread* get() const
    		{
    			return reinterpret_cast<thread*>(TlsGetValue(_slot));
    		}
    		void set(thread* __thr)
    		{
    			TlsSetValue(_slot, __thr);
    		}
    	
    	private:
    		DWORD _slot;
    	};

        thread*   _parent;
        DWORD     _id;
        string    _name;
        runnable* _target;
        HANDLE    _thread;
        DWORD     _tid;
        int32_t   _prio;
        int32_t   _stack_size;

        static current_thread_holder _current_thread_holder;
    };

    thread::private_t::current_thread_holder thread::private_t::_current_thread_holder;

}//namespace ufc

#endif//THREAD_WIN32_THREAD_HPP
