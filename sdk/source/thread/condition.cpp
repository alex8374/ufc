/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : thread/condition.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-21
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/thread/condition.hpp"
#include "ufc/exception/exception.hpp"

namespace ufc {

    condition::condition()
    {
    }

    condition::~condition()
    {
    }

	void condition::wait(mutex& __mutex)
	{
		mutex::scoped_unlock __unlock(__mutex, false);
		event __event;
		{
			mutex::scoped_lock __lock(_mutex);
			__mutex.unlock();
			enqueue(__event);
		}
		__event.wait();
	}

	void condition::wait(mutex& __mutex, long_t __milliseconds)
	{
		if (!try_wait(__mutex, __milliseconds))
			throw timeout_error();
    }

    bool condition::try_wait(mutex& __mutex, long_t __milliseconds)
	{
		mutex::scoped_unlock __unlock(__mutex, false);
		event __event;
		{
			mutex::scoped_lock __lock(_mutex);
			__mutex.unlock();
			enqueue(__event);
		}
		if (!__event.try_wait(__milliseconds))
		{
			mutex::scoped_lock __lock(_mutex);
			dequeue(__event);
			return false;
		}
		return true;
	}
    
    void condition::signal()
    {
    	mutex::scoped_lock __lock(_mutex);
    	
    	if (!_wait_queue.empty())
    	{
    		_wait_queue.front()->set();
    		dequeue();
    	}
    }

    void condition::broadcast()
    {
    	mutex::scoped_lock __lock(_mutex);
    	
    	for (wait_queue::iterator it = _wait_queue.begin(); it != _wait_queue.end(); ++it)
    	{
    		(*it)->set();
    	}
    	_wait_queue.clear();
    }

    void condition::enqueue(event& event)
    {
    	_wait_queue.push_back(&event);
    }

    void condition::dequeue()
    {
    	_wait_queue.pop_front();
    }

    void condition::dequeue(event& event)
    {
    	for (wait_queue::iterator it = _wait_queue.begin(); it != _wait_queue.end(); ++it)
    	{
    		if (*it == &event)
    		{
    			_wait_queue.erase(it);
    			break;
    		}
    	}
    }

}//namespace ufc