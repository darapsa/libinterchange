#ifndef INTERCHANGE_LOGIN_H
#define INTERCHANGE_LOGIN_H

#include "request.h"

static inline void login(const char *username, const char *password,
		const char *verify, const char *click, const char *nextpage,
		const char *successpage, const char *failpage,
		void (*handler)(interchange_response *),
		void (*callback)(void *))
{
	request(handler, callback, (const char *[][2]){
			"mv_username", username,
			"mv_password", password,
			"mv_verify", verify,
			"mv_click", click,
			"mv_nextpage", nextpage,
			"mv_successpage", successpage,
			"mv_failpage", failpage,
			NULL
			}, "%s", "process");
}

#endif
