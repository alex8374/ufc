/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/datetime/date_time.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_DATETIME_DATE_TIME_HPP
#define UFC_DATETIME_DATE_TIME_HPP

#include <ufc/datetime/date.hpp>
#include <ufc/datetime/time.hpp>
#include <ufc/datetime/timespan.hpp>

namespace ufc {

    ///
    /// @breif: This class represents an instant in time, expressed	
    /// in years, months, days, hours, minutes, seconds	
    /// and milliseconds based on the Gregorian calendar.	
    /// The class is mainly useful for conversions between	
    /// UTC/LOCAL(default), Julian day and Gregorian calendar dates.	
    ///	
    /// The date and time stored in a date_time is always in UTC	or local
    /// (Coordinated Universal Time) and thus independent of the 	
    /// timezone in effect on the system.
    ///
    class ufc_api date_time: virtual public object
    {
    public:
        date_time();
        date_time(const date_time& __other);
        date_time(const date& __date);
        date_time(const date& __date, const time& __time);
        date_time(const timestamp& __ts);
        date_time(int32_t __year, 
                  int32_t __month,
                  int32_t __day,
                  int32_t __hour = 0,
                  int32_t __minute = 0,
                  int32_t __second = 0,
                  int32_t __millisecond = 0,
                  int32_t __microsecond = 0);
        date_time(int32_t __tzd,
                  int32_t __year,
                  int32_t __month,
                  int32_t __day,
                  int32_t __hour,
                  int32_t __minute,
                  int32_t __second,
                  int32_t __millisecond,
                  int32_t __microsecond);
        virtual ~date_time();

        date_time& operator = (const date_time& __other);
        date_time& operator = (const date& __date);
        date_time& operator = (const timestamp& __ts);

        date_time& assign(int32_t __tzd,
                          int32_t __year,
                          int32_t __month,
                          int32_t __day,
                          int32_t __hour,
                          int32_t __minute,
                          int32_t __second,
                          int32_t __millisecond,
                          int32_t __microsecond);
        date_time& assign(int32_t __year,
                          int32_t __month,
                          int32_t __day,
                          int32_t __hour = 0,
                          int32_t __minute = 0,
                          int32_t __second = 0,
                          int32_t __millisecond = 0,
                          int32_t __microsecond = 0);
        date_time& assign(const date& __date);
        date_time& assign(const date& __date, const time& __time);
        date_time& assign(const timestamp& __ts);

        void swap(date_time& __other);

        bool operator == (const date_time& __other) const;
        bool operator != (const date_time& __other) const;
        bool operator <  (const date_time& __other) const;
        bool operator <= (const date_time& __other) const;
        bool operator >  (const date_time& __other) const;
        bool operator >= (const date_time& __other) const;

        date_time  operator +  (const timespan& __span) const;
        date_time  operator -  (const timespan& __span) const;
        timespan   operator -  (const date_time& __other) const;
        date_time& operator += (const timespan& __span);
        date_time& operator -= (const timespan& __span);

        /// 
        /// @breif: Adjust to local time
        /// 
        date_time& make_local();

        /// 
        /// @breif: Adjust to UTC time
        /// 
        date_time& make_utc();

        /// 
        /// @breif: Adjust time zone 
        /// 
        date_time& adjust_for_tzd(int32_t __tzd);

        int32_t year() const;
        int32_t month() const;
        int32_t day() const;
        int32_t hour() const;
        int32_t minute() const;
        int32_t second() const;
        int32_t millisecond() const;
        int32_t microsecond() const;
        int32_t tzd() const;

        int32_t hour_ampm() const;
        bool is_am() const;
        bool is_pm() const;

        int32_t day_of_week() const;
        int32_t day_of_year() const;
        int32_t week(int32_t __first_day_of_week = date::monday) const;

        timestamp get_timestamp() const;
        date get_date() const;
        time get_time() const;

        date_time& add(int32_t __years, int32_t __months, int32_t __days);
        date_time& add_year(int32_t __years);
        date_time& add_month(int32_t __months);
        date_time& add_day(int32_t __days);

        /// 
		/// @breif: Formats the given timestamp according to the given format.
		/// The format string is used as a template to format the date and
		/// is copied character by character except for the following special characters,
		/// which are replaced by the corresponding value.
		///
		///   * %w - abbreviated weekday (Mon, Tue, ...)
		///   * %W - full weekday (Monday, Tuesday, ...)
		///   * %b - abbreviated month (Jan, Feb, ...)
		///   * %B - full month (January, February, ...)
		///   * %d - zero-padded day of month (01 .. 31)
		///   * %e - day of month (1 .. 31)
		///   * %f - space-padded day of month ( 1 .. 31)
		///   * %m - zero-padded month (01 .. 12)
		///   * %n - month (1 .. 12)
		///   * %o - space-padded month ( 1 .. 12)
		///   * %y - year without century (70)
		///   * %Y - year with century (1970)
		///   * %H - hour (00 .. 23)
		///   * %h - hour (00 .. 12)
		///   * %a - am/pm
		///   * %A - AM/PM
		///   * %M - minute (00 .. 59)
		///   * %S - second (00 .. 59)
		///   * %s - seconds and microseconds (equivalent to %S.%F)
		///   * %i - millisecond (000 .. 999)
		///   * %c - centisecond (0 .. 9)
		///   * %F - fractional seconds/microseconds (000000 - 999999)
		///   * %z - time zone differential in ISO 8601 format (Z or +NN.NN)
		///   * %Z - time zone differential in RFC format (GMT or +NNNN)
		///   * %% - percent sign
		///
		/// Class time_format defines format strings for various standard date/time formats.
        ///
        string format(const string& __fmt = "%Y-%m-%d %H:%M:%S.%F %z") const;

    public:
        static date_time now();

        static bool is_valid(int32_t __year, 
                             int32_t __month,
                             int32_t __day,
                             int32_t __hour = 0,
                             int32_t __minute = 0,
                             int32_t __second = 0,
                             int32_t __millisecond = 0,
                             int32_t __microsecond = 0);

        /// 
		/// @breif: Parses a time from the given date/time string. Before parsing, the method
		///         examines the time string for a known date/time format.
		///         Please see format() function for a description of the format string.
        ///
        static date_time parse(const string& __str, const string& __fmt);
        static bool try_parse(date_time& __result_date_time, const string& __str, const string& __fmt);

    private:
        inline void normalize();

    private:
        int64_t _datetime_val;
        int16_t _year;
        int16_t _month;
        int16_t _day;
        int16_t _hour;
        int16_t _minute;
        int16_t _second;
        int16_t _millisecond;
        int16_t _microsecond;
        int32_t _tzd;
    };

}//namespace ufc

#endif//UFC_DATETIME_DATE_TIME_HPP
