#ifndef ICCLIENT_ADMIN_H
#define ICCLIENT_ADMIN_H

enum icclient_admin_group {
	ICCLIENT_ADMIN_GROUP_CONTENT,
	ICCLIENT_ADMIN_GROUP_MERCH,
	ICCLIENT_ADMIN_GROUP_ORDERS
};

struct icclient_admin {
	char *username;
	char *password;
	char *name;
	bool super;
	enum icclient_admin_group group;
};

#ifdef __cplusplus
extern "C" {
#endif

	struct icclient_admin *icclient_admin_login(const char *username,
			const char *password, const char *successpage,
			const char *nextpage, const char *failpage,
			void (*handler)(icclient_fetch_t *));
	void icclient_admin_new_admin(const char *username, const char *password, const char *name, bool super,
			enum icclient_admin_group group, void (*handler)(icclient_fetch_t *));
	void icclient_admin_new_item(const char *description, const char *comment, const char *price, const char *image_path,
			void (*handler)(icclient_fetch_t *));
	void icclient_admin_logout(struct icclient_admin *admin, void (*handler)(icclient_fetch_t *));

#ifdef __cplusplus
}
#endif

#endif
