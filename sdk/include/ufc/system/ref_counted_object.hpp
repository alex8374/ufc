/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/system/ref_counted_object.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_SYSTEM_REF_COUNTED_OBJECT_HPP
#define UFC_SYSTEM_REF_COUNTED_OBJECT_HPP

#include <ufc/system/atomic_counter.hpp>

namespace ufc {

    ///
	/// @breif: A base class for objects that employ reference counting based garbage collection.
	///         Reference-counted objects inhibit construction by copying and assignment.
	///
    class ufc_api ref_counted_object: virtual public object
    {
    public:
        ref_counted_object();
        virtual ~ref_counted_object();

        void duplicate();
        void release();
        int32_t ref_count() const;

    private:
        atomic_counter _counter;
    };

}//namespace ufc

#endif//UFC_SYSTEM_REF_COUNTED_OBJECT_HPP