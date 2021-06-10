lib_LTLIBRARIES = libicclient.la
libicclient_la_SOURCES = \
			 request.h \
			 request.c \
			 product.c \
			 catalog.c \
			 client.c
if !WASM
libicclient_la_SOURCES += \
			 ord.c \
			 login.h \
			 login.c \
			 member.c \
			 admin.c
endif
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
		  icclient/typedefs.h \
		  icclient/product.h \
		  icclient/catalog.h \
		  icclient/client.h
if !WASM
pkginclude_HEADERS += \
		  icclient/ord.h \
		  icclient/member.h \
		  icclient/admin.h
endif

if !WASM
bin_PROGRAMS = testicclient
testicclient_SOURCES = main.c client.c catalog.c product.c request.c
testicclient_CPPFLAGS = -I${prefix}/include $(DEPS_CFLAGS)
testicclient_LDFLAGS = $(DEPS_LIBS) -lcurl
endif
