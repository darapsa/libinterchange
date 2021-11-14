#ifndef ICCLIENT_TYPEDEFS_H
#define ICCLIENT_TYPEDEFS_H

#include <stddef.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/fetch.h>
typedef emscripten_fetch_t icclient_response;
#else
#include <curl/curl.h>
typedef struct {
	void *userData;
	char *data;
	size_t numBytes;
	CURL *curl;
} icclient_response;
#endif

#endif
