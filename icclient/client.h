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
	 * \param handler A pointer to a cURL write function callback.
	 * \param catalogptr A pointer to pointer to the catalog to store the data.
	 */
	void icclient_results(const char *prod_group,
			size_t (*handler)(void *, size_t, size_t, void *),
			struct icclient_catalog **catalogptr);

	/*!
	 * \brief For fetching data about all active products.
	 * \param handler A pointer to a cURL write function callback.
	 * \param catalogptr A pointer to pointer to the catalog to store the data.
	 */
	void icclient_allproducts(size_t (*handler)(void *, size_t, size_t, void *),
			struct icclient_catalog **catalogptr);

	/*!
	 * \brief For fetching data about a specific product.
	 * \param sku The SKU of the product.
	 * \param handler A pointer to a cURL write function callback.
	 * \param productptr A pointer to pointer to the product to store the data.
	 */
	void icclient_flypage(const char *sku,
			size_t (*handler)(void *, size_t, size_t, void *),
			struct icclient_product **productptr);

	void icclient_page(const char *path,
			size_t (*handler)(void *, size_t, size_t, void *),
			void **dataptr);
	void icclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_CLIENT_H
