AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)/src
AM_CFLAGS = $(WARN_CFLAGS) $(SAN_CFLAGS)
AM_CXXFLAGS = $(WARN_CXXFLAGS) $(SAN_CXXFLAGS)
AM_LDFLAGS = $(SAN_LDFLAGS)

noinst_PROGRAMS = rs_main

rs_main_SOURCES = rs_main.cc
rs_main_LDADD = $(PTHREAD_LIBS) librs.la

lib_LTLIBRARIES = librs.la
librs_la_SOURCES = reed_solomon.c list.h rslib.h encode_rs.h decode_rs.h

lib_LTLIBRARIES += librs_codec.la
librs_codec_la_SOURCES = rs_codec.h rs_codec.cc
librs_codec_la_LIBADD = librs.la

include_HEADERS = rslib.h rs_codec.h
