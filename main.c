#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "icclient.h"
#include "icclient/member.h"

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
/*
static void print_user(icclient_fetch_t *fetch)
{
	printf("%s\n", fetch->data);
}
*/
int main(int argc, char *argv[])
{
	icclient_init("https://demo.interchangecommerce.org/i/demo", "/demo/images", NULL);
	icclient_allproducts(print_catalog, NULL);
/*
	char *name_line = NULL;
	printf("\nName: ");
	ssize_t name_nread = getline(&name_line, &(size_t){0}, stdin);
	char *name = malloc(--name_nread + 1);
	strncpy(name, name_line, name_nread);
	free(name_line);

	char *pass_line = NULL;
	printf("Pass: ");
	ssize_t pass_nread = getline(&pass_line, &(size_t){0}, stdin);
	char *pass = malloc(--pass_nread + 1);
	strncpy(pass, pass_line, pass_nread);
	free(pass_line);
	pass[pass_nread] = '\0';

	struct icclient_member *member = icclient_member_login(name, pass, NULL, NULL, NULL, print_user);
	free(name);
	free(pass);
	icclient_member_logout(member);
*/
	icclient_cleanup();
}
