#include <stdlib.h>
#include <stdbool.h>
#include "login.h"
#include "icclient/admin.h"

typedef struct icclient_admin icclient_admin;

icclient_admin *icclient_admin_login(const char *username, const char *password,
		const char *successpage, const char *nextpage, const char *failpage,
		size_t (*handler)(void *, size_t, size_t, void *))
{
	icclient_admin *admin = malloc(sizeof(icclient_admin));
	admin->name = NULL;
	admin->username = NULL;
	admin->super = false;
	login(username, password, NULL, "MMLogin", successpage, nextpage, failpage,
			handler, admin);
	return admin;
}

void icclient_admin_newitem(const char *description, const char *comment,
		const char *price, const char *image_path)
{
	struct curl_httppost *post, *last = NULL;
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_click",
			CURLFORM_COPYCONTENTS, "process_filter",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_data_fields",
			CURLFORM_COPYCONTENTS, "sku description prod_group category comment inactive price wholesale image thumb image_large weight nontaxable gift_cert",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_ui",
			CURLFORM_COPYCONTENTS, "1",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "ui_new_item",
			CURLFORM_COPYCONTENTS, "1",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_todo",
			CURLFORM_COPYCONTENTS, "set",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_update_empty",
			CURLFORM_COPYCONTENTS, "1",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_action",
			CURLFORM_COPYCONTENTS, "set",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_data_table",
			CURLFORM_COPYCONTENTS, "products",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_data_function",
			CURLFORM_COPYCONTENTS, "insert",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_data_key",
			CURLFORM_COPYCONTENTS, "sku",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_return_table",
			CURLFORM_COPYCONTENTS, "products",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "sku",
			CURLFORM_PTRCONTENTS, image_path,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "description",
			CURLFORM_PTRCONTENTS, description,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "comment",
			CURLFORM_PTRCONTENTS, comment,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "price",
			CURLFORM_PTRCONTENTS, price,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "image",
			CURLFORM_FILE, image_path,
			CURLFORM_CONTENTTYPE, "image/jpeg",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_data_file_field",
			CURLFORM_COPYCONTENTS, "image",
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "mv_data_file_path",
			CURLFORM_COPYCONTENTS, "images/items",
			CURLFORM_END);
	last = NULL;
	request(NULL, NULL, post, "%s", "admin/item_edit");
	curl_formfree(post);
	post = NULL;
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
