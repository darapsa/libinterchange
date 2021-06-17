#include "request.h"

#ifdef __EMSCRIPTEN__
emscripten_fetch_attr_t attr;
#else
CURL *curl;
size_t append(char *data, size_t size, size_t nmemb, icclient_fetch_t *fetch)
{
	size_t realsize = size * nmemb;
	fetch->data = realloc(fetch->data, fetch->numBytes + realsize + 1);
	memcpy(&(fetch->data[fetch->numBytes]), data, realsize);
	fetch->numBytes += realsize;
	fetch->data[fetch->numBytes] = '\0';
	return realsize;
}
#endif

extern inline void init(const char *);
extern inline void request(void (*)(icclient_fetch_t *), void (*)(void *), struct body *, char *, ...);
extern inline void cleanup();
