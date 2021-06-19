#ifndef REQUEST_H
#define REQUEST_H

#include <stddef.h>
#include "icclient/typedefs.h"

struct body {
	size_t num_pairs;
	struct pair {
		const char *key;
		const char *value;
	} pairs[16];
};

void request(void (*)(icclient_response *), void (*)(void *), struct body *, char *, ...);

#endif
