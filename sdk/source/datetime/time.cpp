/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : datetime/time.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/datetime/time.hpp"
#include "ufc/datetime/time_zone.hpp"
#include "ufc/datetime/timespan.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/string/string_util.hpp"
#include "datetime/date_time_util.hpp"
#include <algorithm>
#include <cmath>

namespace ufc {

    time::time()
        : _time_val(0)
        , _hour(0)
        , _minute(0)
        , _second(0)
        , _millisecond(0)
        , _microsecond(0)
        , _tzd(0)
    {
    }

    time::time(const time& __other)
        : _time_val(__other._time_val)
        , _hour(__other._hour)
        , _minute(__other._minute)
        , _second(__other._second)
        , _millisecond(__other._millisecond)
        , _microsecond(__other._microsecond)
        , _tzd(__other._tzd)
    {
    }

    time::time(const timestamp& __ts)
        : _time_val(0)
        , _hour(0)
        , _minute(0)
        , _second(0)
        , _millisecond(0)
        , _microsecond(0)
        , _tzd(0)
    {
        assign(__ts);
    }

    time::time(int32_t __tzd, int32_t __hour, int32_t __minute, int32_t __second, int32_t __millisecond, int32_t __microsecond)
        : _time_val(0)
        , _hour(0)
        , _minute(0)
        , _second(0)
        , _millisecond(0)
        , _microsecond(0)
        , _tzd(0)
    {
        assign(__tzd, __hour, __minute, __second, __millisecond, __microsecond);
    }

    time::time(int32_t __hour, int32_t __minute, int32_t __second, int32_t __millisecond, int32_t __microsecond)
        : _time_val(0)
        , _hour(0)
        , _minute(0)
        , _second(0)
        , _millisecond(0)
        , _microsecond(0)
        , _tzd(0)
    {
        assign(time_zone::tzd(), __hour, __minute, __second, __millisecond, __microsecond);
    }

    time::~time()
    {
    }

    time& time::operator = (const time& __other)
    {
        if (__other._time_val != _time_val)
        {
            _time_val       = __other._time_val;
            _hour           = __other._hour;
            _minute         = __other._minute;
            _second         = __other._second;
            _millisecond    = __other._millisecond;
            _microsecond    = __other._microsecond;
            _tzd            = __other._tzd;
        }
        return *this;
    }

    time& time::operator = (const timestamp& __ts)
    {
        return assign(__ts);
    }

    time& time::assign(int32_t __tzd, int32_t __hour, int32_t __minute, int32_t __second, int32_t __millisecond, int32_t __microsecond)
    {
        ufc_assert (__hour >= 0 && __hour <= 23);
        ufc_assert (__minute >= 0 && __minute <= 59);
        ufc_assert (__second >= 0 && __second <= 59);
        ufc_assert (__millisecond >= 0 && __millisecond <= 999);
        ufc_assert (__microsecond >= 0 && __microsecond <= 999);

        _time_val    = (__hour * 3600 + __minute * 60 + __second) * timestamp::resolution + __millisecond * 1000 + __microsecond;
        _hour        = __hour;
        _minute      = __minute;
        _second      = __second;
        _millisecond = __millisecond;
        _microsecond = __microsecond;
        _tzd         = __tzd;
        return *this;
    }

    time& time::assign(int32_t __hour, int32_t __minute, int32_t __second, int32_t __millisecond, int32_t __microsecond)
    {
        return assign(time_zone::tzd(), __hour, __minute, __second, __millisecond, __microsecond);
    }

    time& time::assign(const timestamp& __ts)
    {
        /* 基于1970-01-01 00:00:00.000000为了0x3118A41200 */
        _tzd      = time_zone::tzd();
        _time_val = (__ts.epoch_microseconds() + (timestamp::time_val(_tzd) + timestamp::utc_time) * timestamp::resolution) % timespan::days;
        normalize();
        return *this;
    }

    bool time::operator == (const time& __time) const
    {
        return _time_val == __time._time_val;
    }

    bool time::operator != (const time& __time) const
    {
        return _time_val != __time._time_val;
    }

    bool time::operator <  (const time& __time) const
    {
        return _time_val < __time._time_val;
    }

    bool time::operator <= (const time& __time) const
    {
        return _time_val <= __time._time_val;
    }

    bool time::operator >  (const time& __time) const
    {
        return _time_val > __time._time_val;
    }

    bool time::operator >= (const time& __time) const
    {
        return _time_val >= __time._time_val;
    }

    time& time::make_local()
    {
        return adjust_for_tzd(time_zone::tzd());
    }

    time& time::make_utc()
    {
        return adjust_for_tzd(0);
    }

    time& time::adjust_for_tzd(int32_t tzd)
    {
        if (tzd != _tzd)
        {
            _time_val += timestamp::time_val(tzd - _tzd) * timestamp::resolution;
            _tzd      = tzd;

            _time_val += timespan::days;
            _time_val %= timespan::days;

            normalize();
        }
        return *this;
    }

    inline void time::normalize()
    {
        _hour        = (_time_val / timespan::hours);
        _minute      = (_time_val % timespan::hours  ) / timespan::minutes;
        _second      = (_time_val % timespan::minutes) / timespan::seconds;
        _millisecond = (_time_val % timespan::seconds) / timespan::milliseconds;
        _microsecond = (_time_val % timespan::milliseconds);
    }

