/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : datetime/date.cpp
  Author     : cqli[lichangqing1983@sina.com]
  date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/datetime/date.hpp"
#include "ufc/datetime/time_zone.hpp"
#include "ufc/exception/assert.hpp"
#include "ufc/exception/exception.hpp"
#include "ufc/string/string_util.hpp"
#include "datetime/date_time_util.hpp"
#include <algorithm>
#include <cmath>

namespace ufc {

    const string date::weekday_names[7] =
    {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    const string date::month_names[12] =
    {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    date::date()
        : _date_val(0)
    {
        assign(1900, 1, 1);
    }

    date::date(const date& __other)
        : _date_val(__other._date_val)
        , _year(__other._year)
        , _month(__other._month)
        , _day(__other._day)
    {
    }

    date::date(const timestamp& __ts)
        : _date_val(0)
        , _year(0)
        , _month(0)
        , _day(0)
    {
        assign(__ts);
    }

    date::date(int32_t __year, int32_t __month, int32_t __day)
        : _date_val(0)
        , _year(0)
        , _month(0)
        , _day(0)
    {
        assign(__year, __month, __day);
    }

    date::~date()
    {
    }

    date& date::operator = (const date& __other)
    {
        if (_date_val != __other._date_val)
        {
            _date_val = __other._date_val;
            _year     = __other._year;
            _month    = __other._month;
            _day      = __other._day;
        }
        return *this;
    }

    date& date::operator = (const timestamp& __ts)
    {
        return assign(__ts);
    }

    date& date::assign(int32_t __year, int32_t __month, int32_t __day)
    {
        ufc_assert (__year >= 0 && __year <= 9999);
        ufc_assert (__month >= 1 && __month <= 12);
        ufc_assert (__day >= 1 && __day <= days_of_month(__year, __month));

        unsigned short __a = static_cast<unsigned short>((14-__month)/12);
        unsigned short __y = static_cast<unsigned short>(__year + 4800 - __a);
        unsigned short __m = static_cast<unsigned short>(__month + 12*__a - 3);
        _date_val = __day + ((153*__m + 2)/5) + 365*__y + (__y/4) - (__y/100) + (__y/400) - 32045;
        _year     = __year;
        _month    = __month;
        _day      = __day;
        return *this;
    }

    date& date::assign(const timestamp& __ts)
    {
        _date_val = (timestamp::time_val(__ts.epoch_time()) + timestamp::utc_time+ time_zone::tzd()) / 86400;
        return normalize();
    }

    date& date::add(int32_t __years, int32_t __months, int32_t __days)
    {
        __years  += _year;
        __months += _month;
        __days   += _day;
        if (__months != 0)
        {
            __years += __months / 12;
            __months = __months % 12;
        }        
        if (__months == 0)
        {
            __years--; __months = 12;
        }
        return assign(__years, __months, __days);
    }

    date& date::add_year(int32_t __years)
    {
        return add(__years, 0, 0);
    }

    date& date::add_month(int32_t __months)
    {
        return add(0, __months, 0);
    }

    date& date::add_day(int32_t __days)
    {
        return add(0, 0, __days);
    }

    void date::swap(date& __date)
    {
        std::swap(__date._date_val, _date_val);
        std::swap(__date._year, _year);
        std::swap(__date._month, _month);
        std::swap(__date._day, _day);
    }

    int32_t date::year() const
    {
        return _year;
    }

    int32_t date::month() const
    {
        return _month;
    }

    int32_t date::day() const
    {
        return _day;
    }

    int32_t date::day_of_week() const
    {
        uint16_t __a = static_cast<unsigned short>((14-_month)/12);
        uint16_t __y = static_cast<unsigned short>(_year - __a);
        uint16_t __m = static_cast<unsigned short>(_month + 12*__a - 2);
        return static_cast<unsigned short>((_day + __y + (__y/4) - (__y/100) + (__y/400) + (31*__m)/12) % 7);
    }
    
    int32_t date::day_of_year() const
    {
        int32_t __doy = 0;
        for (int32_t __month = 1; __month < _month; ++__month)
        {
            __doy += days_of_month(_year, __month);
        }
        __doy += _day;
        return __doy;
    }
    
    int32_t date::week(int32_t __first_day_of_week) const
    {
        ufc_assert (__first_day_of_week >= 0 && __first_day_of_week <= 6);

        int32_t __base_day = 1;
        while (date(_year, 1, __base_day).day_of_week() != __first_day_of_week) ++__base_day;

        int32_t __doy  = day_of_year();
        int32_t __offs = __base_day <= 4 ? 0 : 1; 
        if (__doy < __base_day)
            return __offs;
        else
            return (__doy - __base_day)/7 + 1 + __offs;
    }

    string date::format(const string& __fmt) const
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
                    case 'w': __result.append(weekday_names[day_of_week()], 0, 3); break;
                    case 'W': __result.append(weekday_names[day_of_week()]); break;
                    case 'b': __result.append(month_names[month() - 1], 0, 3); break;
                    case 'B': __result.append(month_names[month() - 1]); break;
                    case 'd': __result += string_util::format0(day(), 2); break;
                    case 'e': __result += string_util::format(day()); break;
                    case 'f': __result += string_util::format(day(), 2); break;
                    case 'm': __result += string_util::format0(month(), 2); break;
                    case 'n': __result += string_util::format(month()); break;
                    case 'o': __result += string_util::format(month(), 2); break;
                    case 'y': __result += string_util::format0(year() % 100, 2); break;
                    case 'Y': __result += string_util::format0(year(), 4); break;
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

    date& date::operator ++ ()
    {
        _date_val++;
        return normalize();
    }

    date  date::operator ++ (int32_t)
    {
        date result(*this);
        result._date_val++;
        return result.normalize();
    }

    date& date::operator -- ()
    {
        _date_val--;
        return normalize();
    }

    date date::operator-- (int32_t)
    {
        date result(*this);
        result._date_val--;
        return result.normalize();
    }

    date& date::operator += (int32_t __days)
    {
        _date_val += __days;
        return normalize();
    }

    date& date::operator -= (int32_t __days)
    {
        _date_val -= __days;
        return normalize();
    }

    bool date::operator == (const date& __date) const
    {
        return (_date_val == __date._date_val);
    }

    bool date::operator != (const date& __date) const
    {
        return (_date_val != __date._date_val);
    }

    bool date::operator <  (const date& __date) const
    {
        return (_date_val < __date._date_val);
    }

    bool date::operator <= (const date& __date) const
    {
        return (_date_val <= __date._date_val);
    }

    bool date::operator >  (const date& __date) const
    {
        return (_date_val > __date._date_val);
    }

    bool date::operator >= (const date& __date) const
    {
        return (_date_val >= __date._date_val);
    }

    inline date& date::normalize()
    {
        int32_t __a = _date_val + 32044;
        int32_t __b = (4*__a + 3)/146097;
        int32_t __c = __a-((146097*__b)/4);
        int32_t __d = (4*__c + 3)/1461;
        int32_t __e = __c - (1461*__d)/4;
        int32_t __m = (5*__e + 2)/153;
        _day   = static_cast<uint16_t>(__e - ((153*__m + 2)/5) + 1);
        _month = static_cast<uint16_t>(__m + 3 - 12 * (__m/10));
        _year  = static_cast<uint16_t>(100*__b + __d - 4800 + (__m/10));

        return *this;
    }

    date date::now()
    {
        return date(timestamp().update());
    }

    bool date::is_leap_year(int32_t __year)
    {
        return (__year % 4) == 0 && ((__year % 100) != 0 || (__year % 400) == 0);
    }

    int32_t date::days_of_month(int32_t __year, int32_t __month)
    {
        ufc_assert (__month >= 1 && __month <= 12);
        switch (__month)
        {
        case 2:
            return is_leap_year(__year)? 29: 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
        }
    }

    bool date::is_valid(int32_t __year, int32_t __month, int32_t __day)
    {
        return
            (__year >= 0 && __year <= 9999) &&
            (__month >= 1 && __month <= 12) &&
            (__day >= 1 && __day <= days_of_month(__year, __month));
    }

    date date::parse(const string& __str, const string& __fmt)
    {
    	int32_t __year   = 0;
    	int32_t __month  = 0;
    	int32_t __day    = 0;

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
    				}
    				++__itf;
    			}
    		}
    		else ++__itf;
    	}
    	if (__month == 0) __month = 1;
    	if (__day == 0) __day = 1;
    	if (date::is_valid(__year, __month, __day))
    		return date(__year, __month, __day);
    	else 
    		throw syntax_error("date component out of range");
    }

    bool date::try_parse(date& __result_date, const string& __str, const string& __fmt)
    {
        try
        {
            __result_date = parse(__str, __fmt);
            return true;
        }
        catch (...)
        {
        }
        return false;
    }

}//namespace ufc

