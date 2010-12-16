#include <vector>

#include "hElement.h"

class TreeElement
{
public:
	hElement item;
	std::vector<TreeElement*> children;
	
	TreeElement(int itemID, int sup);
	TreeElement* find(int itemID);
	void print(int nParents);
	void print();
	void found();
	TreeElement* addChild(int itemID);
};