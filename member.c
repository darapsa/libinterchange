#include <stdlib.h>
#include "login.h"
#include "interchange/member.h"

void interchange_member_newaccount(const char *username, const char *password,
		const char *verify, const char *failpage,
		void (*handler)(interchange_response *),
		void (*callback)(struct interchange_member *))
{
	login(username, password, verify, "NewAccount", failpage, handler,
			(void (*)(void *))callback);
}

void interchange_member_login(const char *username, const char *password,
		const char *failpage, void (*handler)(interchange_response *),
		void (*callback)(struct interchange_member *))
{
	login(username, password, NULL, "Login", failpage, handler,
			(void (*)(void *))callback);
}

void interchange_member_setaccount(const char *fname, const char *lname,
		const char *address1, const char *address2, const char *city,
		const char *state, const char *zip, const char *email,
		const char *phone_day)
{
	request(NULL, NULL, &(struct body){ 13, {
			{ "mv_form_profile", "account_change" },
			{ "mv_todo", "return" },
			{ "mv_nextpage", "member/account" },
			{ "mv_check", "Save_database" },
			{ "fname", fname },
			{ "lname", lname },
			{ "address1", address1 },
			{ "address2", address2 },
			{ "city", city },
			{ "state", state },
			{ "zip", zip },
			{ "email", email },
			{ "phone_day", phone_day }
			}}, "%s", "process");
}

void interchange_member_changepassword(const char *password_old, const char *password, const char *verify)
{
	request(NULL, NULL, &(struct body){ 6, {
			{ "mv_action", "return" },
			{ "mv_check", "Change_password" },
			{ "mv_successpage", "member/service" },
			{ "mv_password_old", password_old },
			{ "mv_password", password },
			{ "mv_verify", verify }
			}}, "%s", "member/change_password");
}

void interchange_member_logout(struct interchange_member *member)
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
}
