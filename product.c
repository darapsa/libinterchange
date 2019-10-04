#include <stdlib.h>
#include "icclient/product.h"

void icclient_catalog_free(struct icclient_catalog *catalog)
{
	for (size_t i = 0; i < catalog->length; i++) {
		struct icclient_product *product = catalog->products[i];
		if (product->image)
			free(product->image);
		if (product->comment)
			free(product->comment);
		if (product->description)
			free(product->description);
		free(product->sku);
		free(product);
	}
	free(catalog);
	catalog = NULL;
}
