#include <stdbool.h>
#include <stdlib.h>
#include "login.h"
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
		size_t length = strlen(url);
		bool append = !(bool)(url[length - 1] == '/');
		server_url = malloc(length + (size_t)append + 1);
		strcpy(server_url, url);
		if (append)
			strcat(server_url, "/");
	}

	return (bool)curl;
}

void icclient_login(const char *username, const char *password
		, const char *successpage, const char *nextpage
		, const char *failpage)
{
	login(username, password, NULL, "Login", successpage, nextpage, failpage);
}

void icclient_logout()
{
	request(NULL, NULL, NULL, "%s", "logout");
}

void icclient_cleanup()
{
	if (curl) {
		free(server_url);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
