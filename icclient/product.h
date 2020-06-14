#ifndef ICCLIENT_PRODUCT_H
#define ICCLIENT_PRODUCT_H

struct icclient_product {
	char *sku;
	char *description;
	char *comment;
	char *image;
	double price;
	double weight;
	char *author;
};

#endif // ICCLIENT_PRODUCT_H
