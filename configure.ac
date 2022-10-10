AC_INIT([interchange], [0.0], [prabowo@darapsa.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT
AC_ARG_ENABLE([strap],
	      [AS_HELP_STRING([--enable-strap],
			      [enable Strap template parsing with libtidy])],
			      [PKG_CHECK_MODULES([TIDY], [tidy])
			      AC_DEFINE([ENABLE_STRAP], [1],
					[Define to 1 if you enable Strap.])],
			      [enable_strap=no])
AM_CONDITIONAL([STRAP], [test "x$enable_strap" = xyes])
AC_CANONICAL_HOST
case $host_cpu in
	*wasm* ) wasm=true;;
	*) wasm=false;;
esac
AM_CONDITIONAL([WASM], [test "x$wasm" = xtrue])
AS_IF([test "x$wasm" != xtrue],
      [PKG_CHECK_MODULES([CURL], [libcurl])])
case $host in
	*arm*apple-darwin1* ) ios=true;;
	*) ios=false;;
esac
AM_CONDITIONAL([IOS], [test "x$ios" = xtrue])
AC_CHECK_HEADERS([stddef.h, locale.h])
AC_CHECK_HEADERS([threads.h],
		 [AC_DEFINE([HAVE_THREADS_H])])
AC_CHECK_HEADERS([langinfo.h],
		 [AC_DEFINE([HAVE_LANGINFO_H])])
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_CHECK_FUNCS([memset strchr strrchr strstr])
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
