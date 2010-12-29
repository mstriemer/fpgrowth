#include "ItemSet.h"

ItemSet::ItemSet(int item)
{
	items = new int[1];
	items[0] = item;
	size = 1;
}

ItemSet::ItemSet(int item, ItemSet *set)
{
	bool itemIn = false;
	int j = 0;
	size = set->size + 1;
	items = new int[size];
	for (int i = 0; i < size)
	{
		if (!itemIn && item < set[j])
		{
			items[i] = item;
			itemIn = true;
		}
		else
		{
			items[i] = set->items[j];
			j++;
		}
	}
}
