/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/datetime/time_format.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_DATETIME_TIME_FORMAT_HPP
#define UFC_DATETIME_TIME_FORMAT_HPP

#include <ufc/string/string.hpp>

namespace ufc {

    ///
	/// @breif: Definition of date/time formats and various
	///         constants used by DateTimeFormatter and DateTimeParser.
    ///
    class ufc_api time_format
    {
    public:
        ///
		/// The date/time format defined in the ISO 8601 standard.
		///
		/// Examples: 
		///   2005-01-01T12:00:00+01:00
		///   2005-01-01T11:00:00Z
        ///
        static const string iso8601_format;

        ///
		/// The date/time format defined in the ISO 8601 standard,
		/// with fractional seconds.
		///
		/// Examples: 
		///   2005-01-01T12:00:00.000000+01:00
		///   2005-01-01T11:00:00.000000Z
        ///
        static const string iso8601_frac_format;

        ///
		/// The date/time format defined in RFC 822 (obsoleted by RFC 1123).
		///
		/// Examples: 
		///   Sat, 1 Jan 05 12:00:00 +0100
		///   Sat, 1 Jan 05 11:00:00 GMT
        ///
        static const string rfc822_format;

        ///
		/// The date/time format defined in RFC 1123 (obsoletes RFC 822).
		///
		/// Examples: 
		///   Sat, 1 Jan 2005 12:00:00 +0100
		///   Sat, 1 Jan 2005 11:00:00 GMT
        ///
        static const string rfc1123_format;

        ///
		/// The date/time format defined in the HTTP specification (RFC 2616),
		/// which is basically a variant of RFC 1036 with a zero-padded day field.
		///
		/// Examples: 
		///   Sat, 01 Jan 2005 12:00:00 +0100
		///   Sat, 01 Jan 2005 11:00:00 GMT
        ///
        static const string http_format;

        ///
		/// The date/time format defined in RFC 850 (obsoleted by RFC 1036).
		///
		/// Examples: 
		///   Saturday, 1-Jan-05 12:00:00 +0100
		///   Saturday, 1-Jan-05 11:00:00 GMT
        ///
        static const string rfc850_format;

        ///
		/// The date/time format defined in RFC 1036 (obsoletes RFC 850).
		///
		/// Examples: 
		///   Saturday, 1 Jan 05 12:00:00 +0100
		///   Saturday, 1 Jan 05 11:00:00 GMT
        ///
        static const string rfc1036_format;

        ///
		/// The date/time format produced by the ANSI C asctime() function.
		///
		/// Example: 
		///   Sat Jan  1 12:00:00 2005
        ///   Sat Jan  1 12:00:00 2005
        ///
        static const string asctime_format;

        ///
		/// A simple, sortable date/time format.
		///
		/// Example:
		///   2005-01-01 12:00:00
        ///
        static const string simple_format;
    };

}//namespace ufc

#endif//UFC_DATETIME_TIME_FORMAT_HPP
