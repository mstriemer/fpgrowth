#ifndef _hElement
#define _hElement
class hElement {
public:
	int itemID;
	int sup;
	hElement *sibling;
	
	void print();
};
#endif
