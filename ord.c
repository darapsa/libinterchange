#include <stdlib.h>
#include <stdbool.h>
#include "icclient/client.h"
#include "icclient/ord.h"

void icclient_ord_free(struct icclient_ord_order *order)
{
	for (size_t i = 0; i < order->nitems; i++)
		icclient_freeproduct(order->items[i]->product);
}
