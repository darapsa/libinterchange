#ifndef ICCLIENT_CLIENT_H
#define ICCLIENT_CLIENT_H

struct icclient_product;
struct icclient_catalog;

#ifdef __cplusplus
extern "C" {
#endif

	/*!
	 * \brief A function that needs to be run first.
	 * \param url Server root URL.
	 * \param certificate Path to the CA certificate file.
	 * \return True if the initialisation works, false otherwise.
	 */
	bool icclient_init(const char *url, const char *certificate);

	/*!
	 * \brief For fetching data about products that belong a specific group.
	 * \param prod_group The name of the product group.
	 * \param callback A pointer to the function that needs to be called after the catalog is ready.
	 * \param catalog A pointer to pointer to the catalog to store the data.
	 * \param handler A pointer to the function when a custom handler is needed to arrange the data into the catalog.
	 */
	void icclient_results(const char *prod_group, void (*callback)(struct icclient_catalog *),
			struct icclient_catalog **catalog, icclient_handler handler);

	/*!
	 * \brief For fetching data about a specific product.
	 * \param sku The SKU of the product.
	 * \param handler A pointer to a cURL write function callback.
	 * \param productptr A pointer to pointer to the product to store the data.
	 */
	void icclient_flypage(const char *sku, icclient_handler handler, struct icclient_product **productptr);

	void icclient_page(const char *path, icclient_handler handler, void **dataptr);
	void icclient_cleanup();

#ifdef __cplusplus
}
#endif

#define	icclient_allproducts(callback, catalog, handler) icclient_results("All-Products", callback, catalog, handler)

#endif
