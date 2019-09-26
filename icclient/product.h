#ifndef ICCLIENT_PRODUCT_H
#define ICCLIENT_PRODUCT_H

struct icclient_product {
	char *sku, *description, *comment, *image;
	double price;
};

struct icclient_catalog {
	size_t length;
	struct icclient_product *products[];
};

#ifdef __cplusplus
extern "C" {
#endif

	void icclient_product_all(struct icclient_catalog **catalogptr
			, size_t (*callback)(void *contents, size_t size
				, size_t nmemb, void *userdata));
	void icclient_product_freecatalog(struct icclient_catalog *catalog);

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_PRODUCT_H
