/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : base/numeric.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/base/numeric.hpp"

namespace ufc {

    numeric::numeric()
        : _val(0.00)
    {
    }

    numeric::numeric(const numeric& __rhs)
        : _val(__rhs._val)
    {
    }

    numeric::numeric(float __val)
        : _val(__val)
    {
    }

    numeric::numeric(double __val)
        : _val(__val)
    {
    }

    numeric::numeric(int8_t __val)
        : _val(__val)
    {
    }

    numeric::numeric(uint8_t __val)
        : _val(__val)
    {
    }

    numeric::numeric(int16_t __val)
        : _val(__val)
    {
    }

    numeric::numeric(uint16_t __val)
        : _val(__val)
    {
    }

    numeric::numeric(int32_t __val)
        : _val(__val)
    {
    }

    numeric::numeric(uint32_t __val)
        : _val(__val)
    {
    }

    numeric::numeric(int64_t __val)
        : _val(__val)
    {
    }

    numeric::numeric(uint64_t __val)
        : _val(__val)
    {
    }

#ifndef ufc_long_is_64_bit
    numeric::numeric(long_t __val)
        : _val(__val)
    {
    }

    numeric::numeric(ulong_t __val)
        : _val(__val)
    {
    }

#endif//ufc_long_is_64_bit
    numeric::~numeric()
    {
    }

    numeric& numeric::operator = (const numeric& __rhs)
    {
        _val = __rhs._val;
        return *this;
    }

    numeric& numeric::operator = (float __val)
    {
        _val = __val;
        return *this;
    }

    numeric& numeric::operator = (double __val)
    {
        _val = __val;
        return *this;
    }

    numeric& numeric::operator = (int8_t __val)
    {
        _val = __val;
        return *this;
    }

    numeric& numeric::operator = (uint8_t __val)
    {
        _val = __val;
        return *this;
    }

    numeric& numeric::operator = (int16_t __val)
    {
        _val = __val;
        return *this;
    }

    numeric& numeric::operator = (uint16_t __val)
    {
        _val = __val;
        return *this;
    }

    numeric& numeric::operator = (int32_t __val)
    {
        _val = __val;
        return *this;
    }

    numeric& numeric::operator = (uint32_t __val)
    {
        _val = __val;
        return *this;
    }

    numeric& numeric::operator = (int64_t __val)
    {
        _val = __val;
        return *this;
    }

    numeric& numeric::operator = (uint64_t __val)
    {
        _val = __val;
        return *this;
    }

#ifndef ufc_long_is_64_bit

    numeric& numeric::operator = (long_t __val)
    {
        _val = __val;
        return *this;
    }

    numeric& numeric::operator = (ulong_t __val)
    {
        _val = __val;
        return *this;
    }

#endif//ufc_long_is_64_bit

    double numeric::value() const
    {
        return _val;
    }

    numeric::operator double () const
    {
        return _val;
    }

    numeric& numeric::operator ++ ()
    {
        _val += 1.00;
        return *this;
    }

    numeric  numeric::operator ++ (int) const
    {
        numeric result(*this);
        result._val += 1.00;
        return result;
    }

    numeric& numeric::operator -- ()
    {
        _val -= 1.00;
        return *this;
    }

    numeric  numeric::operator -- (int) const
    {
        numeric result(*this);
        result._val -= 1.00;
        return result;
    }

    numeric& numeric::operator += (const numeric& __rhs)
    {
        _val += __rhs._val;
        return *this;
    }

    numeric& numeric::operator += (float __val)
    {
        _val += __val;
        return *this;
    }

    numeric& numeric::operator += (double __val)
    {
        _val += __val;
        return *this;
    }

    numeric& numeric::operator += (int8_t __val)
    {
        _val += __val;
        return *this;
    }

    numeric& numeric::operator += (uint8_t __val)
    {
        _val += __val;
        return *this;
    }

    numeric& numeric::operator += (int16_t __val)
    {
        _val += __val;
        return *this;
    }

    numeric& numeric::operator += (uint16_t __val)
    {
        _val += __val;
        return *this;
    }

