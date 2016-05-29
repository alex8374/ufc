/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/thread/thread_local.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-22
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_THREAD_THREAD_LOCAL_HPP
#define UFC_THREAD_THREAD_LOCAL_HPP

#include <ufc/base/config.hpp>

namespace ufc {

    ///
    /// @breif: This is the base class for all objects that 
    ///         the thread_local_storage class manages.
    ///
    class ufc_api tls_abstract_slot: virtual public object
    {
    public:
        tls_abstract_slot();
        virtual ~tls_abstract_slot();
    };
    
    ///
    /// @breif: This class manages the local storage for each thread.
    ///         Never use this class directly, always use the
    ///         thread_local template for managing thread local storage.
    ///
    class ufc_api thread_local_storage: virtual public object
    {
    public:
        ///
        /// @breif: creates the tls.
        ///
        thread_local_storage();

        ///
        /// @breif: destroy the tls.
        ///
        virtual ~thread_local_storage();

        ///
        /// @breif: associate a thread-specific value. Different threads may bind different values 
        ///         to the same key. These values are typically pointers to blocks of dynamically 
        ///         allocated memory that have been reserved for use by the calling thread.
        ///
        void set(tls_abstract_slot* __value);

        ///
        /// @breif: return the value currently bound to the specified key on behalf of the calling thread.
        ///
        tls_abstract_slot* get() const;

    private:
        class private_t;
        private_t* _impl;
    };

    ///
    /// @breif: This template is used to declare type safe thread
    ///         local variables. It can basically be used like
    ///         a smart pointer class with the special feature
    ///         that it references a different object
    ///         in every thread. The underlying object will
    ///         be created when it is referenced for the first time.
    ///         See the NestedDiagnosticContext class for an
    ///         example how to use this template.
    ///         Every thread only has access to its own
    ///         thread local data. There is no way for a thread
    ///         to access another thread's local data.
    ///
    template <class C> class thread_local: virtual public object
    {
        class tls_slot: public tls_abstract_slot
        {
        public:
            tls_slot()
                : _value()
            {
            }

            virtual ~tls_slot()
            {
            }

            C& value()
            {
                return _value;
            }

        private:
            C _value;
        };

    public:
        thread_local()
        {
        }

        ~thread_local()
        {
        }

        C* operator -> () const
        {
            return &get();
        }

        C& operator * () const
        {
            return get();
        }

        ///
        /// @breif: Returns a reference to the underlying data object.
        ///         The reference can be used to modify the object.
        ///
        C& get() const
        {
            tls_abstract_slot* __p = _tls.get();
            if (!__p)
            {
                _tls.set(new tls_slot());
            }
            return static_cast<tls_slot*>(_tls.get())->value();
        }

    private:
        thread_local_storage _tls;
    };

}//namespace ufc

#endif//UFC_THREAD_THREAD_LOCAL_HPP
