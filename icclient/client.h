#ifndef ICCLIENT_CLIENT_H
#define ICCLIENT_CLIENT_H

struct icclient_product;
struct icclient_catalog;

#ifdef __cplusplus
extern "C" {
#endif

	bool icclient_init(const char *url, const char *certificate);
	void icclient_allproducts(size_t (*handler)(void *contents, size_t size
				, size_t nmemb, void *userdata)
			, struct icclient_catalog **catalogptr);
	void icclient_newaccount(const char *username, const char *password
			, const char *verify, const char *successpage
			, const char *nextpage, const char *failpage);
	void icclient_login(const char *username, const char *password
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