    numeric& numeric::operator += (int32_t __val)
    {
        _val += __val;
        return *this;
    }

    numeric& numeric::operator += (uint32_t __val)
    {
        _val += __val;
        return *this;
    }

    numeric& numeric::operator += (int64_t __val)
    {
        _val += __val;
        return *this;
    }

    numeric& numeric::operator += (uint64_t __val)
    {
        _val += __val;
        return *this;
    }

#ifndef ufc_long_is_64_bit

    numeric& numeric::operator += (long_t __val)
    {
        _val += __val;
        return *this;
    }

    numeric& numeric::operator += (ulong_t __val)
    {
        _val += __val;
        return *this;
    }

#endif//ufc_long_is_64_bit

    numeric& numeric::operator -= (const numeric& __rhs)
    {
        _val -= __rhs._val;
        return *this;
    }

    numeric& numeric::operator -= (float __val)
    {
        _val -= __val;
        return *this;
    }

    numeric& numeric::operator -= (double __val)
    {
        _val -= __val;
        return *this;
    }

    numeric& numeric::operator -= (int8_t __val)
    {
        _val -= __val;
        return *this;
    }

    numeric& numeric::operator -= (uint8_t __val)
    {
        _val -= __val;
        return *this;
    }

    numeric& numeric::operator -= (int16_t __val)
    {
        _val -= __val;
        return *this;
    }

    numeric& numeric::operator -= (uint16_t __val)
    {
        _val -= __val;
        return *this;
    }

    numeric& numeric::operator -= (int32_t __val)
    {
        _val -= __val;
        return *this;
    }

    numeric& numeric::operator -= (uint32_t __val)
    {
        _val -= __val;
        return *this;
    }

    numeric& numeric::operator -= (int64_t __val)
    {
        _val -= __val;
        return *this;
    }

    numeric& numeric::operator -= (uint64_t __val)
    {
        _val -= __val;
        return *this;
    }

#ifndef ufc_long_is_64_bit

    numeric& numeric::operator -= (long_t __val)
    {
        _val -= __val;
        return *this;
    }

    numeric& numeric::operator -= (ulong_t __val)
    {
        _val -= __val;
        return *this;
    }

#endif//ufc_long_is_64_bit

    numeric& numeric::operator *= (const numeric& __rhs)
    {
        _val *= __rhs._val;
        return *this;
    }

    numeric& numeric::operator *= (float __val)
    {
        _val *= __val;
        return *this;
    }

    numeric& numeric::operator *= (double __val)
    {
        _val *= __val;
        return *this;
    }

    numeric& numeric::operator *= (int8_t __val)
    {
        _val *= __val;
        return *this;
    }

    numeric& numeric::operator *= (uint8_t __val)
    {
        _val *= __val;
        return *this;
    }

    numeric& numeric::operator *= (int16_t __val)
    {
        _val *= __val;
        return *this;
    }

    numeric& numeric::operator *= (uint16_t __val)
    {
        _val *= __val;
        return *this;
    }

    numeric& numeric::operator *= (int32_t __val)
    {
        _val *= __val;
        return *this;
    }

    numeric& numeric::operator *= (uint32_t __val)
    {
        _val *= __val;
        return *this;
    }

    numeric& numeric::operator *= (int64_t __val)
    {
        _val *= __val;
        return *this;
    }

    numeric& numeric::operator *= (uint64_t __val)
    {
        _val *= __val;
        return *this;
    }

#ifndef ufc_long_is_64_bit

    numeric& numeric::operator *= (long_t __val)
    {
        _val *= __val;
        return *this;
    }

    numeric& numeric::operator *= (ulong_t __val)
    {
        _val *= __val;
        return *this;
    }

#endif//ufc_long_is_64_bit

    numeric& numeric::operator /= (const numeric& __rhs)
    {
        _val /= __rhs._val;
        return *this;
    }

    numeric& numeric::operator /= (float __val)
    {
        _val /= __val;
        return *this;
    }

