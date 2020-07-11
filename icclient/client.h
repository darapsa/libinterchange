#ifndef ICCLIENT_CLIENT_H
#define ICCLIENT_CLIENT_H

struct icclient_product;
struct icclient_catalog;
struct icclient_ord_order;

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
	 * \param prodgroup The name of the product group.
	 * \param handler A pointer to a cURL write function callback.
	 * \param catalogptr A pointer to pointer to the catalog to store the data.
	 */
	void icclient_results(const char *prodgroup,
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
	 * \param sku The SKU of the item to order.
	 * \param handler A pointer to a cURL write function callback.
	 * \param productptr A pointer to pointer to the product to store the data.
	 */
	void icclient_flypage(const char *sku,
			size_t (*handler)(void *, size_t, size_t, void *),
			struct icclient_product **productptr);

	/*!
	 * \brief For putting an item to a cart.
	 * \param sku The SKU of the item to order.
	 * \param catalog A pointer to the catalog from which the item is.
	 * \param orderptr A pointer to pointer to the order.
	 */
	void icclient_order(const char *sku, const struct icclient_catalog *catalog,
			struct icclient_ord_order **orderptr);
	void icclient_page(const char *path,
			size_t (*handler)(void *, size_t, size_t, void *),
			void **dataptr);
	void icclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_CLIENT_H
