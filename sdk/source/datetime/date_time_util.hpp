/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : datetime/date_time_util.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-20
  Description: 
  History    : 
*******************************************************************************/
#ifndef DATETIME_DATE_TIME_UTIL_HPP
#define DATETIME_DATE_TIME_UTIL_HPP

#include "ufc/datetime/date.hpp"
#include "ufc/string/string.hpp"
#include "ufc/exception/exception.hpp"

namespace ufc {

    class date_time_util
    {
    public:
        static void skip_junk(string::const_iterator& __it, const string::const_iterator& __end)
        {
            while (__it != __end && !string::traits_type::is_digit(*__it))
            {
                 ++__it;
            }
        }

        static void parse_number(string::const_iterator& __it, const string::const_iterator& __end, int32_t& __var)
        {
            while (__it != __end && string::traits_type::is_digit(*__it)) 
            {
                __var = __var*10 + ((*__it++) - '0');
            }
        }

        static void parse_number_n(string::const_iterator& __it, const string::const_iterator& __end, int32_t& __var, int32_t __n)
        {
            int32_t __i = 0; 
            while (__i++ < __n && __it != __end && string::traits_type::is_digit(*__it))
            {
                __var = __var*10 + ((*__it++) - '0'); 
            }
        }

        static void parse_fractional_n(string::const_iterator& __it, const string::const_iterator& __end, int32_t& __var, int32_t __n)
        {
            int32_t __i = 0; 
            while (__i < __n && __it != __end && string::traits_type::is_digit(*__it)) 
            { 
                __var = __var*10 + ((*__it++) - '0'); 
                __i++; 
            } 
            while (__i++ < __n) 
            {
                __var *= 10; 
            }
        }
        
        static int32_t parse_month(string::const_iterator& __it, const string::const_iterator& __end)
        {
            string __month;
            while (__it != __end && (string::traits_type::is_space(*__it) || string::traits_type::is_punct(*__it))) ++__it;
            bool __isFirst = true;
            while (__it != __end && string::traits_type::is_alpha(*__it)) 
            {
                char __ch = (*__it++);
                if (__isFirst) 
                { 
                    __month += string::traits_type::to_upper(__ch); 
                    __isFirst = false; 
                }
                else 
                    __month += string::traits_type::to_lower(__ch);
            }
            if (__month.length() < 3) 
                throw syntax_error("Month name must be at least three characters long", __month);
            for (int i = 0; i < 12; ++i) 
            {
                if (date::month_names[i].find(__month) == 0)
                    return i + 1;
            }
            throw syntax_error("Not a valid month name", __month);
        }
        
        static int32_t parse_day_of_week(string::const_iterator& __it, const string::const_iterator& __end)
        {
        	string __dow;
        	while (__it != __end && (string::traits_type::is_space(*__it) || string::traits_type::is_punct(*__it))) ++__it;
        	bool __isFirst = true;
        	while (__it != __end && string::traits_type::is_alpha(*__it)) 
        	{
        		char __ch = (*__it++);
        		if (__isFirst) 
                {
                    __dow += string::traits_type::to_upper(__ch); 
                    __isFirst = false; 
                }
        		else 
                {
                    __dow += string::traits_type::to_lower(__ch);
                }      
        	}
        	if (__dow.length() < 3) 
            {
                throw syntax_error("Weekday name must be at least three characters long", __dow);
            }
        	for (int i = 0; i < 7; ++i) 
        	{
        		if (date::weekday_names[i].find(__dow) == 0)
        			return i;
        	}
        	throw syntax_error("Not a valid weekday name", __dow);
        }

