#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "icclient/client.h"

CURL *curl = NULL;
char *server_url = NULL;

bool icclient_init(const char *url)
{
	curl_global_init(CURL_GLOBAL_SSL);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
#ifdef DEBUG
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
		server_url = malloc(strlen(url) + 1);
		strcpy(server_url, url);
	}

	return (bool)curl;
}

void icclient_cleanup()
{
	if (curl) {
		free(server_url);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
