#include <stdlib.h>
#include "icclient/product.h"

void icclient_product_init(struct icclient_product *product)
{
	product->sku = NULL;
	product->description = NULL;
	product->comment = NULL;
	product->thumb = NULL;
	product->image = NULL;
	product->price = .0;
	product->prod_group = NULL;
	product->weight = .0;
	product->author = NULL;
	product->crosssell = NULL;
}

void icclient_product_free(struct icclient_product *product)
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
	product = NULL;
}
