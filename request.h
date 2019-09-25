#ifndef ICCLIENT_REQUEST_H
#define ICCLIENT_REQUEST_H

#if defined(ANDROID) && defined(DEBUG)
#include <android/log.h>
#endif
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <curl/curl.h>

extern CURL *curl;
extern char *server_url;

inline void request(size_t (*writefunction)(void *, size_t, size_t, void *)
		, void *writedata, struct curl_httppost *post, char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	unsigned int ival;
	size_t length = strlen(server_url) + strlen(fmt);

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
	strcpy(url, server_url);

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

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunction);
	if (writedata)
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, writedata);
	else
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
	if (post)
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
	else
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

#ifdef DEBUG
	CURLcode res =
#endif // DEBUG
		curl_easy_perform(curl);
#ifdef DEBUG
	if (res != CURLE_OK) {
		const char *error = curl_easy_strerror(res);
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_ERROR, "libicclient", "%s: %s"
				, __func__, error);
#else
		fprintf(stderr, "%s: %s\n", __func__, error);
#endif // ANDROID
	}
#endif // DEBUG
}

#endif // ICCLIENT_REQUEST_H
