#include <stdlib.h>
#include <stdbool.h>
#include "request.h"
#include "icclient/catalog.h"
#include "icclient/product.h"
#include "icclient/member.h"
#include "icclient/ord.h"

typedef struct icclient_catalog icclient_catalog;
typedef struct icclient_product icclient_product;
typedef struct icclient_ord_item icclient_ord_item;

void icclient_ord_init(struct icclient_ord_order *order)
{
	order->subtotal = .0;
	order->shipping = .0;
	order->subtotal = .0;
	order->nitems = 0;
}

static int prodcmp(const void *product1, const void *product2)
{
	return strcmp((*(icclient_product * const *)product1)->sku
			, (*(icclient_product * const *)product2)->sku);
}

static int itemcmp(const void *item1, const void *item2)
{
	return strcmp((*(icclient_ord_item * const *)item1)->product->sku
			, (*(icclient_ord_item * const *)item2)->product->sku);
}

void icclient_ord_order(const char *sku, const icclient_catalog *catalog,
		struct icclient_ord_order **orderptr)
{
	icclient_product **products = ((icclient_catalog *)catalog)->products;
	qsort(products, catalog->length, sizeof(icclient_product *), prodcmp);
	icclient_product *key_product = malloc(sizeof(icclient_product));
	memset(key_product, '\0', sizeof(icclient_product));
	key_product->sku = malloc(strlen(sku) + 1);
	strcpy(key_product->sku, sku);
	icclient_product *product = *(icclient_product **)bsearch(&key_product
			, products, catalog->length, sizeof(icclient_product *)
			, prodcmp);
	icclient_product_free(key_product);

	struct icclient_ord_order *order = *orderptr;
	icclient_ord_item *item = NULL;

	if (order) {
		icclient_ord_item **items = order->items;
		qsort(items, order->nitems, sizeof(icclient_ord_item *), itemcmp);
		icclient_ord_item *key_item = malloc(sizeof(icclient_ord_item));
		key_item->product = product;
		icclient_ord_item **itemptr = bsearch(&key_item, items
				, order->nitems, sizeof(icclient_ord_item *)
				, itemcmp);
		if (itemptr)
			item = *itemptr;
		free(key_item);
	} else {
		*orderptr = malloc(sizeof(struct icclient_ord_order));
		order = *orderptr;
		icclient_ord_init(order);
	}

	if (item)
		item->quantity++;
	else {
		size_t i = order->nitems;
		*orderptr = realloc(order, sizeof(struct icclient_ord_order)
				+ (i + 1) * sizeof(icclient_ord_item));
		order = *orderptr;
		order->items[i] = malloc(sizeof(icclient_ord_item));
		order->nitems++;
		item = order->items[i];
		item->product = product;
		item->quantity = 1;
	}

	order->subtotal += item->product->price;
	order->total_cost += item->product->price;

	request(NULL, NULL, NULL, "%s%s", "order?mv_arg=", sku);
}

void icclient_ord_checkout(struct icclient_ord_order *order,
		struct icclient_member *member)
{
	request(NULL, NULL, &(struct icclient_request_data){ 14, {
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
			{ "mv_same_billing", member->preferences->mv_same_billing? "1" : "0" },
			{ "email_copy", member->preferences->email_copy? "1" : "0" }
			}}, "%s", "ord/checkout");
}

void icclient_ord_free(struct icclient_ord_order *order)
{
	for (size_t i = 0; i < order->nitems; i++)
		icclient_product_free(order->items[i]->product);
}
