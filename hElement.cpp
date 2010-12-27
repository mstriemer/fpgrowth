#include <stdio.h>

#include "hElement.h"

void hElement::print()
{
	printf("%d: %d -> ", itemID, sup);
	if (sibling)
		sibling->print();
	else
		printf("NULL\n");
}