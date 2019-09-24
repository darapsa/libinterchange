#ifndef ICCLIENT_CLIENT_H
#define ICCLIENT_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

	bool icclient_init(const char *url, const char *certificate);
	void icclient_login(const char *username, const char *password
			, const char *successpage, const char *nextpage
			, const char *failpage);
	void icclient_logout();
	void icclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_CLIENT_H
