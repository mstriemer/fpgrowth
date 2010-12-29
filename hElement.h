#ifndef _hElement
#define _hElement

class TreeElement;

class hElement {
public:
	int itemID;
	int sup;
	TreeElement *link;
	
	hElement(int _itemID, int _sup, TreeElement *_link);
	void print();
};
#endif
