#ifndef INTERCHANGE_MEMBER_H
#define INTERCHANGE_MEMBER_H

#include <stdbool.h>
#include "typedefs.h"

struct interchange_member_preferences {
	bool mv_same_billing;
	bool email_copy;
};

struct interchange_member {
	char *username;
	char *usernick;
	char *password;
	char *expiration;
	char *acl;
	char *mod_time;
	char *s_nickname;
	char *company;
	char *fname; /*!< Shipping first name */
	char *lname; /*!< Shipping last name */
	char *address1;
	char *address2;
	char *address3;
	char *city;
	char *state;
	char *zip;
	char *country;
	char *phone_day;
	char *mv_shipmode;
	char *b_nickname;
	char *b_fname; /*!< Billing first name */
	char *b_lname; /*!< Billing last name */
	char *b_company;
	char *b_address1;
	char *b_address2;
	char *b_address3;
	char *b_city;
	char *b_state;
	char *b_zip;
	char *b_country;
	char *b_phone;
	char *p_nickname;
	char *email;
	char *fax;
	char *phone_night;
	char *address_book;
	char *accounts;
	struct interchange_member_preferences preferences;
	char *carts;
	char *owner;
	char *file_acl;
	char *db_acl;
	char *mail_list;
	char *credit_limit;
	bool inactive;
	bool dealer;
	char *price_level;
};

#ifdef __cplusplus
extern "C" {
#endif

void interchange_member_newaccount(const char *username, const char *password,
		const char *verify, const char *failpage,
		void (*handler)(interchange_response *),
		void (*callback)(struct interchange_member *));
void interchange_member_login(const char *username, const char *password,
		const char *failpage, void (*handler)(interchange_response *),
		void (*callback)(struct interchange_member *));
void interchange_member_account(const char *fname, const char *lname,
		const char *address1, const char *address2,
		const char *city, const char *state, const char *zip,
		const char *email, const char *phone_day);
void interchange_member_changepassword(const char *password_old,
		const char *password, const char *verify);
void interchange_member_logout(struct interchange_member *member);

#ifdef __cplusplus
}
#endif

#endif
