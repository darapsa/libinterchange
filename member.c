#include <stdbool.h>
#include "request.h"
#include "icclient/member.h"

void icclient_member_account(const char *fname, const char *lname, const char *address1,
		const char *address2, const char *city, const char *state,
		const char *zip, const char *email, const char *phone_day)
{
	struct curl_httppost *post, *last = NULL;
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_form_profile",
			CURLFORM_COPYCONTENTS, "account_change",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_todo",
			CURLFORM_COPYCONTENTS, "return",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_nextpage",
			CURLFORM_COPYCONTENTS, "member/account",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_check",
			CURLFORM_COPYCONTENTS, "Save_database",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "fname",
			CURLFORM_PTRCONTENTS, fname,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "lname",
			CURLFORM_PTRCONTENTS, lname,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "address1",
			CURLFORM_PTRCONTENTS, address1,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "address2",
			CURLFORM_PTRCONTENTS, address2,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "city",
			CURLFORM_PTRCONTENTS, city,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "state",
			CURLFORM_PTRCONTENTS, state,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "zip",
			CURLFORM_PTRCONTENTS, zip,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "email",
			CURLFORM_PTRCONTENTS, email,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "phone_day",
			CURLFORM_PTRCONTENTS, phone_day,
			CURLFORM_END);
	last = NULL;
	request(NULL, NULL, post, "%s", "process");
	curl_formfree(post);
	post = NULL;
}

void icclient_member_changepassword(const char *password_old, const char *password,
		const char *verify)
{
	struct curl_httppost *post, *last = NULL;
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_action",
			CURLFORM_COPYCONTENTS, "return",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_check",
			CURLFORM_COPYCONTENTS, "Change_password",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_successpage",
			CURLFORM_COPYCONTENTS, "member/service",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_password_old",
			CURLFORM_PTRCONTENTS, password_old,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_password",
			CURLFORM_PTRCONTENTS, password,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_verify",
			CURLFORM_PTRCONTENTS, verify,
			CURLFORM_END);
	last = NULL;
	request(NULL, NULL, post, "%s", "member/change_password");
	curl_formfree(post);
	post = NULL;
}
