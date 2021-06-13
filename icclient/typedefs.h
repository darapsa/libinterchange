#ifndef ICCLIENT_TYPEDEFS_H
#define ICCLIENT_TYPEDEFS_H

#ifdef __EMSCRIPTEN__
#include <emscripten/fetch.h>
typedef emscripten_fetch_t icclient_fetch_t;
#else
typedef struct {
	void *userData;
	char *data;
	size_t numBytes;
} icclient_fetch_t;
#endif

#endif
