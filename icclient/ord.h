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
	char *profile;
	size_t nitems;
	struct icclient_ord_item *items[];
};

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief For putting an item to a cart.
 * \param sku The SKU of the item to order.
 * \param catalog The catalog from which the item is.
 * \param order The address of an order instance.
 */
void icclient_ord_order(const char *sku, const struct icclient_catalog *catalog,
		struct icclient_ord_order **order);
void icclient_ord_checkout(const struct icclient_ord_order *order, const struct icclient_member *member);
void icclient_ord_free(struct icclient_ord_order *order);

#ifdef __cplusplus
}
#endif

#endif
