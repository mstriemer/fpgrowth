#include "Transaction.h"

class Transaction;
class Database
{
public:
	Transaction **transactions;
	int size;
	
	Database(int xns);
	~Database();
	Transaction* addRow(int count, int items[]);
	Transaction* addRow(int id, int count, int items[]);
	Transaction* getRow(int index);
	void print();
};