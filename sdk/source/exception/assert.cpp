/*******************************************************************************
       Copyright(C) 2016, Free software engineer and contributor
 ******************************************************************************
  File name  : exception/assert.cpp
  Author     : lcq<lichangqing8374@hotmail.com>
  Date       : 2016-05-09
  Description: 
  Modified   : 
*******************************************************************************/

#include "ufc/exception/assert.hpp"
#include "ufc/exception/exception.hpp"

namespace ufc {

    void assertion::throw_assert_(const char* __description, const char* __file, uint32_t __line)
    {
        throw assertion_violation_error(string::format("%s in file \"%s\", line %d", __description, __file, __line));
    }

    void assertion::throw_check_ptr_(const char* __description, const char* __file, uint32_t __line)
    {
        throw null_pointer_error(string::format("%s in file \"%s\", line %d", __description, __file, __line));
    }

}//namespace ufc
