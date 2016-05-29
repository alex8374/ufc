/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/thread_pool.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-22
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/thread/thread_pool.hpp"
#include "ufc/thread/mutex.hpp"
#include "ufc/thread/event.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/string/string_util.hpp"
#include <ctime>

namespace ufc {

    class thread_pool::pool_thread: public runnable
    {
    public:
        pool_thread(const string& __name, int32_t __stack_size = 0);
        ~pool_thread();

        void start();
        void start(thread::priority __prio, runnable& __target);
        void start(thread::priority __prio, runnable& __target, const string& __name);
        bool idle();
        int32_t idleTime();
        void join();
        void activate();
        void release();
        void run();

    private:
        volatile bool        _idle;
        volatile std::time_t _idle_time;
        runnable*            _target;
        string               _name;
        thread               _thread;
        event                _targetReady;
        event                _targetCompleted;
        event                _started;
        mutex                _mutex;
    };

    inline thread_pool::pool_thread::pool_thread(const string& __name, int32_t __stack_size)
        : _idle(true)
        , _idle_time(0)
        , _target(0)
        , _name(__name)
        , _thread(__name)
        , _targetCompleted(false)
    {
        ufc_assert (__stack_size >= 0);
        _thread.set_stack_size(__stack_size);
        _idle_time = std::time(NULL);
    }

    inline thread_pool::pool_thread::~pool_thread()
    {
    }

    inline void thread_pool::pool_thread::start()
    {
        _thread.start(*this);
        _started.wait();
    }

    inline void thread_pool::pool_thread::start(thread::priority __prio, runnable& __target)
    {
        mutex::scoped_lock __lock(_mutex);

        ufc_assert (_target == 0);

        _target = &__target;
        _thread.set_priority(__prio);
        _targetReady.set();
    }

    inline void thread_pool::pool_thread::start(thread::priority __prio, runnable& __target, const string& __name)
    {
        mutex::scoped_lock __lock(_mutex);

        string __full_name(__name);
        if (__name.empty())
        {
            __full_name = _name;
        }
        else
        {
            __full_name.append(" (");
            __full_name.append(_name);
            __full_name.append(")");
        }
        _thread.set_name(__full_name);
        _thread.set_priority(__prio);

        ufc_assert (_target == 0);

        _target = &__target;
        _targetReady.set();
    }

    inline bool thread_pool::pool_thread::idle()
    {
        return _idle;
    }

    inline int32_t thread_pool::pool_thread::idleTime()
    {
        mutex::scoped_lock __lock(_mutex);

        return (int32_t) (time(NULL) - _idle_time);
    }

    inline void thread_pool::pool_thread::join()
    {
        _mutex.lock();
        runnable* pTarget = _target;
        _mutex.unlock();
        if (pTarget)
            _targetCompleted.wait();
    }

    inline void thread_pool::pool_thread::activate()
    {
        mutex::scoped_lock __lock(_mutex);

        ufc_assert (_idle);
        _idle = false;
        _targetCompleted.reset();
    }

    inline void thread_pool::pool_thread::release()
    {
        _mutex.lock();
        _target = 0;
        _mutex.unlock();

        _targetReady.set();
        if (_thread.try_join(10000))
        {
            delete this;
        }
    }

    void thread_pool::pool_thread::run()
    {
        _started.set();
        for (;;)
        {
            _targetReady.wait();
            _mutex.lock();
            if (_target) // a NULL __target means kill yourself
            {
                _mutex.unlock();
                try
                {
                    _target->run();
                }
                catch (exception& exc)
                {
                    //UFC_LOG_EXCEPTION(exc);
                }
                catch (std::exception& exc)
                {
                    //UFC_LOG_EXCEPTION(exc);
                }
                catch (...)
                {
                    //UFC_LOG_EXCEPTION();
                }
                mutex::scoped_lock __lock(_mutex);
                _target  = 0;
                _idle_time = time(NULL);
                _idle     = true;
                _targetCompleted.set();
                _thread.set_name(_name);
                _thread.set_priority(thread::prio_normal);
            }
            else
            {
                _mutex.unlock();
                break;
            }
        }
    }

    thread_pool::thread_pool(int32_t __min_capacity,
        int32_t __max_capacity,
        int32_t __idle_time,
        int32_t __stack_size)
        : _min_capacity(__min_capacity)
        , _max_capacity(__max_capacity)
        , _idle_time(__idle_time)
        , _serial(0)
        , _age(0)
        , _stack_size(__stack_size)
    {
        ufc_assert (__min_capacity >= 1 && __max_capacity >= __min_capacity && __idle_time > 0);

        for (int32_t i = 0; i < _min_capacity; i++)
        {
            pool_thread* pThread = create_thread();
            _threads.push_back(pThread);
            pThread->start();
        }
    }

    thread_pool::thread_pool(const string& __name,
        int32_t __min_capacity,
        int32_t __max_capacity,
        int32_t __idle_time,
        int32_t __stack_size)
        : _name(__name)
        , _min_capacity(__min_capacity)
        , _max_capacity(__max_capacity)
        , _idle_time(__idle_time)
        , _serial(0)
        , _age(0)
        , _stack_size(__stack_size)
    {
        ufc_assert (__min_capacity >= 1 && __max_capacity >= __min_capacity && __idle_time > 0);

        for (int32_t i = 0; i < _min_capacity; i++)
        {
            pool_thread* pThread = create_thread();
            _threads.push_back(pThread);
            pThread->start();
        }
    }

    thread_pool::~thread_pool()
    {
        stop_all();
    }

