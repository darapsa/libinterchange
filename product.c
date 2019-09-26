#include <stdlib.h>
#include "request.h"
#include "icclient/product.h"

void icclient_product_all(struct ic_catalog **catalogptr
		, size_t (*callback)(void *, size_t, size_t, void *))
{
	request(NULL, NULL, NULL, "%s", "All-Products");
}

void rtclient_product_freecatalog(struct ic_catalog *catalog)
{
	for (size_t i = 0; i < catalog->length; i++) {
		struct ic_product *product = catalog->products[i];
		if (product->image)
			free(product->image);
		if (product->comment)
			free(product->comment);
		if (product->description)
			free(product->description);
		if (product->sku)
			free(product->sku);
		free(product);
	}
	free(catalog);
	catalog = NULL;
}
