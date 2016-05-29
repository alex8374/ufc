/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : datetime/date_time.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/datetime/date_time.hpp"
#include "ufc/datetime/time_zone.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/string/string_util.hpp"
#include "datetime/date_time_util.hpp"
#include <algorithm>
#include <cctype>

namespace ufc {

    date_time::date_time()
        : _datetime_val(0)
        , _year(0)
        , _month(0)
        , _day(0)
        , _hour(0)
        , _minute(0)
        , _second(0)
        , _millisecond(0)
        , _microsecond(0)
        , _tzd(0)
    {
    }

    date_time::date_time(const date_time& __other)
        : _datetime_val(__other._datetime_val)
        , _year(__other._year)
        , _month(__other._month)
        , _day(__other._day)
        , _hour(__other._hour)
        , _minute(__other._minute)
        , _second(__other._second)
        , _millisecond(__other._millisecond)
        , _microsecond(__other._microsecond)
        , _tzd(__other._tzd)
    {
    }

    date_time::date_time(const date& __date)
        : _datetime_val(0)
        , _year(0)
        , _month(0)
        , _day(0)
        , _hour(0)
        , _minute(0)
        , _second(0)
        , _millisecond(0)
        , _microsecond(0)
        , _tzd(0)
    {
        assign(time_zone::tzd(), 
               __date.year(),
               __date.month(),
               __date.day(),
               0,
               0,
               0,
               0,
               0);
    }

    date_time::date_time(const date& __date, const time& __time)
        : _datetime_val(0)
        , _year(0)
        , _month(0)
        , _day(0)
        , _hour(0)
        , _minute(0)
        , _second(0)
        , _millisecond(0)
        , _microsecond(0)
        , _tzd(0)
    {
        assign(__time.tzd(), 
               __date.year(), 
               __date.month(), 
               __date.day(), 
               __time.hour(), 
               __time.minute(), 
               __time.second(), 
               __time.millisecond(), 
               __time.microsecond());
    }      

    date_time::date_time(const timestamp& __ts)
        : _datetime_val(0)
        , _year(0)
        , _month(0)
        , _day(0)
        , _hour(0)
        , _minute(0)
        , _second(0)
        , _millisecond(0)
        , _microsecond(0)
        , _tzd(0)
    {
        assign(__ts);
    }

    date_time::date_time(int32_t year, 
                       int32_t month,
                       int32_t day,
                       int32_t hour,
                       int32_t minute,
                       int32_t second,
                       int32_t millisecond,
                       int32_t microsecond)
        : _datetime_val(0)
        , _year(0)
        , _month(0)
        , _day(0)
        , _hour(0)
        , _minute(0)
        , _second(0)
        , _millisecond(0)
        , _microsecond(0)
        , _tzd(0)
    {
        assign(time_zone::tzd(), 
               year, 
               month, 
               day,
               hour,
               minute,
               second,
               millisecond,
               microsecond);
    }

    date_time::date_time(int32_t tzd,
                       int32_t year,
                       int32_t month,
                       int32_t day,
                       int32_t hour,
                       int32_t minute,
                       int32_t second,
                       int32_t millisecond,
                       int32_t microsecond)
    {
        assign(tzd, year, month, day, hour, minute, second, millisecond, microsecond);
    }

    date_time::~date_time()
    {
    }

    date_time& date_time::operator = (const date_time& __other)
    {
        if (__other._datetime_val != _datetime_val)
        {
            _datetime_val = __other._datetime_val;
            _year        = __other._year;
            _month       = __other._month;
            _day         = __other._day;
            _hour        = __other._hour;
            _minute      = __other._minute;
            _second      = __other._second;
            _millisecond = __other._millisecond;
            _microsecond = __other._microsecond;
            _tzd         = __other._tzd;
        }
        return *this;
    }

    date_time& date_time::operator = (const date& __date)
    {
        return assign(time_zone::tzd(), 
                      __date.year(),
                      __date.month(),
                      __date.day(),
                      0,
                      0,
                      0,
                      0,
                      0);
    }

    date_time& date_time::operator = (const timestamp& __ts)
    {
        return assign(__ts);
    }

