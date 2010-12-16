#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

#include "Database.h"

#define LINE_BUF_SIZE 512

Database* read_database(char *filename)
{
	FILE *dbfile = fopen(filename,"r");
	int  tid;
	int  itemCount;
	char *itemsStr;
	char row[LINE_BUF_SIZE];
	Database *db = new Database(atoi(fgets(row, LINE_BUF_SIZE, dbfile)));
	
	while (fgets(row, LINE_BUF_SIZE, dbfile))
	{
		// Get the row info
		tid = atoi(strtok(row, "\t"));
		itemCount = atoi(strtok(NULL, "\t"));
		itemsStr = strtok(NULL, "\t");
		int items[itemCount];
		
		// Split up the itemStr into items
		items[0] = atoi(strtok(itemsStr, " "));
		for (int i = 1; i < itemCount; i++)
			items[i] = atoi(strtok(NULL, " "));
		
		// Add the row to the database
		db->addRow(itemCount, items);
	}
	
	return db;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <db_file>\n", argv[0]);
		exit(1);
	}
	
	Database* db = read_database(argv[1]);
	
	db->print();
	
	return 0;
}