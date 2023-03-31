#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "interchange.h"
#include "interchange/member.h"
#include "interchange/ord.h"

void interchange_ord_order(const char *sku,
		void (*handler)(interchange_response *))
{
	request(handler, NULL, NULL, "%s%s", "order?mv_arg=", sku);
}

void interchange_ord_remove(const char *name, const char *nextpage,
		void (*parser)(interchange_response *))
{
	request(parser, NULL, &(struct body){ 2 + (nextpage ? 1 : 0), {
		{ name, "0" },
		{ "mv_doit", "refresh" },
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
