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
		const char *verify, const char *nextpage,
		const char *successpage, const char *failpage,
		void (*handler)(interchange_response *),
		void (*callback)(struct interchange_member *));
void interchange_member_login(const char *username, const char *password,
		const char *nextpage, const char *successpage,
		const char *failpage, void (*handler)(interchange_response *),
		void (*callback)(struct interchange_member *));

/*!
 * \brief For getting member account information.
 * \param handler A pointer to the function when a custom handler is needed to
 * arrange the data into the member instance.
*/
void interchange_member_account(void (*handler)(interchange_response *));

/*!
 * \brief For setting member account information.
 * \param member A pointer to a member instance whose members will be used in
 * POST data.
 * \param handler A pointer to the function when a custom handler is needed to
 * arrange the data into the member instance.
*/
void interchange_member_setaccount(const struct interchange_member *member,
		void (*handler)(interchange_response *));

void interchange_member_changepassword(const char *password_old,
		const char *password, const char *verify);
void interchange_member_logout();
void interchange_member_clear(struct interchange_member *member);

#ifdef __cplusplus
}
#endif

#endif
