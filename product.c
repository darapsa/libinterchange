#include <stdlib.h>
#include "icclient/request.h"
#include "icclient/product.h"

void icclient_product_all(struct ic_catalog **catalogptr
		, size_t (*callback)(void *, size_t, size_t, void *))
{
	request("All-Products", callback, (void *)catalogptr,  NULL);
}

void rtclient_product_freecatalog(struct ic_catalog *catalog)
{
	for (unsigned short i = 0; i < catalog->length; i++) {
		struct ic_product *product = catalog->products[i];
		free(product->image);
		free(product->comment);
		free(product->description);
		free(product->sku);
		free(product);
	}
	free(catalog);
	catalog = NULL;
}
