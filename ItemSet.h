#ifndef _ItemSet
#define _ItemSet

class ItemSet {
public:
	int *items;
	int size;
	
	ItemSet(int);
	ItemSet(int, ItemSet*);
	void printSet();
	bool compare(ItemSet*);
};
#endif