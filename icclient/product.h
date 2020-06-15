#ifndef ICCLIENT_PRODUCT_H
#define ICCLIENT_PRODUCT_H

struct icclient_product {
	char *sku;
	char *description;
	char *comment;
	char *image;
	double price;
	char *prod_group;
	double weight;
	char *author;
};

#endif // ICCLIENT_PRODUCT_H
