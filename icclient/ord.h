#ifndef ICCLIENT_ORD_H
#define ICCLIENT_ORD_H

struct icclient_ord_item {
	struct icclient_product *product;
	unsigned int quantity;
};

struct icclient_ord_order {
	double subtotal;
	double shipping;
	double total_cost;
	size_t nitems;
	struct icclient_ord_item *items[];
};

#ifdef __cplusplus
extern "C" {
#endif

	void icclient_ord_free(struct icclient_ord_order *order);

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_ORD_H
