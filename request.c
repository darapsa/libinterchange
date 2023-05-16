#if defined __ANDROID__ && defined DEBUG
#include <android/log.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "request.h"

#ifdef __EMSCRIPTEN__

extern emscripten_fetch_attr_t attr;

#else

#include <pthread.h>
#include <curl/curl.h>

extern char *sampleurl;
extern char *cainfo;
extern char *cookiefile;

struct container {
	struct curl_httppost *post;
	void (*handler)(interchange_response *);
	interchange_response *response;
};

static size_t append(char *data, size_t size, size_t nmemb, interchange_response *response)
{
	size_t realsize = size * nmemb;
	response->data = realloc(response->data, response->numBytes + realsize + 1);
	memcpy(&(response->data[response->numBytes]), data, realsize);
	response->numBytes += realsize;
	response->data[response->numBytes] = '\0';
	return realsize;
}

static void *async(void *arg)
{
	struct container *container = (struct container *)arg;
	CURLcode res = curl_easy_perform(container->response->curl);
	if (container->post)
		curl_formfree(container->post);
	if (res == CURLE_OK && container->handler)
		container->handler(container->response);
	else {
#ifdef DEBUG
		const char *error = curl_easy_strerror(res);
#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_ERROR, "libinterchange.so", "%s", error);
#else
		fprintf(stderr, "%s\n", error);
#endif
#endif
	}
	free(container);
	return NULL;
}
#endif

void request(void (*handler)(interchange_response *), void (*callback)(void *),
		const char *body[][2], char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	unsigned int ival;
	size_t length =
#ifndef __EMSCRIPTEN__
		strlen(sampleurl) +
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
	memset(url, '\0', length + 1);
#else
	strcpy(url, sampleurl);
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
	if (handler)
		attr.onsuccess = handler;
	if (body) {
		size_t length = 0;
		char *post = malloc(1);
		memset(post, '\0', 1);
		size_t i = 0;
		const char **pair = *body;
		while (pair[0] && pair[1]) {
			length += strlen(pair[0]) + strlen(pair[1])
				+ (i ? 1 : 0) + 1;
			post = realloc(post, length + 1);
			if (i++)
				strcat(post, "&");
			sprintf(post, "%s%s=%s", post, pair[0], pair[1]);
			if (!strncmp(pair[0], "quantity", 8))
				free((void *)pair[1]);
			pair = *++body;
		}
		strcpy(attr.requestMethod, "POST");
		static const char *headers[] = { "Content-Type",
			"application/x-www-form-urlencoded", NULL };
		attr.requestHeaders = headers;
		attr.requestData = post;
		attr.requestDataSize = length + 1;
		attr.userData = post;
	} else {
		strcpy(attr.requestMethod, "GET");
		attr.userData = callback;
	}
	emscripten_fetch(&attr, url);
#else
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookiefile);
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookiefile);
	if (cainfo)
		curl_easy_setopt(curl, CURLOPT_CAINFO, cainfo);
#ifdef DEBUG
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, append);
	interchange_response *response = malloc(sizeof(interchange_response));
	response->url = malloc(length + 1);
	strcpy(response->url, url);
	response->data = malloc(1);
	response->numBytes = 0;
	response->userData = callback;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
	struct curl_httppost *post = NULL;
	struct curl_httppost *last = NULL;
	if (body) {
		const char **pair = *body;
		while (pair[0] && pair[1]) {
			curl_formadd(&post, &last, CURLFORM_COPYNAME, pair[0],
					CURLFORM_COPYCONTENTS, pair[1],
					CURLFORM_END);
			if (!strncmp(pair[0], "quantity", 8))
				free((void *)pair[1]);
			pair = *++body;
		}
		last = NULL;
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
	} else
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
	struct container *container = malloc(sizeof(struct container));
	response->curl = curl;
	container->post = post;
	container->handler = handler;
	container->response = response;
	pthread_t thread;
	pthread_create(&thread, NULL, async, container);
#endif
}
