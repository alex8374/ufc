/*******************************************************************************
       Copyright(C) 2016, Free software engineer and contributor
 ******************************************************************************
  Filename   : ufc/ufc.hpp
  Author     : lcq<lichangqing8374@hotmail.com>
  Date       : 2016-05-09
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_UFC_HPP
#define UFC_UFC_HPP

#include <ufc/container/buffer.hpp>
#include <ufc/container/array.hpp>
#include <ufc/container/ptr_array.hpp>
#include <ufc/container/circulation_queue.hpp>
#include <ufc/container/deque.hpp>
#include <ufc/container/list.hpp>
#include <ufc/container/map.hpp>
#include <ufc/container/multimap.hpp>
#include <ufc/container/multiset.hpp>
#include <ufc/container/priority_queue.hpp>
#include <ufc/container/queue.hpp>
#include <ufc/container/set.hpp>
#include <ufc/container/stack.hpp>
#include <ufc/container/vector.hpp>
#include <ufc/datetime/timestamp.hpp>
#include <ufc/datetime/timespan.hpp>
#include <ufc/datetime/time_zone.hpp>
#include <ufc/datetime/time_format.hpp>
#include <ufc/datetime/time.hpp>
#include <ufc/datetime/date.hpp>
#include <ufc/datetime/date_time.hpp>
#include <ufc/exception/assert.hpp>
#include <ufc/exception/exception.hpp>
#include <ufc/filesystem/file.hpp>
#include <ufc/filesystem/path.hpp>
#include <ufc/filesystem/fstream.hpp>
#include <ufc/smart_ptr/scoped_array.hpp>
#include <ufc/smart_ptr/scoped_ptr.hpp>
#include <ufc/smart_ptr/shared_array.hpp>
#include <ufc/smart_ptr/shared_ptr.hpp>
#include <ufc/string/string.hpp>
#include <ufc/string/string_util.hpp>
#include <ufc/string/string_builder.hpp>
#include <ufc/string/string_tokenizer.hpp>
#include <ufc/system/atomic_counter.hpp>
#include <ufc/system/environment.hpp>
#include <ufc/system/ref_counted_object.hpp>
#include <ufc/thread/mutex.hpp>
#include <ufc/thread/event.hpp>
#include <ufc/thread/condition.hpp>
#include <ufc/thread/rwlock.hpp>
#include <ufc/thread/semaphore.hpp>
#include <ufc/thread/runnable.hpp>
#include <ufc/thread/runnable_adapter.hpp>
#include <ufc/thread/runnable_target.hpp>
#include <ufc/thread/thread.hpp>
#include <ufc/thread/thread_local.hpp>
#include <ufc/thread/thread_pool.hpp>
#include <ufc/thread/thread_group.hpp>

#if defined(ufc_os_family_windows)
    #if !defined(ufc_no_automatic_libs)
        #pragma comment(lib, "ufc.lib")
    #endif
#endif

#if defined(WIN32) || defined(_WIN32)
    #define ufc_export __declspec(dllexport)
#else
    #define ufc_export
#endif

extern "C"
{
    void ufc_export ufc_build_manifest(ufc::manifest& __manifest);
    void ufc_export ufc_initialize_library();
    void ufc_export ufc_uninitialize_library();
}

//
// 
// This macro is used to automatically implement the ufc_build_manifest interface,
// and is used to load objects in a dynamic library. 
//
// Usage:
//
// ufc_export_begin
//     ufc_export_object(__key1, __object_type1)
//     ufc_export_object(__key2, __object_type2)
//     ...
// ufc_export_end
//
#define ufc_export_begin                                      	    \
    extern "C" void ufc_build_manifest(ufc::manifest& __manifest)  	\
    {
#define ufc_export_object(__key, __type)                            \
        __manifest.add<__type>(__key);

#define ufc_export_end                                        	    \
    }

#define ufc_export_object_once(__key, __type)                       \
    ufc_begin_manifest                                          	\
        ufc_export_object(__key, __type)                            \
    ufc_end_manifest

#endif//UFC_UFC_HPP
