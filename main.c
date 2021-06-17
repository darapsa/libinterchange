#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "icclient.h"
#include "icclient/member.h"
#include "icclient/admin.h"

static void print_catalog(struct icclient_catalog *catalog)
{
	for (size_t i = 0; i < catalog->length; i++) {
		struct icclient_product *product = catalog->products[i];
		printf("sku: %s | "
				"desc: %s | "
				"img: %s | "
				"prc: %f | "
				"cat: %s\n",
				product->sku,
				product->description,
				product->image,
				product->price,
				product->category
		      );
	}
	icclient_free_catalog(catalog);
}

static void print(icclient_response *response)
{
	printf("%s\n", response->data);
}

int main(int argc, char *argv[])
{
	icclient_init("https://demo.interchangecommerce.org/i/demo", "/demo/images", NULL);
	icclient_allproducts(NULL, print_catalog);
	icclient_admin_login("demo", "demo", print, NULL);
	icclient_member_login("kirk@icdevgroup.net", "kirk", print, NULL);
	icclient_cleanup();
}
