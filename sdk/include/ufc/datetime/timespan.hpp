/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/datetime/timespan.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_DATETIME_TIMESPAN_HPP
#define UFC_DATETIME_TIMESPAN_HPP

#include <ufc/datetime/timestamp.hpp>
#include <ufc/string/string.hpp>

namespace ufc {

    ///
    /// @brief: A class that represents time spans up to microsecond resolution.
    ///
    class ufc_api timespan: virtual public object
    {
    public:
        typedef timestamp::time_diff time_diff;

        timespan();
        timespan(const timespan& __other);
        timespan(time_diff __microseconds);
        timespan(long_t __seconds, long_t __microseconds);
        timespan(int32_t __days, 
                 int32_t __hours,
                 int32_t __minutes,
                 int32_t __seconds,
                 int32_t __microseconds);
        virtual ~timespan();

        timespan& operator = (const timespan& __other);
        timespan& operator = (time_diff __microseconds);

        timespan& assign(int32_t __days, 
                         int32_t __hours,
                         int32_t __minutes,
                         int32_t __seconds,
                         int32_t __microseconds);
        timespan& assign(long_t __seconds, long_t __microseconds);

        void swap(timespan& __other);

        bool operator == (const timespan& __other) const;
        bool operator != (const timespan& __other) const;
        bool operator >  (const timespan& __other) const;
        bool operator >= (const timespan& __other) const;
        bool operator <  (const timespan& __other) const;
        bool operator <= (const timespan& __other) const;

        bool operator == (time_diff __microseconds) const;
        bool operator != (time_diff __microseconds) const;
        bool operator >  (time_diff __microseconds) const;
        bool operator >= (time_diff __microseconds) const;
        bool operator <  (time_diff __microseconds) const;
        bool operator <= (time_diff __microseconds) const;

        timespan operator + (const timespan& __diff) const;
        timespan operator - (const timespan& __diff) const;
        timespan& operator += (const timespan& __diff);
        timespan& operator -= (const timespan& __diff);

        timespan operator + (time_diff __microseconds) const;
        timespan operator - (time_diff __microseconds) const;
        timespan& operator += (time_diff __microseconds);
        timespan& operator -= (time_diff __microseconds);

        int32_t get_days() const;
        int32_t get_hours() const;
        int32_t get_total_hours() const;
        int32_t get_minutes() const;
        int32_t get_total_minutes() const;
        int32_t get_seconds() const;
        int32_t get_total_seconds() const;
        int32_t get_milliseconds() const;
        time_diff get_total_milliseconds() const;
        int32_t get_microseconds() const;
        int32_t get_useconds() const;
        time_diff get_total_microseconds() const;

        ///
        /// @biref: Formats the given timespan according to the given format.
        ///         The format string is used as a template to format the date and
        ///         is copied character by character except for the following special characters,
        ///         which are replaced by the corresponding value.
        ///
        ///   * %d - days
        ///   * %H - hours     (00 .. 23)
        ///   * %h - total hours (0 .. n)
        ///   * %M - minutes (00 .. 59)
        ///   * %m - total minutes (0 .. n)
        ///   * %S - seconds (00 .. 59)
        ///   * %s - total seconds (0 .. n)
        ///   * %i - milliseconds (000 .. 999)
        ///   * %c - centisecond (0 .. 9)
        ///   * %F - fractional seconds/microseconds (000000 - 999999)
        ///   * %% - percent sign
        ///
        string format(const string& __fmt = "%dd %H:%M:%S.%F") const;

    public:
        static const time_diff milliseconds; /// The number of microseconds in a millisecond.
        static const time_diff seconds;      /// The number of microseconds in a second.
        static const time_diff minutes;      /// The number of microseconds in a minute.
        static const time_diff hours;        /// The number of microseconds in a hour.
        static const time_diff days;         /// The number of microseconds in a day.

    private:
        time_diff _span;
    };

}//namespace ufc

#endif//UFC_DATETIME_TIMESPAN_HPP
