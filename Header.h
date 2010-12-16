#include "hElement.h"

class Header
{
public:
	Header(int d);
	~Header();
	void itemFound(int itemID);
	void print();
	int getSupport(int itemID);
	hElement* getItem(int itemID);
	
private:
	hElement *items;
	int domain;
};
