#ifndef ICCLIENT_H
#define ICCLIENT_H

#include "icclient/typedefs.h"

struct icclient_product {
	char *sku;
	char *description;
	char *comment;
	char *thumb;
	char *image;
	double price;
	char *prod_group;
	char *category;
	double weight;
	char *author;
	struct icclient_product_crosssell {
		size_t length;
		char *skus[];
	} *crosssell;
};

struct icclient_catalog {
	size_t length;
	struct icclient_product *products[];
};

/*!
 * \brief For fetching data about all of the products that are active.
 * \param handler A pointer to the function when a custom handler is needed to arrange the data into the catalog.
 * \param callback A pointer to the function that needs to be called after the catalog is ready.
 */
#define	icclient_allproducts(handler, callback) icclient_results("All-Products", handler, callback)

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief A function that needs to be run first.
 * \param sampleurl The value of the SAMPLEURL setting in products/variable.txt.
 * \param image_dir The value of the IMAGE_DIR setting in products/variable.txt.
 * \param certificate Path to the CA certificate file.
 */
void icclient_init(const char *sampleurl, const char *image_dir, const char *certificate);

/*!
 * \brief For fetching data about products that belong a specific group.
 * \param prod_group The name of the product group.
 * \param handler A pointer to the function when a custom handler is needed to arrange the data into the catalog.
 * \param callback A pointer to the function that needs to be called after the catalog is ready.
 */
void icclient_results(const char *prod_group, void (*handler)(icclient_response *), void (*callback)(struct icclient_catalog *));

/*!
 * \brief For fetching data about a specific product.
 * \param sku The SKU of the product.
 * \param handler A pointer to a cURL write function callback.
 * \param productptr A pointer to pointer to the product to store the data.
 */
void icclient_flypage(const char *sku, void (*handler)(icclient_response *), struct icclient_product **productptr);

void icclient_page(const char *path, void (*handler)(icclient_response *), void **dataptr);

void icclient_free_product(struct icclient_product *product);

void icclient_free_catalog(struct icclient_catalog *catalog);

void icclient_free_response(icclient_response *response);

void icclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif
