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

static void print(icclient_fetch_t *fetch)
{
	printf("%s\n", fetch->data);
}

int main(int argc, char *argv[])
{
	icclient_init("https://demo.interchangecommerce.org/i/demo", "/demo/images", NULL);
/*
	icclient_allproducts(print_catalog, NULL);
	struct icclient_member *member = icclient_member_login("kirk@icdevgroup.net", "kirk", NULL, NULL, NULL, print);
	icclient_member_logout(member);
*/
	struct icclient_admin *admin = icclient_admin_login("interch", "pass", NULL);
	icclient_admin_new_admin("Hardware", "pass", "Hardware stuff", 0, ICCLIENT_ADMIN_GROUP_MERCH, NULL);
	icclient_admin_logout(admin, NULL);
	icclient_cleanup();
}
