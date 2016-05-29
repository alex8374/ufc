/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/container/stack.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-24
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_CONTAINER_STACK_HPP
#define UFC_CONTAINER_STACK_HPP

#include <ufc/base/config.hpp>
#include <stack>
#include <algorithm>

namespace ufc {
    
    template<typename T>
    class stack: public std::stack<T>, virtual public object
    {
        typedef typename std::stack<T>               super_type;

    public:
        typedef typename super_type::value_type      value_type;
        typedef typename super_type::reference       reference;
        typedef typename super_type::const_reference const_reference;
        typedef typename super_type::size_type       size_type;

    public:
        stack()
        {
        }

        virtual ~stack()
        {
        }
    };

}//namespace ufc

#endif//UFC_CONTAINER_STACK_HPP
