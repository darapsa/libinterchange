#ifndef ICCLIENT_TYPEDEFS_H
#define ICCLIENT_TYPEDEFS_H

#ifdef __cplusplus
#include <cstddef>
#endif

#ifdef __EMSCRIPTEN__

#include <emscripten/fetch.h>

typedef emscripten_fetch_t icclient_fetch_t;
typedef char icclient_post;

#else

#include <curl/curl.h>

typedef struct {
	void *userData;
	char *data;
	size_t numBytes;
} icclient_fetch_t;
typedef struct curl_httppost icclient_post;

#endif

struct icclient_post_callback {
	icclient_post *post;
	void (*callback)(void *);
};

#endif
