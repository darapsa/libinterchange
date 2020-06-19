#ifndef ICCLIENT_PRODUCT_H
#define ICCLIENT_PRODUCT_H

struct icclient_product_crosssell {
	size_t length;
	char *skus[];
};

struct icclient_product {
	char *sku;
	char *description;
	char *comment;
	char *thumb;
	char *image;
	double price;
	char *prodgroup;
	double weight;
	char *author;
	struct icclient_product_crosssell *crosssell;
};

#endif // ICCLIENT_PRODUCT_H
