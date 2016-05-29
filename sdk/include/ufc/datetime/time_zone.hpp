/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/datetime/time_zone.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_DATETIME_TIME_ZONE_HPP
#define UFC_DATETIME_TIME_ZONE_HPP

#include <ufc/datetime/timestamp.hpp>
#include <ufc/string/string.hpp>

namespace ufc {

    ///
    /// @breif: This class provides information about the current timezone.
    ///
    class ufc_api time_zone
    {
    public:	
        ///
        /// @breif: Returns the offset of local time to UTC, in seconds. 
        ///         local time = UTC + utcOffset() + dst().
        ///
        static int32_t utc_offset();

        ///
        /// @breif: Returns the daylight saving time offset in seconds if
        ///         daylight saving time is in use.
        ///         local time = UTC + utcOffset() + dst().
        ///
        static int32_t dst();

		/// @breif: Returns true if daylight saving time is in effect
		///         for the given time. Depending on the operating system
		///         platform this might only work reliably for certain
		///         date ranges, as the C library's localtime() function
		///         is used.
        static bool    is_dst(const timestamp& __ts);

		/// @breif: Returns the timezone name if daylight saving time is in effect.
        static string  dst_name();

		/// @breif: Returns the time zone differential for the current timezone.
		///         The timezone differential is computed as utcOffset() + dst()
		///         and is expressed in seconds.
        static int32_t tzd();

		/// @breif: Returns the timezone name currently in effect.
        static string  name();

		/// @breif: Returns the timezone name if not daylight saving time is in effect.
        static string  standard_name();
    };

}//namespace ufc

#endif//UFC_DATETIME_TIME_ZONE_HPP