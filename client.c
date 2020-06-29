#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "icclient/product.h"
#include "icclient/catalog.h"
#include "icclient/ord.h"
#include "icclient/member.h"
#include "icclient/client.h"

typedef struct icclient_product icclient_product;
typedef struct icclient_catalog icclient_catalog;
typedef struct icclient_ord_item icclient_ord_item;
typedef struct icclient_ord_order icclient_ord_order;

CURL *curl = NULL;
char *server_url = NULL;

bool icclient_init(const char *url, const char *certificate)
{
	curl_global_init(CURL_GLOBAL_SSL);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
		if (certificate)
			curl_easy_setopt(curl, CURLOPT_CAINFO, certificate);
#ifdef DEBUG
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
		size_t length = strlen(url);
		bool append = !(bool)(url[length - 1] == '/');
		server_url = malloc(length + (size_t)append + 1);
		strcpy(server_url, url);
		if (append)
			strcat(server_url, "/");
	}

	return (bool)curl;
}

void icclient_results(const char *prodgroup,
		size_t (*handler)(void *contents, size_t size,
			size_t nmemb, void *userdata),
		struct icclient_catalog **catalogptr)
{
	char nonspaced[strlen(prodgroup) + 1];
	strcpy(nonspaced, prodgroup);
	char *space = NULL;
	while ((space = strchr(nonspaced, ' ')))
		*space = '-';
	request(handler, (void *)catalogptr, NULL, "%s", nonspaced);
}

void icclient_allproducts(size_t (*handler)(void *, size_t, size_t, void *)
		, icclient_catalog **catalogptr)
{
	request(handler, (void *)catalogptr, NULL, "%s", "All-Products");
}

void icclient_flypage(const char *sku,
		size_t (*handler)(void *, size_t, size_t, void *),
		icclient_product **productptr)
{
	request(handler, (void *)productptr, NULL, "%s", sku);
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

void icclient_order(const char *sku, const icclient_catalog *catalog,
		icclient_ord_order **orderptr)
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

	icclient_ord_order *order = *orderptr;
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
		*orderptr = malloc(sizeof(icclient_ord_order));
		order = *orderptr;
		icclient_ord_init(order);
	}

	if (item)
		item->quantity++;
	else {
		size_t i = order->nitems;
		*orderptr = realloc(order, sizeof(icclient_ord_order)
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

void icclient_newaccount(size_t (*handler)(void *contents, size_t size
				, size_t nmemb, void *userdata)
		, struct icclient_user *user
		, const char *username, const char *password
		, const char *verify, const char *successpage, const char *nextpage
		, const char *failpage)
{
	login(handler, user, username, password, verify, "NewAccount", successpage
			, nextpage, failpage);
}

void icclient_login(size_t (*handler)(void *contents, size_t size
			, size_t nmemb, void *userdata)
		, struct icclient_user *user
		, const char *username, const char *password
		, const char *successpage, const char *nextpage
		, const char *failpage)
{
	login(handler, user, username, password, NULL, "Login", successpage
			, nextpage, failpage);
}

void icclient_logout()
{
	request(NULL, NULL, NULL, "%s", "logout");
}

void icclient_page(const char *path, size_t (*handler)(void *, size_t, size_t
			, void *), void **dataptr)
{
	request(handler, (void *)dataptr, NULL, "%s", path);
}

void icclient_cleanup()
{
	if (curl) {
		free(server_url);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
