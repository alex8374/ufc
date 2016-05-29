/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : datetime/timestamp.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/datetime/timestamp.hpp"
#include "ufc/exception/exception.hpp"
#include <algorithm>
#include <cmath>
#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#else
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/times.h>
#endif

namespace ufc {

    timestamp::time_val timestamp::resolution = 1000000;
    timestamp::time_val timestamp::utc_time   = timestamp::time_val(0x31) << 32 | timestamp::time_val(0x18A41200); //0x3118A41200

    timestamp::timestamp()
        : _tv(0)
    {
    }

    timestamp::timestamp(time_val __tv)
        : _tv(__tv)
    {
    }

    timestamp::timestamp(const timestamp& __ts)
        : _tv(__ts._tv)
    {
    }

    timestamp::~timestamp()
    {
    }

    timestamp& timestamp::operator = (const timestamp& __ts)
    {
        _tv = __ts._tv;
        return *this;
    }

    timestamp& timestamp::operator = (time_val __tv)
    {
        _tv = __tv;
        return *this;
    }

    void timestamp::swap(timestamp& __ts)
    {
        std::swap(_tv, __ts._tv);
    }

    timestamp timestamp::from_epoch_time(std::time_t __tv)
    {
        return timestamp(time_val(__tv) * resolution);
    }

    timestamp& timestamp::update()
    {
#if defined(_WIN32) || defined(WIN32)

        FILETIME __ft;
        GetSystemTimeAsFileTime(&__ft);

        ULARGE_INTEGER __epoch; // UNIX __epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
        __epoch.LowPart  = 0xD53E8000;
        __epoch.HighPart = 0x019DB1DE;

        ULARGE_INTEGER __ts;
        __ts.LowPart  = __ft.dwLowDateTime;
        __ts.HighPart = __ft.dwHighDateTime;
        __ts.QuadPart -= __epoch.QuadPart;
        _tv = __ts.QuadPart/10;

#else
        struct timeval __tv;
        if (gettimeofday(&__tv, NULL))
        {
            throw system_error("cannot get time of day");
        }
        _tv = time_val(__tv.tv_sec) * resolution + __tv.tv_usec;

#endif
        return *this;
    }

#if defined(_WIN32) || defined(WIN32)

    timestamp timestamp::from_file_time_np(uint32_t __file_time_low, uint32_t __file_time_high)
    {
        ULARGE_INTEGER __epoch; // UNIX __epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
        __epoch.LowPart  = 0xD53E8000;
        __epoch.HighPart = 0x019DB1DE;

        ULARGE_INTEGER __ts;
        __ts.LowPart  = __file_time_low;
        __ts.HighPart = __file_time_high;
        __ts.QuadPart -= __epoch.QuadPart;

        return timestamp(time_val(__ts.QuadPart/10));
    }

    void timestamp::to_file_time_np(uint32_t& __file_time_low, uint32_t& __file_time_high) const
    {
        ULARGE_INTEGER __epoch; // UNIX __epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
        __epoch.LowPart  = 0xD53E8000;
        __epoch.HighPart = 0x019DB1DE;

        ULARGE_INTEGER __ts;
        __ts.QuadPart  = _tv*10;
        __ts.QuadPart += __epoch.QuadPart;
        __file_time_low  = __ts.LowPart;
        __file_time_high = __ts.HighPart;
    }

#endif

    bool timestamp::operator == (const timestamp& __ts) const
    {
        return _tv == __ts._tv;
    }

    bool timestamp::operator != (const timestamp& __ts) const
    {
        return _tv != __ts._tv;
    }

    bool timestamp::operator >  (const timestamp& __ts) const
    {
        return _tv > __ts._tv;
    }

    bool timestamp::operator >= (const timestamp& __ts) const
    {
        return _tv >= __ts._tv;
    }

    bool timestamp::operator <  (const timestamp& __ts) const
    {
        return _tv < __ts._tv;
    }

    bool timestamp::operator <= (const timestamp& __ts) const
    {
        return _tv <= __ts._tv;
    }

    timestamp timestamp::operator + (timestamp::time_diff __diff) const
    {
        return timestamp(_tv + __diff);
    }

    timestamp timestamp::operator - (timestamp::time_diff __diff) const
    {
        return timestamp(_tv - __diff);
    }

    timestamp::time_diff timestamp::operator - (const timestamp& __ts) const
    {
        return _tv - __ts._tv;
    }

    timestamp& timestamp::operator += (timestamp::time_diff __diff)
    {
        _tv += __diff;
        return *this;
    }

    timestamp& timestamp::operator -= (timestamp::time_diff __diff)
    {
        _tv -= __diff;
        return *this;
    }

    std::time_t timestamp::epoch_time() const
    {
        return std::time_t(_tv/resolution);
    }

    timestamp::time_val timestamp::epoch_microseconds() const
    {
        return _tv;
    }

    timestamp::time_diff timestamp::elapsed() const
    {
        return timestamp().update() - *this;
    }

    bool timestamp::is_elapsed(timestamp::time_diff __interval) const
    {
        timestamp::time_diff __diff = timestamp().update() - *this;
        return __diff >= __interval;
    }

}//namespace ufc