    numeric& numeric::operator /= (double __val)
    {
        _val /= __val;
        return *this;
    }

    numeric& numeric::operator /= (int8_t __val)
    {
        _val /= __val;
        return *this;
    }

    numeric& numeric::operator /= (uint8_t __val)
    {
        _val /= __val;
        return *this;
    }

    numeric& numeric::operator /= (int16_t __val)
    {
        _val /= __val;
        return *this;
    }

    numeric& numeric::operator /= (uint16_t __val)
    {
        _val /= __val;
        return *this;
    }

    numeric& numeric::operator /= (int32_t __val)
    {
        _val /= __val;
        return *this;
    }

    numeric& numeric::operator /= (uint32_t __val)
    {
        _val /= __val;
        return *this;
    }

    numeric& numeric::operator /= (int64_t __val)
    {
        _val /= __val;
        return *this;
    }

    numeric& numeric::operator /= (uint64_t __val)
    {
        _val /= __val;
        return *this;
    }

#ifndef ufc_long_is_64_bit

    numeric& numeric::operator /= (long_t __val)
    {
        _val /= __val;
        return *this;
    }

    numeric& numeric::operator /= (ulong_t __val)
    {
        _val /= __val;
        return *this;
    }

#endif//ufc_long_is_64_bit

    bool numeric::equal(double __lhs, double __rhs)
    {
        return (std::fabs(__lhs - __rhs) < 0.0001);
    }

