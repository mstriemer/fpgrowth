#include <stdio.h>

#include "Header.h"

Header::Header(int d)
{
	domain = d;
	items = new hElement*[domain];
	
	for (int i = 0; i < domain; i++)
		items[i] = new hElement(i + 1, 0, NULL);
}

Header::~Header()
{
	delete [] items;
}

void Header::itemFound(int itemID)
{
	items[itemID - 1]->sup++;
}

int Header::getSupport(int itemID)
{
	items[itemID - 1]->sup;
}

hElement* Header::getItem(int itemID)
{
	return items[itemID - 1];
}

void Header::print()
{
	for (int i = 0; i < domain; i++)
	{
		if (items[i]->sup > 0)
			items[i]->print();
	}
}
