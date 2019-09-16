#ifndef ICCLIENT_REQUEST_H
#define ICCLIENT_REQUEST_H

#ifdef DEBUG
#ifdef ANDROID
#include <android/log.h>
#else
#include <stdio.h>
#endif // ANDROID
#endif // DEBUG
#include <string.h>
#include <curl/curl.h>

extern CURL *curl;
extern char *server_url;

inline void request(const char *path
		, size_t (*writefunction)(void *, size_t, size_t, void *)
		, void *writedata, struct curl_httppost *post)
{
	char url[strlen(server_url) + strlen(path) + 1];
	sprintf(url, "%s%s", server_url, path);
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
