AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)/src
AM_CFLAGS = $(WARN_CFLAGS) $(SAN_CFLAGS)
AM_LDFLAGS = $(SAN_LDFLAGS)

check_PROGRAMS = rs255_223_test golden_vectors_test random_test
TESTS = $(check_PROGRAMS)

rs255_223_test_SOURCES = rs255_223_test.c
rs255_223_test_LDADD = ../src/librs.la $(PTHREAD_LIBS)

golden_vectors_test_SOURCES = golden_vectors_test.c
golden_vectors_test_LDADD = ../src/librs.la $(PTHREAD_LIBS)

random_test_SOURCES = random_test.c
random_test_LDADD = ../src/librs.la $(PTHREAD_LIBS)
