#include "hElement.h"

class Header
{
public:
	hElement **items;
	int domain;
	
	Header(int d);
	~Header();
	void itemFound(int itemID);
	void print();
	int getSupport(int itemID);
	hElement* getItem(int itemID);
};
