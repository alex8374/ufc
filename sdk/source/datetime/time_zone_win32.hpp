/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : datetime/time_zone_win32.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef DATETIME_TIME_ZONE_WIN32_HPP
#define DATETIME_TIME_ZONE_WIN32_HPP

#include "ufc/datetime/time_zone.hpp"
#include "ufc/exception/exception.hpp"
#include <Windows.h>
#include <cctype>
#include <ctime>

namespace ufc {

    int32_t time_zone::utc_offset()
    {
        TIME_ZONE_INFORMATION __tzinfo;
        DWORD __dst_flag = GetTimeZoneInformation(&__tzinfo);
        return -__tzinfo.Bias*60;
    }

    int32_t time_zone::dst()
    {
        TIME_ZONE_INFORMATION __tzinfo;
        DWORD __dst_flag = GetTimeZoneInformation(&__tzinfo);
        return __dst_flag == TIME_ZONE_ID_DAYLIGHT ? -__tzinfo.DaylightBias*60 : 0;
    }

    bool time_zone::is_dst(const timestamp& __ts)
    {
        std::time_t time = __ts.epochTime();
        struct std::tm* tms = std::localtime(&time);
        if (!tms) throw system_error("cannot get local time DST flag");
        return tms->tm_isdst > 0;
    }

    string time_zone::name()
    {
        string __result;
        TIME_ZONE_INFORMATION __tzinfo;
        DWORD __dst_flag = GetTimeZoneInformation(&__tzinfo);
        WCHAR* __ptr = __dst_flag == TIME_ZONE_ID_DAYLIGHT ? __tzinfo.DaylightName : __tzinfo.StandardName;
        char __buffer[256];
        DWORD rc = WideCharToMultiByte(CP_ACP, 0, __ptr, -1, __buffer, sizeof(__buffer), NULL, NULL);
        if (rc) __result = __buffer;
        return __result;
    }

    string time_zone::standard_name()
    {
        string __result;
        TIME_ZONE_INFORMATION __tzinfo;
        DWORD __dst_flag = GetTimeZoneInformation(&__tzinfo);
        WCHAR* __ptr = __tzinfo.StandardName;
        char __buffer[256];
        DWORD rc = WideCharToMultiByte(CP_ACP, 0, __ptr, -1, __buffer, sizeof(__buffer), NULL, NULL);
        if (rc) __result = __buffer;
        return __result;
    }

    string time_zone::dst_name()
    {
        string __result;
        TIME_ZONE_INFORMATION __tzinfo;
        DWORD __dst_flag = GetTimeZoneInformation(&__tzinfo);
        WCHAR* __ptr = __tzinfo.DaylightName;
        char __buffer[256];
        DWORD rc = WideCharToMultiByte(CP_ACP, 0, __ptr, -1, __buffer, sizeof(__buffer), NULL, NULL);
        if (rc) __result = __buffer;
        return __result;
    }

}//namespace ufc

#endif//DATETIME_TIME_ZONE_WIN32_HPP
