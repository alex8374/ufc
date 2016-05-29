/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/container/queue.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-24
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_CONTAINER_QUEUE_HPP
#define UFC_CONTAINER_QUEUE_HPP

#include <ufc/base/config.hpp>
#include <queue>
#include <algorithm>

namespace ufc {

    template <class T>
    class queue: public std::queue<T>, virtual public object
    {
        typedef typename std::queue<T>                  super_type;    

    public:
        typedef typename super_type::value_type         value_type;
        typedef typename super_type::reference          reference;
        typedef typename super_type::const_reference    const_reference;
        typedef typename super_type::size_type          size_type;

    public:
        queue()
        {
        }

        queue(const queue& __other)
            : queue(__other)
        {
        }

        virtual ~queue()
        {
        }

        queue& operator = (const queue& __other)
        {
            super_type::operator = (__other);
            return *this;
        }

        void swap(queue& __other)
        {
            std::swap(dynamic_cast<super_type&>(*this), dynamic_cast<super_type&>(__other));
        }

    public:
        bool operator == (const queue& __other) const
        {
            return dynamic_cast<const super_type&>(*this) == dynamic_cast<const super_type&>(__other) ;
        }

        bool operator != (const queue& __other) const
        {
            return dynamic_cast<const super_type&>(*this) != dynamic_cast<const super_type&>(__other) ;
        }

        bool operator >= (const queue& __other) const
        {
            return dynamic_cast<const super_type&>(*this) >= dynamic_cast<const super_type&>(__other) ;
        }

        bool operator >  (const queue& __other) const
        {
            return dynamic_cast<const super_type&>(*this) > dynamic_cast<const super_type&>(__other) ;
        }

        bool operator <= (const queue& __other) const
        {
            return dynamic_cast<const super_type&>(*this) <= dynamic_cast<const super_type&>(__other) ;
        }

        bool operator <  (const queue& __other) const
        {
            return dynamic_cast<const super_type&>(*this) < dynamic_cast<const super_type&>(__other) ;
        }
    };

}//namespace ufc

#endif//UFC_CONTAINER_QUEUE_HPP
