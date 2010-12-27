#include <vector>

#include "hElement.h"

class TreeElement
{
public:
	hElement item;
	std::vector<TreeElement*> children;
	
	TreeElement(int itemID, int sup, hElement *headerNode);
	TreeElement* find(int itemID);
	void print(int nParents);
	void print();
	void found();
	TreeElement* addChild(hElement *headerNode);
};