    date_time& date_time::assign(int32_t __tzd,
                                 int32_t __year,
                                 int32_t __month,
                                 int32_t __day,
                                 int32_t __hour,
                                 int32_t __minute,
                                 int32_t __second,
                                 int32_t __millisecond,
                                 int32_t __microsecond)
    {
        ufc_assert (__year >= 0 && __year <= 9999);
        ufc_assert (__month >= 1 && __month <= 12);
        ufc_assert (__day >= 1 && __day <= date::days_of_month(__year, __month));
        ufc_assert (__hour >= 0 && __hour <= 23);
        ufc_assert (__minute >= 0 && __minute <= 59);
        ufc_assert (__second >= 0 && __second <= 59);
        ufc_assert (__millisecond >= 0 && __millisecond <= 999);
        ufc_assert (__microsecond >= 0 && __microsecond <= 999);

        uint16_t __a = static_cast<uint16_t>((14 - __month)/12);
        uint16_t __y = static_cast<uint16_t>(__year + 4800 - __a);
        uint16_t __m = static_cast<uint16_t>(__month + 12 * __a - 3);
        _datetime_val  = timestamp::time_val((__day + ((153 * __m + 2) / 5) + 365 * __y + (__y / 4) - (__y / 100) + (__y / 400) - 32045)) * timespan::days;
        _datetime_val += (__hour * 3600 + __minute * 60 + __second) * timestamp::resolution + __millisecond * 1000 + __microsecond;
        _year         = __year;
        _month        = __month;
        _day          = __day;
        _hour         = __hour;
        _minute       = __minute;
        _second       = __second;
        _millisecond  = __millisecond;
        _microsecond  = __microsecond;
        _tzd          = __tzd;
        return *this;
    }

    date_time& date_time::assign(int32_t __year,
                                 int32_t __month,
                                 int32_t __day,
                                 int32_t __hour,
                                 int32_t __minute,
                                 int32_t __second,
                                 int32_t __millisecond,
                                 int32_t __microsecond)
    {
        return assign(time_zone::tzd(), 
                      __year, 
                      __month, 
                      __day, 
                      __hour, 
                      __minute, 
                      __second, 
                      __millisecond, 
                      __microsecond);
    }

    date_time& date_time::assign(const date& __date)
    {
        return assign(time_zone::tzd(), 
                      __date.year(),
                      __date.month(),
                      __date.day(),
                      0,
                      0,
                      0,
                      0,
                      0);
    }

    date_time& date_time::assign(const date& __date, const time& __time)
    {
        return assign(__time.tzd(), 
                      __date.year(), 
                      __date.month(), 
                      __date.day(), 
                      __time.hour(), 
                      __time.minute(), 
                      __time.second(), 
                      __time.millisecond(), 
                      __time.microsecond());
    }

    date_time& date_time::assign(const timestamp& __ts)
    {
        _tzd          = time_zone::tzd();
        _datetime_val = __ts.epoch_microseconds() + (timestamp::time_val(_tzd) + (timestamp::time_val(0x3118) << 24) + 0xA41200) * timestamp::resolution;
        normalize();
        return *this;
    }

    bool date_time::operator == (const date_time& __other) const
    {
        return (_datetime_val == __other._datetime_val);
    }

    bool date_time::operator != (const date_time& __other) const
    {
        return (_datetime_val != __other._datetime_val);
    }

    bool date_time::operator <  (const date_time& __other) const
    {
        return (_datetime_val < __other._datetime_val);
    }

    bool date_time::operator <= (const date_time& __other) const
    {
        return (_datetime_val <= __other._datetime_val);
    }

    bool date_time::operator >  (const date_time& __other) const
    {
        return (_datetime_val > __other._datetime_val);
    }

    bool date_time::operator >= (const date_time& __other) const
    {
        return (_datetime_val >= __other._datetime_val);
    }

    date_time date_time::operator + (const timespan& __span) const
    {
        date_time __result(*this);
        __result += __span;
        return __result;
    }

    date_time date_time::operator - (const timespan& __span) const
    {
        date_time __result(*this);
        __result -= __span;
        return __result;
    }

    timespan date_time::operator - (const date_time& __other) const
    {
        return timespan(_datetime_val - __other._datetime_val);
    }

    date_time& date_time::operator += (const timespan& __span)
    {
        _datetime_val += __span.get_total_microseconds();
        normalize();
        return *this;
    }

    date_time& date_time::operator -= (const timespan& __span)
    {
        _datetime_val -= __span.get_total_microseconds();
        normalize();
        return *this;
    }

    date_time& date_time::make_local()
    {
        return adjust_for_tzd(time_zone::tzd());
    }

