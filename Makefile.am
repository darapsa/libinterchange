lib_LTLIBRARIES = libicclient.la
libicclient_la_SOURCES = \
			 client.c \
			 request.h \
			 request.c \
			 catalog.c \
			 product.c \
			 ord.c \
			 login.h \
			 login.c \
			 member.c \
			 admin.c
libicclient_la_CPPFLAGS = -I${prefix}/include $(DEPS_CFLAGS)
if WASM
libicclient_la_LDFLAGS = -static
else
libicclient_la_LDFLAGS = $(DEPS_LIBS) -lcurl
endif
if IOS
libicclient_la_LDFLAGS += -static
endif
pkginclude_HEADERS = \
		  icclient/client.h \
		  icclient/catalog.h \
		  icclient/product.h \
		  icclient/typedefs.h \
		  icclient/ord.h \
		  icclient/member.h \
		  icclient/admin.h
#if !WASM
#bin_PROGRAMS = icclient
#icclient_SOURCES = main.c client.c catalog.c product.c request.c ord.c login.c member.c admin.c
#icclient_CPPFLAGS = -I${prefix}/include $(DEPS_CFLAGS)
#icclient_LDFLAGS = $(DEPS_LIBS) -lcurl
#endif
