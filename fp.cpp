#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <vector>

#include "Database.h"

#define LINE_BUF_SIZE 512

using namespace std;

typedef struct {
	int itemID;
	int sup;
} hElement;

class TreeElement
{
	public: 
	hElement item;
	vector<TreeElement*> children;
	
	TreeElement* find(int item)
	{
		int i;
		for(i = 0; i < children.size(); i++)
		{
			if(children[i]->item.itemID == item)
			{
				return children[i];
			}
		}
		return NULL;
	}
	
	TreeElement* print(int nParents)
	{
		if (item.itemID != 0)
		{
			for (int i = 0; i < nParents; i++)
				printf("\t");
				
			printf("%d:%d\n", item.itemID, item.sup);
		}
		
		for (int i = 0; i < children.size(); i++)
			children[i]->print(nParents + 1);
	}
};

int main(int argc, char *argv[] )
{
	if (argc != 4)
	{
		printf("Usage: %s <db_file> <minsup> <max_domain>\n", argv[0]);
		exit(1);
	}
	
	char *filename = argv[1];
	int minsup = atoi(argv[2]);
	int domain = atoi(argv[3]);
	
	// Initialize the header table
	hElement header[domain];
	for (int i = 0; i < domain; i++)
	{
		header[i].sup = 0;
		header[i].itemID = i + 1;
	}
	
	// Scan the DB finding frequent 1-itemsets
	FILE *db = fopen(filename,"r");
	char line[LINE_BUF_SIZE];
	int  tid;
	int  itemCount;
	char *itemstr;  
	char *item;
	int xns = atoi(fgets(line, LINE_BUF_SIZE, db));
	Database *tdb = new Database(xns);
	
	while(fgets(line, LINE_BUF_SIZE, db))
	{
		// Split up the line on tabs
		tid       = atoi(strtok (line,"\t"));
		itemCount = atoi(strtok (NULL,"\t"));
		itemstr     = strtok (NULL,"\t");
		
		item = strtok (itemstr," ");
		
		// Parse the items
		while(item != NULL)
		{
			header[atoi(item) - 1].sup++;
			item = strtok (NULL," ");
		}
	}
	
	// Scan the DB again constructing the FP-Tree
	rewind(db);
	TreeElement *head, *curr;
	head = new TreeElement;
	head->item.sup = -1;
	head->item.itemID = -1;
	
	fgets(line, LINE_BUF_SIZE, db);
	
	while(fgets(line, LINE_BUF_SIZE, db))
	{
		// Split up the line on tabs
		tid       = atoi(strtok (line,"\t"));
		itemCount = atoi(strtok (NULL,"\t"));
		itemstr   = strtok (NULL,"\t");
		hElement* items[itemCount];
		
		curr = head;
		
		item = strtok (itemstr," ");
		// Get the hElements for these itemIDs
		items[0] = &header[atoi(item) - 1];
		for (int i = 1; i < itemCount; i++)
		{
			item = strtok (NULL," ");
			items[i] = &header[atoi(item) - 1];
		}
		
		// Bubble sort the elements into their sup order
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
		
		// Go through the elements, while they meet minsup
		for (int i = 0; i < itemCount && items[i]->sup >= minsup; i++)
		{
			// Check if this node exists
			TreeElement *tempNode = curr->find(items[i]->itemID);
	
			if (tempNode != NULL)
			{
				tempNode->item.sup++;
			}
			else // It doesn't exist, make it
			{
				tempNode = new TreeElement;
				tempNode->item.sup = 1;
				tempNode->item.itemID = items[i]->itemID;
				curr->children.push_back(tempNode);
			}
			
			curr = tempNode;
		}
	}
	
	// Print out the tree
	head->print(0);
	
	exit(0);
}
