/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : datetime/timespan.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/datetime/timespan.hpp"
#include "ufc/string/string_util.hpp"

namespace ufc {

    const timespan::time_diff timespan::milliseconds = 1000;
    const timespan::time_diff timespan::seconds      = 1000 * timespan::milliseconds;
    const timespan::time_diff timespan::minutes      =   60 * timespan::seconds;
    const timespan::time_diff timespan::hours        =   60 * timespan::minutes;
    const timespan::time_diff timespan::days         =   24 * timespan::hours;

    timespan::timespan()
        : _span(0)
    {
    }

    timespan::timespan(const timespan& __other)
        : _span(__other._span)
    {
    }

    timespan::timespan(time_diff __microseconds)
        : _span(__microseconds)
    {
    }

    timespan::timespan(long_t __seconds, long_t __microseconds)
        : _span(time_diff(__seconds) * seconds + __microseconds)
    {
    }

    timespan::timespan(int32_t __days, 
             int32_t __hours,
             int32_t __minutes,
             int32_t __seconds,
             int32_t __microseconds)        
        : _span(time_diff(__microseconds) + time_diff(__seconds)*seconds + time_diff(__minutes)*minutes + time_diff(__hours)*hours + time_diff(__days)*days)
    {
    }

    timespan::~timespan()
    {
    }

    timespan& timespan::operator = (const timespan& __other)
    {
        _span = __other._span;
        return *this;
    }
    
    timespan& timespan::operator = (time_diff __microseconds)
    {
        _span = __microseconds;
        return *this;
    }

    timespan& timespan::assign(int32_t __days, 
                               int32_t __hours,
                               int32_t __minutes,
                               int32_t __seconds,
                               int32_t __microseconds)
    {
        _span = time_diff(__microseconds) + time_diff(__seconds)*seconds + time_diff(__minutes)*minutes + time_diff(__hours)*hours + time_diff(__days)*days;
        return *this;
    }

    timespan& timespan::assign(long_t __seconds, long_t __microseconds)
    {
        _span = time_diff(__seconds) * seconds + __microseconds;
        return *this;
    }

    void timespan::swap(timespan& __other)
    {
        std::swap(_span, __other._span);
    }

    bool timespan::operator == (const timespan& __other) const
    {
        return (_span == __other._span);
    }

    bool timespan::operator != (const timespan& __other) const
    {
        return (_span != __other._span);
    }

    bool timespan::operator >  (const timespan& __other) const
    {
        return (_span > __other._span);
    }

    bool timespan::operator >= (const timespan& __other) const
    {
        return (_span >= __other._span);
    }

    bool timespan::operator <  (const timespan& __other) const
    {
        return (_span < __other._span);
    }

    bool timespan::operator <= (const timespan& __other) const
    {
        return (_span <= __other._span);
    }

    bool timespan::operator == (time_diff __microseconds) const
    {
        return (_span == __microseconds);
    }

    bool timespan::operator != (time_diff __microseconds) const
    {
        return (_span != __microseconds);
    }

    bool timespan::operator >  (time_diff __microseconds) const
    {
        return (_span > __microseconds);
    }

    bool timespan::operator >= (time_diff __microseconds) const
    {
        return (_span >= __microseconds);
    }

    bool timespan::operator <  (time_diff __microseconds) const
    {
        return (_span < __microseconds);
    }

    bool timespan::operator <= (time_diff __microseconds) const
    {
        return (_span <= __microseconds);
    }
    
    timespan timespan::operator + (const timespan& __diff) const
    {
        return timespan(_span + __diff._span);
    }

    timespan timespan::operator - (const timespan& __diff) const
    {
        return timespan(_span - __diff._span);
    }

    timespan& timespan::operator += (const timespan& __diff)
    {
        _span += __diff._span;
        return *this;
    }

    timespan& timespan::operator -= (const timespan& __diff)
    {
        _span -= __diff._span;
        return *this;
    }

    timespan timespan::operator + (time_diff __microseconds) const
    {
        return timespan(_span + __microseconds);
    }

    timespan timespan::operator - (time_diff __microseconds) const
    {
        return timespan(_span - __microseconds);
    }

    timespan& timespan::operator += (time_diff __microseconds)
    {
        _span += __microseconds;
        return *this;
    }

    timespan& timespan::operator -= (time_diff __microseconds)
    {
        _span -= __microseconds;
        return *this;
    }
    
    int32_t timespan::get_days() const
    {
        return int(_span/days);
    }
 
    int32_t timespan::get_hours() const
    {
        return int32_t((_span/hours) % 24);
    }

    int32_t timespan::get_total_hours() const
    {
        return int32_t(_span/hours);
    }

    int32_t timespan::get_minutes() const
    {
        return int32_t((_span/minutes) % 60);
    }

    int32_t timespan::get_total_minutes() const
    {
        return int32_t(_span/minutes);
    }

    int32_t timespan::get_seconds() const
    {
        return int32_t((_span/seconds) / 60);
    }

    int32_t timespan::get_total_seconds() const
    {
        return int32_t(_span/seconds);
    }

    int32_t timespan::get_milliseconds() const
    {
        return int32_t((_span/milliseconds) % 1000);
    }

    timespan::time_diff timespan::get_total_milliseconds() const
    {
        return _span/milliseconds;
    }

    int32_t timespan::get_microseconds() const
    {
        return int32_t(_span % milliseconds);
    }

    int32_t timespan::get_useconds() const
    { 
        return int32_t(_span % seconds);
    }

    timespan::time_diff timespan::get_total_microseconds() const
    {
        return _span;
    }

    string timespan::format(const string& __fmt) const
    {
        string __res;
        string::const_iterator __it  = __fmt.begin();
        string::const_iterator __end = __fmt.end();
        while (__it != __end)
        {
            if (*__it == '%')
            {
                if (++__it != __end)
                {
                    switch (*__it)
                    {
                    case 'd': __res += string_util::format(get_days()); break;
                    case 'H': __res += string_util::format0(get_hours(), 2); break;
                    case 'h': __res += string_util::format(get_total_hours()); break;
                    case 'M': __res += string_util::format0(get_minutes(), 2); break;
                    case 'm': __res += string_util::format(get_total_minutes()); break;
                    case 'S': __res += string_util::format0(get_seconds(), 2); break;
                    case 's': __res += string_util::format(get_total_seconds()); break;
                    case 'i': __res += string_util::format0(get_milliseconds(), 3); break;
                    case 'c': __res += string_util::format(get_milliseconds()/100); break;
                    case 'F': __res += string_util::format0(get_useconds(), 6); break;
                    default:  __res += *__it; break;
                    }
                    ++__it;
                }
            }
            else 
            {
                __res = *__it;
                __it++;
            }
        }
        return __res;
    }

}//namespace ufc
