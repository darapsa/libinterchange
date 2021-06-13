#include "request.h"

#ifdef __EMSCRIPTEN__
emscripten_fetch_attr_t attr;
#else
CURL *curl;
char *server_url;
#endif

extern inline void icclient_request_init(const char *, const char *);
extern inline void request(icclient_handler, void *, struct icclient_request_data *, char *, ...);
extern inline void icclient_request_cleanup();
