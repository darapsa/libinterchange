#ifndef INTERCHANGE_TYPEDEFS_H
#define INTERCHANGE_TYPEDEFS_H

#include <stddef.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/fetch.h>
typedef emscripten_fetch_t interchange_response;
#else
#include <curl/curl.h>
typedef struct {
	void *userData;
	char *url;
	char *data;
	size_t numBytes;
	CURL *curl;
} interchange_response;
#endif

#endif
