#include "login.h"

extern inline void login(size_t (*handler)(void *contents, size_t size
			, size_t nmemb, void *userdata), struct icclient_user *user
		, const char *, const char *, const char *, const char *
		, const char *, const char *, const char *);
