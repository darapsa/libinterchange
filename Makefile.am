noinst_LIBRARIES = libicclient.a
libicclient_a_SOURCES = \
			icclient/product.h \
			icclient/catalog.h \
			icclient/ord.h \
			icclient/member.h \
			icclient/admin.h \
			icclient/client.h \
			request.h \
			request.c \
			login.h \
			login.c \
			ord.c \
			member.c \
			admin.c \
			client.c

bin_PROGRAMS = icclienttest
icclienttest_SOURCES = main.c
icclienttest_LDADD = libicclient.a
icclienttest_LDFLAGS = -lcurl
