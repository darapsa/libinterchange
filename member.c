#include <stdlib.h>
#include <stdbool.h>
#include "login.h"
#include "icclient/member.h"

typedef struct icclient_member icclient_member;

icclient_member *initialise(const char *username, const char *password)
{
	icclient_member *member = malloc(sizeof(icclient_member));
	member->username = NULL;
	member->usernick = NULL;
	member->password = NULL;
	member->expiration = NULL;
	member->acl = NULL;
	member->mod_time = NULL;
	member->s_nickname = NULL;
	member->company = NULL;
	member->fname = NULL;
	member->lname = NULL;
	member->address1 = NULL;
	member->address2 = NULL;
	member->address3 = NULL;
	member->city = NULL;
	member->state = NULL;
	member->zip = NULL;
	member->country = NULL;
	member->phone_day = NULL;
	member->mv_shipmode = NULL;
	member->b_nickname = NULL;
	member->b_fname = NULL;
	member->b_lname = NULL;
	member->b_company = NULL;
	member->b_address1 = NULL;
	member->b_address2 = NULL;
	member->b_address3 = NULL;
	member->b_city = NULL;
	member->b_state = NULL;
	member->b_zip = NULL;
	member->b_country = NULL;
	member->b_phone = NULL;
	member->p_nickname = NULL;
	member->email = NULL;
	member->fax = NULL;
	member->phone_night = NULL;
	member->address_book = NULL;
	member->accounts = NULL;
	member->preferences = NULL;
	member->carts = NULL;
	member->owner = NULL;
	member->file_acl = NULL;
	member->db_acl = NULL;
	member->mail_list = NULL;
	member->credit_limit = NULL;
	member->inactive = false;
	member->dealer = false;
	member->price_level = NULL;
	return member;
}

icclient_member *icclient_member_newaccount(const char *username, const char *password,
		const char *verify, const char *successpage, const char *nextpage,
		const char *failpage, size_t (*handler)(void *, size_t, size_t, void *))
{
	icclient_member *member = initialise(username, password);
	login(username, password, verify, "NewAccount", successpage, nextpage, failpage,
			handler, member);
	return member;
}

icclient_member *icclient_member_login(const char *username, const char *password,
		const char *successpage, const char *nextpage, const char *failpage,
		size_t (*handler)(void *, size_t, size_t, void *))
{
	icclient_member *member = initialise(username, password);
	login(username, password, NULL, "Login", successpage, nextpage, failpage, handler,
			member);
	return member;
}

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

void icclient_member_logout(icclient_member *member)
{
	request(NULL, NULL, NULL, "%s", "logout");
}
