#ifndef ICCLIENT_ORD_H
#define ICCLIENT_ORD_H

#include "product.h"

struct icclient_item {
	struct icclient_product *product;
	unsigned int quantity;
};

struct icclient_order {
	double subtotal, shipping, totalcost;
	size_t nitems;
	struct icclient_item *items[];
};

#ifdef __cplusplus
extern "C" {
#endif

	void icclient_remove(const unsigned int *indices);
	void icclient_checkout(struct ic_order *order);

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_ORD_H
