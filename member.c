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
		const char *failpage, icclient_handler handler)
{
	icclient_member *member = initialise(username, password);
	login(username, password, verify, "NewAccount", successpage, nextpage, failpage,
			handler, member);
	return member;
}

icclient_member *icclient_member_login(const char *username, const char *password,
		const char *successpage, const char *nextpage, const char *failpage, icclient_handler handler)
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
	if (member->username)
		free(member->username);
	if (member->usernick)
		free(member->usernick);
	if (member->password)
		free(member->password);
	if (member->expiration)
		free(member->expiration);
	if (member->acl)
		free(member->acl);
	if (member->mod_time)
		free(member->mod_time);
	if (member->s_nickname)
		free(member->s_nickname);
	if (member->company)
		free(member->company);
	if (member->fname)
		free(member->fname);
	if (member->lname)
		free(member->lname);
	if (member->address1)
		free(member->address1);
	if (member->address2)
		free(member->address2);
	if (member->address3)
		free(member->address3);
	if (member->city)
		free(member->city);
	if (member->state)
		free(member->state);
	if (member->zip)
		free(member->zip);
	if (member->country)
		free(member->country);
	if (member->phone_day)
		free(member->phone_day);
	if (member->mv_shipmode)
		free(member->mv_shipmode);
	if (member->b_nickname)
		free(member->b_nickname);
	if (member->b_fname)
		free(member->b_fname);
	if (member->b_lname)
		free(member->b_lname);
	if (member->b_company)
		free(member->b_company);
	if (member->b_address1)
		free(member->b_address1);
	if (member->b_address2)
		free(member->b_address2);
	if (member->b_address3)
		free(member->b_address3);
	if (member->b_city)
		free(member->b_city);
	if (member->b_state)
		free(member->b_state);
	if (member->b_zip)
		free(member->b_zip);
	if (member->b_country)
		free(member->b_country);
	if (member->b_phone)
		free(member->b_phone);
	if (member->p_nickname)
		free(member->p_nickname);
	if (member->email)
		free(member->email);
	if (member->fax)
		free(member->fax);
	if (member->phone_night)
		free(member->phone_night);
	if (member->address_book)
		free(member->address_book);
	if (member->accounts)
		free(member->accounts);
	if (member->preferences)
		free(member->preferences);
	if (member->carts)
		free(member->carts);
	if (member->owner)
		free(member->owner);
	if (member->file_acl)
		free(member->file_acl);
	if (member->db_acl)
		free(member->db_acl);
	if (member->mail_list)
		free(member->mail_list);
	if (member->credit_limit)
		free(member->credit_limit);
	if (member->price_level)
		free(member->price_level);
	free(member);
	member = NULL;
}
