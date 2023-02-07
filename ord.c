#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "interchange.h"
#include "interchange/member.h"
#include "interchange/ord.h"

static int prodcmp(const void *product1, const void *product2)
{
	return strcmp((*(struct interchange_product * const *)product1)->sku,
			(*(struct interchange_product * const *)product2)->sku);
}

static int itemcmp(const void *item1, const void *item2)
{
	return strcmp((*(struct interchange_ord_item * const *)item1)->product->sku,
			(*(struct interchange_ord_item * const *)item2)->product->sku);
}

void interchange_ord_order(const char *sku, const struct interchange_catalog *catalog,
		struct interchange_ord_order **order)
{
	struct interchange_product **products = ((struct interchange_catalog *)catalog)->products;
	qsort(products, catalog->length, sizeof(struct interchange_product *), prodcmp);
	struct interchange_product *key_product = malloc(sizeof(struct interchange_product));
	memset(key_product, '\0', sizeof(struct interchange_product));
	key_product->sku = malloc(strlen(sku) + 1);
	strcpy(key_product->sku, sku);
	struct interchange_product *product = *(struct interchange_product **)bsearch(&key_product, products,
			catalog->length, sizeof(struct interchange_product *), prodcmp);
	interchange_free_product(key_product);
	struct interchange_ord_item *item = NULL;
	if (*order) {
		struct interchange_ord_item **items = (*order)->items;
		qsort(items, (*order)->nitems, sizeof(struct interchange_ord_item *), itemcmp);
		struct interchange_ord_item *key_item = malloc(sizeof(struct interchange_ord_item));
		key_item->product = product;
		struct interchange_ord_item **itemptr = bsearch(&key_item, items, (*order)->nitems,
				sizeof(struct interchange_ord_item *), itemcmp);
		if (itemptr)
			item = *itemptr;
		free(key_item);
	} else {
		*order = malloc(sizeof(struct interchange_ord_order));
		memset(*order, '\0', sizeof(struct interchange_ord_order));
	}
	if (item)
		item->quantity++;
	else {
		size_t i = (*order)->nitems;
		*order = realloc(*order, sizeof(struct interchange_ord_order) + (i + 1)
				* sizeof(struct interchange_ord_item));
		(*order)->items[i] = malloc(sizeof(struct interchange_ord_item));
		(*order)->nitems++;
		item = (*order)->items[i];
		item->product = product;
		item->quantity = 1;
	}
	(*order)->subtotal += item->product->price;
	(*order)->total_cost += item->product->price;
	request(NULL, NULL, NULL, "%s%s", "order?mv_arg=", sku);
}

void interchange_ord_checkout(const struct interchange_ord_order *order, const struct interchange_member *member)
{
	request(NULL, NULL, &(struct body){ 14, {
		{ "mv_todo", "submit" },
		{ "mv_action", "refresh" },
		{ "mv_order_profile", order->profile },
		{ "fname", member->fname },
		{ "lname", member->lname },
		{ "address1", member->address1 },
		{ "address2", member->address2 },
		{ "city", member->city },
		{ "state", member->state },
		{ "zip", member->zip },
		{ "email", member->email },
		{ "phone_day", member->phone_day },
		{ "mv_same_billing", member->preferences.mv_same_billing? "1" : "0" },
		{ "email_copy", member->preferences.email_copy? "1" : "0" }
	}}, "%s", "ord/checkout");
}

void interchange_ord_free(struct interchange_ord_order *order)
{
	if (order->profile)
		free(order->profile);
	for (size_t i = 0; i < order->nitems; i++)
		interchange_free_product(order->items[i]->product);
}
