#ifndef INTERCHANGE_LOGIN_H
#define INTERCHANGE_LOGIN_H

#include "request.h"

static inline void login(const char *username, const char *password,
		const char *verify, const char *click, const char *nextpage,
		const char *failpage, void (*handler)(interchange_response *),
		void (*callback)(void *))
{
	request(handler, callback, &(struct body){ 4 + (nextpage ? 1 : 0)
			+ (failpage ? 1 : 0), {
			{ "mv_username", username },
			{ "mv_password", password },
			{ "mv_verify", verify },
			{ "mv_click", click },
			{ "mv_nextpage", nextpage },
			{ "mv_failpage", failpage },
			}}, "%s", "process");
}

#endif
