#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <vector>

//#include "tree.hh"
//#include "tree_util.hh"

//#include <omp.h>
//#include <mpi.h>

#define LINE_BUF_SIZE 512
#define MIN_SUP 1
#define DOMAIN 1000

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
};

int compare(const void *a, const void *b) 
{ 
    hElement *ia = (hElement *)a;
    hElement *ib = (hElement *)b;
    return (int)(ib->sup - ia->sup);
}



int main(int argc, char *argv[] )
{	
	hElement header[DOMAIN];
	int headerCount = 0;
	
	//scan DB once, find frequent 1-itemset
	FILE *db = fopen("PreciseDB.txt","r");
	char line[LINE_BUF_SIZE];
	int  tid;
	int  itemCount;
	char *items;  
	char *item;
	
	fgets(line, LINE_BUF_SIZE, db);
	printf("Database transactions: %s",line);
	
	while(fgets(line, LINE_BUF_SIZE, db))
	{
		//split up the line by tab
		tid       = atoi(strtok (line,"\t"));
		itemCount = atoi(strtok (NULL,"\t"));
		items     = strtok (NULL,"\t");
		
		//printf("TID: %d,Item Count: %d,Items: %s",tid,itemCount,items);
		
		
		item = strtok (items," ");
		
		//parse the items
		while(item != NULL)
		{
			int temp = atoi(item);
			
			if(header[temp-1].sup == 0)
			{
				headerCount++;
			}
			
			header[temp-1].sup++;
			header[temp-1].itemID = temp;
			
			//printf(">: %s\n",item);
			item = strtok (NULL," ");
		}
	}
	
	int i;
	/*
	for(i = 0; i < DOMAIN; i ++)
	{
		printf("%d: %d\n", header[i].item, header[i].sup);
	}
	*/
	
	//Sort frequent items in frequency descending order into header table
    //qsort(header, DOMAIN, sizeof(hElement), compare);
	printf("\n");
	
	printf("Header:\n");
	printf("-------\n");
	for(i = 0; i < headerCount; i ++)
	{
		printf("%d: %d\n", header[i].itemID, header[i].sup);
	}
	
	//discard infrequent items
	
	rewind(db);
	
	//scan DB again, construct FP-Tree
	
	//time to make a tree!
	TreeElement *head, *curr;		//head is the root of the node, curr is the node we are checking ???
	head = new TreeElement;
	head->item.sup = -1;
	head->item.itemID = -1;
	
	fgets(line, LINE_BUF_SIZE, db);
	
	while(fgets(line, LINE_BUF_SIZE, db))
	{
		//split up the line by tab
		tid       = atoi(strtok (line,"\t"));
		itemCount = atoi(strtok (NULL,"\t"));
		items     = strtok (NULL,"\t");
		
		//printf("TID: %d,Item Count: %d,Items: %s",tid,itemCount,items);
		
		item = strtok (items," ");
		curr = head;
		
		
		
		//parse the items
		while(item != NULL)
		{
			int tempID = atoi(item);
			
			//check for an instance of item
			TreeElement *tempNode = curr->find(tempID);
			
			if(tempNode != NULL)
			{
				tempNode->item.sup++;
			}
			else//if it doesn't exist, make it.
			{
				tempNode = new TreeElement;
				tempNode->item.sup = 1;
				tempNode->item.itemID = tempID;
				curr->children.push_back(tempNode);
			}
			
			curr = tempNode;
			
			//printf(">: %s\n",item);
			item = strtok (NULL," ");
		}
	}
	
	
	
	//printout the tree
	for(int i = 0; i < head->children.size(); i++)
	{
		//printf("> %d:%d \n", head->children[i]->item.itemID,head->children[i]->item.sup);
	}
	
	
	return 0;
}
