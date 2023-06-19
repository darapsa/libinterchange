#ifndef INTERCHANGE_ORD_H
#define INTERCHANGE_ORD_H

#include "interchange/typedefs.h"

struct interchange_ord_item {
	struct interchange_product product;
	unsigned int quantity;
	char *name;
};

struct interchange_ord_order {
	double subtotal;
	double shipping;
	double total_cost;
	char *profile;
	size_t nitems;
	struct interchange_ord_item **items;
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
 * \param sku The product or variant SKU of the item to order.
 * \param item The product SKU of the item to order.
 * \param quantity The quantity of the item to order.
 * \param options Any additional pairs of custom options.
 * \param parser Function for parsing the formatted response.
 */
void interchange_ord_order(const char *sku, const char *item,
		const unsigned int quantity, const char *options[][2],
		void (*parser)(interchange_response *));

/*!
 * \brief For updating the quantity of an item in a cart.
 * \param name The name given, in the cart, to the item.
 * \param quantity The desired quantity.
 * \param orderpage The order page, by default it's ord/basket.
 * \param nextpage The page to expect response from, whatever the result is.
 * \param parser Function for parsing the formatted response.
 */
void interchange_ord_update(const char *name, const unsigned int quantity,
		const char *orderpage, const char *nextpage,
		void (*parser)(interchange_response *));

/*!
 * \brief For removing an item from a cart.
 * \param name The name given, in the cart, to the item.
 * \param orderpage The order page, by default it's ord/basket.
 * \param nextpage The page to expect response from, whatever the result is.
 * \param parser Function for parsing the formatted response.
 */
#define interchange_ord_remove(a, b, c, d) interchange_ord_update(a, 0, b, c, d)

/*!
 * \brief For checking out items in the cart.
 * \param order_profile The order profile/method.
 * \param member The member checking out.
 * \param handler A pointer to the function when a custom handler is needed to
 * arrange the data into the product.
*/
void interchange_ord_checkout(const char *order_profile,
		struct interchange_member member,
		void (*handler)(interchange_response *));

void interchange_ord_free_order(struct interchange_ord_order *order);

void interchange_ord_clear_transaction(struct interchange_ord_transaction
		*transaction);

#ifdef __cplusplus
}
#endif

#endif
