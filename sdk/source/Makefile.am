AUTOMAKE_OPTIONS = foreign
AM_CPPFLAGS = -I$(top_srcdir)/include -Dufc_have_ipv6
SUBDIRS =

#
#
lib_LTLIBRARIES = libufc.la

libufc_la_LDFLAGS = -version-info $(VERSION_INFO) -lpthread -ldl -lrt -lm
libufc_la_SOURCES = base/object.cpp \
					base/source_info.cpp \
					base/numeric.cpp \
					datetime/timestamp.cpp \
					datetime/timespan.cpp \
					datetime/time_format.cpp \
					datetime/time_zone.cpp \
					datetime/time_zone_win32.hpp \
					datetime/time_zone_unix.hpp \
					datetime/date.cpp \
					datetime/time.cpp \
					datetime/date_time.cpp \
					datetime/date_time_util.hpp \
					exception/assert.cpp \
					exception/exception.cpp \
					filesystem/file.cpp \
					filesystem/detail/file_win32.hpp \
					filesystem/detail/file_unix.hpp \
					filesystem/path.cpp \
					filesystem/detail/path_win32.hpp \
					filesystem/detail/path_unix.hpp \
					filesystem/fstream.cpp \
					string/string.cpp \
					string/string_builder.cpp \
					string/string_tokenizer.cpp \
					string/string_util.cpp \
					string/codecvt.cpp \
					system/atomic_counter.cpp \
					system/atomic_counter_win32.hpp \
					system/atomic_counter_unix.hpp \
					system/environment.cpp \
					system/environment_win32.hpp \
					system/environment_unix.hpp \
					system/ref_counted_object.cpp \
					thread/mutex.cpp \
					thread/mutex_win32.hpp \
					thread/mutex_posix.hpp \
					thread/event.cpp \
					thread/event_win32.hpp \
					thread/event_posix.hpp \
					thread/rwlock.cpp \
					thread/rwlock_win32.hpp \
					thread/rwlock_posix.hpp \
					thread/semaphore.cpp \
					thread/semaphore_win32.hpp \
					thread/semaphore_posix.hpp \
					thread/condition.cpp \
					thread/runnable.cpp \
					thread/runnable_target.cpp \
					thread/thread.cpp \
					thread/thread_win32.hpp \
					thread/thread_posix.hpp \
					thread/thread_local.cpp \
					thread/thread_local_win32.hpp \
					thread/thread_local_posix.hpp \
					thread/thread_group.cpp \
					thread/thread_pool.cpp \
					network/socketdefs.cpp \
					network/ip_address.cpp \
					network/socket_address.cpp \
					network/host_entry.cpp \
					network/dns.cpp 

