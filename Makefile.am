lib_LTLIBRARIES = libinterchange.la
libinterchange_la_SOURCES = \
			 client.c \
			 request.c \
			 ord.c \
			 login.c \
			 member.c \
			 admin.c
libinterchange_la_CPPFLAGS = -I${prefix}/include
if WASM
libinterchange_la_LDFLAGS = -static
else
libinterchange_la_CPPFLAGS += $(CURL_CFLAGS)
libinterchange_la_LDFLAGS = $(CURL_LIBS)
endif
if IOS
libinterchange_la_LDFLAGS += -static
endif
if TIDY
libinterchange_la_SOURCES += handler.c
libinterchange_la_CPPFLAGS += $(TIDY_CFLAGS)
libinterchange_la_LDFLAGS += $(TIDY_LIBS)
endif
include_HEADERS = icclient.h
pkginclude_HEADERS = \
		  icclient/typedefs.h \
		  icclient/ord.h \
		  icclient/member.h \
		  icclient/admin.h
