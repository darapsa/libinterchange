#ifndef ICCLIENT_MEMBER_H
#define ICCLIENT_MEMBER_H

struct icclient_member_preferences {
	bool mv_same_billing;
	bool email_copy;
};

struct icclient_member {
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
	struct icclient_member_preferences *preferences;
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

	struct icclient_member *icclient_member_newaccount(const char *username,
			const char *password, const char *verify, const char *successpage,
			const char *nextpage, const char *failpage, void (*handler)(icclient_fetch_t *));
	struct icclient_member *icclient_member_login(const char *username,
			const char *password, const char *successpage,
			const char *nextpage, const char *failpage, void (*handler)(icclient_fetch_t *));
	void icclient_member_account(const char *fname, const char *lname,
			const char *address1, const char *address2, const char *city,
			const char *state, const char *zip, const char *email,
			const char *phone_day);
	void icclient_member_changepassword(const char *password_old, const char *password,
			const char *verify);
	void icclient_member_logout(struct icclient_member *member);

#ifdef __cplusplus
}
#endif

#endif // ICCLIENT_MEMBER_H
