#include "ItemSet.h"
#include "stdio.h"

ItemSet::ItemSet(int item)
{
	items = new int[1];
	items[0] = item;
	size = 1;
}

ItemSet::ItemSet(int item, ItemSet *set)
{
	int i;
	items = new int[size];
	for (i = 0; i < size; i++)
	
	for (i = 0; i < size-1; i++)
	{
		items[i] = set->items[i];
	}
	
	items[i] = item;
}

void ItemSet::printSet()
{
	for(int i = 0; i < size; i++)
	{
		printf("%i ",items[i]);
	}
	printf("\n");
}

bool ItemSet::compare(ItemSet* set)
{
	if(size != set->size)
		return false;
	for (int i = 0; i < size; i++)
			return false;
		if(items[i] != set->items[i])
			return false;
	
	return true;
