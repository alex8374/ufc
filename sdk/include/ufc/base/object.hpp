/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/base/object.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-05
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_BASE_OBJECT_HPP
#define UFC_BASE_OBJECT_HPP

#include <ufc/base/platform.hpp>
#include <ufc/base/types.hpp>

namespace ufc {

    class ufc_api object
    {
    public:
        virtual ~object();

        intptr_t hash_code() const;

    public:
        static const char* get_class_name(const std::type_info& __typeinfo);

    protected:
        object();

    private:
        object(const object&);
        object& operator = (const object&);
    };

}//namespace ufc

#ifndef ufc_typename
#define ufc_typename(__type)    ufc::object::get_class_name(typeid(__type))
#endif//ufc_typename

#endif//UFC_BASE_OBJECT_HPP
