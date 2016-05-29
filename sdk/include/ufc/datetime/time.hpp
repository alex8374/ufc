/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/datetime/time.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_DATETIME_TIME_HPP
#define UFC_DATETIME_TIME_HPP

#include <ufc/datetime/timestamp.hpp>
#include <ufc/string/string.hpp>

namespace ufc {

    ///
    /// @breif: time class (no time zone, default local time zone) 
    ///
    class ufc_api time: virtual public object
    {
    public:
        time();
        time(const time& __other);
        time(const timestamp& __ts);
        time(int32_t __tzd, 
             int32_t __hour, 
             int32_t __minute, 
             int32_t __second, 
             int32_t __millisecond, 
             int32_t __microsecond);
        time(int32_t __hour, 
             int32_t __minute, 
             int32_t __second, 
             int32_t __millisecond = 0, 
             int32_t __microsecond = 0);
        virtual ~time();

        time& operator = (const time& __other);
        time& operator = (const timestamp& __ts);

        time& assign(int32_t __tzd, 
                     int32_t __hour, 
                     int32_t __minute, 
                     int32_t __second, 
                     int32_t __millisecond, 
                     int32_t __microsecond);
        time& assign(int32_t __hour, 
                     int32_t __minute, 
                     int32_t __second, 
                     int32_t __millisecond = 0, 
                     int32_t __microsecond = 0);
        time& assign(const timestamp& __ts);

        void swap(time& __time);

        bool operator == (const time& __time) const;
        bool operator != (const time& __time) const;
        bool operator <  (const time& __time) const;
        bool operator <= (const time& __time) const;
        bool operator >  (const time& __time) const;
        bool operator >= (const time& __time) const;

        time& make_local();
        time& make_utc();
        time& adjust_for_tzd(int32_t __tzd);

        int32_t hour() const;
        int32_t minute() const;
        int32_t second() const;
        int32_t millisecond() const;
        int32_t microsecond() const;
        int32_t tzd() const;
        int32_t hour_ampm() const;
        bool is_am() const;
        bool is_pm() const;
 
        /// 
		/// @breif: Formats the given time according to the given format.
		/// The format string is used as a template to format the date and
		/// is copied character by character except for the following special characters,
		/// which are replaced by the corresponding value.
		///
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
        string format(const string& __fmt = "%H:%M:%S") const;

    public:
        /// 
        /// @breif: 系统当前时间
        ///
        static time now();

        static bool is_valid(int32_t __hour, 
                             int32_t __minute, 
                             int32_t __second,
                             int32_t __millisecond = 0,
                             int32_t __microsecond = 0);

        /// 
		/// @breif: Parses a time from the given time string. Before parsing, the method
		///         examines the time string for a known time format.
		///         Please see format() function for a description of the format string.
        ///
        static time parse(const string& __str, const string& __fmt = "%H:%M:%S");
        static bool try_parse(time& __result_time, const string& __str, const string& __fmt = "%H:%M:%S");

    private:
        inline void normalize();

    private:
        int64_t _time_val;
        int16_t _hour;
        int16_t _minute;
        int16_t _second;
        int16_t _millisecond;
        int16_t _microsecond;
        int32_t _tzd;
    };

}//namespace ufc

#endif//UFC_DATETIME_TIME_HPP
