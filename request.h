#ifndef ICCLIENT_REQUEST_H
#define ICCLIENT_REQUEST_H

#if defined __ANDROID__ && defined DEBUG
#include <android/log.h>
#endif
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#ifndef __EMSCRIPTEN__
#include <curl/curl.h>
#endif
#include "icclient/typedefs.h"

#ifdef __EMSCRIPTEN__
extern emscripten_fetch_attr_t attr;
#else
extern CURL *curl;
extern char *server_url;
#endif

inline void request(icclient_handler writefunction, void *writedata, 
#ifdef __EMSCRIPTEN__
		int
#else
		struct curl_httppost *
#endif
		post, char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	unsigned int ival;
	size_t length =
#ifndef __EMSCRIPTEN__
		strlen(server_url) +
#endif
		strlen(fmt);

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%')
			continue;
		switch(*++p) {
			case 's':
				sval = va_arg(ap, char *);
				length += strlen(sval) - 2;
				break;
			case 'd':
				ival = va_arg(ap, unsigned int);
				do {
					length++;
				} while ((ival /= 10));
				length -= 2;
				break;
			default:
				break;
		}
	}
	va_end(ap);

	char url[length + 1];
#ifdef __EMSCRIPTEN__
	memset(url, 0, length + 1);
#else
	strcpy(url, server_url);
#endif

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%')
			continue;
		switch(*++p) {
			case 's':
				sval = va_arg(ap, char *);
				strcat(url, sval);
				break;
			case 'd':
				ival = va_arg(ap, unsigned int);
				sprintf(url, "%s%d", url, ival);
				break;
			default:
				break;
		}
	}
	va_end(ap);

#ifdef __EMSCRIPTEN__
	attr.onsuccess = writefunction;
#else
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunction);
#endif
	if (writedata)
#ifdef __EMSCRIPTEN__
		attr.userData = writedata;
#else
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, writedata);
	else
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
#endif
	if (post)
#ifdef __EMSCRIPTEN__
		strcpy(attr.requestMethod, "POST");
#else
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
#endif
	else
#ifdef __EMSCRIPTEN__
		strcpy(attr.requestMethod, "GET");
#else
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
#endif

#ifdef __EMSCRIPTEN__
		emscripten_fetch(&attr, url);
#else
#ifdef DEBUG
	CURLcode res =
#endif
		curl_easy_perform(curl);
#ifdef DEBUG
	if (res != CURLE_OK) {
		const char *error = curl_easy_strerror(res);
#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_ERROR, "libicclient.so", "%s: %s", __func__, error);
#else
		fprintf(stderr, "%s: %s\n", __func__, error);
#endif
#endif
	}
#endif
}

#endif
