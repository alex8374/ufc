/*******************************************************************************
       Copyright(C) 2016, Free software engineer and contributor
 ******************************************************************************
  Filename   : ufc/core/scopedptr.hpp
  Author     : lcq<lichangqing8374@hotmail.com>
  Date       : 2016-05-09
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_CORE_SCOPEDPTR_HPP
#define UFC_CORE_SCOPEDPTR_HPP

#include <ufc/system/ref_counted_object.hpp>
#include <memory>

namespace ufc {

    ///
    /// @breif: scoped_ptr mimics a built-in pointer except that it guarantees deletion
    /// of the object pointed to, either on destruction of the scoped_ptr or via
    /// an explicit reset(). scoped_ptr is a simple solution for simple needs;
    /// use shared_ptr or std::auto_ptr if your needs are more complex.
    ///
    template <class T> class scoped_ptr: public ref_counted_object
    {
    public:
        inline scoped_ptr() throw()
            : _ptr(0), _auto_delete(true)
        {
        }

        inline scoped_ptr(T* ptr, bool __auto_delete = true) throw()
            : _ptr(ptr), _auto_delete(__auto_delete)
        {
        }

        inline scoped_ptr(const std::auto_ptr<T>& ptr, bool __auto_delete = true) throw()
            : _ptr(ptr.release()), _auto_delete(__auto_delete)
        {
        }

        virtual ~scoped_ptr() throw()
        {
            reset();
        }

        inline T* operator -> () const
        {
            ufc_check_ptr(_ptr);
            return _ptr;
        }

        inline T& operator * () const
        {
            ufc_check_ptr(_ptr);
            return *_ptr;
        }

        inline bool auto_delete() const
        {
            return _auto_delete;
        }

        inline T* get() const throw()
        {
            return _ptr;
        }

        inline T* unbind() const throw()
        {
            T* ptr = _ptr;
            _ptr   = 0;
            return ptr;
        }

        inline void reset(T* ptr = 0, bool __auto_delete = true) throw()
        {
            if (ptr != _ptr)
            {
                memory::delete_ptr(_ptr, _auto_delete);
                _ptr = ptr;
                _auto_delete = __auto_delete;
            }
        }

        inline bool is_null() const throw()
        {
            return _ptr == NULL;
        }

        inline operator bool () const throw()
        {
            return !is_null();
        }

        inline bool operator ! () const throw()
        {
            return is_null();
        }

    private:
        mutable T* _ptr;
        bool       _auto_delete;
    };

    template <class T>
    inline bool operator == (const scoped_ptr<T>& __lhs, const scoped_ptr<T>& __rhs)
    {
        return __lhs.get() == __rhs.get();
    }

    template <class T>
    inline bool operator == (const scoped_ptr<T>& __lhs, T* __rhs)
    {
        return __lhs.get() == __rhs;
    }

    template <class T>
    inline bool operator == (T* __lhs, const scoped_ptr<T>& __rhs)
    {
        return __lhs == __rhs.get();
    }

    template <class T>
    inline bool operator != (const scoped_ptr<T>& __lhs, const scoped_ptr<T>& __rhs)
    {
        return __lhs.get() != __rhs.get();
    }

    template <class T>
    inline bool operator != (const scoped_ptr<T>& __lhs, T* __rhs)
    {
        return __lhs.get() != __rhs;
    }

    template <class T>
    inline bool operator != (T* __lhs, const scoped_ptr<T>& __rhs)
    {
        return __lhs != __rhs.get();
    }

}//namespace ufc

#endif//UFC_CORE_SCOPEDPTR_HPP

