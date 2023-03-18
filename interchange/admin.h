#ifndef INTERCHANGE_ADMIN_H
#define INTERCHANGE_ADMIN_H

#include "typedefs.h"

enum interchange_admin_group {
	INTERCHANGE_ADMIN_GROUP_CONTENT,
	INTERCHANGE_ADMIN_GROUP_MERCH,
	INTERCHANGE_ADMIN_GROUP_ORDERS
};

struct interchange_admin {
	char *username;
	char *password;
	char *name;
	bool super;
	enum interchange_admin_group group;
};

#ifdef __cplusplus
extern "C" {
#endif

void interchange_admin_login(const char *username, const char *password,
		const char *nextpage, const char *successpage,
		const char *failpage, void (*handler)(interchange_response *),
		void (*callback)(struct interchange_admin *));
void interchange_admin_new_admin(const char *username, const char *password, const char *name, bool super,
		enum interchange_admin_group group, void (*handler)(interchange_response *));
void interchange_admin_new_item(const char *description, const char *comment, const char *price,
		const char *image_path, void (*handler)(interchange_response *));
void interchange_admin_new_transaction(const struct interchange_ord_order *order,
		const struct interchange_member *member, bool new_customer_id,
		void (*handler)(interchange_response *));
void interchange_admin_logout(struct interchange_admin *admin, void (*handler)(interchange_response *));

#ifdef __cplusplus
}
#endif

#endif
