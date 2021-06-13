#include <stdbool.h>
#include <string.h>
#include "request.h"
#include "icclient/client.h"

#ifdef __EMSCRIPTEN__
extern void icclient_catalog_results(emscripten_fetch_t *);
#else
extern size_t icclient_catalog_results(void *, size_t, size_t, void *);
#endif

void icclient_init(const char *url, const char *certificate)
{
	icclient_request_init(url, certificate);
}

void icclient_results(const char *prod_group, void (*callback)(struct icclient_catalog *), icclient_handler handler)
{
	char nonspaced[strlen(prod_group) + 1];
	strcpy(nonspaced, prod_group);
	char *space = NULL;
	while ((space = strchr(nonspaced, ' ')))
		*space = '-';
	request(handler, (void *)callback, 0, "%s", nonspaced);
}

void icclient_flypage(const char *sku, icclient_handler handler, struct icclient_product **productptr)
{
	request(handler, (void *)productptr, 0, "%s", sku);
}

void icclient_page(const char *path, icclient_handler handler, void **dataptr)
{
	request(handler, (void *)dataptr, 0, "%s", path);
}

void icclient_free_product(struct icclient_product *product)
{
	if (product->crosssell)
		for (size_t i = 0; i < product->crosssell->length; i++)
			free(product->crosssell->skus[i]);
	if (product->author)
		free(product->author);
	if (product->prod_group)
		free(product->prod_group);
	if (product->image)
		free(product->image);
	if (product->thumb)
		free(product->thumb);
	if (product->comment)
		free(product->comment);
	if (product->description)
		free(product->description);
	free(product->sku);
	free(product);
}

void icclient_free_catalog(struct icclient_catalog *catalog)
{
	for (size_t i = 0; i < catalog->length; i++)
		icclient_free_product(catalog->products[i]);
	free(catalog);
}

void icclient_cleanup()
{
	icclient_request_cleanup();
}
