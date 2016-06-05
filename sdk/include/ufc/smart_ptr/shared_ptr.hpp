/*******************************************************************************
       Copyright(C) 2016, Free software engineer and contributor
 ******************************************************************************
  Filename   : ufc/core/sharedptr.hpp
  Author     : lcq<lichangqing8374@hotmail.com>
  Date       : 2016-05-09
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_CORE_SHAREDPTR_HPP
#define UFC_CORE_SHAREDPTR_HPP

#include <ufc/smart_ptr/scoped_ptr.hpp>
#include <algorithm>

namespace ufc {
    
    ///
    /// @breif: An enhanced relative of scoped_ptr with reference counted copy semantics.
    /// The object pointed to is deleted when the last shared_ptr pointing to it
    /// is destroyed or reset.
    ///
    template <class T> class shared_ptr: virtual public object
    {
        template <class U> friend class shared_ptr;

    public:
        inline shared_ptr()
            : _counter(new scoped_ptr<T>())
            , _ptr(0)
        {
        }

        inline shared_ptr(T* __ptr)
            : _counter(new scoped_ptr<T>(__ptr))
            , _ptr(__ptr)
        {
        }

        template <class U>
        inline shared_ptr(U* __ptr)
            : _counter(new scoped_ptr<T>(dynamic_cast<T*>(__ptr)))
            , _ptr(dynamic_cast<T*>(__ptr))
        {
            ufc_assert((__ptr && _ptr) || (!__ptr && !_ptr));
        }

        inline shared_ptr(const shared_ptr& __ptr)
            : _counter(__ptr._counter)
            , _ptr(const_cast<T*>(__ptr.get()))
        {
            _counter->duplicate();
        }

        template <class U>
        inline shared_ptr(const shared_ptr<U>& __ptr)
            : _counter(__ptr._counter)
            , _ptr(const_cast<U*>(__ptr.get()))
        {
            _counter->duplicate();
        }

        virtual ~shared_ptr()
        {
            _counter->release();
        }

        inline shared_ptr& operator = (T* __ptr)
        {
            if (get() != __ptr)
            {
                shared_ptr(__ptr).swap(*this);
            }
            return *this;
        }

        template <class U>
        inline shared_ptr& operator = (U* __ptr)
        {
            if (get() != __ptr)
            {
                shared_ptr(__ptr).swap(*this);
            }
            return *this;
        }

        inline shared_ptr& operator = (const shared_ptr& __ptr)
        {
            if (__ptr.get() != get())
            {
                shared_ptr(__ptr).swap(*this);
            }
            return *this;
        }

        template <class U>
        inline shared_ptr& operator = (const shared_ptr<U>& __ptr)
        {
            if (__ptr.get() != get())
            {
                shared_ptr(__ptr).swap(*this);
            }
            return *this;
        }

        inline void swap(shared_ptr& __ptr)
        {
            std::swap(__ptr._ptr, _ptr);
            std::swap(__ptr._counter, _counter);
        }

        template <class U>
        inline shared_ptr<U> cast() const
        {
            U* __ptr = dynamic_cast<U*>(_ptr);
            if (__ptr)
                return shared_ptr<U>(_counter, __ptr);
            else
                return shared_ptr();
        }

        template <class U>
        inline shared_ptr<U> unsafe_cast() const
        {
            U* __ptr = static_cast<U*>(_ptr);
            return shared_ptr<U>(_counter, __ptr);
        }

        inline T* operator -> ()
        {
            return deref();
        }

        inline const T* operator -> () const
        {
            return deref();
        }

        inline T& operator * ()
        {
            return *deref();
        }

        inline const T& operator * () const
        {
            return *deref();
        }

        inline T* get()
        {
            return _ptr;
        }

        inline const T* get() const
        {
            return _ptr;
        }

        inline operator T* ()
        {
            return deref();
        }

        inline operator const T* () const
        {
            return deref();
        }

        inline bool is_null() const
        {
            return _ptr == NULL;
        }

        inline bool operator ! () const
        {
            return is_null();
        }

        inline operator bool () const
        {
            return !is_null();
        }

        inline bool Unique() const
        {
            return _counter->RefCount() == 1;
        }

        inline uint32_t use_count() const
        {
            return _counter->RefCount();
        }

    private:
        inline shared_ptr(ref_counted_object* __counter, T* __ptr)
            : _counter(__counter)
            , _ptr(__ptr)
        {
            _counter->duplicate();
        }

        inline T* deref() const
        {
            ufc_check_ptr(_ptr);
            return _ptr;
        }

    private:
        ref_counted_object* _counter;
        T*                  _ptr;
    };

    template <class T> inline bool operator == (const shared_ptr<T>& lhs, const shared_ptr<T>& rhs)
    {
        return lhs.get() == rhs.get();
    }

    template <class T> inline bool operator == (const shared_ptr<T>& lhs, const T* rhs)
    {
        return lhs.get() == rhs;
    }

    template <class T> inline bool operator == (const shared_ptr<T>& lhs, T* rhs)
    {
        return lhs.get() == rhs;
    }

    template <class T> inline bool operator == (const T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs == rhs.get();
    }

    template <class T> inline bool operator == (T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs == rhs.get();
    }

    template <class T> inline bool operator != (const shared_ptr<T>& lhs, const shared_ptr<T>& rhs)
    {
        return lhs.get() != rhs.get();
    }

    template <class T> inline bool operator != (const shared_ptr<T>& lhs, const T* rhs)
    {
        return lhs.get() != rhs;
    }

    template <class T> inline bool operator != (const shared_ptr<T>& lhs, T* rhs)
    {
        return lhs.get() != rhs;
    }

    template <class T> inline bool operator != (const T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs != rhs.get();
    }

    template <class T> inline bool operator != (T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs != rhs.get();
    }

    template <class T> inline bool operator >= (const shared_ptr<T>& lhs, const shared_ptr<T>& rhs)
    {
        return lhs.get() >= rhs.get();
    }

    template <class T> inline bool operator >= (const shared_ptr<T>& lhs, const T* rhs)
    {
        return lhs.get() >= rhs;
    }

    template <class T> inline bool operator >= (const shared_ptr<T>& lhs, T* rhs)
    {
        return lhs.get() >= rhs;
    }

    template <class T> inline bool operator >= (const T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs >= rhs.get();
    }

    template <class T> inline bool operator >= (T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs >= rhs.get();
    }

    template <class T> inline bool operator <= (const shared_ptr<T>& lhs, const shared_ptr<T>& rhs)
    {
        return lhs.get() <= rhs.get();
    }

    template <class T> inline bool operator <= (const shared_ptr<T>& lhs, const T* rhs)
    {
        return lhs.get() <= rhs;
    }

    template <class T> inline bool operator <= (const shared_ptr<T>& lhs, T* rhs)
    {
        return lhs.get() <= rhs;
    }

    template <class T> inline bool operator <= (const T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs <= rhs.get();
    }

    template <class T> inline bool operator <= (T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs <= rhs.get();
    }

    template <class T> inline bool operator > (const shared_ptr<T>& lhs, const shared_ptr<T>& rhs)
    {
        return lhs.get() > rhs.get();
    }

    template <class T> inline bool operator > (const shared_ptr<T>& lhs, const T* rhs)
    {
        return lhs.get() > rhs;
    }

    template <class T> inline bool operator > (const shared_ptr<T>& lhs, T* rhs)
    {
        return lhs.get() > rhs;
    }

    template <class T> inline bool operator > (const T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs > rhs.get();
    }

    template <class T> inline bool operator > (T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs > rhs.get();
    }

    template <class T> inline bool operator < (const shared_ptr<T>& lhs, const shared_ptr<T>& rhs)
    {
        return lhs.get() < rhs.get();
    }

    template <class T> inline bool operator < (const shared_ptr<T>& lhs, const T* rhs)
    {
        return lhs.get() < rhs;
    }

    template <class T> inline bool operator < (const shared_ptr<T>& lhs, T* rhs)
    {
        return lhs.get() < rhs;
    }

    template <class T> inline bool operator < (const T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs < rhs.get();
    }

    template <class T> inline bool operator < (T* lhs, const shared_ptr<T>& rhs)
    {
        return lhs < rhs.get();
    }

}//namespace ufc

#endif//UFC_CORE_SHAREDPTR_HPP
