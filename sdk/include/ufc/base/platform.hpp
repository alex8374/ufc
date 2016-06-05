/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : ufc/base/platform.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-06-05
  Description: 
  History    : 
*******************************************************************************/
#ifndef UFC_BASE_PLATFORM_HPP
#define UFC_BASE_PLATFORM_HPP

//
// Platform Identification
//
#define ufc_os_free_bsd      0x0001
#define ufc_os_aix           0x0002
#define ufc_os_hpux          0x0003
#define ufc_os_tru64         0x0004
#define ufc_os_linux         0x0005
#define ufc_os_mac_os_x      0x0006
#define ufc_os_net_bsd       0x0007
#define ufc_os_open_bsd      0x0008
#define ufc_os_irix          0x0009
#define ufc_os_solaris       0x000a
#define ufc_os_qnx           0x000b
#define ufc_os_vxworks       0x000c
#define ufc_os_cygwin        0x000d
#define ufc_os_unknown_unix  0x00ff
#define ufc_os_windows_nt    0x1001
#define ufc_os_windows_ce    0x1011
#define ufc_os_vms           0x2001
    
#if defined(__FreeBSD__)
	#define ufc_os_family_unix 1
	#define ufc_os_family_bsd  1
	#define ufc_os ufc_os_free_bsd
#elif defined(_AIX) || defined(__TOS_AIX__)
	#define ufc_os_family_unix 1
	#define ufc_os ufc_os_aix
#elif defined(hpux) || defined(_hpux)
	#define ufc_os_family_unix 1
	#define ufc_os ufc_os_hpux
#elif defined(__digital__) || defined(__osf__)
	#define ufc_os_family_unix 1
	#define ufc_os ufc_os_tru64
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__TOS_LINUX__)
	#define ufc_os_family_unix 1
	#define ufc_os ufc_os_linux
#elif defined(__APPLE__) || defined(__TOS_MACOS__)
	#define ufc_os_family_unix 1
	#define ufc_os_family_bsd  1
	#define ufc_os ufc_os_mac_os_x
#elif defined(__NetBSD__)
	#define ufc_os_family_unix 1
	#define ufc_os_family_bsd  1
	#define ufc_os ufc_os_net_bsd
#elif defined(__OpenBSD__)
	#define ufc_os_family_unix 1
	#define ufc_os_family_bsd  1
	#define ufc_os ufc_os_open_bsd
#elif defined(sgi) || defined(__sgi)
	#define ufc_os_family_unix 1
	#define ufc_os ufc_os_irix
#elif defined(sun) || defined(__sun)
	#define ufc_os_family_unix 1
	#define ufc_os ufc_os_solaris
#elif defined(__QNX__)
	#define ufc_os_family_unix 1
	#define ufc_os ufc_os_qnx
#elif defined(unix) || defined(__unix) || defined(__unix__)
	#define ufc_os_family_unix 1
	#define ufc_os ufc_os_unknown_unix
#elif defined(_WIN32_WCE)
	#define ufc_os_family_windows 1
	#define ufc_os ufc_os_windows_ce
#elif defined(_WIN32) || defined(_WIN64)
	#define ufc_os_family_windows 1
	#define ufc_os ufc_os_windows_nt
#elif defined(__CYGWIN__)
	#define ufc_os_family_unix 1
	#define ufc_os ufc_os_cygwin
#elif defined(__VMS)
	#define ufc_os_family_vms 1
	#define ufc_os ufc_os_vms
#elif defined(ufc_vxworks)
  #define ufc_os_family_unix 1
  #define ufc_os ufc_os_vxworks
#endif

//
// Hardware Architecture and Byte Order
//
#define ufc_arch_alpha   0x01
#define ufc_arch_ia32    0x02
#define ufc_arch_ia64    0x03
#define ufc_arch_mips    0x04
#define ufc_arch_hppa    0x05
#define ufc_arch_ppc     0x06
#define ufc_arch_power   0x07
#define ufc_arch_sparc   0x08
#define ufc_arch_amd64   0x09
#define ufc_arch_arm     0x0a
#define ufc_arch_m68k    0x0b
#define ufc_arch_s390    0x0c
#define ufc_arch_sh      0x0d
#define ufc_arch_nios2   0x0e

