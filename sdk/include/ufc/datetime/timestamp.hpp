/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/datetime/timestamp.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_DATETIME_TIMESTAMP_HPP
#define UFC_DATETIME_TIMESTAMP_HPP

#include <ufc/base/config.hpp>
#include <ctime>

namespace ufc {

    ///
	/// @breif: a timestamp stores a monotonic* time value
	/// with (theoretical) microseconds resolution.
	/// Timestamps can be compared with each other
	/// and simple arithmetics are supported.
	///
	/// [*] Note that Timestamp values are only monotonic as
	/// long as the systems's clock is monotonic as well
	/// (and not, e.g. set back).
	///
	/// Timestamps are UTC (Coordinated Universal Time)
	/// based and thus independent of the timezone
	/// in effect on the system.
	///
    class ufc_api timestamp: virtual public object
    {
    public:
        typedef int64_t time_val;   /// monotonic UTC time value in microsecond resolution
        typedef int64_t time_diff;  /// difference between two timestamps in microseconds

        timestamp();
        timestamp(time_val __tv);
        timestamp(const timestamp& __ts);
        virtual ~timestamp();

        timestamp& operator = (const timestamp& __ts);
        timestamp& operator = (time_val __tv);

        void swap(timestamp& __ts);

        timestamp& update();

        bool operator == (const timestamp& __ts) const;
        bool operator != (const timestamp& __ts) const;
        bool operator >  (const timestamp& __ts) const;
        bool operator >= (const timestamp& __ts) const;
        bool operator <  (const timestamp& __ts) const;
        bool operator <= (const timestamp& __ts) const;

        timestamp  operator +  (time_diff __diff) const;
        timestamp  operator -  (time_diff __diff) const;
        time_diff  operator -  (const timestamp& __ts) const;
        timestamp& operator += (time_diff __diff);
        timestamp& operator -= (time_diff __diff);

        ///
        /// @breif: returns the number of seconds from the start of 1970-01-01 00:00:00.
        ///
        std::time_t epoch_time() const;

        ///
        /// @breif: returns the number of milliseconds starting from 1970-01-01 00:00:00.000000. 
        ///
        time_val epoch_microseconds() const;

        ///
        /// @brief: current time stamp overflow 
        ///
        time_diff elapsed() const;

        ///
        /// @brief: to determine whether the time stamp is beyond the specified time period 
        ///
        bool is_elapsed(time_diff __interval) const;

    public:
        static timestamp from_epoch_time(std::time_t __time);

        static time_val resolution; /// one second per second 
        static time_val utc_time;   

#if defined(_WIN32) || defined(WIN32)
        static timestamp from_file_time_np(uint32_t __file_time_low, uint32_t __file_time_high);

        void to_file_time_np(uint32_t& __file_time_low, uint32_t& __file_time_high) const;
#endif

    private:
        time_val _tv;
    };

}//namespace ufc

#endif//UFC_DATETIME_TIMESTAMP_HPP