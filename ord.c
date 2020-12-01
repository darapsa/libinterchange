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
	icclient_product_init(key_product);
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
	struct curl_httppost *post, *last = NULL;
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_todo",
			CURLFORM_COPYCONTENTS, "submit",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_action",
			CURLFORM_COPYCONTENTS, "refresh",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_order_profile",
			CURLFORM_PTRCONTENTS, order->profile,
			CURLFORM_END);
	if (member->fname)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "fname",
				CURLFORM_PTRCONTENTS, member->fname,
				CURLFORM_END);
	if (member->lname)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "lname",
				CURLFORM_PTRCONTENTS, member->lname,
				CURLFORM_END);
	if (member->address1)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "address1",
				CURLFORM_PTRCONTENTS, member->address1,
				CURLFORM_END);
	if (member->address2)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "address2",
				CURLFORM_PTRCONTENTS, member->address2,
				CURLFORM_END);
	if (member->city)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "city",
				CURLFORM_PTRCONTENTS, member->city,
				CURLFORM_END);
	if (member->state)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "state",
				CURLFORM_PTRCONTENTS, member->state,
				CURLFORM_END);
	if (member->zip)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "zip",
				CURLFORM_PTRCONTENTS, member->zip,
				CURLFORM_END);
	if (member->email)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "email",
				CURLFORM_PTRCONTENTS, member->email,
				CURLFORM_END);
	if (member->phone_day)
		curl_formadd(&post, &last,
				CURLFORM_COPYNAME, "phone_day",
				CURLFORM_PTRCONTENTS, member->phone_day,
				CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_same_billing",
			CURLFORM_COPYCONTENTS,
			member->preferences->mv_same_billing? "1" : "0",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "email_copy",
			CURLFORM_COPYCONTENTS, member->preferences->email_copy? "1" : "0",
			CURLFORM_END);
	last = NULL;
	request(NULL, NULL, post, "%s", "ord/checkout");
	curl_formfree(post);
	post = NULL;
}

void icclient_ord_free(struct icclient_ord_order *order)
{
	for (size_t i = 0; i < order->nitems; i++)
		icclient_product_free(order->items[i]->product);
}