    date_time& date_time::make_utc()
    {
        return adjust_for_tzd(0);
    }

    date_time& date_time::adjust_for_tzd(int32_t __tzd)
    {
        if (__tzd != _tzd)
        {
            _datetime_val += timestamp::time_val(__tzd - _tzd) * timestamp::resolution;
            _tzd          = __tzd;
            normalize();
        }
        return *this;
    }/*

    date_time& date_time::adjust_for_tzd(const string& __tzd)
    {
        return adjust_for_tzd(time_zone::parse(__tzd));
    }*/

    void date_time::swap(date_time& __other)
    {
        std::swap(_datetime_val, __other._datetime_val);
        std::swap(_year, __other._year);
        std::swap(_month, __other._month);
        std::swap(_day, __other._day);
        std::swap(_hour, __other._hour);
        std::swap(_minute, __other._minute);
        std::swap(_second, __other._second);
        std::swap(_millisecond, __other._millisecond);
        std::swap(_microsecond, __other._microsecond);
        std::swap(_tzd, __other._tzd);
    }

    int32_t date_time::year() const
    {
        return _year;
    }

    int32_t date_time::month() const
    {
        return _month;
    }

    int32_t date_time::day() const
    {
        return _day;
    }

    int32_t date_time::hour() const
    {
        return _hour;
    }

    int32_t date_time::minute() const
    {
        return _minute;
    }

    int32_t date_time::second() const
    {
        return _second;
    }

    int32_t date_time::millisecond() const
    {
        return _millisecond;
    }

    int32_t date_time::microsecond() const
    {
        return _microsecond;
    }

    int32_t date_time::tzd() const
    {
        return _tzd;
    }

    int32_t date_time::hour_ampm() const
    {
        return _hour % 12;
    }

    bool date_time::is_am() const
    {
        return _hour < 12;
    }

    bool date_time::is_pm() const
    {
        return !is_am();
    }

    int32_t date_time::day_of_week() const
    {
        return date(_year, _month, _day).day_of_week();
    }

    int32_t date_time::day_of_year() const
    {
        return date(_year, _month, _day).day_of_year();
    }
    
    int32_t date_time::week(int32_t __first_dayOfWeek) const
    {
        ufc_assert (__first_dayOfWeek >= 0 && __first_dayOfWeek <= 6);

        return date(_year, _month, _day).week(__first_dayOfWeek);
    }

    timestamp date_time::get_timestamp() const
    {
        //return timestamp(_datetime_val - (timestamp::time_val(_tzd) + 0x3118A41200) * timestamp::resolution);
        return timestamp(_datetime_val - (timestamp::time_val(_tzd) + (timestamp::time_val(0x3118) << 24) + 0xA41200) * timestamp::resolution);
    }
    
    date date_time::get_date() const
    {
        return date(_year, _month, _day);
    }

    time date_time::get_time() const
    {
        return time(_tzd, _hour, _minute, _second, _millisecond, _microsecond);
    }

    date_time& date_time::add(int32_t __years, int32_t __months, int32_t __days)
    {
        date __date(_year, _month, _day);
        __date.add(__years, __months, __days);
        return assign(_tzd, __date.year(), __date.month(), __date.day(), _hour, _minute, _second, _millisecond, _microsecond);
    }

    date_time& date_time::add_year(int32_t __years)
    {
        return add(__years, 0, 0);
    }

    date_time& date_time::add_month(int32_t __months)
    {
        return add(0, __months, 0);
    }

    date_time& date_time::add_day(int32_t __days)
    {
        return add(0, 0, __days);
    }

    string date_time::format(const string& __fmt) const
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
                    case 'w': __result.append(date::weekday_names[day_of_week()], 0, 3); break;
                    case 'W': __result.append(date::weekday_names[day_of_week()]); break;
                    case 'b': __result.append(date::month_names[_month - 1], 0, 3); break;
                    case 'B': __result.append(date::month_names[_month - 1]); break;
                    case 'd': __result += string_util::format0(_day, 2); break;
                    case 'e': __result += string_util::format(_day); break;
                    case 'f': __result += string_util::format(_day, 2); break;
                    case 'm': __result += string_util::format0(_month, 2); break;
                    case 'n': __result += string_util::format(_month); break;
                    case 'o': __result += string_util::format(_month, 2); break;
                    case 'y': __result += string_util::format0(_year % 100, 2); break;
                    case 'Y': __result += string_util::format0(_year, 4); break;
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
                    //case 'z': __result += time_zone::formatForISO(_tzd); break;
                    //case 'Z': __result += time_zone::formatForRFC(_tzd); break;
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

