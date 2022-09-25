#ifndef INTERCHANGE_ORD_H
#define INTERCHANGE_ORD_H

struct interchange_ord_item {
	struct interchange_product *product;
	unsigned int quantity;
};

struct interchange_ord_order {
	double subtotal;
	double shipping;
	double total_cost;
	char *profile;
	size_t nitems;
	struct interchange_ord_item *items[];
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
void interchange_ord_order(const char *sku, const struct interchange_catalog *catalog,
		struct interchange_ord_order **order);
void interchange_ord_checkout(const struct interchange_ord_order *order, const struct interchange_member *member);
void interchange_ord_free(struct interchange_ord_order *order);

#ifdef __cplusplus
}
#endif

#endif
