#include <stdbool.h>
#include <string.h>
#include "request.h"
#include "icclient/product.h"
#include "icclient/catalog.h"
#include "icclient/client.h"

#ifdef __EMSCRIPTEN__
extern void icclient_catalog_results(emscripten_fetch_t *);
#else
extern size_t icclient_catalog_results(void *, size_t, size_t, void *);
#endif

bool icclient_init(const char *url, const char *certificate)
{
	icclient_catalog_init();
	return icclient_request_init(url, certificate);
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
	icclient_request_cleanup();
}
