/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : datetime/time_zone_unix.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef DATETIME_TIME_ZONE_UNIX_HPP
#define DATETIME_TIME_ZONE_UNIX_HPP

#include "ufc/datetime/time_zone.hpp"
#include "ufc/exception/exception.hpp"
#include <ctime>
#include <cctype>

namespace ufc {

    class tz_info
    {
    private:
        inline tz_info()
        {
            tzset();
        }

    public:

        static tz_info& instance()
        {
            static tz_info __tzinfo;
            return __tzinfo;
        }

        inline int32_t tzone()
        {
#if defined(__APPLE__)  || defined(__FreeBSD__) || defined(POCO_ANDROID) // no timezone global var
            std::time_t now = std::time(NULL);
            struct std::tm t;
            gmtime_r(&now, &t);
            std::time_t utc = std::mktime(&t);
            return now - utc;
#elif defined(__CYGWIN__)
            return -_timezone;
#else
            return -timezone;
#endif
        }

        inline const char* name(bool dst)
        {
            return tzname[dst ? 1 : 0];
        }
    };

    int32_t time_zone::utc_offset()
    {
        return tz_info::instance().tzone();
    }

    int32_t time_zone::dst()
    {
        std::time_t now = std::time(NULL);
        struct std::tm __tm;
        if (!localtime_r(&now, &__tm))
        {
            throw system_error("cannot get local time DST offset");
        }
        return __tm.tm_isdst == 1 ? 3600 : 0;
    }

    bool time_zone::is_dst(const timestamp& __ts)
    {
        std::time_t __time = __ts.epoch_time();
        struct std::tm* __ptm = std::localtime(&__time);
        if (!__ptm) 
        {
            throw system_error("cannot get local time DST flag");
        }
        return __ptm->tm_isdst > 0;
    }

    string time_zone::name()
    {
        return string(tz_info::instance().name(dst() != 0));
    }

    string time_zone::standard_name()
    {
        return string(tz_info::instance().name(false));
    }

    string time_zone::dst_name()
    {
        return string(tz_info::instance().name(true));
    }

}//namespace ufc

#endif//DATETIME_TIME_ZONE_UNIX_HPP
