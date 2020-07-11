#include "login.h"

extern inline void login(size_t (*)(void *, size_t, size_t, void *),
		struct icclient_member *, const char *, const char *, const char *,
		const char *, const char *, const char *, const char *);
