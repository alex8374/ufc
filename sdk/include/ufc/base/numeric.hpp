/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/base/numeric.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_BASE_NUMERIC_HPP
#define UFC_BASE_NUMERIC_HPP

#include <ufc/base/platform.hpp>
#include <ufc/base/types.hpp>
#include <ufc/base/object.hpp>

namespace ufc {

    class ufc_api numeric: virtual public object
    {
    public:
        numeric();
        numeric(const numeric& __other);
        numeric(float __val);
        numeric(double __val);
        numeric(int8_t __val);
        numeric(uint8_t __val);
        numeric(int16_t __val);
        numeric(uint16_t __val);
        numeric(int32_t __val);
        numeric(uint32_t __val);
        numeric(int64_t __val);
        numeric(uint64_t __val);
#ifndef ufc_long_is_64_bit
        numeric(long_t __val);
        numeric(ulong_t __val);
#endif//ufc_long_is_64_bit
        virtual ~numeric();

        numeric& operator = (const numeric& __other);
        numeric& operator = (float __val);
        numeric& operator = (double __val);
        numeric& operator = (int8_t __val);
        numeric& operator = (uint8_t __val);
        numeric& operator = (int16_t __val);
        numeric& operator = (uint16_t __val);
        numeric& operator = (int32_t __val);
        numeric& operator = (uint32_t __val);
        numeric& operator = (int64_t __val);
        numeric& operator = (uint64_t __val);
#ifndef ufc_long_is_64_bit
        numeric& operator = (long_t __val);
        numeric& operator = (ulong_t __val);
#endif//ufc_long_is_64_bit

        double value() const;
        operator double () const;

        numeric& operator ++ ();
        numeric  operator ++ (int) const;
        numeric& operator -- ();
        numeric  operator -- (int) const;

        numeric& operator += (const numeric& __other);
        numeric& operator += (float __val);
        numeric& operator += (double __val);
        numeric& operator += (int8_t __val);
        numeric& operator += (uint8_t __val);
        numeric& operator += (int16_t __val);
        numeric& operator += (uint16_t __val);
        numeric& operator += (int32_t __val);
        numeric& operator += (uint32_t __val);
        numeric& operator += (int64_t __val);
        numeric& operator += (uint64_t __val);
#ifndef ufc_long_is_64_bit
        numeric& operator += (long_t __val);
        numeric& operator += (ulong_t __val);
#endif//ufc_long_is_64_bit

        numeric& operator -= (const numeric& __other);
        numeric& operator -= (float __val);
        numeric& operator -= (double __val);
        numeric& operator -= (int8_t __val);
        numeric& operator -= (uint8_t __val);
        numeric& operator -= (int16_t __val);
        numeric& operator -= (uint16_t __val);
        numeric& operator -= (int32_t __val);
        numeric& operator -= (uint32_t __val);
        numeric& operator -= (int64_t __val);
        numeric& operator -= (uint64_t __val);
#ifndef ufc_long_is_64_bit
        numeric& operator -= (long_t __val);
        numeric& operator -= (ulong_t __val);
#endif//ufc_long_is_64_bit

        numeric& operator *= (const numeric& __other);
        numeric& operator *= (float __val);
        numeric& operator *= (double __val);
        numeric& operator *= (int8_t __val);
        numeric& operator *= (uint8_t __val);
        numeric& operator *= (int16_t __val);
        numeric& operator *= (uint16_t __val);
        numeric& operator *= (int32_t __val);
        numeric& operator *= (uint32_t __val);
        numeric& operator *= (int64_t __val);
        numeric& operator *= (uint64_t __val);
#ifndef ufc_long_is_64_bit
        numeric& operator *= (long_t __val);
        numeric& operator *= (ulong_t __val);
#endif//ufc_long_is_64_bit

