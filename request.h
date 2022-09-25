#ifndef REQUEST_H
#define REQUEST_H

#include "interchange/typedefs.h"

struct body {
	size_t num_pairs;
	struct pair {
		const char *key;
		const char *value;
	} pairs[16];
};

void request(void (*)(interchange_response *), void (*)(void *), struct body *, char *, ...);

#endif
