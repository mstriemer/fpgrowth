#ifndef _TreeElement
#define _TreeElement

#include <vector>

class hElement;

class TreeElement
{
public:
	int sup;
	int itemID;
	TreeElement *sibling;
	TreeElement *parent;
	std::vector<TreeElement*> children;
	
	TreeElement(int _itemID, int _sup, TreeElement *_sibling, TreeElement *_parent);
	TreeElement* find(int itemID);
	void print(int nParents);
	void print();
	void found();
	TreeElement* getSibling();
	TreeElement* getParent();
	int getSupport();
	int getTotalSupport();
	int getItemID();
	TreeElement* addChild(hElement *headerNode);
};
#endif
