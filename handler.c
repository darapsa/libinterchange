#include <stdbool.h>
#include <locale.h>
#include <langinfo.h>
#include <tidy.h>
#include <tidybuffio.h>
#include "icclient.h"

extern char *image_dir;
static locale_t loc = 0;

static void dumpNode(TidyDoc doc, TidyNode tnod, struct icclient_catalog **catalog, char **category,
		bool is_sku, bool is_category, bool is_price)
{
	struct icclient_product *product;
	for (TidyNode child = tidyGetChild(tnod); child; child = tidyGetNext(child)) {
		ctmbstr name = tidyNodeGetName(child);
		if (name) {
			if (!strcmp(name, "html")) {
				char locale[11];
				for (TidyAttr attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr)) {
					if (!strcmp(tidyAttrValue(attr), "en"))
						strcpy(locale, "en_US.utf8");
					else if (!strcmp(tidyAttrValue(attr), "id"))
						strcpy(locale, "id_ID.utf8");
					loc = newlocale(LC_MONETARY_MASK | LC_NUMERIC_MASK, locale, 0);
				}
			} else if (!strcmp(name, "h3")) {
				is_sku = false;
				is_category = true;
				is_price = false;
			} else if (!strcmp(name, "img")) {
				static const char *subdir = "/items/";
				char prefix[strlen(image_dir) + strlen(subdir) + 1];
				sprintf(prefix, "%s%s", image_dir, subdir);
				size_t prefix_len = strlen(prefix);
				for (TidyAttr attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr)) {
					if (!strcmp(tidyAttrName(attr), "src")) {
						if (strncmp(tidyAttrValue(attr), prefix, prefix_len))
							break;
						product = malloc(sizeof(struct icclient_product));
						memset(product, '\0', sizeof(struct icclient_product));
						size_t len = strlen(tidyAttrValue(attr)) - prefix_len;
						product->image = malloc(len + 1);
						strncpy(product->image, tidyAttrValue(attr) + prefix_len, len + 1);
					}
					if (strcmp(tidyAttrName(attr), "title"))
						continue;
					product->description = malloc(strlen(tidyAttrValue(attr)) + 1);
					strcpy(product->description, tidyAttrValue(attr));
					if (*category) {
						product->category = malloc(strlen(*category) + 1);
						strcpy(product->category, *category);
					}
					(*catalog)->length++;
					*catalog = realloc(*catalog, sizeof(struct icclient_catalog)
							+ sizeof(struct icclient_product *[(*catalog)->length]));
					(*catalog)->products[(*catalog)->length - 1] = product;
				}
			} else if (!strcmp(name, "h4")) {
				is_sku = true;
				is_category = false;
				is_price = false;
			} else if (is_sku && !strcmp(name, "a")) {
				is_sku = false;
				for (TidyAttr attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr)) {
					char *sku = strrchr(tidyAttrValue(attr), '/');
					char *session_id = strchr(sku++, '?');
					if (session_id)
						*session_id = '\0';
					product = (*catalog)->products[(*catalog)->length - 1];
					product->sku = malloc(strlen(sku) + 1);
					strcpy(product->sku, sku);
				}
			} else if (!strcmp(name, "p") && !((*catalog)->products[(*catalog)->length - 1])->price) {
				is_sku = false;
				is_category = false;
				is_price = true;
			} else {
				is_sku = false;
				is_category = false;
				is_price = false;
			}
		} else if (is_category || is_price) {
			TidyBuffer buf;
			tidyBufInit(&buf);
			tidyNodeGetText(doc, child, &buf);
			char *text = (char *)buf.bp;
			product = (*catalog)->products[(*catalog)->length - 1];
			if (is_category) {
				is_category = false;
				text[strlen(text) - 1] = '\0';
				if (*category)
					free(*category);
				*category = malloc(strlen(text) + 1);
				strcpy(*category, text);
			} else {
				is_price = false;
#ifndef __ANDROID__
				char *symbol = nl_langinfo_l(CRNCYSTR, loc);
				size_t symbol_len = strlen(symbol) - 1;
				if (symbol[0] == '-')
					text += symbol_len;
				char *separator = nl_langinfo_l(THOUSEP, loc);
				if (strstr(text, separator)) {
					size_t price_len = strlen(text) - symbol_len - 1;
					char price[price_len];
					memset(price, '\0', price_len);
					strcat(price, strtok(text, separator));
					strcat(price, strtok(NULL, separator));
					product->price = atof(price);
				} else
					product->price = atof(text);
#endif
			}
			tidyBufFree(&buf);
		}
		dumpNode(doc, child, catalog, category, is_sku, is_category, is_price);
	}
}

void handle_results(icclient_fetch_t *fetch)
{
	TidyDoc tdoc = tidyCreate();
	tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
	tidyParseString(tdoc, fetch->data);
	tidyCleanAndRepair(tdoc);
	tidyOptSetBool(tdoc, TidyForceOutput, yes);
	TidyBuffer output = {0};
	tidyBufInit(&output);
	tidySaveBuffer(tdoc, &output);
	struct icclient_catalog *catalog = malloc(sizeof(struct icclient_catalog));
	catalog->length = 0;
	dumpNode(tdoc, tidyGetRoot(tdoc), &catalog, &(char *){NULL}, false, false, false);
	tidyBufFree(&output);
	tidyRelease(tdoc);
	if (loc)
		freelocale(loc);
	((void (*)(struct icclient_catalog *))fetch->userData)(catalog);
}