        numeric& operator /= (const numeric& __other);
        numeric& operator /= (float __val);
        numeric& operator /= (double __val);
        numeric& operator /= (int8_t __val);
        numeric& operator /= (uint8_t __val);
        numeric& operator /= (int16_t __val);
        numeric& operator /= (uint16_t __val);
        numeric& operator /= (int32_t __val);
        numeric& operator /= (uint32_t __val);
        numeric& operator /= (int64_t __val);
        numeric& operator /= (uint64_t __val);
#ifndef ufc_long_is_64_bit
        numeric& operator /= (long_t __val);
        numeric& operator /= (ulong_t __val);
#endif//ufc_long_is_64_bit

    public:
        static bool equal(double __lhs, double __rhs);
        static bool equal(double __lhs, float __rhs);
        static bool equal(float __lhs, double __rhs);
        static bool equal(double __lhs, int8_t __rhs);
        static bool equal(int8_t __lhs, double __rhs);
        static bool equal(double __lhs, uint8_t __rhs);
        static bool equal(uint8_t __lhs, double __rhs);
        static bool equal(float __lhs, int8_t __rhs);
        static bool equal(int8_t __lhs, float __rhs);
        static bool equal(float __lhs, uint8_t __rhs);
        static bool equal(uint8_t __lhs, float __rhs);
        static bool equal(double __lhs, int16_t __rhs);
        static bool equal(int16_t __lhs, double __rhs);
        static bool equal(double __lhs, uint16_t __rhs);
        static bool equal(uint16_t __lhs, double __rhs);
        static bool equal(float __lhs, int16_t __rhs);
        static bool equal(int16_t __lhs, float __rhs);
        static bool equal(float __lhs, uint16_t __rhs);
        static bool equal(uint16_t __lhs, float __rhs);
        static bool equal(double __lhs, int32_t __rhs);
        static bool equal(int32_t __lhs, double __rhs);
        static bool equal(double __lhs, uint32_t __rhs);
        static bool equal(uint32_t __lhs, double __rhs);
        static bool equal(float __lhs, int32_t __rhs);
        static bool equal(int32_t __lhs, float __rhs);
        static bool equal(float __lhs, uint32_t __rhs);
        static bool equal(uint32_t __lhs, float __rhs);
        static bool equal(double __lhs, int64_t __rhs);
        static bool equal(int64_t __lhs, double __rhs);
        static bool equal(double __lhs, uint64_t __rhs);
        static bool equal(uint64_t __lhs, double __rhs);
        static bool equal(float __lhs, int64_t __rhs);
        static bool equal(int64_t __lhs, float __rhs);
        static bool equal(float __lhs, uint64_t __rhs);
        static bool equal(uint64_t __lhs, float __rhs);
#ifndef ufc_long_is_64_bit
        static bool equal(double __lhs, long_t __rhs);
        static bool equal(long_t __lhs, double __rhs);
        static bool equal(double __lhs, ulong_t __rhs);
        static bool equal(ulong_t __lhs, double __rhs);
        static bool equal(float __lhs, long_t __rhs);
        static bool equal(long_t __lhs, float __rhs);
        static bool equal(float __lhs, ulong_t __rhs);
        static bool equal(ulong_t __lhs, float __rhs);
#endif//ufc_long_is_64_bit

    private:
        double _val;
    };

