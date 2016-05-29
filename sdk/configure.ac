#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])
AC_INIT([ufc], [1.2.0], [cqli@cufs.com.cn])

#
# set version information
LIBUFC_MAJOR_VERSION=1
LIBUFC_MINOR_VERSION=0
LIBUFC_MICRO_VERSION=0
VERSION=$LIBUFC_MAJOR_VERSION.$LIBUFC_MINOR_VERSION.$LIBUFC_MICRO_VERSION
VERSION_INFO=`expr $LIBUFC_MAJOR_VERSION + $LIBUFC_MINOR_VERSION`:$LIBUFC_MICRO_VERSION:$LIBUFC_MINOR_VERSION

AC_SUBST(VERSION_INFO)
AC_SUBST(LIBUFC_MAJOR_VERSION)
AC_SUBST(LIBUFC_MINOR_VERSION)
AC_SUBST(LIBUFC_MICRO_VERSION)

AC_DEFINE_UNQUOTED([LIBUFC_MAJOR_VERSION],$LIBUFC_MAJOR_VERSION,[Major version])
AC_DEFINE_UNQUOTED([LIBUFC_MINOR_VERSION],$LIBUFC_MINOR_VERSION,[Minor version])
AC_DEFINE_UNQUOTED([LIBUFC_MICRO_VERSION],$LIBUFC_MICRO_VERSION,[Micro version])

#
# Initialize
AM_INIT_AUTOMAKE(ufc, $VERSION)
AC_CONFIG_SRCDIR([source/base/config.cpp])
AC_CONFIG_HEADERS([config.h])
AC_PREFIX_DEFAULT(/usr/local/ufc)

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
# AC_PROG_LIBTOOL
LT_INIT

# Checks for libraries.
#WITH_ICONV=0
#AC_ARG_WITH(iconv, [  --with-iconv[=DIR]        add ICONV support (on)])
#if test "$with_iconv" = "yes" ; then
#    echo Disabling ICONV support
#fi

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_DIRENT
AC_DECL_SYS_SIGLIST
AC_DIR_HEADER
AC_HEADER_SYS_WAIT
#AC_HEADER_VFORK
AC_UNISTD_H
AC_MEMORY_H
AC_HEADER_TIME
AC_HEADER_STAT
AC_SIZEOF_TYPE

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_LONG_LONG_INT
AC_CHECK_SIZEOF([long int])
AC_CHECK_SIZEOF([int])
if test $ac_cv_type_long_long_int = yes; then
  AC_CHECK_SIZEOF([long long int])
fi
AC_C_STRINGIZE
AC_CHECK_HEADERS([wchar.h])

AC_DEFINE([NDEBUG], [1], [Disables Assertions])

# Checks for library functions.
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([memset memcpy memcmp])
AC_CHECK_FUNCS([strchr strcmp strncmp stricmp strnicmp strcasecmp strncasecmp])
AC_CHECK_FUNCS([wcschr wcscmp wcsncmp wcsicmp wcsnicmp wcscasecmp wcsncasecmp])
AC_CHECK_FUNCS([snprintf vsnprintf])
AC_CHECK_FUNCS([_snprintf _vsnprintf])
AC_CHECK_FUNCS([setlocale])
AC_CHECK_FUNCS([strerror])
AC_CHECK_FUNCS([iconv_open])
AC_CHECK_FUNCS([iconv_close])
AC_CHECK_FUNCS([iconv])
AC_CHECK_FUNCS([mbstowcs])
AC_CHECK_FUNCS([wcstombs])

AC_CHECK_LIB([pthread],[main])
AC_CHECK_LIB([dl],[main])
AC_CHECK_LIB([rt],[main])
AC_CHECK_LIB([m],[main])
AC_CHECK_LIB([mqm],[main])


AC_CONFIG_FILES([Makefile
                 include/Makefile
                 include/ufc/Makefile
                 source/Makefile])
AC_OUTPUT
