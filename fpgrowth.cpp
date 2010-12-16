#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

#include "Database.h"
#include "Header.h"
#include "TreeElement.h"
#include "hElement.h"

#define LINE_BUF_SIZE 512

using namespace std;

Database* read_database(char *filename);
void bubble_sort(hElement *items[], int itemCount);

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Usage: %s <db_file> <minsup> <max_domain>\n", argv[0]);
		exit(1);
	}
	
	int minsup = atoi(argv[2]);
	int domain = atoi(argv[3]);
	Database* db = read_database(argv[1]);
	Transaction *row;
	Header *header = new Header(domain);
	
	// Find frequent 1-item sets
	for (int i = 0; i < db->size; i++)
	{
		for (int j = 0; j < db->getRow(i)->count; j++)
		{
			header->itemFound(db->getRow(i)->items[j]);
		}
	}
	
	// Construct the FP-Tree
	TreeElement *fpTree = new TreeElement(-1, -1);
	TreeElement *curr = fpTree;
	
	for (int i = 0; i < db->size; i++)
	{
		curr = fpTree;
		row = db->getRow(i);
		hElement *items[row->count];
		
		// Get the items from the header table
		for (int j = 0; j < row->count; j++)
		{
			items[j] = header->getItem(row->items[j]);
		}
		
		// Stable sort the elements into their sup order
		bubble_sort(items, row->count);
		
		// Go through the elements, while they meet minsup
		for (int j = 0; j < row->count && items[j]->sup >= minsup; j++)
		{
			// Add the child and set it to curr
			curr = curr->addChild(items[j]->itemID);
		}
	}
	
	printf("Database\n");
	db->print();
	printf("\nHeader\n");
	header->print();
	printf("\nFP-Tree\n");
	fpTree->print();
	
	exit(0);
}

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
		db->addRow(tid, itemCount, items);
	}
	
	return db;
}

void bubble_sort(hElement *items[], int itemCount)
{
	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		for (int i = 1; i < itemCount; i++)
		{
			if (items[i]->sup > items[i-1]->sup)
			{
				hElement* t = items[i];
				items[i] = items[i-1];
				items[i-1] = t;
				sorted = false;
			}
		}
	}
}
