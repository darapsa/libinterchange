#ifndef REQUEST_H
#define REQUEST_H

#include "interchange/typedefs.h"

void request(void (*)(interchange_response *), void (*)(void *),
		const char *[][2], char *, ...);

#endif
