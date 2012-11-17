noinst_PROGRAMS = rs_main

rs_main_SOURCES = rs_main.cc
rs_main_LDADD = -lm -lpthread librs.a

noinst_LIBRARIES = librs.a
librs_a_SOURCES = reed_solomon.c list.h rslib.h encode_rs.h decode_rs.h

noinst_LIBRARIES += librs_codec.a
librs_codec_a_SOURCES = rs_codec.h rs_codec.cc
