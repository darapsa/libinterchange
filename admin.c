#include "login.h"
#include "icclient/admin.h"

void icclient_admin_login(size_t (*handler)(void *contents, size_t size
			, size_t nmemb, void *userdata)
		, struct icclient_user *user
		, const char *username, const char *password
		, const char *successpage, const char *nextpage
		, const char *failpage)
{
	login(handler, user, username, password, NULL, "MMLogin", successpage
			, nextpage, failpage);
}

void icclient_admin_logout()
{
	request(NULL, NULL, NULL, "%s", "admin/login");
}
