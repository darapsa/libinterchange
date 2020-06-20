#include <stdlib.h>
#include "icclient/product.h"
#include "icclient/catalog.h"

void icclient_catalog_free(struct icclient_catalog *catalog)
{
	for (size_t i = 0; i < catalog->length; i++)
		icclient_product_free(catalog->products[i]);
	free(catalog);
	catalog = NULL;
}
