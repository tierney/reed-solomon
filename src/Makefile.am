noinst_PROGRAMS = rs_main

rs_main_SOURCES = rs_main.cc
rs_main_LDADD = -lm -lpthread librs.la

lib_LTLIBRARIES = librs.la
librs_la_SOURCES = reed_solomon.c list.h rslib.h encode_rs.h decode_rs.h

lib_LTLIBRARIES += librs_codec.la
librs_codec_la_SOURCES = rs_codec.h rs_codec.cc
