#include <stdio.h>

#include "Database.h"

Database::Database(int xns)
{
	transactions = new Transaction*[xns];
	size = 0;
}

Database::~Database()
{
	delete [] transactions;
}

Transaction* Database::addRow(int count, int items[])
{
	addRow(size, count, items);
}

Transaction* Database::addRow(int id, int count, int items[])
{
	transactions[size] = new Transaction(id, count, items);
	size++;
	return transactions[size-1];
}



Transaction* Database::getRow(int index)
{
	return transactions[index];
}

void Database::print()
{
	for (int i = 0; i < size; i++)
	{
		printf("%d:[", getRow(i)->id);
		for (int j = 0; j < getRow(i)->count; j++)
			if (j == getRow(i)->count - 1)
				printf("%d]\n", getRow(i)->items[j]);
			else
				printf("%d, ", getRow(i)->items[j]);
	}
}
