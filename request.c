#include "request.h"

extern inline void request(size_t (*)(void *, size_t, size_t, void *), void *
		, struct curl_httppost *, char *, ...);