        static int32_t parse_tzd(string::const_iterator& __it, const string::const_iterator& __end)
        {
        	struct zone
        	{
        		const char* designator;
        		int         timeZoneDifferential;
        	};

        	static zone zones[] =
        	{
        		{"Z",           0},
        		{"UT",          0},
        		{"GMT",         0},
        		{"BST",    1*3600},
        		{"IST",    1*3600},
        		{"WET",         0},
        		{"WEST",   1*3600},
        		{"CET",    1*3600},
        		{"CEST",   2*3600},
        		{"EET",    2*3600},
        		{"EEST",   3*3600},
        		{"MSK",    3*3600},
        		{"MSD",    4*3600},
        		{"NST",   -3*3600-1800},
        		{"NDT",   -2*3600-1800},
        		{"AST",   -4*3600},
        		{"ADT",   -3*3600},
        		{"EST",   -5*3600},
        		{"EDT",   -4*3600},
        		{"CST",   -6*3600},
        		{"CDT",   -5*3600},
        		{"MST",   -7*3600},
        		{"MDT",   -6*3600},
        		{"PST",   -8*3600},
        		{"PDT",   -7*3600},
        		{"AKST",  -9*3600},
        		{"AKDT",  -8*3600},
        		{"HST",  -10*3600},
        		{"AEST",  10*3600},
        		{"AEDT",  11*3600},
        		{"ACST",   9*3600+1800},
        		{"ACDT",  10*3600+1800},
        		{"AWST",   8*3600},
        		{"AWDT",   9*3600}
        	};

        	while (__it != __end && string::traits_type::is_space(*__it)) ++__it;
        	if (__it != __end)
        	{
        		if (string::traits_type::is_alpha(*__it))
        		{
        			string __designator;
        			__designator += *__it++;
        			if (__it != __end && string::traits_type::is_alpha(*__it)) __designator += *__it++;
        			if (__it != __end && string::traits_type::is_alpha(*__it)) __designator += *__it++;
        			if (__it != __end && string::traits_type::is_alpha(*__it)) __designator += *__it++;
        			for (uint32_t __i = 0; __i < sizeof(zones)/sizeof(zone); ++__i)
        			{
        				if (__designator == zones[__i].designator)
        					return zones[__i].timeZoneDifferential;
        			}
        		}
        		else if (*__it == '+' || *__it == '-')
        		{
        			int32_t __sign = *__it == '+' ? 1 : -1;
        			++__it;
        			int32_t __hours = 0;
                    parse_number_n(__it, __end, __hours, 2);
        			if (__it != __end && *__it == ':') ++__it;
        			int32_t __minutes = 0;
                    parse_number_n(__it, __end, __minutes, 2);
        			return __sign*(__hours*3600 + __minutes*60);
        		}
        	}
        	return 0;
        }

        static int32_t parse_ampm(string::const_iterator& __it, const string::const_iterator& __end, int32_t __hour)
        {
        	string __ampm;
        	while (__it != __end && (string::traits_type::is_space(*__it) || string::traits_type::is_punct(*__it))) ++__it;
        	while (__it != __end && string::traits_type::is_alpha(*__it)) 
        	{
        		char __ch = (*__it++);
        		__ampm += string::traits_type::to_upper(__ch);
        	}
        	if (__ampm == "AM")
        	{
        		if (__hour == 12)
        			return 0;
        		else
        			return __hour;
        	}
        	else if (__ampm == "PM")
        	{
        		if (__hour < 12)
        			return __hour + 12;
        		else
        			return __hour;
        	}
        	else 
                throw syntax_error("Not a valid AM/PM designator", __ampm);
        }

        static string tzd_iso(int32_t __tzd, string& __str)
        {
        	if (__tzd != 0)
        	{
        		if (__tzd >= 0)
        		{
        			__str += '+';
        			__str += string_util::format0(__tzd/3600, 2);
        			__str += ':';
        			__str += string_util::format0((__tzd%3600)/60, 2);
        		}
        		else
        		{
        			__str += '-';
        			__str += string_util::format0(-__tzd/3600, 2);
        			__str += ':';
        			__str += string_util::format0((-__tzd%3600)/60, 2);
        		}
        	}
        	else 
                __str += 'Z';
        }

        static string tzd_rfc(int32_t __tzd, string& __str)
        {
        	if (__tzd != 0)
        	{
        		if (__tzd >= 0)
        		{
        			__str += '+';
        			__str += string_util::format0(__tzd/3600, 2);
        			__str += string_util::format0((__tzd%3600)/60, 2);
        		}
        		else
        		{
        			__str += '-';
        			__str += string_util::format0(-__tzd/3600, 2);
        			__str += string_util::format0((-__tzd%3600)/60, 2);
        		}		
        	}
        	else 
                __str += "GMT";
        }
    };

}//namespace ufc

#endif//DATETIME_DATE_TIME_UTIL_HPP
