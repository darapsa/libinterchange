noinst_LIBRARIES = libicclient.a
libicclient_a_SOURCES = \
			icclient/request.h \
			icclient/login.h \
			icclient/client.h \
			request.c \
			login.c \
			client.c

bin_PROGRAMS = icclienttest
icclienttest_SOURCES = main.c
icclienttest_LDADD = libicclient.a
icclienttest_LDFLAGS = -lcurl
