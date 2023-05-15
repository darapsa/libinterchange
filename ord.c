#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "interchange.h"
#include "interchange/member.h"
#include "interchange/ord.h"

void interchange_ord_order(const char *sku, const char *item,
		const unsigned int quantity,
		void (*parser)(interchange_response *))
{
	size_t length = 0;
	unsigned int qty = quantity;
	do {
		length++;
	} while ((qty /= 10));
	char *qty_str = malloc(length + 1);
	sprintf(qty_str, "%d", quantity);
	request(parser, NULL, &(struct body){ 4, {
		{ "mv_action", "refresh" },
		{ "mv_sku", sku },
		{ "mv_order_item", item },
		{ "mv_order_quantity", qty_str }
	}}, "%s", "ord/basket");
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
	request(parser, NULL, &(struct body){ 4 + (nextpage ? 1 : 0), {
		{ "mv_quantity_update", "1" },
		{ "mv_doit", "refresh" },
		{ name, qty_str },
		{ "mv_orderpage", orderpage ? orderpage : "ord/basket" },
		{ "mv_nextpage", nextpage }
	}}, "%s", "process");
}

void interchange_ord_checkout(const char *order_profile,
		struct interchange_member member,
		void (*handler)(interchange_response *))
{
	request(handler, NULL, &(struct body){ 14, {
		{ "mv_todo", "submit" },
		{ "mv_action", "refresh" },
		{ "mv_order_profile", order_profile },
		{ "fname", member.fname },
		{ "lname", member.lname },
		{ "address1", member.address1 },
		{ "address2", member.address2 },
		{ "city", member.city },
		{ "state", member.state },
		{ "zip", member.zip },
		{ "email", member.email },
		{ "phone_day", member.phone_day },
		{ "mv_same_billing", member.preferences.mv_same_billing? "1" : "0" },
		{ "email_copy", member.preferences.email_copy? "1" : "0" }
	}}, "%s", "ord/checkout");
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
