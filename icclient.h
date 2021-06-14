#ifndef ICCLIENT_H
#define ICCLIENT_H

#include "icclient/typedefs.h"

#define	icclient_allproducts(callback, handler) icclient_results("All-Products", callback, handler)

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

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief A function that needs to be run first.
 * \param sampleurl The value of the SAMPLEURL setting in products/variable.txt.
 * \param image_dir The value of the IMAGE_DIR setting in products/variable.txt.
 * \param certificate Path to the CA certificate file.
 * \return True if the initialisation works, false otherwise.
 */
void icclient_init(const char *sampleurl, const char *image_dir, const char *certificate);

/*!
 * \brief For fetching data about products that belong a specific group.
 * \param prod_group The name of the product group.
 * \param callback A pointer to the function that needs to be called after the catalog is ready.
 * \param handler A pointer to the function when a custom handler is needed to arrange the data into the catalog.
 */
void icclient_results(const char *prod_group, void (*callback)(struct icclient_catalog *), void (*handler)(icclient_fetch_t *));

/*!
 * \brief For fetching data about a specific product.
 * \param sku The SKU of the product.
 * \param handler A pointer to a cURL write function callback.
 * \param productptr A pointer to pointer to the product to store the data.
 */
void icclient_flypage(const char *sku, void (*handler)(icclient_fetch_t *), struct icclient_product **productptr);

void icclient_page(const char *path, void (*handler)(icclient_fetch_t *), void **dataptr);

void icclient_free_product(struct icclient_product *product);

void icclient_free_catalog(struct icclient_catalog *catalog);

void icclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif
