/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : network/socketdefs.hpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-25
  Description: 
  History    : 
*******************************************************************************/
#ifndef NETWORK_SOCKETDEFS_HPP
#define NETWORK_SOCKETDEFS_HPP

#include "ufc/core/standard.hpp"
#include <cerrno>
#include <cstring>
#if defined(WIN32) || defined(_WIN32)
# include <WinSock2.h>
#else
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# if defined(hpux) || defined(_hpux)
#  include <sys/select.h>
# endif
# include <sys/ioctl.h>
# if defined(__VMS)
#  include <inet.h>
# else
#  include <arpa/inet.h>
# endif
# include <netinet/in.h>
# include <netinet/tcp.h>
# include <netdb.h>
# include <net/if.h>
# if defined(sun) || defined(__APPLE__)
#  include <sys/sockio.h>
#  include <sys/filio.h>
# endif
#endif

#endif//NETWORK_SOCKETDEFS_HPP
