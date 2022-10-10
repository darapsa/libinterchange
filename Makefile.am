lib_LTLIBRARIES = libinterchange.la
libinterchange_la_SOURCES = \
			 interchange.c \
			 request.c \
			 ord.c \
			 login.c \
			 member.c \
			 admin.c
if WASM
libinterchange_la_LDFLAGS = -static
else
libinterchange_la_CPPFLAGS = $(CURL_CFLAGS)
libinterchange_la_LDFLAGS = $(CURL_LIBS)
endif
if IOS
libinterchange_la_LDFLAGS += -static
endif
if STRAP
libinterchange_la_SOURCES += strap.c
libinterchange_la_CPPFLAGS = $(libinterchange_la_CPPFLAGS) $(TIDY_CFLAGS)
endif
include_HEADERS = interchange.h
pkginclude_HEADERS = \
		  interchange/typedefs.h \
		  interchange/ord.h \
		  interchange/member.h \
		  interchange/admin.h
