/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/base/config.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-17
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_BASE_CONFIG_HPP
#define UFC_BASE_CONFIG_HPP

#define __ufc_do_string(__s)        #__s
#define ufc_string(__s)             __ufc_do_string(__s)

#define __ufc_do_char(__c)          @#__c
#define ufc_char(__c)               __ufc_do_char(__c)

#define __ufc_do_join(__a, __b)     __a ## __b
#define ufc_join(__a, Y)            __ufc_do_join(__a, __b)

#define ufc_kb(__n)                 ((1024) * (__n))
#define ufc_mb(__n)                 ((1024) * ufc_kb(__n))
#define ufc_gb(__n)                 ((1024) * ufc_mb(__n))
#define ufc_tb(__n)                 ((1024) * ufc_gb(__n))

#define ufc_min(__a, __b)           ((__a) >= (__b)? (__b): (__a))
#define ufc_max(__a, __b)           ((__a) >= (__b)? (__a): (__b))
#define ufc_abs(__a)                ((__a) >= 0? (__a): -(__a))

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <typeinfo>
#include <algorithm>
#include <cmath>
#include <istream>
#include <ostream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#if !defined(_WIN32)
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#endif//!defined(_WIN32)

#include <ufc/base/platform.hpp>
#include <ufc/base/types.hpp>
#include <ufc/base/object.hpp>
#include <ufc/base/memory.hpp>
#include <ufc/base/source_info.hpp>
#include <ufc/base/numeric.hpp>

#endif//UFC_BASE_CONFIG_HPP
