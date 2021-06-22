#include <stdlib.h>
#include <stdbool.h>
#include "login.h"
#include "icclient.h"
#include "icclient/member.h"
#include "icclient/ord.h"
#include "icclient/admin.h"

void icclient_admin_login(const char *username, const char *password, void (*handler)(icclient_response *),
		void (*callback)(struct icclient_admin *))
{
	login(username, password, NULL, "MMLogin", handler, (void (*)(void *))callback);
}

void icclient_admin_new_admin(const char *username, const char *password, const char *name, bool super,
		enum icclient_admin_group group, void (*handler)(icclient_response *))
{
	request(handler, NULL, &(struct body){ 13, {
		{ "mv_todo", "set" },
		{ "mv_data_table", "access" },
		{ "mv_data_key", "username" },
		{ "mv_update_empty", "1" },
		{ "mv_data_fields", "username password name super groups" },
		{ "mv_click", "process_filter" },
		{ "user_id", "NEW" },
		{ "name", name },
		{ "mv_data_function", "insert" },
		{ "username", username },
		{ "password", password },
		{ "super", super ? "1" : "0" },
		{ "groups", group == ICCLIENT_ADMIN_GROUP_CONTENT ? ":CONTENT"
		: group == ICCLIENT_ADMIN_GROUP_MERCH ? ":MERCH" : ":ORDERS" }
	}}, "%s", "ui");
}

void icclient_admin_new_item(const char *description, const char *comment, const char *price,
		const char *image_path, void (*handler)(icclient_response *))
{
	request(handler, NULL, &(struct body){ 15, {
		{ "mv_click", "process_filter" },
		{ "mv_data_fields", "sku description prod_group category comment inactive price wholesale"
						"image thumb image_large weight nontaxable gift_cert" },
		{ "mv_ui", "1" },
		{ "ui_new_item", "1" },
		{ "mv_todo", "set" },
		{ "mv_update_empty", "1" },
		{ "mv_action", "set" },
		{ "mv_data_table", "products" },
		{ "mv_data_function", "insert" },
		{ "mv_data_key", "sku" },
		{ "mv_return_table", "products" },
		{ "sku", image_path },
		{ "description", description },
		{ "comment", comment },
		{ "price", price }
		/*
		{ "image",
		CURLFORM_FILE, image_path,
		CURLFORM_CONTENTTYPE, "image/jpeg" },
		{ "mv_data_file_field", "image" },
		{ "mv_data_file_path", "images/items" }
		*/
	}}, "%s", "admin/item_edit");
}

void icclient_admin_new_transaction(const struct icclient_ord_order *order,
		const struct icclient_member *member, bool new_customer_id,
		void (*handler)(icclient_response *))
{
	request(handler, NULL, &(struct body){ 12, {
		{ "mv_values_space", "order_entry" },
		{ "order_desk_entry", "1" },
		{ "customer_id", member->username },
		{ "new_customer_id", new_customer_id ? "1" : "0" },
		{ "fname", member->fname },
		{ "lname", member->lname },
		{ "address1", member->address1 },
		{ "city", member->city },
		{ "zip", member->zip },
		{ "email", member->email },
		{ "country", member->country },
		{ "phone_day", member->phone_day }
	}}, "%s", "process");
}

void icclient_admin_logout(struct icclient_admin *admin, void (*handler)(icclient_response *))
{
	request(handler, NULL, NULL, "%s", "admin/login");
	if (admin->name)
		free(admin->name);
	if (admin->username)
		free(admin->username);
	free(admin);
}
