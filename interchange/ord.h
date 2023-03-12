#ifndef INTERCHANGE_ORD_H
#define INTERCHANGE_ORD_H

#include "interchange/typedefs.h"

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

struct interchange_ord_transaction {
	char *order_number;
	char *payment_method;
	double total_cost;
};

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief For putting an item to a cart.
 * \param sku The SKU of the item to order.
 * \param handler A pointer to the function when a custom handler is needed to
 * arrange the data into the order.
 */
void interchange_ord_order(const char *sku,
		void (*handler)(interchange_response *));

/*!
 * \brief For checking out items in the cart.
 * \param order The order to be checked out.
 * \param member The member checking out.
 * \param handler A pointer to the function when a custom handler is needed to
 * arrange the data into the product.
*/
void interchange_ord_checkout(const struct interchange_ord_order *order,
		const struct interchange_member *member,
		void (*handler)(interchange_response *));

void interchange_ord_free_order(struct interchange_ord_order *order);

void interchange_ord_free_transaction(struct interchange_ord_transaction
		*transaction);

#ifdef __cplusplus
}
#endif

#endif
