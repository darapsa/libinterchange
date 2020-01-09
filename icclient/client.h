#ifndef ICCLIENT_CLIENT_H
#define ICCLIENT_CLIENT_H

struct icclient_product;
struct icclient_catalog;
struct icclient_user;
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
	 * \brief For fetching data about all active products.
	 * \param handler A pointer to a cURL write function callback.
	 * \param catalogptr A pointer to pointer to the catalog to store the data.
	 */
	void icclient_allproducts(size_t (*handler)(void *contents, size_t size
				, size_t nmemb, void *userdata)
			, struct icclient_catalog **catalogptr);

	/*!
	 * \brief For fetching data about all active products.
	 * \param orderptr A pointer to pointer to the order.
	 * \param sku The SKU of the item to order.
	 * \param catalog A pointer to the catalog from which the item is.
	 */
	void icclient_order(struct icclient_ord_order **orderptr, const char *sku
			, struct icclient_catalog *catalog);
	void icclient_newaccount(size_t (*handler)(void *contents, size_t size
				, size_t nmemb, void *userdata)
			, struct icclient_user *user
			, const char *username, const char *password
			, const char *verify, const char *successpage
			, const char *nextpage, const char *failpage);
	void icclient_login(size_t (*handler)(void *contents, size_t size
				, size_t nmemb, void *userdata)
			, struct icclient_user *user
			, const char *username, const char *password
			, const char *successpage, const char *nextpage
			, const char *failpage);
	void icclient_logout();
	void icclient_page(const char *path
			, size_t (*handler)(void *contents, size_t size
				, size_t nmemb, void *userdata)
			, void **dataptr);
	void icclient_freeproduct(struct icclient_product *product);
	void icclient_freecatalog(struct icclient_catalog *catalog);
	void icclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_CLIENT_H
