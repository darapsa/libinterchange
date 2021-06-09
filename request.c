#include "request.h"

extern inline void request(icclient_handler, void *,
#ifdef __EMSCRIPTEN__
		int
#else
		struct curl_httppost *
#endif
		, char *, ...);
