#ifndef ICCLIENT_TYPEDEFS_H
#define ICCLIENT_TYPEDEFS_H

#ifdef __EMSCRIPTEN__
#include <emscripten/fetch.h>
typedef void (*icclient_handler)(emscripten_fetch_t *);
#else
typedef size_t (*icclient_handler)(void *, size_t, size_t, void *);
#endif

#endif
