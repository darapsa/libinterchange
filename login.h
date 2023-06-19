#ifndef INTERCHANGE_LOGIN_H
#define INTERCHANGE_LOGIN_H

#include "request.h"

static inline void login(const char *username, const char *password,
		const char *verify, const char *click, const char *nextpage,
		const char *successpage, const char *failpage,
		void (*handler)(interchange_response *),
		void (*callback)(void *))
{
	const char *body[(verify ? 1 : 0) + (successpage ? 1: 0)
		+ (failpage ? 1 : 0) + 5][2];
	body[0][0] = "mv_username";
	body[0][1] = username;
	body[1][0] = "mv_password";
	body[1][1] = password;
	body[2][0] = "mv_click";
	body[2][1] = click;
	body[3][0] = "mv_nextpage";
	body[3][1] = nextpage;
	size_t i = 4;
	if (successpage) {
		body[i][0] = "mv_successpage";
		body[i++][1] = successpage;
	}
	if (failpage) {
		body[i][0] = "mv_failpage";
		body[i++][1] = failpage;
	}
	if (verify) {
		body[i][0] = "mv_verify";
		body[i++][1] = verify;
	}
	body[i][0] = NULL;
	request(handler, callback, body, "%s", "process");
}

#endif
