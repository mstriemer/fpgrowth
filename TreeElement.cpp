#include <stdio.h>

#include "TreeElement.h"

TreeElement::TreeElement(int itemID, int sup)
{
	item.itemID = itemID;
	item.sup = sup;
}

TreeElement* TreeElement::addChild(int itemID)
{
	TreeElement* child = find(itemID);
	
	if (child)
	{
		child->found();
	}
	else
	{
		child = new TreeElement(itemID, 1);
		children.push_back(child);
	}
	
	return child;
}

TreeElement* TreeElement::find(int itemID)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->item.itemID == itemID)
		{
			return children[i];
		}
	}
	return NULL;
}

void TreeElement::found()
{
	item.sup++;
}

void TreeElement::print(int nParents)
{
	if (item.itemID != 0)
	{
		for (int i = 0; i < nParents; i++)
			printf("\t");
			
		printf("%d:%d\n", item.itemID, item.sup);
	}
	
	for (int i = 0; i < children.size(); i++)
		children[i]->print(nParents + 1);
}

void TreeElement::print()
{
	print(0);
}