    ufc_api numeric operator + (const numeric& __lhs, const numeric& __rhs);
    ufc_api numeric operator + (const numeric& __lhs, double __rhs);
    ufc_api numeric operator + (double __lhs, const numeric& __rhs);
    ufc_api numeric operator + (const numeric& __lhs, float __rhs);
    ufc_api numeric operator + (float __lhs, const numeric& __rhs);
    ufc_api numeric operator + (const numeric& __lhs, int8_t __rhs);
    ufc_api numeric operator + (int8_t __lhs, const numeric& __rhs);
    ufc_api numeric operator + (const numeric& __lhs, uint8_t __rhs);
    ufc_api numeric operator + (uint8_t __lhs, const numeric& __rhs);
    ufc_api numeric operator + (const numeric& __lhs, int16_t __rhs);
    ufc_api numeric operator + (int16_t __lhs, const numeric& __rhs);
    ufc_api numeric operator + (const numeric& __lhs, uint16_t __rhs);
    ufc_api numeric operator + (uint16_t __lhs, const numeric& __rhs);
    ufc_api numeric operator + (const numeric& __lhs, int32_t __rhs);
    ufc_api numeric operator + (int32_t __lhs, const numeric& __rhs);
    ufc_api numeric operator + (const numeric& __lhs, uint32_t __rhs);
    ufc_api numeric operator + (uint32_t __lhs, const numeric& __rhs);
    ufc_api numeric operator + (const numeric& __lhs, int64_t __rhs);
    ufc_api numeric operator + (int64_t __lhs, const numeric& __rhs);
    ufc_api numeric operator + (const numeric& __lhs, uint64_t __rhs);
    ufc_api numeric operator + (uint64_t __lhs, const numeric& __rhs);
#ifndef ufc_long_is_64_bit
    ufc_api numeric operator + (const numeric& __lhs, long_t __rhs);
    ufc_api numeric operator + (long_t __lhs, const numeric& __rhs);
    ufc_api numeric operator + (const numeric& __lhs, ulong_t __rhs);
    ufc_api numeric operator + (ulong_t __lhs, const numeric& __rhs);
#endif//ufc_long_is_64_bit

    ufc_api numeric operator - (const numeric& __lhs, const numeric& __rhs);
    ufc_api numeric operator - (const numeric& __lhs, double __rhs);
    ufc_api numeric operator - (double __lhs, const numeric& __rhs);
    ufc_api numeric operator - (const numeric& __lhs, float __rhs);
    ufc_api numeric operator - (float __lhs, const numeric& __rhs);
    ufc_api numeric operator - (const numeric& __lhs, int8_t __rhs);
    ufc_api numeric operator - (int8_t __lhs, const numeric& __rhs);
    ufc_api numeric operator - (const numeric& __lhs, uint8_t __rhs);
    ufc_api numeric operator - (uint8_t __lhs, const numeric& __rhs);
    ufc_api numeric operator - (const numeric& __lhs, int16_t __rhs);
    ufc_api numeric operator - (int16_t __lhs, const numeric& __rhs);
    ufc_api numeric operator - (const numeric& __lhs, uint16_t __rhs);
    ufc_api numeric operator - (uint16_t __lhs, const numeric& __rhs);
    ufc_api numeric operator - (const numeric& __lhs, int32_t __rhs);
    ufc_api numeric operator - (int32_t __lhs, const numeric& __rhs);
    ufc_api numeric operator - (const numeric& __lhs, uint32_t __rhs);
    ufc_api numeric operator - (uint32_t __lhs, const numeric& __rhs);
    ufc_api numeric operator - (const numeric& __lhs, int64_t __rhs);
    ufc_api numeric operator - (int64_t __lhs, const numeric& __rhs);
    ufc_api numeric operator - (const numeric& __lhs, uint64_t __rhs);
    ufc_api numeric operator - (uint64_t __lhs, const numeric& __rhs);
#ifndef ufc_long_is_64_bit
    ufc_api numeric operator - (const numeric& __lhs, long_t __rhs);
    ufc_api numeric operator - (long_t __lhs, const numeric& __rhs);
    ufc_api numeric operator - (const numeric& __lhs, ulong_t __rhs);
    ufc_api numeric operator - (ulong_t __lhs, const numeric& __rhs);
#endif//ufc_long_is_64_bit

