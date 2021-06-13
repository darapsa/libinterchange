#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json.h>
#include "icclient.h"
#include "icclient/member.h"

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
	icclient_free_catalog(catalog);
}

static void handle_results(icclient_fetch_t *fetch)
{
	json_tokener *tokener = json_tokener_new();
	json_object *products = json_tokener_parse_ex(tokener, fetch->data, fetch->numBytes);
	json_tokener_free(tokener);
	size_t length = json_object_array_length(products);
	struct icclient_catalog *catalog = malloc(sizeof(struct icclient_catalog) + sizeof(struct icclient_product *[length]));
	catalog->length = length;
	for (size_t i = 0; i < length; i++) {
		catalog->products[i] = malloc(sizeof(struct icclient_product));
		struct icclient_product *product = catalog->products[i];
		memset(product, '\0', sizeof(struct icclient_product));
		json_object *object = json_object_array_get_idx(products, i);
		struct json_object_iterator iterator = json_object_iter_begin(object);
		struct json_object_iterator iterator_end = json_object_iter_end(object);
		while (!json_object_iter_equal(&iterator, &iterator_end)) {
			const char *key = json_object_iter_peek_name(&iterator);
			json_object *val = json_object_iter_peek_value(&iterator);
			if (!strcmp(key, "price"))
				product->price = json_object_get_double(val);
			else {
				int len = json_object_get_string_len(val);
				if (len) {
					char *value = malloc(len + 1);
					strcpy(value, json_object_get_string(val));
					if (!strcmp(key, "sku"))
						product->sku = value;
					else if (!strcmp(key, "thumb"))
						product->thumb = value;
					else if (!strcmp(key, "image"))
						product->image = value;
					else if (!strcmp(key, "description"))
						product->description = value;
					else if (!strcmp(key, "prod_group"))
						product->prod_group = value;
				}
			}
			json_object_iter_next(&iterator);
		}
	}
	((void (*)(struct icclient_catalog *))fetch->userData)(catalog);
}

static void print_user(icclient_fetch_t *fetch)
{
	printf("%s\n", fetch->data);
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

	icclient_allproducts(print_catalog, handle_results);

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
