#include <stdlib.h>
#include "request.h"
#include "icclient/product.h"

typedef struct icclient_catalog icclient_catalog;

void icclient_product_freecatalog(icclient_catalog *catalog)
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