    date_time date_time::now()
    {
        return date_time(timestamp().update());
    }

    bool date_time::is_valid(int32_t __year, 
                             int32_t __month,
                             int32_t __day,
                             int32_t __hour,
                             int32_t __minute,
                             int32_t __second,
                             int32_t __millisecond,
                             int32_t __microsecond)
    {
        return
            (__year >= 0 && __year <= 9999) &&
            (__month >= 1 && __month <= 12) &&
            (__day >= 1 && __day <= date::days_of_month(__year, __month)) &&
            (__hour >= 0 && __hour <= 23) &&
            (__minute >= 0 && __minute <= 59) &&
            (__second >= 0 && __second <= 59) &&
            (__millisecond >= 0 && __millisecond <= 999) &&
            (__microsecond >= 0 && __microsecond <= 999);
    }

    inline void date_time::normalize()
    {
        timestamp::time_val dateVal = _datetime_val / timespan::days;
        timestamp::time_val timeVal = _datetime_val % timespan::days;
        int32_t a = dateVal + 32044;
        int32_t b = (4 * a + 3) / 146097;
        int32_t c = a - ((146097 * b) / 4);
        int32_t d = (4 * c + 3) / 1461;
        int32_t e = c - (1461 * d) / 4;
        int32_t m = (5 * e + 2) / 153;

        _year        = static_cast<unsigned short>(100*b + d - 4800 + (m/10));
        _month       = static_cast<unsigned short>(m + 3 - 12 * (m/10));
        _day         = static_cast<unsigned short>(e - ((153*m + 2)/5) + 1);
        _hour        = (timeVal / timespan::hours);
        _minute      = (timeVal % timespan::hours  ) / timespan::hours;
        _second      = (timeVal % timespan::minutes) / timespan::seconds;
        _millisecond = (timeVal % timespan::seconds) / timespan::milliseconds;
        _microsecond = (timeVal % timespan::milliseconds);
    }
    
    date_time date_time::parse(const string& __str, const string& __fmt)
    {
    	int32_t __year   = 0;
    	int32_t __month  = 0;
    	int32_t __day    = 0;
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
    				case 'w':
    				case 'W':
    					while (__it != __end && string::traits_type::is_space(*__it)) ++__it;
    					while (__it != __end && string::traits_type::is_alpha(*__it)) ++__it;
    					break;
    				case 'b':
    				case 'B':
    					__month = date_time_util::parse_month(__it, __end);
    					break;
    				case 'd':
    				case 'e':
    				case 'f':
    					date_time_util::skip_junk(__it, __end);
                        date_time_util::parse_number_n(__it, __end, __day, 2);
    					break;
    				case 'm':
    				case 'n':
    				case 'o':
    					date_time_util::skip_junk(__it, __end);
    					date_time_util::parse_number_n(__it, __end, __month, 2);
    					break;					 
    				case 'y':
    					date_time_util::skip_junk(__it, __end);
    					date_time_util::parse_number_n(__it, __end, __year, 2);
    					if (__year >= 69) 
    						__year += 1900;
    					else
    						__year += 2000;
    					break;
    				case 'Y':
    					date_time_util::skip_junk(__it, __end);
    					date_time_util::parse_number_n(__it, __end, __year, 4);
    					break;
    				case 'r':
    					date_time_util::skip_junk(__it, __end);
    					date_time_util::parse_number(__it, __end, __year);
    					if (__year < 1000)
    					{
    						if (__year >= 69) 
    							__year += 1900;
    						else
    							__year += 2000;
    					}
    					break;
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
    	if (__month == 0) __month = 1;
    	if (__day == 0) __day = 1;
    	if (date_time::is_valid(__year, __month, __day, __hour, __minute, __second, __millis, __micros))
    		return date_time(__tzd, __year, __month, __day, __hour, __minute, __second, __millis, __micros);
    	else 
    		throw syntax_error("date/time component out of range");
    }

    bool date_time::try_parse(date_time& __result_date_time, const string& __str, const string& __fmt)
    {
        try
        {
            __result_date_time = parse(__str, __fmt);
            return true;
        }
        catch (...)
        {
        }
        return false;
    }

}//namespace ufc
