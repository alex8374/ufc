/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/runnable_adapter.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_RUNNABLE_ADAPTER_HPP
#define UFC_THREAD_RUNNABLE_ADAPTER_HPP

#include <ufc/thread/runnable.hpp>

namespace ufc {
    
    ///
    /// @breif: This adapter simplifies using ordinary methods as
    /// targets for threads.
    /// Usage:
    ///    runnable_adapter<my_class> ra(my_object, &MyObject::do_something));
    ///    thread thr;
    ///    thr.start(ra);
    ///
    /// For using a freestanding or static member function as a thread
    /// target, please see the ThreadTarget class.
    ///
    template <class type> class runnable_adapter: public runnable
    {
    public:
        typedef void (type::*callback)();
        
        runnable_adapter(type& __object, callback __method)
            : _object(&object), _method(__method)
        {
        }

        runnable_adapter(const runnable_adapter& __ra)
            : _object(__ra._object)
            , _method(__ra._method)
        {
        }

        virtual ~runnable_adapter()
        {
        }

        runnable_adapter& operator = (const runnable_adapter& __ra)
        {
            _object = __ra._object;
            _method = __ra._method;
            return *this;
        }

        void run()
        {
            (_object->*_method)();
        }

    private:
        runnable_adapter();

        type*    _object;
        callback _method;
    };

}//namespace ufc

#endif//UFC_THREAD_RUNNABLE_ADAPTER_HPP
