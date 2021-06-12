#ifndef ICCLIENT_CATALOG_H
#define ICCLIENT_CATALOG_H

struct icclient_catalog {
	size_t length;
	struct icclient_product *products[];
};

#ifdef __cplusplus
extern "C" {
#endif

	void icclient_catalog_free(struct icclient_catalog *catalog);

#ifdef __cplusplus
}
#endif

#endif