#if defined(__ALPHA) || defined(__alpha) || defined(__alpha__) || defined(_M_ALPHA)
	#define ufc_arch ufc_arch_alpha
	#define ufc_arch_little_endian 1
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86)
	#define ufc_arch ufc_arch_ia32
	#define ufc_arch_little_endian 1
#elif defined(_IA64) || defined(__IA64__) || defined(__ia64__) || defined(__ia64) || defined(_M_IA64)
	#define ufc_arch ufc_arch_ia64
	#if defined(hpux) || defined(_hpux)
		#define ufc_arch_big_endian 1
	#else
		#define ufc_arch_little_endian 1
	#endif
#elif defined(__x86_64__) || defined(_M_X64)
	#define ufc_arch ufc_arch_amd64
	#define ufc_arch_little_endian 1
#elif defined(__mips__) || defined(__mips) || defined(__MIPS__) || defined(_M_MRX000)
	#define ufc_arch ufc_arch_mips
	#define ufc_arch_big_endian 1
#elif defined(__hppa) || defined(__hppa__)
	#define ufc_arch ufc_arch_hppa
	#define ufc_arch_big_endian 1
#elif defined(__PPC) || defined(__POWERPC__) || defined(__powerpc) || defined(__PPC__) || \
      defined(__powerpc__) || defined(__ppc__) || defined(__ppc) || defined(_ARCH_PPC) || defined(_M_PPC)
	#define ufc_arch ufc_arch_ppc
	#define ufc_arch_big_endian 1
#elif defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || \
      defined(_ARCH_PWR4) || defined(__THW_RS6000)
	#define ufc_arch ufc_arch_power
	#define ufc_arch_big_endian 1
#elif defined(__sparc__) || defined(__sparc) || defined(sparc)
	#define ufc_arch ufc_arch_sparc
	#define ufc_arch_big_endian 1
#elif defined(__arm__) || defined(__arm) || defined(ARM) || defined(_ARM_) || defined(__ARM__) || defined(_M_ARM)
	#define ufc_arch ufc_arch_arm
	#if defined(__ARMEB__)
		#define ufc_arch_big_endian 1
	#else
		#define ufc_arch_little_endian 1
	#endif
#elif defined(__m68k__)
	#define ufc_arch ufc_arch_m68k
	#define ufc_arch_big_endian 1
#elif defined(__s390__)
	#define ufc_arch ufc_arch_s390
	#define ufc_arch_big_endian 1
#elif defined(__sh__) || defined(__sh)
	#define ufc_arch ufc_arch_sh
	#if defined(__LITTLE_ENDIAN__)
		#define ufc_arch_little_endian 1
	#else
		#define ufc_arch_big_endian 1
	#endif
#elif defined (nios2) || defined(__nios2) || defined(__nios2__)
    #define ufc_arch ufc_arch_nios2
    #if defined(__nios2_little_endian) || defined(nios2_little_endian) || defined(__nios2_little_endian__)
		#define ufc_arch_little_endian 1
	#else
		#define ufc_arch_big_endian 1
	#endif
#endif

