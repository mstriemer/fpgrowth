class Transaction
{
public:
	int id;
	int count;
	int *items;
	
	Transaction(int id, int count, int items[]);
	~Transaction();
};
