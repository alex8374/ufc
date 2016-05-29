/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/container/array.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_CONTAINER_ARRAY_HPP
#define UFC_CONTAINER_ARRAY_HPP

#include <ufc/system/ref_counted_object.hpp>
#include <ufc/exception/assert.hpp>
#include <vector>
#include <functional>
#include <algorithm>

namespace ufc {

    ///
    ///  @brief A standard container which offers fixed time access to
    ///  individual elements in any order.
    ///
    template <class T> class array: virtual public object
    {
        class private_t: public ref_counted_object
        {
        public:
            typedef typename std::vector<T> vector;

        public:
            private_t()
            {
            }

            virtual ~private_t()
            {
            }

        public:
            vector _datas;
        };
        typedef typename private_t::vector::iterator   iterator;

    public:
        array() 
            : _impl(new private_t)
        {
            ufc_check_ptr(_impl);
        }

        array(const array& __arr) 
            : _impl(__arr._impl)
        {
            ufc_check_ptr(_impl);
            _impl->duplicate();
        }

        array(const T* __buffer, uint32_t __buffer_length) 
            : _impl(new private_t)
        {
            ufc_check_ptr(_impl);
            _impl->_datas.assign(__buffer, __buffer + __buffer_length);
        }

        virtual ~array()
        {
            _impl->release();
        }

        array& operator = (const array& __arr)
        {
            if (_impl != __arr._impl)
            {
                _impl->release();
                _impl = __arr._impl;
                _impl->duplicate();
            }
            return *this;
        }

        T& operator [] (uint32_t __pos)
        {
            return _impl->_datas[__pos];
        }

        const T& operator [] (uint32_t __pos) const
        {
            return _impl->_datas[__pos];
        }

        bool empty() const
        {
            return _impl->_datas.empty();
        }

        uint32_t length() const
        {
            return _impl->_datas.size();
        }

        T* data()
        {
            if (_impl->_datas.empty()) 
            {
                return 0;
            }
            return &(_impl->_datas[0]);
        }

        const T* data() const
        {
            if (_impl->_datas.empty()) 
            {
                return 0;
            }
            return &(_impl->_datas[0]);
        }

        bool has(const T& __element) const
        {
            return find(__element) >= 0;
        }

        int32_t find(const T& __element) const
        {
            for (int32_t __pos = 0; __pos < _impl->_datas.size(); __pos++)
            {
                if (_impl->_datas[__pos] == __element) 
                {
                    return __pos;
                }
            }
            return -1;
        }

        array& clear()
        {
            _impl->_datas.clear();
            return *this;
        }

        array& assign(const T& __element, uint32_t __length)
        {
            _impl->_datas.assign(__element, __length);
            return *this;
        }

        array& assign(const T* __buffer, uint32_t __buffer_length)
        {
            _impl->_datas.assign(__buffer, __buffer + __buffer_length);
            return *this;
        }

        array& insert(uint32_t __pos, const T& __element)
        {
            if (__pos >= _impl->_datas.size())
                _impl->_datas.insert(_impl->_datas.end(), __element);
            else
                _impl->_datas.insert(_impl->_datas.begin() + __pos, __element);
            return *this;
        }

        array& insert(uint32_t __pos, const T* __buffer, uint32_t __buffer_length)
        {
            if (__pos >= _impl->_datas.size())
                _impl->_datas.insert(_impl->_datas.end(), __buffer, __buffer + __buffer_length);
            else
                _impl->_datas.insert(_impl->_datas.begin() + __pos, __buffer, __buffer + __buffer_length);
            return *this;
        }

        array& append(const T& __element)
        {
            _impl->_datas.insert(_impl->_datas.end(), __element);
            return *this;
        }

        array& append(const T* __buffer, uint32_t __buffer_length)
        {
            _impl->_datas.insert(_impl->_datas.end(), __buffer, __buffer + __buffer_length);
            return *this;
        }

        array& erase(uint32_t __pos, uint32_t __num = 1)
        {
            if (__pos < _impl->_datas.size() && __num > 0)
            {
                iterator __it  = _impl->_datas.begin();
                iterator __end = _impl->_datas.end();
                __it += __pos;
                if (__it != __end)
                {
                    if ((__pos + __num) <= _impl->_datas.size())
                    {
                        _impl->_datas.erase(__it, __it + __num);
                    }
                    else
                    {
                        _impl->_datas.erase(__it, __end);
                    }
                }
            }
            return *this;
        }

        array& sort()
        {
            return sort(std::less<T>());
        }

        template <class Compare>
        array& sort(const Compare& __compare)
        {
            int32_t __size = _impl->_datas.size();
            for (int32_t __pos = 0; __pos < __size; __pos++)
            {
                for (int32_t __i = __pos + 1; __i < __size; __i++)
                {
                    if (__compare(_impl->_datas[__i], _impl->_datas[__pos]))
                    {
                        std::swap(_impl->_datas[__pos], _impl->_datas[__i]);
                    }
                }
            }
            return *this;
        }

        bool operator == (const array& __arr) const
        {
            if (__arr._impl != _impl)
            {
                if (__arr._impl->_datas.size() != _impl->_datas.size()) 
                {
                    return false;
                }

                iterator __it  = _impl->_datas.begin();
                iterator __end = _impl->_datas.end();
                iterator __tmp = __arr._impl->_datas.begin();
                for (; __it != __end; __it++, __tmp++)
                {
                    if (*__it != *__tmp)
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        bool operator != (const array& __arr) const
        {
            return !(__arr == *this);
        }

    private:
        private_t* _impl;
    };

    typedef array<byte_t> byte_array;
    typedef array<string> string_array;

}//namespace ufc

#endif//UFC_CONTAINER_ARRAY_HPP