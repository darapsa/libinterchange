lib_LTLIBRARIES = libicclient.la
libicclient_la_SOURCES = \
			 request.h \
			 request.c \
			 product.c \
			 catalog.c \
			 ord.c \
			 login.h \
			 login.c \
			 member.c \
			 admin.c \
			 client.c
libicclient_la_CFLAGS = -I${prefix}/include
libicclient_la_LDFLAGS = $(CURL_LIBS)
if WASM
libicclient_la_LDFLAGS += -static
endif
if IOS
libicclient_la_LDFLAGS += -static
endif
pkginclude_HEADERS = \
		  icclient/product.h \
		  icclient/catalog.h \
		  icclient/ord.h \
		  icclient/member.h \
		  icclient/admin.h \
		  icclient/client.h
