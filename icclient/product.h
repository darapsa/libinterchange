#ifndef ICCLIENT_PRODUCT_H
#define ICCLIENT_PRODUCT_H

struct ic_product {
	char *sku, *description, *comment, *image;
	double price;
};

struct ic_catalog {
	unsigned int length;
	struct ic_product *products[];
};

#ifdef __cplusplus
extern "C" {
#endif

	void icclient_product_all(struct ic_catalog **catalogptr
			, size_t (*callback)(void *contents, size_t size
				, size_t nmemb, void *userdata));
	void rtclient_product_freecatalog(struct ic_catalog *catalog);

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_PRODUCT_H
