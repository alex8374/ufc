/*******************************************************************************
       Copyright(C) 2016, Free software engineer and contributor
 ******************************************************************************
  Filename   : ufc/core/sharedarray.hpp
  Author     : lcq<lichangqing8374@hotmail.com>
  Date       : 2016-05-09
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_CORE_SHAREDARRAY_HPP
#define UFC_CORE_SHAREDARRAY_HPP

#include <ufc/smart_ptr/scoped_array.hpp>
#include <algorithm>

namespace ufc {
    
    ///
    /// @breif: shared_array extends shared_ptr to arrays.
    /// The array pointed to is deleted when the last shared_array pointing to it
    /// is destroyed or reset.
    ///
    template <class T> class shared_array: virtual public object
    {
        template<class U> friend class shared_array;

    public:
        inline shared_array()
            : _parray(0)
            , _counter(new scoped_array<T>())
        {
            ufc_check_ptr(_counter);
        }

        template <class U>
        explicit shared_array(U * __parray)
            : _parray(__parray)
            , _counter(new scoped_array<T>(__parray))
        {
            ufc_check_ptr(_counter);
        }

        template <class U>
        inline shared_array(const shared_array<U>& __array)
            : _parray(const_cast<U*>(__array._parray))
            , _counter(__array._counter)
        {
            ufc_check_ptr(_counter);

            _counter->duplicate();
        }

        inline ~shared_array()
        {
            _counter->release();
        }

        template <class U>
        inline shared_array& operator = (const shared_array<U>& __array)
        {
            if (__array._parray != _parray)
            {
                shared_array(__array).swap(*this);
            }
            return *this;
        }

        template <class U>
        inline shared_array& operator = (U* __parray)
        {
            if (__parray != _parray)
            {
                shared_array(__parray).swap(*this);
            }
            return *this;
        }

        template <class U>
        inline void reset(const shared_array<U>& __array)
        {
            if (__array._parray != _parray)
            {
                shared_array(__array).swap(*this);
            }
            return *this;
        }

        template <class U>
        inline void reset(U* __parray)
        {
            if (__parray != _parray)
            {
                shared_array(__parray).swap(*this);
            }
            return *this;
        }

        inline T* get() const throw ()
        {
            return _parray;
        }

        inline const T& operator [] (uint32_t __pos) const
        {
            ufc_check_ptr(_parray);
            ufc_assert(__pos >= 0);
            return _parray[__pos];
        }

        inline T& operator [] (uint32_t __pos)
        {
            ufc_check_ptr(_parray);
            ufc_assert(__pos >= 0);
            return _parray[__pos];
        }

        inline operator bool () const throw()
        {
            return !is_null();
        }

        inline bool operator ! () const throw()
        {
            return is_null();
        }

        inline bool is_null() const throw()
        {
            return !_parray;
        }

        inline bool unique() const
        {
            return _counter->ref_count() == 1;
        }

        inline uint32_t use_count() const
        {
            return _counter->ref_count();
        }

        inline void swap(shared_array& __array)
        {
            std::swap(_parray, __array._parray);
            std::swap(_counter, __array._counter);
        }

    private:
        inline shared_array(T* __parray, ref_counted_object* __counter)
            : _parray(__parray), _counter(__counter)
        {
            _counter->duplicate();
        }

        T*                  _parray;
        ref_counted_object* _counter;
    };

    template <class T, class U> inline bool operator == (const shared_array<T>& __rhs, const shared_array<U>& __lhs)
    {
        return __rhs.get() == __lhs.get();
    }

    template <class T, class U> inline bool operator == (const shared_array<T>& __rhs, const U* __lhs)
    {
        return __rhs.get() == __lhs;
    }

    template <class T, class U> inline bool operator == (const U* __rhs, const shared_array<U>& __lhs)
    {
        return __rhs == __lhs.get();
    }

    template <class T, class U> inline bool operator != (const shared_array<T>& __rhs, const shared_array<U>& __lhs)
    {
        return __rhs.get() != __lhs.get();
    }

    template <class T, class U> inline bool operator != (const shared_array<T>& __rhs, const U* __lhs)
    {
        return __rhs.get() != __lhs;
    }

    template <class T, class U> inline bool operator != (const U* __rhs, const shared_array<U>& __lhs)
    {
        return __rhs != __lhs.get();
    }

    template <class T, class U> inline bool operator >= (const shared_array<T>& __rhs, const shared_array<U>& __lhs)
    {
        return __rhs.get() >= __lhs.get();
    }

    template <class T, class U> inline bool operator >= (const shared_array<T>& __rhs, const U* __lhs)
    {
        return __rhs.get() >= __lhs;
    }

    template <class T, class U> inline bool operator >= (const U* __rhs, const shared_array<U>& __lhs)
    {
        return __rhs >= __lhs.get();
    }

    template <class T, class U> inline bool operator >  (const shared_array<T>& __rhs, const shared_array<U>& __lhs)
    {
        return __rhs.get() > __lhs.get();
    }

    template <class T, class U> inline bool operator >  (const shared_array<T>& __rhs, const U* __lhs)
    {
        return __rhs.get() >  __lhs;
    }

    template <class T, class U> inline bool operator >  (const U* __rhs, const shared_array<U>& __lhs)
    {
        return __rhs >  __lhs.get();
    }

    template <class T, class U> inline bool operator <= (const shared_array<T>& __rhs, const shared_array<U>& __lhs)
    {
        return __rhs.get() <= __lhs.get();
    }

    template <class T, class U> inline bool operator <= (const shared_array<T>& __rhs, const U* __lhs)
    {
        return __rhs.get() <= __lhs;
    }

    template <class T, class U> inline bool operator <= (const U* __rhs, const shared_array<U>& __lhs)
    {
        return __rhs <= __lhs.get();
    }

    template <class T, class U> inline bool operator <  (const shared_array<T>& __rhs, const shared_array<U>& __lhs)
    {
        return __rhs.get() < __lhs.get();
    }

    template <class T, class U> inline bool operator <  (const shared_array<T>& __rhs, const U* __lhs)
    {
        return __rhs.get() <  __lhs;
    }

    template <class T, class U> inline bool operator <  (const U* __rhs, const shared_array<U>& __lhs)
    {
        return __rhs <  __lhs.get();
    }

}//namespace ufc

#endif//UFC_CORE_SHAREDARRAY_HPP
