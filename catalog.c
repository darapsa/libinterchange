#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json.h>
#include "icclient/product.h"
#include "icclient/catalog.h"
#ifdef __EMSCRIPTEN__
#include <emscripten/fetch.h>
#define ICCLIENT_HANDLER_REALSIZE fetch->numBytes
#define ICCLIENT_HANDLER_RETURN 
#define ICCLIENT_HANDLER_STRUCT fetch->
#else
#define ICCLIENT_HANDLER_REALSIZE size * nmemb
#define ICCLIENT_HANDLER_RETURN realsize
#define ICCLIENT_HANDLER_STRUCT
#endif

#ifdef __EMSCRIPTEN__
void icclient_catalog_results(emscripten_fetch_t *fetch)
#else
size_t icclient_catalog_results(void *data, size_t size, size_t nmemb, void *userData)
#endif
{
	size_t realsize = ICCLIENT_HANDLER_REALSIZE; 
	json_tokener *tokener = json_tokener_new();
	json_object *products = json_tokener_parse_ex(tokener, ICCLIENT_HANDLER_STRUCT data, realsize);
	enum json_tokener_error error = json_tokener_get_error(tokener);
	if (!products) {
		if (error == json_tokener_continue)
			return ICCLIENT_HANDLER_RETURN;
		else {
			json_tokener_reset(tokener);
			return ICCLIENT_HANDLER_RETURN;
		}
	} else if (!json_object_is_type(products, json_type_array) || error != json_tokener_success)
		return ICCLIENT_HANDLER_RETURN;
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
	((void (*)(struct icclient_catalog *))ICCLIENT_HANDLER_STRUCT userData)(catalog);
#ifdef __EMSCRIPTEN__
	emscripten_fetch_close(fetch);
#endif
	return ICCLIENT_HANDLER_RETURN;
}

void icclient_catalog_free(struct icclient_catalog *catalog)
{
	for (size_t i = 0; i < catalog->length; i++)
		icclient_product_free(catalog->products[i]);
	free(catalog);
}
