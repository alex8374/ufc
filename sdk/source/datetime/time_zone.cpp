/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : datetime/time_zone.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/datetime/time_zone.hpp"
#if defined(_WIN32) || defined(WIN32)
#include <datetime/time_zone_win32.hpp>
#else
#include <datetime/time_zone_unix.hpp>
#endif

namespace ufc {

    int32_t time_zone::tzd()
    {
        return utc_offset() + dst();
    }

}//namespace ufc
