#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "interchange.h"
#include "interchange/member.h"
#include "interchange/admin.h"

static void print_catalog(struct interchange_catalog *catalog)
{
	for (size_t i = 0; i < catalog->length; i++) {
		struct interchange_product *product = catalog->products[i];
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
	interchange_free_catalog(catalog);
}

static void print(interchange_response *response)
{
	printf("%s\n", response->data);
}

int main(int argc, char *argv[])
{
	interchange_init("https://demo.interchangecommerce.org/i/demo", "/demo/images", NULL);
	interchange_allproducts(NULL, print_catalog);
	interchange_admin_login("demo", "demo", print, NULL);
	interchange_member_login("kirk@icdevgroup.net", "kirk", print, NULL);
	interchange_cleanup();
}
