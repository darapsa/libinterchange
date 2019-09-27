noinst_LIBRARIES = libicclient.a
libicclient_a_SOURCES = \
			icclient/request.h \
			icclient/login.h \
			icclient/product.h \
			icclient/ord.h \
			icclient/member.h \
			icclient/admin.h \
			icclient/client.h \
			request.c \
			login.c \
			product.c \
			member.c \
			admin.c \
			client.c
libicclient_a_CFLAGS = -fPIC

bin_PROGRAMS = icclienttest
icclienttest_SOURCES = main.c
icclienttest_LDADD = libicclient.a
icclienttest_LDFLAGS = -lcurl
