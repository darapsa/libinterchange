#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "icclient/product.h"
#include "icclient/catalog.h"
#include "icclient/client.h"

CURL *curl = NULL;
char *server_url = NULL;

bool icclient_init(const char *url, const char *certificate)
{
	curl_global_init(CURL_GLOBAL_SSL);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
		if (certificate)
			curl_easy_setopt(curl, CURLOPT_CAINFO, certificate);
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

void icclient_results(const char *prodgroup,
		size_t (*handler)(void *, size_t, size_t, void *),
		struct icclient_catalog **catalogptr)
{
	char nonspaced[strlen(prodgroup) + 1];
	strcpy(nonspaced, prodgroup);
	char *space = NULL;
	while ((space = strchr(nonspaced, ' ')))
		*space = '-';
	request(handler, (void *)catalogptr, NULL, "%s", nonspaced);
}

void icclient_allproducts(size_t (*handler)(void *, size_t, size_t, void *),
		struct icclient_catalog **catalogptr)
{
	request(handler, (void *)catalogptr, NULL, "%s", "All-Products");
}

void icclient_flypage(const char *sku,
		size_t (*handler)(void *, size_t, size_t, void *),
		struct icclient_product **productptr)
{
	request(handler, (void *)productptr, NULL, "%s", sku);
}

void icclient_page(const char *path,
		size_t (*handler)(void *, size_t, size_t, void *),
		void **dataptr)
{
	request(handler, (void *)dataptr, NULL, "%s", path);
}

void icclient_cleanup()
{
	if (curl) {
		free(server_url);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
