#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([reed-solomon], [1.0], [tierney@cs.nyu.edu])
AC_CONFIG_SRCDIR([src/reed_solomon.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects dist-xz no-dist-gzip])
AM_SILENT_RULES([yes])
AC_USE_SYSTEM_EXTENSIONS

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

# Ensure C++11 support for RsCodec
CXXFLAGS="$CXXFLAGS -std=c++11"

LT_INIT([])

AC_DEFINE(CONFIG_REED_SOLOMON_ENC8, 1, Reed Solomon encoding word length)
AC_DEFINE(CONFIG_REED_SOLOMON_DEC8, 1, Reed Solomon decoding word length)
dnl AC_DEFINE(CONFIG_REED_SOLOMON_ENC16, 1, Reed Solomon encoding word length)
dnl AC_DEFINE(CONFIG_REED_SOLOMON_DEC16, 1, Reed Solomon decoding word length)

# Compiler hardening flags (opt-in/opt-out).
AC_ARG_ENABLE([strict-warnings],
  AS_HELP_STRING([--disable-strict-warnings],
                 [disable -Wall/-Wextra/-Wpedantic]),
  [],
  [enable_strict_warnings=yes])

WARN_CFLAGS=""
WARN_CXXFLAGS=""
if test "x$enable_strict_warnings" = "xyes"; then
  WARN_CFLAGS="-Wall -Wextra -Wpedantic"
  WARN_CXXFLAGS="-Wall -Wextra -Wpedantic"
fi
AC_SUBST([WARN_CFLAGS])
AC_SUBST([WARN_CXXFLAGS])

AC_ARG_ENABLE([sanitizers],
  AS_HELP_STRING([--enable-sanitizers],
                 [enable address+undefined sanitizers]),
  [],
  [enable_sanitizers=no])

SAN_CFLAGS=""
SAN_CXXFLAGS=""
SAN_LDFLAGS=""
if test "x$enable_sanitizers" = "xyes"; then
  SAN_CFLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer"
  SAN_CXXFLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer"
  SAN_LDFLAGS="-fsanitize=address,undefined"
fi
AC_SUBST([SAN_CFLAGS])
AC_SUBST([SAN_CXXFLAGS])
AC_SUBST([SAN_LDFLAGS])

save_LIBS="$LIBS"
AC_SEARCH_LIBS([pthread_mutex_lock], [pthread], [],
               [AC_MSG_ERROR([pthread library not found])])
if test "x$ac_cv_search_pthread_mutex_lock" = "xnone required"; then
  PTHREAD_LIBS=""
else
  PTHREAD_LIBS="$ac_cv_search_pthread_mutex_lock"
fi
LIBS="$save_LIBS"
AC_SUBST([PTHREAD_LIBS])

# Checks for header files.
AC_CHECK_HEADERS([errno.h pthread.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memmove memset])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
