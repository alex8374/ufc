/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/base/types.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-17
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_BASE_TYPES_HPP
#define UFC_BASE_TYPES_HPP

namespace ufc {

    typedef unsigned char               byte_t;
    typedef unsigned short              word_t;
    typedef unsigned int                dword_t;

    typedef long                        long_t;
    typedef unsigned long               ulong_t;

    typedef signed char                 int8_t;
    typedef unsigned char               uint8_t;
    typedef signed short                int16_t;
    typedef unsigned short              uint16_t;
    typedef signed int                  int32_t;
    typedef unsigned int                uint32_t;

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
    //
    // Windows/Visual C++
    //
    typedef signed __int64              int64_t;
    typedef unsigned __int64            uint64_t;
    #if defined(_WIN64)
        #define ufc_ptr_is_64_bit       1
        typedef signed __int64          intptr_t;
        typedef unsigned __int64        uintptr_t;
    #else
        typedef signed long             intptr_t;
        typedef unsigned long           uintptr_t;
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    //
    // Unix/GCC
    //
    typedef signed long                 intptr_t;
    typedef unsigned long               uintptr_t;
    #if defined(__LP64__)
        #define ufc_ptr_is_64_bit       1
        #define ufc_long_is_64_bit      1
        typedef signed long             int64_t;
        typedef unsigned long           uint64_t;
    #else
        typedef signed long long        int64_t;
        typedef unsigned long long      uint64_t;
    #endif
#elif defined(__DECCXX)
    //
    // Compaq C++
    //
    typedef signed __int64              int64_t;
    typedef unsigned __int64            uint64_t;
    #if defined(__VMS)
        #if defined(__32BITS)
            typedef signed long         intptr_t;
            typedef unsigned long       uintptr_t;
        #else
            typedef int64_t             intptr_t;
            typedef uint64_t            uintptr_t;
            #define ufc_ptr_is_64_bit   1
        #endif
    #else
        typedef signed long             intptr_t;
        typedef unsigned long           uintptr_t;
        #define ufc_ptr_is_64_bit       1
        #define ufc_long_is_64_bit      1
    #endif
#elif defined(__HP_aCC)
    //
    // HP Ansi C++
    //
    typedef signed long                 intptr_t;
    typedef unsigned long               uintptr_t;
    #if defined(__LP64__)
        #define ufc_ptr_is_64_bit       1
        #define ufc_long_is_64_bit      1
        typedef signed long             int64_t;
        typedef unsigned long           uint64_t;
    #else
        typedef signed long long        int64_t;
        typedef unsigned long long      uint64_t;
    #endif
#elif defined(__SUNPRO_CC)
    //
    // SUN Forte C++
    //
    typedef signed long                 intptr_t;
    typedef unsigned long               uintptr_t;
    #if defined(__sparcv9)
        #define ufc_ptr_is_64_bit       1
        #define ufc_long_is_64_bit      1
        typedef signed long             int64_t;
        typedef unsigned long           uint64_t;
    #else
        typedef signed long long        int64_t;
        typedef unsigned long long      uint64_t;
    #endif
#elif defined(__IBMCPP__) 
    //
    // IBM XL C++
    //
    typedef signed long                 intptr_t;
    typedef unsigned long               uintptr_t;
    #if defined(__64BIT__)
        #define ufc_ptr_is_64_bit       1
        #define ufc_long_is_64_bit      1
        typedef signed long             int64_t;
        typedef unsigned long           uint64_t;
    #else
        typedef signed long long        int64_t;
        typedef unsigned long long      uint64_t;
    #endif
#elif defined(__sgi) 
    //
    // MIPSpro C++
    //
    typedef signed long                 intptr_t;
    typedef unsigned long               uintptr_t;
    #if _MIPS_SZLONG == 64
        #define ufc_ptr_is_64_bit       1
        #define ufc_long_is_64_bit      1
        typedef signed long             int64_t;
        typedef unsigned long           uint64_t;
    #else
        typedef signed long long        int64_t;
        typedef unsigned long long      uint64_t;
    #endif
#elif defined(_DIAB_TOOL)
    typedef signed long                 intptr_t;
    typedef unsigned long               uintptr_t;
    typedef signed long long            int64_t;
    typedef unsigned long long          uint64_t;
#endif

    ///
    /// @breif: alignment
    ///
    enum alignment_t
    {
        al_left   = 1, /// align left
        al_middle = 2, /// align middle
        al_right  = 3  /// align right
    };

}//namespace ufc

#endif//UFC_BASE_TYPES_HPP
