#ifndef ICCLIENT_LOGIN_H
#define ICCLIENT_LOGIN_H

#include "request.h"

inline void login(const char *username, const char *password, const char *verify,
		const char *click, const char *successpage, const char *nextpage,
		const char *failpage, size_t (*handler)(void *, size_t, size_t, void *),
		void *user)
{
	struct curl_httppost *post, *last = NULL;
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_username",
			CURLFORM_PTRCONTENTS, username,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_password",
			CURLFORM_PTRCONTENTS, password,
			CURLFORM_END);
	if (verify)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "mv_verify",
				CURLFORM_PTRCONTENTS, verify,
				CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_click",
			CURLFORM_PTRCONTENTS, click,
			CURLFORM_END);
	if (successpage)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "mv_successpage",
				CURLFORM_PTRCONTENTS, successpage,
				CURLFORM_END);
	if (nextpage)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "mv_nextpage",
				CURLFORM_PTRCONTENTS, nextpage,
				CURLFORM_END);
	if (failpage)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "mv_failpage",
				CURLFORM_PTRCONTENTS, failpage,
				CURLFORM_END);
	last = NULL;
	request(handler, user, post, "%s", "process");
	curl_formfree(post);
	post = NULL;
}

#endif // ICCLIENT_LOGIN_H
