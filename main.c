#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json.h>
#include "icclient/typedefs.h"
#include "icclient/product.h"
#include "icclient/catalog.h"
#include "icclient/client.h"

static json_tokener *tokener;

static void callback(struct icclient_catalog *catalog)
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
}

static size_t handler_results(void *contents, size_t size, size_t nmemb, void *userData)
{
	size_t realsize = size * nmemb;
	char data[realsize + 1];
	memcpy(data, contents, realsize);
	data[realsize] = '\0';
	json_object *products = json_tokener_parse_ex(tokener, data, realsize);
	enum json_tokener_error error = json_tokener_get_error(tokener);
	if (!products) {
		if (error == json_tokener_continue)
			return realsize;
		else {
			json_tokener_reset(tokener);
			return realsize;
		}
	} else if (!json_object_is_type(products, json_type_array) || error != json_tokener_success)
		return realsize;
	size_t length = json_object_array_length(products);
	struct icclient_catalog_callback *catalog_callback = (struct icclient_catalog_callback *)userData;
	struct icclient_catalog **catalogptr = catalog_callback->catalog;
	*catalogptr = malloc(sizeof(struct icclient_catalog) + sizeof(struct icclient_product *[length]));
	struct icclient_catalog *catalog = *catalogptr;
	catalog->length = length;
	for (size_t i = 0; i < length; i++) {
		catalog->products[i] = malloc(sizeof(struct icclient_product));
		struct icclient_product *product = catalog->products[i];
		icclient_product_init(product);
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
	catalog_callback->callback(catalog);
	free(catalog_callback);
	return realsize;
}

int main(int argc, char *argv[])
{
	tokener = json_tokener_new();
	/*
	char *url_line = NULL, *name_line = NULL, *pass_line = NULL;
	printf("URL: ");
	ssize_t url_nread = getline(&url_line, &(size_t){0}, stdin);
	printf("Name: ");
	ssize_t name_nread = getline(&name_line, &(size_t){0}, stdin);
	printf("Pass: ");
	ssize_t pass_nread = getline(&pass_line, &(size_t){0}, stdin);
	char *url =  malloc(--url_nread + 1), *name = malloc(--name_nread + 1), *pass = malloc(--pass_nread + 1);
	strncpy(url, url_line, url_nread);
	free(url_line);
	strncpy(name, name_line, name_nread);
	free(name_line);
	strncpy(pass, pass_line, pass_nread);
	free(pass_line);
	*/
	icclient_init(argv[1], NULL);
	/*
	free(url);

	icclient_login(NULL, NULL, name, pass, NULL, NULL, NULL);
	free(name);
	free(pass);

	icclient_logout();
	*/
	struct icclient_catalog *catalog;
	icclient_allproducts(callback, &catalog, handler_results);
	icclient_catalog_free(catalog);
	icclient_cleanup();
	json_tokener_free(tokener);
}
