/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/container/buffer.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_CONTAINER_BUFFER_HPP
#define UFC_CONTAINER_BUFFER_HPP

#include <ufc/exception/assert.hpp>
#include <cstring>

namespace ufc {

    ///
	/// @breif: A very simple buffer class that allocates a buffer of
	///         a given type and size in the constructor and
	///         deallocates the buffer in the destructor.
	///
	///         This class is useful everywhere where a temporary buffer
	///         is needed.
    ///
    template <class T> class buffer: virtual public object
    {
    public:
        inline buffer()
            : _size(0)
            , _buffer(0)
        {
        }

        explicit buffer(uint32_t __size)
            : _size(0)
            , _buffer(0)
        {
            resize(__size, false);
        }

        virtual ~buffer()
        {
            resize();
        }

        inline const T& operator [] (uint32_t __pos) const
        {
            ufc_assert (__pos >= 0 && __pos < _size);
            return *(_buffer + __pos);
        }

        inline T& operator [] (uint32_t __pos)
        {
            ufc_assert (__pos >= 0 && __pos < _size);
            return *(_buffer + __pos);
        }

        inline uint32_t size() const
        {
            return _size;
        }

        inline bool empty() const
        {
            return (_size <= 0);
        }

        inline void resize(uint32_t __size = 0, bool __save_content = true)
        {
            if (__size != _size)
            {
                T* __buffer = 0;
                if (__size > 0)
                {
                    memory::new_array(__buffer, __size);
                    if (__buffer && __save_content && _size > 0)
                    {
                        uint32_t __size = __size > _size? _size: __size;
                        std::memcpy(__buffer, _buffer, __size);
                    }
                }
                memory::delete_array(_buffer);

                _buffer = __buffer;
                _size   = __size;
            }
        }

        inline T* get()
        {
            return _buffer;
        }

        inline const T* get() const
        {
            return _buffer;
        }

        inline T* release() const
        {
            T* p    = _buffer;
            _size   = 0;
            _buffer = NULL;
            return p;
        }

    private:
        uint32_t _size;
        T*       _buffer;
    };

}//namespace ufc

#endif//UFC_CONTAINER_BUFFER_HPP