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

void interchange_ord_checkout(const struct interchange_ord_order *order,
		const struct interchange_member *member,
		void (*handler)(interchange_response *))
{
	request(handler, NULL, &(struct body){ 14, {
		{ "mv_todo", "submit" },
		{ "mv_action", "refresh" },
		{ "mv_order_profile", order->profile },
		{ "fname", member->fname },
		{ "lname", member->lname },
		{ "address1", member->address1 },
		{ "address2", member->address2 },
		{ "city", member->city },
		{ "state", member->state },
		{ "zip", member->zip },
		{ "email", member->email },
		{ "phone_day", member->phone_day },
		{ "mv_same_billing", member->preferences.mv_same_billing? "1" : "0" },
		{ "email_copy", member->preferences.email_copy? "1" : "0" }
	}}, "%s", "ord/checkout");
}

void interchange_ord_free_order(struct interchange_ord_order *order)
{
	if (order->profile)
		free(order->profile);
	free(order);
}

void interchange_ord_free_transaction(struct interchange_ord_transaction
		*transaction)
{
	if (transaction->order_number)
		free(transaction->order_number);
	if (transaction->payment_method)
		free(transaction->payment_method);
	free(transaction);
}
