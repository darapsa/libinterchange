#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "interchange.h"
#include "interchange/member.h"
#include "interchange/ord.h"

void interchange_ord_order(const char *sku, const char *item,
		const unsigned int quantity, const char *options[][2],
		void (*parser)(interchange_response *))
{
	size_t length = 0;
	unsigned int qty = quantity;
	do {
		length++;
	} while ((qty /= 10));
	char *qty_str = malloc(length + 1);
	sprintf(qty_str, "%d", quantity);
	const char **pair = *options;
	size_t nopts = 0;
	while (pair[0] && pair[1]) {
		nopts++;
		pair = *++options;
	}
	for (size_t i = 0; i < nopts; i++)
		--options;
	size_t total_nopts = 4 + nopts;
	const char *order[total_nopts + 1][2];
	order[0][0] = "mv_action";
	order[0][1] = "refresh";
	order[1][0] = "mv_sku";
	order[1][1] = sku;
	order[2][0] = "mv_order_item";
	order[2][1] = item;
	order[3][0] = "mv_order_quantity";
	order[3][1] = qty_str;
	static const char *prefix = "mv_order_";
	for (size_t i = 0; i < nopts; i++) {
		const char **pair = options[i];
		order[4 + i][0] = malloc(strlen(prefix) + strlen(pair[0]) + 1);
		sprintf((char *)order[4 + i][0], "%s%s", prefix, pair[0]);
		order[4 + i][1] = malloc(strlen(pair[1]) + 1);
		strcpy((char *)order[4 + i][1], pair[1]);
	}
	order[total_nopts][0] = NULL;
	request(parser, NULL, order, "%s", "ord/basket");
}

void interchange_ord_update(const char *name, const unsigned int quantity,
		const char *orderpage, const char *nextpage,
		void (*parser)(interchange_response *))
{
	size_t length = 0;
	unsigned int qty = quantity;
	do {
		length++;
	} while ((qty /= 10));
	char *qty_str = malloc(length + 1);
	sprintf(qty_str, "%d", quantity);
	request(parser, NULL, (const char *[][2]){
		"mv_quantity_update", "1",
		"mv_doit", "refresh",
		name, qty_str,
		"mv_orderpage", orderpage ? orderpage : "ord/basket",
		"mv_nextpage", nextpage,
		NULL
	}, "%s", "process");
}

void interchange_ord_checkout(const char *order_profile,
		struct interchange_member member,
		void (*handler)(interchange_response *))
{
	request(handler, NULL, (const char *[][2]){
		"mv_todo", "submit",
		"mv_action", "refresh",
		"mv_order_profile", order_profile,
		"fname", member.fname,
		"lname", member.lname,
		"address1", member.address1,
		"address2", member.address2,
		"city", member.city,
		"state", member.state,
		"zip", member.zip,
		"email", member.email,
		"phone_day", member.phone_day,
		"mv_same_billing",
		member.preferences.mv_same_billing ? "1" : "0",
		"email_copy", member.preferences.email_copy? "1" : "0",
		NULL
	}, "%s", "ord/checkout");
}

void interchange_ord_free_order(struct interchange_ord_order *order)
{
	if (order->profile)
		free(order->profile);
	free(order);
}

void interchange_ord_clear_transaction(struct interchange_ord_transaction
		*transaction)
{
	if (transaction->order_number)
		free(transaction->order_number);
	if (transaction->payment_method)
		free(transaction->payment_method);
}
