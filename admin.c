#include "login.h"
#include "icclient/admin.h"

void icclient_admin_login(const char *username, const char *password
		, const char *successpage, const char *nextpage
		, const char *failpage)
{
	login(username, password, NULL, "MMLogin", successpage, nextpage, failpage);
}

void icclient_admin_logout()
{
	request(NULL, NULL, NULL, "%s", "admin/login");
}
