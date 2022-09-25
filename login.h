#ifndef INTERCHANGE_LOGIN_H
#define INTERCHANGE_LOGIN_H

#include "request.h"

static inline void login(const char *username, const char *password, const char *verify, const char *click,
		void (*handler)(interchange_response *), void (*callback)(void *))
{
	request(handler, callback, &(struct body){ 4, {
			{ "mv_username", username },
			{ "mv_password", password },
			{ "mv_verify", verify },
			{ "mv_click", click },
			}}, "%s", "process");
}

#endif
