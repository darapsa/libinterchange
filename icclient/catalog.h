#ifndef ICCLIENT_CATALOG_H
#define ICCLIENT_CATALOG_H

struct icclient_catalog {
	size_t length;
	struct icclient_product *products[];
};

struct icclient_catalog_callback {
	struct icclient_catalog **catalog;
	void (*callback)(struct icclient_catalog *);
};

#ifdef __cplusplus
extern "C" {
#endif

	void icclient_catalog_init();
	void icclient_catalog_free(struct icclient_catalog *catalog);

#ifdef __cplusplus
}
#endif

#endif