    bool numeric::equal(double __lhs, float __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(float __lhs, double __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(double __lhs, int8_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(int8_t __lhs, double __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(double __lhs, uint8_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(uint8_t __lhs, double __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(float __lhs, int8_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(int8_t __lhs, float __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(float __lhs, uint8_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(uint8_t __lhs, float __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(double __lhs, int16_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(int16_t __lhs, double __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(double __lhs, uint16_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(uint16_t __lhs, double __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(float __lhs, int16_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(int16_t __lhs, float __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(float __lhs, uint16_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(uint16_t __lhs, float __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(double __lhs, int32_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(int32_t __lhs, double __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(double __lhs, uint32_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(uint32_t __lhs, double __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(float __lhs, int32_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(int32_t __lhs, float __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(float __lhs, uint32_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(uint32_t __lhs, float __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(double __lhs, int64_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(int64_t __lhs, double __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(double __lhs, uint64_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(uint64_t __lhs, double __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(float __lhs, int64_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(int64_t __lhs, float __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(float __lhs, uint64_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(uint64_t __lhs, float __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

#ifndef ufc_long_is_64_bit

    bool numeric::equal(double __lhs, long_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(long_t __lhs, double __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(double __lhs, ulong_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(ulong_t __lhs, double __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(float __lhs, long_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(long_t __lhs, float __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(float __lhs, ulong_t __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

    bool numeric::equal(ulong_t __lhs, float __rhs)
    {
        return equal((double)__lhs, (double)__rhs);
    }

#endif//ufc_long_is_64_bit

    numeric operator + (const numeric& __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (const numeric& __lhs, double __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (double __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (const numeric& __lhs, float __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (float __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (const numeric& __lhs, int8_t __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (int8_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (const numeric& __lhs, uint8_t __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (uint8_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (const numeric& __lhs, int16_t __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (int16_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (const numeric& __lhs, uint16_t __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (uint16_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (const numeric& __lhs, int32_t __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (int32_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (const numeric& __lhs, uint32_t __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (uint32_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (const numeric& __lhs, int64_t __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (int64_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (const numeric& __lhs, uint64_t __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (uint64_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

#ifndef ufc_long_is_64_bit

    numeric operator + (const numeric& __lhs, long_t __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (long_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (const numeric& __lhs, ulong_t __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

    numeric operator + (ulong_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result += __rhs;
        return result;
    }

#endif//ufc_long_is_64_bit

    numeric operator - (const numeric& __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (const numeric& __lhs, double __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (double __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (const numeric& __lhs, float __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (float __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (const numeric& __lhs, int8_t __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (int8_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (const numeric& __lhs, uint8_t __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (uint8_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (const numeric& __lhs, int16_t __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (int16_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (const numeric& __lhs, uint16_t __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (uint16_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (const numeric& __lhs, int32_t __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (int32_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (const numeric& __lhs, uint32_t __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (uint32_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (const numeric& __lhs, int64_t __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (int64_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (const numeric& __lhs, uint64_t __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (uint64_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

#ifndef ufc_long_is_64_bit

    numeric operator - (const numeric& __lhs, long_t __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (long_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (const numeric& __lhs, ulong_t __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

    numeric operator - (ulong_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result -= __rhs;
        return result;
    }

#endif//ufc_long_is_64_bit

    numeric operator * (const numeric& __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (const numeric& __lhs, double __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (double __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (const numeric& __lhs, float __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (float __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (const numeric& __lhs, int8_t __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (int8_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (const numeric& __lhs, uint8_t __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (uint8_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (const numeric& __lhs, int16_t __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (int16_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (const numeric& __lhs, uint16_t __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (uint16_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (const numeric& __lhs, int32_t __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (int32_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (const numeric& __lhs, uint32_t __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (uint32_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (const numeric& __lhs, int64_t __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (int64_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (const numeric& __lhs, uint64_t __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (uint64_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

#ifndef ufc_long_is_64_bit

    numeric operator * (const numeric& __lhs, long_t __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (long_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (const numeric& __lhs, ulong_t __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

    numeric operator * (ulong_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result *= __rhs;
        return result;
    }

#endif//ufc_long_is_64_bit

    numeric operator / (const numeric& __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (const numeric& __lhs, double __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (double __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (const numeric& __lhs, float __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (float __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (const numeric& __lhs, int8_t __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (int8_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (const numeric& __lhs, uint8_t __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (uint8_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (const numeric& __lhs, int16_t __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (int16_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (const numeric& __lhs, uint16_t __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (uint16_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (const numeric& __lhs, int32_t __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (int32_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (const numeric& __lhs, uint32_t __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (uint32_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (const numeric& __lhs, int64_t __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (int64_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (const numeric& __lhs, uint64_t __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (uint64_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

#ifndef ufc_long_is_64_bit

    numeric operator / (const numeric& __lhs, long_t __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (long_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (const numeric& __lhs, ulong_t __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

    numeric operator / (ulong_t __lhs, const numeric& __rhs)
    {
        numeric result(__lhs);
        result /= __rhs;
        return result;
    }

#endif//ufc_long_is_64_bit

    bool operator == (const numeric& __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (const numeric& __lhs, double __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (double __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (const numeric& __lhs, float __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (float __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (const numeric& __lhs, int8_t __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (int8_t __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (const numeric& __lhs, uint8_t __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (uint8_t __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (const numeric& __lhs, int16_t __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (int16_t __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (const numeric& __lhs, uint16_t __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (uint16_t __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (const numeric& __lhs, int32_t __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (int32_t __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (const numeric& __lhs, uint32_t __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (uint32_t __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (const numeric& __lhs, int64_t __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (int64_t __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (const numeric& __lhs, uint64_t __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (uint64_t __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

#ifndef ufc_long_is_64_bit

    bool operator == (const numeric& __lhs, long_t __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (long_t __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (const numeric& __lhs, ulong_t __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

    bool operator == (ulong_t __lhs, const numeric& __rhs)
    {
        return numeric::equal(__lhs, __rhs);
    }

#endif//ufc_long_is_64_bit

    bool operator != (const numeric& __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (const numeric& __lhs, double __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (double __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (const numeric& __lhs, float __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (float __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (const numeric& __lhs, int8_t __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (int8_t __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (const numeric& __lhs, uint8_t __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (uint8_t __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (const numeric& __lhs, int16_t __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (int16_t __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (const numeric& __lhs, uint16_t __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (uint16_t __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (const numeric& __lhs, int32_t __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (int32_t __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (const numeric& __lhs, uint32_t __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (uint32_t __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (const numeric& __lhs, int64_t __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (int64_t __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (const numeric& __lhs, uint64_t __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (uint64_t __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

#ifndef ufc_long_is_64_bit

    bool operator != (const numeric& __lhs, long_t __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (long_t __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (const numeric& __lhs, ulong_t __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

    bool operator != (ulong_t __lhs, const numeric& __rhs)
    {
        return !numeric::equal(__lhs, __rhs);
    }

#endif//ufc_long_is_64_bit

    bool operator >= (const numeric& __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (const numeric& __lhs, double __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (double __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (const numeric& __lhs, float __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (float __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (const numeric& __lhs, int8_t __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (int8_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (const numeric& __lhs, uint8_t __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (uint8_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (const numeric& __lhs, int16_t __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (int16_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (const numeric& __lhs, uint16_t __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (uint16_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (const numeric& __lhs, int32_t __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (int32_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (const numeric& __lhs, uint32_t __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (uint32_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (const numeric& __lhs, int64_t __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (int64_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (const numeric& __lhs, uint64_t __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (uint64_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

#ifndef ufc_long_is_64_bit

    bool operator >= (const numeric& __lhs, long_t __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (long_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (const numeric& __lhs, ulong_t __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator >= (ulong_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs) || numeric::equal(__lhs, __rhs));
    }

#endif//ufc_long_is_64_bit

    bool operator > (const numeric& __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (const numeric& __lhs, double __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (double __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (const numeric& __lhs, float __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (float __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (const numeric& __lhs, int8_t __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (int8_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (const numeric& __lhs, uint8_t __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (uint8_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (const numeric& __lhs, int16_t __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (int16_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (const numeric& __lhs, uint16_t __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (uint16_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (const numeric& __lhs, int32_t __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (int32_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (const numeric& __lhs, uint32_t __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (uint32_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (const numeric& __lhs, int64_t __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (int64_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (const numeric& __lhs, uint64_t __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (uint64_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

#ifndef ufc_long_is_64_bit

    bool operator > (const numeric& __lhs, long_t __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (long_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (const numeric& __lhs, ulong_t __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

    bool operator > (ulong_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) > double(__rhs));
    }

#endif//ufc_long_is_64_bit

    bool operator <= (const numeric& __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (const numeric& __lhs, double __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (double __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (const numeric& __lhs, float __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (float __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (const numeric& __lhs, int8_t __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (int8_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (const numeric& __lhs, uint8_t __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (uint8_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (const numeric& __lhs, int16_t __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (int16_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (const numeric& __lhs, uint16_t __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (uint16_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (const numeric& __lhs, int32_t __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (int32_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (const numeric& __lhs, uint32_t __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (uint32_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (const numeric& __lhs, int64_t __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (int64_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (const numeric& __lhs, uint64_t __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (uint64_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

#ifndef ufc_long_is_64_bit

    bool operator <= (const numeric& __lhs, long_t __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (long_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (const numeric& __lhs, ulong_t __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

    bool operator <= (ulong_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs) || numeric::equal(__lhs, __rhs));
    }

#endif//ufc_long_is_64_bit

    bool operator < (const numeric& __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (const numeric& __lhs, double __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (double __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (const numeric& __lhs, float __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (float __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (const numeric& __lhs, int8_t __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (int8_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (const numeric& __lhs, uint8_t __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (uint8_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (const numeric& __lhs, int16_t __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (int16_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (const numeric& __lhs, uint16_t __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (uint16_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (const numeric& __lhs, int32_t __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (int32_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (const numeric& __lhs, uint32_t __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (uint32_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (const numeric& __lhs, int64_t __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (int64_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (const numeric& __lhs, uint64_t __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (uint64_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

#ifndef ufc_long_is_64_bit

    bool operator < (const numeric& __lhs, long_t __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (long_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (const numeric& __lhs, ulong_t __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

    bool operator < (ulong_t __lhs, const numeric& __rhs)
    {
        return (double(__lhs) < double(__rhs));
    }

#endif//ufc_long_is_64_bit

}//namespace ufc