    ufc_api numeric operator * (const numeric& __lhs, const numeric& __rhs);
    ufc_api numeric operator * (const numeric& __lhs, double __rhs);
    ufc_api numeric operator * (double __lhs, const numeric& __rhs);
    ufc_api numeric operator * (const numeric& __lhs, float __rhs);
    ufc_api numeric operator * (float __lhs, const numeric& __rhs);
    ufc_api numeric operator * (const numeric& __lhs, int8_t __rhs);
    ufc_api numeric operator * (int8_t __lhs, const numeric& __rhs);
    ufc_api numeric operator * (const numeric& __lhs, uint8_t __rhs);
    ufc_api numeric operator * (uint8_t __lhs, const numeric& __rhs);
    ufc_api numeric operator * (const numeric& __lhs, int16_t __rhs);
    ufc_api numeric operator * (int16_t __lhs, const numeric& __rhs);
    ufc_api numeric operator * (const numeric& __lhs, uint16_t __rhs);
    ufc_api numeric operator * (uint16_t __lhs, const numeric& __rhs);
    ufc_api numeric operator * (const numeric& __lhs, int32_t __rhs);
    ufc_api numeric operator * (int32_t __lhs, const numeric& __rhs);
    ufc_api numeric operator * (const numeric& __lhs, uint32_t __rhs);
    ufc_api numeric operator * (uint32_t __lhs, const numeric& __rhs);
    ufc_api numeric operator * (const numeric& __lhs, int64_t __rhs);
    ufc_api numeric operator * (int64_t __lhs, const numeric& __rhs);
    ufc_api numeric operator * (const numeric& __lhs, uint64_t __rhs);
    ufc_api numeric operator * (uint64_t __lhs, const numeric& __rhs);
#ifndef ufc_long_is_64_bit
    ufc_api numeric operator * (const numeric& __lhs, long_t __rhs);
    ufc_api numeric operator * (long_t __lhs, const numeric& __rhs);
    ufc_api numeric operator * (const numeric& __lhs, ulong_t __rhs);
    ufc_api numeric operator * (ulong_t __lhs, const numeric& __rhs);
#endif//ufc_long_is_64_bit

    ufc_api numeric operator / (const numeric& __lhs, const numeric& __rhs);
    ufc_api numeric operator / (const numeric& __lhs, double __rhs);
    ufc_api numeric operator / (double __lhs, const numeric& __rhs);
    ufc_api numeric operator / (const numeric& __lhs, float __rhs);
    ufc_api numeric operator / (float __lhs, const numeric& __rhs);
    ufc_api numeric operator / (const numeric& __lhs, int8_t __rhs);
    ufc_api numeric operator / (int8_t __lhs, const numeric& __rhs);
    ufc_api numeric operator / (const numeric& __lhs, uint8_t __rhs);
    ufc_api numeric operator / (uint8_t __lhs, const numeric& __rhs);
    ufc_api numeric operator / (const numeric& __lhs, int16_t __rhs);
    ufc_api numeric operator / (int16_t __lhs, const numeric& __rhs);
    ufc_api numeric operator / (const numeric& __lhs, uint16_t __rhs);
    ufc_api numeric operator / (uint16_t __lhs, const numeric& __rhs);
    ufc_api numeric operator / (const numeric& __lhs, int32_t __rhs);
    ufc_api numeric operator / (int32_t __lhs, const numeric& __rhs);
    ufc_api numeric operator / (const numeric& __lhs, uint32_t __rhs);
    ufc_api numeric operator / (uint32_t __lhs, const numeric& __rhs);
    ufc_api numeric operator / (const numeric& __lhs, int64_t __rhs);
    ufc_api numeric operator / (int64_t __lhs, const numeric& __rhs);
    ufc_api numeric operator / (const numeric& __lhs, uint64_t __rhs);
    ufc_api numeric operator / (uint64_t __lhs, const numeric& __rhs);
#ifndef ufc_long_is_64_bit
    ufc_api numeric operator / (const numeric& __lhs, long_t __rhs);
    ufc_api numeric operator / (long_t __lhs, const numeric& __rhs);
    ufc_api numeric operator / (const numeric& __lhs, ulong_t __rhs);
    ufc_api numeric operator / (ulong_t __lhs, const numeric& __rhs);
#endif//ufc_long_is_64_bit

