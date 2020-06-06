ACLOCAL_AMFLAGS = -I m4
lib_LTLIBRARIES = libicclient.la
libicclient_la_SOURCES = \
			 request.h \
			 request.c \
			 login.h \
			 login.c \
			 ord.c \
			 member.c \
			 admin.c \
			 client.c
pkginclude_HEADERS = \
		  icclient/product.h \
		  icclient/catalog.h \
		  icclient/ord.h \
		  icclient/member.h \
		  icclient/admin.h \
		  icclient/client.h

libicclient_la_LDFLAGS = -lcurl

#bin_PROGRAMS = icclienttest
#icclienttest_SOURCES = main.c
#icclienttest_LDADD = libicclient.la
#icclienttest_LDFLAGS = -lcurl
