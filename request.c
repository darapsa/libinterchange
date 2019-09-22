#include "request.h"

extern inline void request(size_t (*writefunction)(void *, size_t, size_t, void *)
		, void *writedata, struct curl_httppost *post, char *fmt, ...);
