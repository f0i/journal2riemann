AC_INIT(journal2riemann, 0.0.0, arnaud.wetzel@kbrwadventure.com)
AC_PREREQ(2.52)

AC_CONFIG_SRCDIR([src/main.c])
AM_CONFIG_HEADER(src/config.h)
AC_CONFIG_MACRO_DIR([m4])

AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_TYPE_INT64_T
AC_TYPE_SSIZE_T

AC_PROG_CC
PKG_PROG_PKG_CONFIG

#AC_CHECK_HEADERS([arpa/inet.h netdb.h stdlib.h sys/socket.h])
#AC_CHECK_FUNCS([memset socket strcasecmp strchr strdup strerror])

PKG_CHECK_MODULES([RIEMANN_CLIENT], riemann-client)
PKG_CHECK_MODULES([LIBSYSTEMD], libsystemd)

AM_INIT_AUTOMAKE(1.6 dist-bzip2)
AC_OUTPUT([Makefile])
