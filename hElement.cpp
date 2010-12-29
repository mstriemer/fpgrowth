#include <stdio.h>

#include "hElement.h"
#include "TreeElement.h"

hElement::hElement(int _itemID, int _sup, TreeElement *_link)
{
	itemID = _itemID;
	sup = _sup;
	link = _link;
}

void hElement::print()
{
	printf("%d: %d\n", itemID, sup);
}