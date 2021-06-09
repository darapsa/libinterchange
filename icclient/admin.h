#ifndef ICCLIENT_ADMIN_H
#define ICCLIENT_ADMIN_H

struct icclient_admin {
	char *username;
	char *password;
	char *name;
	bool super;
};

#ifdef __cplusplus
extern "C" {
#endif

	struct icclient_admin *icclient_admin_login(const char *username,
			const char *password, const char *successpage,
			const char *nextpage, const char *failpage,
			icclient_handler handler);
	void icclient_admin_newitem(const char *description, const char *comment,
			const char *price, const char *image_path);
	void icclient_admin_logout(struct icclient_admin *admin);

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_ADMIN_H
