#ifndef INTERCHANGE_H
#define INTERCHANGE_H

#include "interchange/typedefs.h"

struct interchange_product {
	char *sku;
	char *description;
	char *title;
	char *comment;
	char *thumb;
	char *image;
	double price;
	char *prod_group;
	char *category;
	double weight;
	char *author;
	struct interchange_product_crosssell {
		size_t length;
		char *skus[];
	} *crosssell;
};

struct interchange_catalog {
	size_t length;
	struct interchange_product products[];
};

/*!
 * \brief For fetching data about all active products.
 * \param handler A pointer to the function when a custom handler is needed to arrange the data into the catalog.
 * \param callback A pointer to the function that needs to be called after the catalog is ready.
 */
#define	interchange_allproducts(handler, callback) interchange_catalog("All-Products", handler, callback)

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief A function that needs to be run first.
 * \param sampleurl The value of the SAMPLEURL setting in products/variable.txt.
 * \param image_dir The value of the IMAGE_DIR setting in products/variable.txt.
 * \param cookie Path to the cookie file.
 * \param certificate Path to the CA certificate file.
 */
void interchange_init(const char *sampleurl, const char *image_dir,
		const char *cookie, const char *certificate);

/*!
 * \brief For fetching data about products that belong a specific group.
 * \param prod_group The name of the product group.
 * \param handler A pointer to the function when a custom handler is needed to arrange the data into the catalog.
 * \param callback A pointer to the function that needs to be called after the catalog is ready.
 */
void interchange_catalog(const char *prod_group, void (*handler)(interchange_response *), void (*callback)(struct interchange_catalog *));

/*!
 * \brief For fetching data about a specific product.
 * \param sku The SKU of the product.
 * \param handler A pointer to the function when a custom handler is needed to arrange the data into the product.
 * \param callback A pointer to the function that needs to be called after the product is ready.
*/
void interchange_product(const char *sku, void (*handler)(interchange_response *), void (*callback)(struct interchange_product *));

void interchange_page(const char *path, void (*handler)(interchange_response *));

void interchange_free_product(struct interchange_product *product);

void interchange_free_catalog(struct interchange_catalog *catalog);

void interchange_free_response(interchange_response *response);

void interchange_cleanup();

#ifdef __cplusplus
}
#endif

#endif
