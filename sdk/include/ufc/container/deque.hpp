/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/container/deque.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-24
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_CONTAINER_DEQUE_HPP
#define UFC_CONTAINER_DEQUE_HPP

#include <ufc/base/config.hpp>
#include <deque>
#include <algorithm>

namespace ufc {

    template <class T>
    class deque: public std::deque<T>, virtual public object
    {
        typedef typename std::deque<T>                      super_type;

    public:
        typedef typename super_type::value_type             value_type;
        typedef typename super_type::pointer                pointer;
        typedef typename super_type::const_pointer          const_pointer;
        typedef typename super_type::reference              reference;
        typedef typename super_type::const_reference        const_reference;
        typedef typename super_type::iterator               iterator;
        typedef typename super_type::const_iterator         const_iterator;
        typedef typename super_type::const_reverse_iterator const_reverse_iterator;
        typedef typename super_type::reverse_iterator       reverse_iterator;
        typedef typename super_type::size_type              size_type;
        typedef typename super_type::difference_type        difference_type;
        typedef typename super_type::allocator_type         allocator_type;

    public:
        deque()
        {
        }

        deque(const deque& __other)
            : super_type(__other)
        {
        }

        explicit deque(size_type __n, const value_type& __value = value_type())
            : super_type(__n, __value)
        {
        }

        template <class InputIterator>
        deque(InputIterator __first, InputIterator __last)
            : super_type(__first, __last)
        {
        }

        virtual ~deque()
        {
        }

        deque& operator = (const deque& __other)
        {
            super_type::operator = (__other);
            return *this;
        }

        void swap(deque& __other)
        {
            std::swap(dynamic_cast<super_type&>(*this), dynamic_cast<super_type&>(__other));
        }

    public:
        bool operator == (const deque& __other) const
        {
            return dynamic_cast<const super_type&>(*this) == dynamic_cast<const super_type&>(__other) ;
        }

        bool operator != (const deque& __other) const
        {
            return dynamic_cast<const super_type&>(*this) != dynamic_cast<const super_type&>(__other) ;
        }

        bool operator >= (const deque& __other) const
        {
            return dynamic_cast<const super_type&>(*this) >= dynamic_cast<const super_type&>(__other) ;
        }

        bool operator >  (const deque& __other) const
        {
            return dynamic_cast<const super_type&>(*this) > dynamic_cast<const super_type&>(__other) ;
        }

        bool operator <= (const deque& __other) const
        {
            return dynamic_cast<const super_type&>(*this) <= dynamic_cast<const super_type&>(__other) ;
        }

        bool operator <  (const deque& __other) const
        {
            return dynamic_cast<const super_type&>(*this) < dynamic_cast<const super_type&>(__other) ;
        }
    };

}//namespace ufc

#endif//UFC_CONTAINER_DEQUE_HPP
