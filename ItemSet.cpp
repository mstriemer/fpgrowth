#include "ItemSet.h"
#include "stdio.h"

ItemSet::ItemSet(int item)
{
	size = 1;
	items = new int[size];
	items[0] = item;
}

ItemSet::ItemSet(int item, ItemSet *set)
{
	bool itemAdded = false;
	int j = 0;
	size = set->size + 1;
	items = new int[size];
	for (int i = 0; i < size; i++)
	{
		if (itemAdded || (j < set->size && set->items[j] < item))
		{
			items[i] = set->items[j];
			j++;
		}
		else
		{
			items[i] = item;
			itemAdded = true;
		}
	}
}

void ItemSet::printSet()
{
	for(int i = 0; i < size; i++)
		printf("%i ",items[i]);
	printf("\n");
}

bool ItemSet::compare(ItemSet *set)
{
	if (size != set->size)
		return false;
	for (int i = 0; i < size; i++)
		if (items[i] != set->items[i])
			return false;
	return true;
}