    int32_t time::hour() const
    {
        return _hour;
    }

    int32_t time::minute() const
    {
        return _minute;
    }

    int32_t time::second() const
    {
        return _second;
    }

    int32_t time::millisecond() const
    {
        return _millisecond;
    }

    int32_t time::microsecond() const
    {
        return _microsecond;
    }

    int32_t time::tzd() const
    {
        return _tzd;
    }

    int32_t time::hour_ampm() const
    {
        return _hour % 12;
    }

    bool time::is_am() const
    {
        return _hour < 12;
    }

    bool time::is_pm() const
    {
        return !is_am();
    }

    string time::format(const string& __fmt) const
    {
        string __result;
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
                    case 'H': __result += string_util::format0(_hour, 2); break;
                    case 'h': __result += string_util::format0(hour_ampm(), 2); break;
                    case 'a': __result += (is_am() ? "am" : "pm"); break;
                    case 'A': __result += (is_am() ? "AM" : "PM"); break;
                    case 'M': __result += string_util::format0(_minute, 2); break;
                    case 'S': __result += string_util::format0(_second, 2); break;
                    case 's': __result += string_util::format0(_second, 2); 
                        __result += '.'; 
                        __result += string_util::format0(_millisecond * 1000 + _microsecond, 6); 
                        break;
                    case 'i': __result += string_util::format0(_millisecond, 3); break;
                    case 'c': __result += string_util::format(_millisecond / 100); break;
                    case 'F': __result += string_util::format0(_millisecond * 1000 + _microsecond, 6); break;
                    case 'z': date_time_util::tzd_iso(_tzd, __result); break;
                    case 'Z': date_time_util::tzd_rfc(_tzd, __result); break;
                    default:  __result += *__it;
                    }
                    ++__it;
                }
            }
            else
            {         
                __result += *__it++;
            }
        }
        return __result;
    }

    time time::now()
    {
        return time(timestamp().update());
    }

    bool time::is_valid(int32_t __hour, int32_t __minute, int32_t __second, int32_t __millisecond, int32_t __microsecond)
    {
        return
            (__hour >= 0 && __hour <= 23) &&
            (__minute >= 0 && __minute <= 59) &&
            (__second >= 0 && __second <= 59) &&
            (__millisecond >= 0 && __millisecond <= 999) &&
            (__microsecond >= 0 && __microsecond <= 999);
    }

    time time::parse(const string& __str, const string& __fmt)
    {
    	int32_t __hour   = 0;
    	int32_t __minute = 0;
    	int32_t __second = 0;
    	int32_t __millis = 0;
    	int32_t __micros = 0;
    	int32_t __tzd    = 0;

    	string::const_iterator __it   = __str.begin();
    	string::const_iterator __end  = __str.end();
    	string::const_iterator __itf  = __fmt.begin();
    	string::const_iterator __endf = __fmt.end();
    	while (__itf != __endf && __it != __end)
    	{
    		if (*__itf == '%')
    		{
    			if (++__itf != __endf)
    			{
    				switch (*__itf)
    				{
    				case 'H':
    				case 'h':
    					date_time_util::skip_junk(__it, __end);
    					date_time_util::parse_number_n(__it, __end, __hour, 2);
    					break;
    				case 'a':
    				case 'A':
    					__hour = date_time_util::parse_ampm(__it, __end, __hour);
    					break;
    				case 'M':
    					date_time_util::skip_junk(__it, __end);
    					date_time_util::parse_number_n(__it, __end, __minute, 2);
    					break;
    				case 'S':
    					date_time_util::skip_junk(__it, __end);
    					date_time_util::parse_number_n(__it, __end, __second, 2);
    					break;
    				case 's':
    					date_time_util::skip_junk(__it, __end);
    					date_time_util::parse_number_n(__it, __end, __second, 2);
    					if (__it != __end && *__it == '.')
    					{
    						++__it;
    						date_time_util::parse_fractional_n(__it, __end, __millis, 3);
    						date_time_util::parse_fractional_n(__it, __end, __micros, 3);
    					}
    					break;
    				case 'i':
    					date_time_util::skip_junk(__it, __end);
    					date_time_util::parse_number_n(__it, __end, __millis, 3);
    					break;
    				case 'c':
    					date_time_util::skip_junk(__it, __end);
    					date_time_util::parse_number_n(__it, __end, __millis, 1);
    					__millis *= 100;
    					break;
    				case 'F':
    					date_time_util::skip_junk(__it, __end);
    					date_time_util::parse_fractional_n(__it, __end, __millis, 3);
    					date_time_util::parse_fractional_n(__it, __end, __micros, 3);
    					break;
    				case 'z':
    				case 'Z':
    					__tzd = date_time_util::parse_tzd(__it, __end);
    					break;
    				}
    				++__itf;
    			}
    		}
    		else ++__itf;
    	}
    	if (time::is_valid(__hour, __minute, __second, __millis, __micros))
    		return time(__tzd, __hour, __minute, __second, __millis, __micros);
    	else 
    		throw syntax_error("date/time component out of range");
    }

    bool time::try_parse(time& __result_time, const string& __str, const string& __fmt)
    {
        try
        {
            __result_time = parse(__str, __fmt);
            return true;
        }
        catch (...)
        {
        }
        return false;
    }

}//namespace ufc

