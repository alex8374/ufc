/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : datetime/time_format.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/datetime/time_format.hpp"

namespace ufc {

    const string time_format::iso8601_format("%Y-%m-%dT%H:%M:%S%z");
    const string time_format::iso8601_frac_format("%Y-%m-%dT%H:%M:%s%z");
    const string time_format::rfc822_format("%w, %e %b %y %H:%M:%S %Z");
    const string time_format::rfc1123_format("%w, %e %b %Y %H:%M:%S %Z");
    const string time_format::http_format("%w, %d %b %Y %H:%M:%S %Z");
    const string time_format::rfc850_format("%W, %e-%b-%y %H:%M:%S %Z");
    const string time_format::rfc1036_format("%W, %e %b %y %H:%M:%S %Z");
    const string time_format::asctime_format("%w %b %f %H:%M:%S %Y");
    const string time_format::simple_format("%Y-%m-%d %H:%M:%S");

}//namespace ufc