    ufc_api bool operator == (const numeric& __lhs, const numeric& __rhs);
    ufc_api bool operator == (const numeric& __lhs, double __rhs);
    ufc_api bool operator == (double __lhs, const numeric& __rhs);
    ufc_api bool operator == (const numeric& __lhs, float __rhs);
    ufc_api bool operator == (float __lhs, const numeric& __rhs);
    ufc_api bool operator == (const numeric& __lhs, int8_t __rhs);
    ufc_api bool operator == (int8_t __lhs, const numeric& __rhs);
    ufc_api bool operator == (const numeric& __lhs, uint8_t __rhs);
    ufc_api bool operator == (uint8_t __lhs, const numeric& __rhs);
    ufc_api bool operator == (const numeric& __lhs, int16_t __rhs);
    ufc_api bool operator == (int16_t __lhs, const numeric& __rhs);
    ufc_api bool operator == (const numeric& __lhs, uint16_t __rhs);
    ufc_api bool operator == (uint16_t __lhs, const numeric& __rhs);
    ufc_api bool operator == (const numeric& __lhs, int32_t __rhs);
    ufc_api bool operator == (int32_t __lhs, const numeric& __rhs);
    ufc_api bool operator == (const numeric& __lhs, uint32_t __rhs);
    ufc_api bool operator == (uint32_t __lhs, const numeric& __rhs);
    ufc_api bool operator == (const numeric& __lhs, int64_t __rhs);
    ufc_api bool operator == (int64_t __lhs, const numeric& __rhs);
    ufc_api bool operator == (const numeric& __lhs, uint64_t __rhs);
    ufc_api bool operator == (uint64_t __lhs, const numeric& __rhs);
#ifndef ufc_long_is_64_bit
    ufc_api bool operator == (const numeric& __lhs, long_t __rhs);
    ufc_api bool operator == (long_t __lhs, const numeric& __rhs);
    ufc_api bool operator == (const numeric& __lhs, ulong_t __rhs);
    ufc_api bool operator == (ulong_t __lhs, const numeric& __rhs);
#endif//ufc_long_is_64_bit

    ufc_api bool operator != (const numeric& __lhs, const numeric& __rhs);
    ufc_api bool operator != (const numeric& __lhs, double __rhs);
    ufc_api bool operator != (double __lhs, const numeric& __rhs);
    ufc_api bool operator != (const numeric& __lhs, float __rhs);
    ufc_api bool operator != (float __lhs, const numeric& __rhs);
    ufc_api bool operator != (const numeric& __lhs, int8_t __rhs);
    ufc_api bool operator != (int8_t __lhs, const numeric& __rhs);
    ufc_api bool operator != (const numeric& __lhs, uint8_t __rhs);
    ufc_api bool operator != (uint8_t __lhs, const numeric& __rhs);
    ufc_api bool operator != (const numeric& __lhs, int16_t __rhs);
    ufc_api bool operator != (int16_t __lhs, const numeric& __rhs);
    ufc_api bool operator != (const numeric& __lhs, uint16_t __rhs);
    ufc_api bool operator != (uint16_t __lhs, const numeric& __rhs);
    ufc_api bool operator != (const numeric& __lhs, int32_t __rhs);
    ufc_api bool operator != (int32_t __lhs, const numeric& __rhs);
    ufc_api bool operator != (const numeric& __lhs, uint32_t __rhs);
    ufc_api bool operator != (uint32_t __lhs, const numeric& __rhs);
    ufc_api bool operator != (const numeric& __lhs, int64_t __rhs);
    ufc_api bool operator != (int64_t __lhs, const numeric& __rhs);
    ufc_api bool operator != (const numeric& __lhs, uint64_t __rhs);
    ufc_api bool operator != (uint64_t __lhs, const numeric& __rhs);
#ifndef ufc_long_is_64_bit
    ufc_api bool operator != (const numeric& __lhs, long_t __rhs);
    ufc_api bool operator != (long_t __lhs, const numeric& __rhs);
    ufc_api bool operator != (const numeric& __lhs, ulong_t __rhs);
    ufc_api bool operator != (ulong_t __lhs, const numeric& __rhs);
#endif//ufc_long_is_64_bit

