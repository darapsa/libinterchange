#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "icclient/product.h"
#include "icclient/catalog.h"
#include "icclient/client.h"

#ifdef __EMSCRIPTEN__
emscripten_fetch_attr_t attr;
extern void icclient_catalog_results(emscripten_fetch_t *);
#else
CURL *curl = NULL;
char *server_url = NULL;
extern size_t icclient_catalog_results(void *, size_t, size_t, void *);
#endif

bool icclient_init(const char *url, const char *certificate)
{
	icclient_catalog_init();
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

void icclient_results(const char *prod_group,
		void (*callback)(struct icclient_catalog *), struct icclient_catalog **catalog, icclient_handler handler)
{
	char nonspaced[strlen(prod_group) + 1];
	strcpy(nonspaced, prod_group);
	char *space = NULL;
	while ((space = strchr(nonspaced, ' ')))
		*space = '-';
	struct icclient_catalog_callback *catalog_callback = malloc(sizeof(struct icclient_catalog_callback));
	catalog_callback->catalog = catalog;
	catalog_callback->callback = callback;
	request(handler ? handler : icclient_catalog_results, (void *)catalog_callback, 0, "%s", nonspaced);
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
