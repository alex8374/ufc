/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/container/ptr_array.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_CONTAINER_PTR_ARRAY_HPP
#define UFC_CONTAINER_PTR_ARRAY_HPP

#include <ufc/smart_ptr/scoped_ptr.hpp>
#include <ufc/exception/assert.hpp>
#include <vector>

namespace ufc {

    ///
    /// @brief A standard container which offers fixed time access to
    /// individual elements in any order.
    /// And can realize the automatic release function of the pointer
    ///
    template <class T> class ptr_array: virtual public object
    {
        typedef typename std::vector<scoped_ptr<T>*> private_t;

    public:
        ptr_array()
        {
        }

        virtual ~ptr_array()
        {
            clear();
        }

        const T* operator [] (uint32_t __pos) const
        {
            ufc_assert(__pos >= 0 && __pos < _datas.size());
            return _datas[__pos]->get();
        }

        T* operator [] (uint32_t __pos)
        {
            ufc_assert(__pos >= 0 && __pos < _datas.size());
            return _datas[__pos]->get();
        }

        uint32_t size() const
        {
            return _datas.size();
        }

        bool empty() const
        {
            return _datas.empty();
        }

        bool has(const T* __ptr) const
        {
            for (int32_t __pos = 0; __pos < _datas.size(); __pos++)
            {
                if (_datas[__pos]->get()== __ptr)
                {
                    return true;
                }
            }
            return false;
        }

        void resize(uint32_t __size)
        {
            if (__size < _datas.size())
            {
                erase(__size, _datas.size() - __size);
            }
        }

        T* append()
        {
            scoped_ptr<T> __ptr(new T);
            if (!__ptr.is_null())
            {
                append(__ptr.get(), true);
            }
            return __ptr.unbind();
        }

        void append(T* __ptr, bool __auto_delete = true)
        {
            ufc_assert(__ptr != NULL && !has(__ptr));

            scoped_ptr<scoped_ptr<T> > __holder(new scoped_ptr<T>(__ptr, __auto_delete));
            _datas.push_back(__holder.get());
            __holder.unbind();
        }

        void insert(uint32_t __pos, T* __ptr, bool __auto_delete = true)
        {
            ufc_assert(__pos >= 0 && __pos < _datas.size());
            ufc_assert(!has(__ptr));

            scoped_ptr<scoped_ptr<T> > __holder(new scoped_ptr<T>(__ptr, __auto_delete));
            if (_datas.size() <= __pos)
                _datas.insert(_datas.end(), __holder.get());
            else
                _datas.insert(_datas.begin() + __pos, __holder.get());
            __holder.unbind();
        }

        void erase(uint32_t __pos, uint32_t __n = 1)
        {
            ufc_assert(__pos >= 0 && __pos < _datas.size());
            typename private_t::iterator __it  = _datas.begin();
            typename private_t::iterator __end = _datas.end();
            typename private_t::iterator __tmp = __it + __pos;
            for (__tmp = __it + __pos; __n-- > 0 && __tmp != __end; __tmp++)
            {
                memory::delete_ptr(*__tmp);
            }
            _datas.erase(__it, __tmp);
        }

        void clear()
        {
           erase(0, _datas.size());
        }

    private:
        private_t _datas;
    };

}//namespace ufc

#endif//UFC_CONTAINER_PTR_ARRAY_HPP