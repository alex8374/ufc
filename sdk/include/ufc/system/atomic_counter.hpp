/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/system/atomiccounter.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_SYSTEM_ATOMIC_COUNTER_HPP
#define UFC_SYSTEM_ATOMIC_COUNTER_HPP

#include <ufc/base/config.hpp>

namespace ufc {

    ///
	/// @breif: This class implements a simple counter, which
	///         provides atomic operations that are safe to
	///         use in a multithreaded environment.
    ///
    class ufc_api atomic_counter: virtual public object
    {
    public:
        atomic_counter();
        atomic_counter(const atomic_counter& __counter);
        explicit atomic_counter(int32_t __initial_value);
        virtual ~atomic_counter();

        atomic_counter& operator = (const atomic_counter& __counter);
        atomic_counter& operator = (int32_t __value);

        operator int32_t () const;

        int32_t value() const;

        int32_t operator ++ ();     // prefix         
        int32_t operator ++ (int);  // postfix          
        int32_t operator -- ();     // prefix         
        int32_t operator -- (int);  // postfix

        bool operator ! () const;

    private:
        class private_t;
        private_t* _impl;
    };

}//namespace ufc

#endif//UFC_SYSTEM_ATOMIC_COUNTER_HPP