#ifndef ICCLIENT_LOGIN_H
#define ICCLIENT_LOGIN_H

#include "request.h"

inline void login(const char *username, const char *password, const char *verify, const char *click,
		const char *successpage, const char *nextpage, const char *failpage, void (*handler)(icclient_fetch_t *), void *user)
{
	request(handler, user, &(struct body){ 7, {
			{ "mv_username", username },
			{ "mv_password", password },
			{ "mv_verify", verify },
			{ "mv_click", click },
			{ "mv_successpage", successpage },
			{ "mv_nextpage", nextpage },
			{ "mv_failpage", failpage }
			}}, "%s", "process");
}

#endif
