#ifndef ICCLIENT_ADMIN_H
#define ICCLIENT_ADMIN_H

#ifdef __cplusplus
extern "C" {
#endif

	void icclient_admin_login(size_t (*handler)(void *, size_t, size_t, void *),
			struct icclient_member *member, const char *username,
			const char *password, const char *successpage,
			const char *nextpage, const char *failpage);
	void icclient_admin_logout();

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_ADMIN_H
