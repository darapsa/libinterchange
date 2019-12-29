#ifndef ICCLIENT_ADMIN_H
#define ICCLIENT_ADMIN_H

#ifdef __cplusplus
extern "C" {
#endif

	void icclient_admin_login(size_t (*handler)(void *contents, size_t size
				, size_t nmemb, void *userdata)
			, struct icclient_user *user
			, const char *username, const char *password
			, const char *successpage, const char *nextpage
			, const char *failpage);
	void icclient_admin_logout();

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_ADMIN_H
