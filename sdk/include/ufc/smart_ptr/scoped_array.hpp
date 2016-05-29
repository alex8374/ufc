/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/smart_ptr/scoped_array.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_SMART_PTR_SCOPED_ARRAY_HPP
#define UFC_SMART_PTR_SCOPED_ARRAY_HPP

#include <ufc/system/ref_counted_object.hpp>

namespace ufc {

    ///
    /// @breif: scoped_array extends scoped_ptr to arrays. Deletion of the array pointed to
    /// is guaranteed, either on destruction of the scoped_array or via an explicit
    /// reset(). Use shared_array or vector if your needs are more complex.
    ///
    template <class T> class scoped_array: public ref_counted_object
    {
    public:
        inline scoped_array()
            : _parray(0), _auto_delete(true)
        {
        }

        explicit scoped_array(T* __parray, bool __auto_delete = true)
            : _parray(__parray), _auto_delete(__auto_delete)
        {
        }

        virtual ~scoped_array()
        {
            reset();
        }

        inline T& operator [] (uint32_t __pos) const
        {
            ufc_check_ptr(_parray);
            return _parray[__pos];
        }

        inline bool auto_delete() const
        {
            return _auto_delete;
        }

        inline T* get() const throw()
        {
            return _parray;
        }

        inline T* unbind() const throw()
        {
            T* __parray = _parray;
            _parray     = 0;
            return __parray;
        }

        inline void reset(T* __parray = 0, bool __auto_delete = true) throw()
        {
            if (__parray != _parray)
            {
                memory::delete_array(_parray, _auto_delete);
                _parray      = __parray;
                _auto_delete = __auto_delete;
            }
        }

        inline bool is_null() const throw()
        {
            return _parray == 0;
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
        mutable T* _parray;
        bool       _auto_delete;
    };

    template <class T>
    inline bool operator == (const scoped_array<T>& __lhs, const scoped_array<T>& __rhs)
    {
        return __lhs.get() == __rhs.get();
    }
        
    template <class T>
    inline bool operator == (const scoped_array<T>& __lhs, T* __rhs)
    {
        return __lhs.get() == __rhs;
    }

    template <class T>
    inline bool operator == (T* __lhs, const scoped_array<T>& __rhs)
    {
        return __lhs == __rhs.get();
    }

    template <class T>
    inline bool operator != (const scoped_array<T>& __lhs, const scoped_array<T>& __rhs)
    {
        return __lhs.get() != __rhs.get();
    }

    template <class T>
    inline bool operator != (const scoped_array<T>& __lhs, T* __rhs)
    {
        return __lhs.get() != __rhs;
    }
    
    template <class T>
    inline bool operator != (T* __lhs, const scoped_array<T>& __rhs)
    {
        return __lhs != __rhs.get();
    }

}//namespace ufc

#endif//UFC_SMART_PTR_SCOPED_ARRAY_HPP
