#include <stdlib.h>
#include "icclient/product.h"

void icclient_product_free(struct icclient_product *product)
{
	if (product->author)
		free(product->author);
	if (product->prodgroup)
		free(product->prodgroup);
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
