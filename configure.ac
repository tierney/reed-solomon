#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB
AM_INIT_AUTOMAKE([])

AC_DEFINE(CONFIG_REED_SOLOMON_ENC8, 1, Reed Solomon encoding word length)
AC_DEFINE(CONFIG_REED_SOLOMON_DEC8, 1, Reed Solomon decoding word length)
dnl AC_DEFINE(CONFIG_REED_SOLOMON_ENC16, 1, Reed Solomon encoding word length)
dnl AC_DEFINE(CONFIG_REED_SOLOMON_DEC16, 1, Reed Solomon decoding word length)

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memmove memset])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
