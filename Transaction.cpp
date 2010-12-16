#include "Transaction.h"

Transaction::Transaction(int xid, int xcount, int xitems[])
{
	id = xid;
	count = xcount;
	items = new int[count];
	for (int i = 0; i < count; i++)
		items[i] = xitems[i];
}

Transaction::~Transaction()
{
	delete [] items;
}
