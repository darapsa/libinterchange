#include <stdlib.h>
#include <stdbool.h>
#include "login.h"
#include "icclient/admin.h"

typedef struct icclient_admin icclient_admin;

icclient_admin *icclient_admin_login(const char *username, const char *password,
		const char *successpage, const char *nextpage, const char *failpage,
		void (*handler)(icclient_fetch_t *))
{
	icclient_admin *admin = malloc(sizeof(icclient_admin));
	admin->name = NULL;
	admin->username = NULL;
	admin->super = false;
	login(username, password, NULL, "MMLogin", successpage, nextpage, failpage, handler, admin);
	return admin;
}

void icclient_admin_newitem(const char *description, const char *comment, const char *price, const char *image_path)
{
	request(NULL, NULL, &(struct body){ 15, {
			{ "mv_click", "process_filter" },
			{ "mv_data_fields", "sku description prod_group category comment inactive price wholesale image thumb image_large weight nontaxable gift_cert" },
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

void icclient_admin_logout(icclient_admin *admin)
{
	request(NULL, NULL, NULL, "%s", "admin/login");
	if (admin->name)
		free(admin->name);
	if (admin->username)
		free(admin->username);
	free(admin);
	admin = NULL;
}
