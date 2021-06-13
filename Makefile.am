lib_LTLIBRARIES = libicclient.la
libicclient_la_SOURCES = \
			 client.c \
			 request.h \
			 request.c \
			 ord.c \
			 login.h \
			 login.c \
			 member.c \
			 admin.c
libicclient_la_CPPFLAGS = -I${prefix}/include
if WASM
libicclient_la_LDFLAGS = -static
else
libicclient_la_LDFLAGS = -lcurl
endif
if IOS
libicclient_la_LDFLAGS += -static
endif
pkginclude_HEADERS = \
		  icclient/client.h \
		  icclient/typedefs.h \
		  icclient/ord.h \
		  icclient/member.h \
		  icclient/admin.h
