#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "icclient/product.h"
#include "icclient/catalog.h"
#include "icclient/client.h"

#ifdef __EMSCRIPTEN__
emscripten_fetch_attr_t attr;
#else
CURL *curl = NULL;
char *server_url = NULL;
#endif

bool icclient_init(const char *url, const char *certificate)
{
#ifdef __EMSCRIPTEN__
	emscripten_fetch_attr_init(&attr);
	attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
	return true;
#else
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
#endif
}

void icclient_results(const char *prod_group, icclient_handler handler, struct icclient_catalog **catalogptr)
{
	char nonspaced[strlen(prod_group) + 1];
	strcpy(nonspaced, prod_group);
	char *space = NULL;
	while ((space = strchr(nonspaced, ' ')))
		*space = '-';
	request(handler, (void *)catalogptr, 0, "%s", nonspaced);
}

void icclient_allproducts(icclient_handler handler, struct icclient_catalog **catalogptr)
{
	request(handler, (void *)catalogptr, 0, "%s", "All-Products");
}

void icclient_flypage(const char *sku, icclient_handler handler, struct icclient_product **productptr)
{
	request(handler, (void *)productptr, 0, "%s", sku);
}

void icclient_page(const char *path, icclient_handler handler, void **dataptr)
{
	request(handler, (void *)dataptr, 0, "%s", path);
}

void icclient_cleanup()
{
#ifndef __EMSCRIPTEN__
	if (curl) {
		free(server_url);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
#endif
}
