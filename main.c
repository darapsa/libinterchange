#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "icclient/typedefs.h"
#include "icclient/product.h"
#include "icclient/catalog.h"
#include "icclient/member.h"
#include "icclient/client.h"

static void print_catalog(struct icclient_catalog *catalog)
{
	for (size_t i = 0; i < catalog->length; i++) {
		struct icclient_product *product = catalog->products[i];
		printf("SKU: %s\n"
				"Description: %s\n"
				"Thumb: %s\n"
				"Image: %s\n"
				"Price: %f\n"
				"Product Group: %s\n",
				product->sku,
				product->description,
				product->thumb,
				product->image,
				product->price,
				product->prod_group
		      );
	}
	icclient_catalog_free(catalog);
}

static size_t print_user(void *contents, size_t size, size_t nmemb, void *userData)
{
	size_t realsize = size * nmemb;
	char data[realsize + 1];
	memcpy(data, contents, realsize);
	data[realsize] = '\0';
	printf("%s\n", data);
	return realsize;
}

int main(int argc, char *argv[])
{
	char *url_line = NULL;
	printf("\nURL: ");
	ssize_t url_nread = getline(&url_line, &(size_t){0}, stdin);
	char *url =  malloc(--url_nread + 1);
	strncpy(url, url_line, url_nread);
	free(url_line);

	printf("\n");
	icclient_init(url, NULL);
	free(url);

	icclient_allproducts(print_catalog, NULL);

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
	//icclient_member_logout(member);

	icclient_cleanup();
}
