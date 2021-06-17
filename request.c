#include "request.h"

#ifdef __EMSCRIPTEN__
emscripten_fetch_attr_t attr;
#else
CURL *curl;
size_t append(char *data, size_t size, size_t nmemb, icclient_response *response)
{
	size_t realsize = size * nmemb;
	response->data = realloc(response->data, response->numBytes + realsize + 1);
	memcpy(&(response->data[response->numBytes]), data, realsize);
	response->numBytes += realsize;
	response->data[response->numBytes] = '\0';
	return realsize;
}
#endif

extern inline void init(const char *);
extern inline void request(void (*)(icclient_response *), void (*)(void *), struct body *, char *, ...);
extern inline void cleanup();
