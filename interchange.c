#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "interchange.h"

char *image_dir;
#ifdef __EMSCRIPTEN__
emscripten_fetch_attr_t attr;
#else
char *sampleurl;
char *cookiefile = NULL;
char *cainfo = NULL;
#endif

#ifdef ENABLE_STRAP
extern void handle_results(interchange_response *);
#endif

void interchange_init(const char *url, const char *dir, const char *cookie,
		const char *certificate)
{
	image_dir = malloc(strlen(dir) + 1);
	strcpy(image_dir, dir);
#ifdef __EMSCRIPTEN__
	emscripten_fetch_attr_init(&attr);
	attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
#else
	size_t length = strlen(url);
	size_t append = url[length - 1] != '/';
	sampleurl = malloc(length + append + 1);
	strcpy(sampleurl, url);
	if (append)
		strcat(sampleurl, "/");
	curl_global_init(CURL_GLOBAL_SSL);
	if (cookie) {
		cookiefile = malloc(strlen(cookie) + 1);
		strcpy(cookiefile, cookie);
	}
	if (certificate) {
		cainfo = malloc(strlen(certificate) + 1);
		strcpy(cainfo, certificate);
	}
#endif
}

void interchange_page(const char *path, void (*parser)(interchange_response *))
{
	char nonspaced[strlen(path) + 1];
	strcpy(nonspaced, path);
	char *space = NULL;
	while ((space = strchr(nonspaced, ' ')))
		*space = '-';
	request(parser, NULL, NULL, "%s", nonspaced);
}

void interchange_catalog(const char *prod_group, void (*handler)(interchange_response *), void (*callback)(struct interchange_catalog *))
{
	char nonspaced[strlen(prod_group) + 1];
	strcpy(nonspaced, prod_group);
	char *space = NULL;
	while ((space = strchr(nonspaced, ' ')))
		*space = '-';
#ifdef ENABLE_STRAP
	request(handler ? handler : handle_results, (void (*)(void *))callback, NULL, "%s", nonspaced);
#else
	request(handler, (void (*)(void *))callback, NULL, "%s", nonspaced);
#endif
}

void interchange_product(const char *sku, void (*handler)(interchange_response *), void (*callback)(struct interchange_product *))
{
	request(handler, (void (*)(void *))callback, NULL, "%s", sku);
}

void interchange_clear_product(struct interchange_product *product)
{
	if (product->crosssell)
		for (size_t i = 0; i < product->crosssell->length; i++)
			free(product->crosssell->skus[i]);
	if (product->author)
		free(product->author);
	if (product->category)
		free(product->category);
	if (product->prod_group)
		free(product->prod_group);
	if (product->image)
		free(product->image);
	if (product->thumb)
		free(product->thumb);
	if (product->comment)
		free(product->comment);
	if (product->title)
		free(product->title);
	if (product->description)
		free(product->description);
	free(product->sku);
}

void interchange_free_catalog(struct interchange_catalog *catalog)
{
	for (size_t i = 0; i < catalog->length; i++)
		interchange_clear_product(&catalog->products[i]);
	free(catalog);
}

void interchange_free_response(interchange_response *response)
{
	if (response->userData)
		free(response->userData);
#ifdef __EMSCRIPTEN__
	emscripten_fetch_close(response);
#else
	free(response->url);
	free(response->data);
	curl_easy_cleanup(response->curl);
	free(response);
#endif
}

void interchange_cleanup()
{
	free(image_dir);
#ifndef __EMSCRIPTEN__
	if (cainfo)
		free(cainfo);
	if (cookiefile)
		free(cookiefile);
	free(sampleurl);
	curl_global_cleanup();
#endif
}
