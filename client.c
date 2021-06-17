#include "request.h"
#include "icclient.h"

char *sampleurl;
char *image_dir;

extern void handle_results(icclient_fetch_t *fetch);

void icclient_init(const char *url, const char *dir, const char *certificate)
{
	size_t length = strlen(url);
	size_t append = url[length - 1] != '/';
	sampleurl = malloc(length + append + 1);
	strcpy(sampleurl, url);
	if (append)
		strcat(sampleurl, "/");
	image_dir = malloc(strlen(dir) + 1);
	strcpy(image_dir, dir);
	init(certificate);
}

void icclient_results(const char *prod_group, void (*handler)(icclient_fetch_t *), void (*callback)(struct icclient_catalog *))
{
	char nonspaced[strlen(prod_group) + 1];
	strcpy(nonspaced, prod_group);
	char *space = NULL;
	while ((space = strchr(nonspaced, ' ')))
		*space = '-';
	request(handler ? handler : handle_results, (void *)callback, 0, "%s", nonspaced);
}

void icclient_flypage(const char *sku, void (*handler)(icclient_fetch_t *), struct icclient_product **productptr)
{
	request(handler, (void *)productptr, 0, "%s", sku);
}

void icclient_page(const char *path, void (*handler)(icclient_fetch_t *), void **dataptr)
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
#ifndef __EMSCRIPTEN__
	cleanup();
#endif
}
