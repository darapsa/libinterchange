#include <stdlib.h>
#include <stdbool.h>
#include "login.h"
#include "icclient/admin.h"

typedef struct icclient_admin icclient_admin;

icclient_admin *icclient_admin_login(const char *username, const char *password,
		const char *successpage, const char *nextpage, const char *failpage,
		size_t (*handler)(void *, size_t, size_t, void *))
{
	icclient_admin *admin = malloc(sizeof(icclient_admin));
	admin->name = NULL;
	admin->username = NULL;
	admin->super = false;
	login(username, password, NULL, "MMLogin", successpage, nextpage, failpage,
			handler, admin);
	return admin;
}

void icclient_admin_logout(icclient_admin *admin)
{
	request(NULL, NULL, NULL, "%s", "admin/login");
	if (admin->name)
		free(admin->name);
	if (admin->username)
		free(admin->username);
	free(admin);
	admin = NULL;
}
