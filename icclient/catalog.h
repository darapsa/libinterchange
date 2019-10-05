#ifndef ICCLIENT_CATALOG_H
#define ICCLIENT_CATALOG_H

struct icclient_catalog {
	size_t length;
	struct icclient_product *products[];
};

#endif // ICCLIENT_CATALOG_H