#if defined(_WIN32)

    // Verify that we're built with the multithreaded 
    // versions of the runtime libraries
    #if defined(_MSC_VER) && !defined(_MT)
    	#error Must compile with /MD, /MDd, /MT or /MTd
    #endif

    // Check debug/release settings consistency
    #if defined(NDEBUG) && defined(_DEBUG)
    	#error Inconsistent build settings (check for /MD[d])
    #endif

    // Reduce bloat imported by "Poco/UnWindows.h"
    #if defined(_WIN32)
    	#if !defined(_WIN32_WINNT)
    		#define _WIN32_WINNT 0x0501
    	#endif
    	#if !defined(WIN32_LEAN_AND_MEAN) && !defined(POCO_BLOATED_WIN32)
    		#define WIN32_LEAN_AND_MEAN
    	#endif
    #endif

    // Unicode Support
    #if defined(UNICODE) && !defined(POCO_WIN32_UTF8)
    	#define POCO_WIN32_UTF8
    #endif

    // Turn off some annoying warnings
    #if defined(_MSC_VER)
    	#pragma warning(disable:4018) // signed/unsigned comparison
    	#pragma warning(disable:4251) // ... needs to have dll-interface warning 
    	#pragma warning(disable:4355) // 'this' : used in base member initializer list
    	#pragma warning(disable:4996) // VC++ 8.0 deprecation warnings
    	#pragma warning(disable:4351) // new behavior: elements of array '...' will be default initialized
    	#pragma warning(disable:4675) // resolved overload was found by argument-dependent lookup
    	#pragma warning(disable:4275) // non dll-interface class 'std::exception' used as base for dll-interface class 'Poco::Exception'
        #pragma warning(disable:4520)
        #pragma warning(disable:4244)
        #pragma warning(disable:4099) 
        #pragma warning(disable:4290)
    #endif
    #if defined(__INTEL_COMPILER)
    	#pragma warning(disable:1738) // base class dllexport/dllimport specification differs from that of the derived class
    	#pragma warning(disable:1478) // function ... was declared "deprecated"
    	#pragma warning(disable:1744) // field of class type without a DLL interface used in a class with a DLL interface
    #endif

#elif defined(__VMS)

    // Define the POCO_DESCRIPTOR_STRING and POCO_DESCRIPTOR_LITERAL
    // macros which we use instead of $DESCRIPTOR and $DESCRIPTOR64. 
    // Our macros work with both 32bit and 64bit pointer sizes.
    #if __INITIAL_POINTER_SIZE != 64
    	#define ufc_descriptor_string(name, string) \
    		struct dsc$descriptor_s name =	\
    		{								\
    			string.size(),				\
    			DSC$K_DTYPE_T,				\
    			DSC$K_CLASS_S,				\
    			(char*) string.data()		\
    		}
    	#define ufc_descriptor_literal(name, string) \
    		struct dsc$descriptor_s name =	\
    		{								\
    			sizeof(string) - 1,			\
    			DSC$K_DTYPE_T,				\
    			DSC$K_CLASS_S,				\
    			(char*) string				\
    		}
    #else
    	#define ufc_descriptor_string(name, string) \
    		struct dsc64$descriptor_s name =\
    		{								\
    			1,							\
    			DSC64$K_DTYPE_T,			\
    			DSC64$K_CLASS_S,			\
    			-1,							\
    			string.size(),				\
    			(char*) string.data()		\
    		}
    	#define ufc_descriptor_literal(name, string) \
    		struct dsc64$descriptor_s name =\
    		{								\
    			1,							\
    			DSC64$K_DTYPE_T,			\
    			DSC64$K_CLASS_S,			\
    			-1,							\
    			sizeof(string) - 1,			\
    			(char*) string				\
    		}
    #endif

    // No <sys/select.h> header file
    #define ufc_no_sys_select_h

#elif defined(ufc_vxworks)
    #define ufc_no_sys_select_h 
    #define ufc_no_fpenvironment
    #define ufc_no_wstring 
    #define ufc_no_sharedmemory
    #define ufc_no_syslogchannel
#elif defined(ufc_os_family_unix)
    //
    // PA-RISC based HP-UX platforms have some issues...
    //
    #if defined(hpux) || defined(_hpux)
    	#if defined(__hppa) || defined(__hppa__)
    		#define ufc_no_sys_select_h 1
    		#if defined(__HP_aCC)
    			#define ufc_no_template_icompare 1
    		#endif
    	#endif
    #endif
#endif

#if defined(_WIN32) && defined(_DLL)
    #if defined(ufc_exports)
        #define ufc_api __declspec(dllexport)
    #else
        #define ufc_api __declspec(dllimport)
    #endif
#else
    #define ufc_api
#endif//defined(_WIN32)

#endif//UFC_BASE_PLATFORM_HPP