    ufc_api bool operator >= (const numeric& __lhs, const numeric& __rhs);
    ufc_api bool operator >= (const numeric& __lhs, double __rhs);
    ufc_api bool operator >= (double __lhs, const numeric& __rhs);
    ufc_api bool operator >= (const numeric& __lhs, float __rhs);
    ufc_api bool operator >= (float __lhs, const numeric& __rhs);
    ufc_api bool operator >= (const numeric& __lhs, int8_t __rhs);
    ufc_api bool operator >= (int8_t __lhs, const numeric& __rhs);
    ufc_api bool operator >= (const numeric& __lhs, uint8_t __rhs);
    ufc_api bool operator >= (uint8_t __lhs, const numeric& __rhs);
    ufc_api bool operator >= (const numeric& __lhs, int16_t __rhs);
    ufc_api bool operator >= (int16_t __lhs, const numeric& __rhs);
    ufc_api bool operator >= (const numeric& __lhs, uint16_t __rhs);
    ufc_api bool operator >= (uint16_t __lhs, const numeric& __rhs);
    ufc_api bool operator >= (const numeric& __lhs, int32_t __rhs);
    ufc_api bool operator >= (int32_t __lhs, const numeric& __rhs);
    ufc_api bool operator >= (const numeric& __lhs, uint32_t __rhs);
    ufc_api bool operator >= (uint32_t __lhs, const numeric& __rhs);
    ufc_api bool operator >= (const numeric& __lhs, int64_t __rhs);
    ufc_api bool operator >= (int64_t __lhs, const numeric& __rhs);
    ufc_api bool operator >= (const numeric& __lhs, uint64_t __rhs);
    ufc_api bool operator >= (uint64_t __lhs, const numeric& __rhs);
#ifndef ufc_long_is_64_bit
    ufc_api bool operator >= (const numeric& __lhs, long_t __rhs);
    ufc_api bool operator >= (long_t __lhs, const numeric& __rhs);
    ufc_api bool operator >= (const numeric& __lhs, ulong_t __rhs);
    ufc_api bool operator >= (ulong_t __lhs, const numeric& __rhs);
#endif//ufc_long_is_64_bit

    ufc_api bool operator > (const numeric& __lhs, const numeric& __rhs);
    ufc_api bool operator > (const numeric& __lhs, double __rhs);
    ufc_api bool operator > (double __lhs, const numeric& __rhs);
    ufc_api bool operator > (const numeric& __lhs, float __rhs);
    ufc_api bool operator > (float __lhs, const numeric& __rhs);
    ufc_api bool operator > (const numeric& __lhs, int8_t __rhs);
    ufc_api bool operator > (int8_t __lhs, const numeric& __rhs);
    ufc_api bool operator > (const numeric& __lhs, uint8_t __rhs);
    ufc_api bool operator > (uint8_t __lhs, const numeric& __rhs);
    ufc_api bool operator > (const numeric& __lhs, int16_t __rhs);
    ufc_api bool operator > (int16_t __lhs, const numeric& __rhs);
    ufc_api bool operator > (const numeric& __lhs, uint16_t __rhs);
    ufc_api bool operator > (uint16_t __lhs, const numeric& __rhs);
    ufc_api bool operator > (const numeric& __lhs, int32_t __rhs);
    ufc_api bool operator > (int32_t __lhs, const numeric& __rhs);
    ufc_api bool operator > (const numeric& __lhs, uint32_t __rhs);
    ufc_api bool operator > (uint32_t __lhs, const numeric& __rhs);
    ufc_api bool operator > (const numeric& __lhs, int64_t __rhs);
    ufc_api bool operator > (int64_t __lhs, const numeric& __rhs);
    ufc_api bool operator > (const numeric& __lhs, uint64_t __rhs);
    ufc_api bool operator > (uint64_t __lhs, const numeric& __rhs);
#ifndef ufc_long_is_64_bit
    ufc_api bool operator > (const numeric& __lhs, long_t __rhs);
    ufc_api bool operator > (long_t __lhs, const numeric& __rhs);
    ufc_api bool operator > (const numeric& __lhs, ulong_t __rhs);
    ufc_api bool operator > (ulong_t __lhs, const numeric& __rhs);
#endif//ufc_long_is_64_bit

