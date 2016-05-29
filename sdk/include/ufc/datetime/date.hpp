/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/datetime/date.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_DATETIME_DATE_HPP
#define UFC_DATETIME_DATE_HPP

#include <ufc/datetime/timestamp.hpp>
#include <ufc/string/string.hpp>

namespace ufc {

    ///
    /// @breif: time class (no time zone, default local time zone) 
    ///
    class ufc_api date: virtual public object
    {
    public:
        enum months
        {
            january = 1,
            february,
            march,
            april,
            may,
            june,
            july,
            august,
            september,
            october,
            november,
            december
        };

        enum days_of_week
        {
            sunday = 0,
            monday,
            tuesday,
            wednesday,
            thursday,
            friday,
            saturday
        };

    public:
        date();
        date(const date& __other);
        date(const timestamp& __ts);
        date(int32_t __year, int32_t __month, int32_t __day);
        virtual ~date();

        date& operator = (const date& __other);
        date& operator = (const timestamp& __ts);

        date& assign(int32_t __year, int32_t __month, int32_t __day);
        date& assign(const timestamp& __ts);

        void swap(date& __date);

        date& operator ++ ();
        date  operator ++ (int32_t);
        date& operator -- ();
        date  operator -- (int32_t);
        date& operator += (int32_t __days);
        date& operator -= (int32_t __days);

        bool operator == (const date& __date) const;
        bool operator != (const date& __date) const;
        bool operator <  (const date& __date) const;
        bool operator <= (const date& __date) const;
        bool operator >  (const date& __date) const;
        bool operator >= (const date& __date) const;

        date& add(int32_t __years, int32_t __months, int32_t __days);
        date& add_year(int32_t __years);
        date& add_month(int32_t __months);
        date& add_day(int32_t __days);

        int32_t year() const;
        int32_t month() const;
        int32_t day() const;
        int32_t day_of_week() const;
        int32_t day_of_year() const;
        int32_t week(int32_t __first_day_of_week = monday) const;

        /// 
		/// @breif: Formats the given date according to the given format.
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
		///
        string format(const string& __fmt = "%Y-%m-%d") const;

    public:
        static date now();

        static bool is_leap_year(int32_t __year);
        static bool is_valid(int32_t __year, int32_t __month, int32_t __day);

        static int32_t days_of_month(int32_t __year, int32_t __month);

        /// 
		/// @breif: Parses a date from the given date string. Before parsing, the method
		///         examines the date string for a known date format.
		///         Please see format() function for a description of the format string.
        ///
        static date parse(const string& __str, const string& __fmt = "%Y-%m-%d");
        static bool try_parse(date& __result_date, const string& __str, const string& __fmt = "%Y-%m-%d");

    public:
        static const string weekday_names[7];
        static const string month_names[12];

    private:
        inline date& normalize();

    private:
        int32_t _date_val;
        int16_t _year;
        int16_t _month;
        int16_t _day;
    };

}//namespace ufc

#endif//UFC_DATETIME_DATE_HPP