    void thread_pool::add_capacity(int32_t __n)
    {
        mutex::scoped_lock __lock(_mutex);

        ufc_assert (__n >= 1);
        ufc_assert (_max_capacity + __n >= _min_capacity);
        _max_capacity += __n;
        housekeep();
    }

    int32_t thread_pool::capacity() const
    {
        mutex::scoped_lock __lock(_mutex);
        return _max_capacity;
    }

    int32_t thread_pool::available() const
    {
        mutex::scoped_lock __lock(_mutex);

        int32_t count = 0;
        for (thread_vec::const_iterator __it = _threads.begin(); __it != _threads.end(); ++__it)
        {
            if ((*__it)->idle()) ++count;
        }
        return (int32_t) (count + _max_capacity - _threads.size());
    }

    int32_t thread_pool::used() const
    {
        mutex::scoped_lock __lock(_mutex);

        int32_t count = 0;
        for (thread_vec::const_iterator __it = _threads.begin(); __it != _threads.end(); ++__it)
        {
            if (!(*__it)->idle()) ++count;
        }
        return count;
    }

    int32_t thread_pool::allocated() const
    {
        mutex::scoped_lock __lock(_mutex);

        return int32_t(_threads.size());
    }

    void thread_pool::start(runnable& __target)
    {
        get_thread()->start(thread::prio_normal, __target);
    }

    void thread_pool::start(runnable& __target, const string& __name)
    {
        get_thread()->start(thread::prio_normal, __target, __name);
    }

    void thread_pool::start_with_priority(thread::priority __prio, runnable& __target)
    {
        get_thread()->start(__prio, __target);
    }

    void thread_pool::start_with_priority(thread::priority __prio, runnable& __target, const string& __name)
    {
        get_thread()->start(__prio, __target, __name);
    }

    void thread_pool::stop_all()
    {
        mutex::scoped_lock __lock(_mutex);

        for (thread_vec::iterator __it = _threads.begin(); __it != _threads.end(); ++__it)
        {
            (*__it)->release();
        }
        _threads.clear();
    }

    void thread_pool::join_all()
    {
        mutex::scoped_lock __lock(_mutex);

        for (thread_vec::iterator __it = _threads.begin(); __it != _threads.end(); ++__it)
        {
            (*__it)->join();
        }
        housekeep();
    }

    void thread_pool::collect()
    {
        mutex::scoped_lock __lock(_mutex);
        housekeep();
    }

    void thread_pool::housekeep()
    {
        _age = 0;
        if ((int32_t)_threads.size() <= _min_capacity)
            return;

        thread_vec idleThreads;
        thread_vec expiredThreads;
        thread_vec activeThreads;
        idleThreads.reserve(_threads.size());
        activeThreads.reserve(_threads.size());

        for (thread_vec::iterator __it = _threads.begin(); __it != _threads.end(); ++__it)
        {
            if ((*__it)->idle())
            {
                if ((*__it)->idleTime() < _idle_time)
                    idleThreads.push_back(*__it);
                else 
                    expiredThreads.push_back(*__it);    
            }
            else activeThreads.push_back(*__it);
        }
        int32_t __n = (int32_t) activeThreads.size();
        int32_t limit = (int32_t) idleThreads.size() + __n;
        if (limit < _min_capacity) limit = _min_capacity;
        idleThreads.insert(idleThreads.end(), expiredThreads.begin(), expiredThreads.end());
        _threads.clear();
        for (thread_vec::iterator __it = idleThreads.begin(); __it != idleThreads.end(); ++__it)
        {
            if (__n < limit)
            {
                _threads.push_back(*__it);
                ++__n;
            }
            else (*__it)->release();
        }
        _threads.insert(_threads.end(), activeThreads.begin(), activeThreads.end());
    }

    thread_pool::pool_thread* thread_pool::get_thread()
    {
        mutex::scoped_lock __lock(_mutex);

        if (++_age == 32)
            housekeep();

        pool_thread* pThread = 0;
        for (thread_vec::iterator __it = _threads.begin(); !pThread && __it != _threads.end(); ++__it)
        {
            if ((*__it)->idle()) pThread = *__it;
        }
        if (!pThread)
        {
            if ((int32_t)_threads.size() < _max_capacity)
            {
                pThread = create_thread();
                try
                {
                    pThread->start();
                    _threads.push_back(pThread);
                }
                catch (...)
                {
                    delete pThread;
                    throw;
                }
            }
            else 
                throw no_thread_available_error();
        }
        pThread->activate();
        return pThread;
    }

    thread_pool::pool_thread* thread_pool::create_thread()
    {
        return new pool_thread(string::format("%s[#%d]", _name.c_str(), ++_serial), _stack_size);
    }

    void thread_pool::set_stack_size(int32_t __stack_size)
    {
        _stack_size = __stack_size;
    }

    int32_t thread_pool::get_stack_size() const
    {
        return _stack_size;
    }


    const string& thread_pool::name() const
    {
        return _name;
    }

    class thread_pool_singleton_holder
    {
    public:
        thread_pool_singleton_holder()
        {
            _pool = 0;
        }
        ~thread_pool_singleton_holder()
        {
            delete _pool;
        }
        thread_pool* pool()
        {
            mutex::scoped_lock __lock(_mutex);

            if (!_pool)
            {
                _pool = new thread_pool("default");
                _pool->set_stack_size(0);
            }
            return _pool;
        }

    private:
        thread_pool* _pool;
        mutex        _mutex;
    };

    thread_pool& thread_pool::default_pool()
    {
        static thread_pool_singleton_holder __holder;
        return *__holder.pool();
    }

}//namespace ufc