    ufc_api bool operator <= (const numeric& __lhs, const numeric& __rhs);
    ufc_api bool operator <= (const numeric& __lhs, double __rhs);
    ufc_api bool operator <= (double __lhs, const numeric& __rhs);
    ufc_api bool operator <= (const numeric& __lhs, float __rhs);
    ufc_api bool operator <= (float __lhs, const numeric& __rhs);
    ufc_api bool operator <= (const numeric& __lhs, int8_t __rhs);
    ufc_api bool operator <= (int8_t __lhs, const numeric& __rhs);
    ufc_api bool operator <= (const numeric& __lhs, uint8_t __rhs);
    ufc_api bool operator <= (uint8_t __lhs, const numeric& __rhs);
    ufc_api bool operator <= (const numeric& __lhs, int16_t __rhs);
    ufc_api bool operator <= (int16_t __lhs, const numeric& __rhs);
    ufc_api bool operator <= (const numeric& __lhs, uint16_t __rhs);
    ufc_api bool operator <= (uint16_t __lhs, const numeric& __rhs);
    ufc_api bool operator <= (const numeric& __lhs, int32_t __rhs);
    ufc_api bool operator <= (int32_t __lhs, const numeric& __rhs);
    ufc_api bool operator <= (const numeric& __lhs, uint32_t __rhs);
    ufc_api bool operator <= (uint32_t __lhs, const numeric& __rhs);
    ufc_api bool operator <= (const numeric& __lhs, int64_t __rhs);
    ufc_api bool operator <= (int64_t __lhs, const numeric& __rhs);
    ufc_api bool operator <= (const numeric& __lhs, uint64_t __rhs);
    ufc_api bool operator <= (uint64_t __lhs, const numeric& __rhs);
#ifndef ufc_long_is_64_bit
    ufc_api bool operator <= (const numeric& __lhs, long_t __rhs);
    ufc_api bool operator <= (long_t __lhs, const numeric& __rhs);
    ufc_api bool operator <= (const numeric& __lhs, ulong_t __rhs);
    ufc_api bool operator <= (ulong_t __lhs, const numeric& __rhs);
#endif//ufc_long_is_64_bit

    ufc_api bool operator < (const numeric& __lhs, const numeric& __rhs);
    ufc_api bool operator < (const numeric& __lhs, double __rhs);
    ufc_api bool operator < (double __lhs, const numeric& __rhs);
    ufc_api bool operator < (const numeric& __lhs, float __rhs);
    ufc_api bool operator < (float __lhs, const numeric& __rhs);
    ufc_api bool operator < (const numeric& __lhs, int8_t __rhs);
    ufc_api bool operator < (int8_t __lhs, const numeric& __rhs);
    ufc_api bool operator < (const numeric& __lhs, uint8_t __rhs);
    ufc_api bool operator < (uint8_t __lhs, const numeric& __rhs);
    ufc_api bool operator < (const numeric& __lhs, int16_t __rhs);
    ufc_api bool operator < (int16_t __lhs, const numeric& __rhs);
    ufc_api bool operator < (const numeric& __lhs, uint16_t __rhs);
    ufc_api bool operator < (uint16_t __lhs, const numeric& __rhs);
    ufc_api bool operator < (const numeric& __lhs, int32_t __rhs);
    ufc_api bool operator < (int32_t __lhs, const numeric& __rhs);
    ufc_api bool operator < (const numeric& __lhs, uint32_t __rhs);
    ufc_api bool operator < (uint32_t __lhs, const numeric& __rhs);
    ufc_api bool operator < (const numeric& __lhs, int64_t __rhs);
    ufc_api bool operator < (int64_t __lhs, const numeric& __rhs);
    ufc_api bool operator < (const numeric& __lhs, uint64_t __rhs);
    ufc_api bool operator < (uint64_t __lhs, const numeric& __rhs);
#ifndef ufc_long_is_64_bit
    ufc_api bool operator < (const numeric& __lhs, long_t __rhs);
    ufc_api bool operator < (long_t __lhs, const numeric& __rhs);
    ufc_api bool operator < (const numeric& __lhs, ulong_t __rhs);
    ufc_api bool operator < (ulong_t __lhs, const numeric& __rhs);
#endif//ufc_long_is_64_bit

}//namespace ufc

#endif//UFC_BASE_NUMERIC_HPP