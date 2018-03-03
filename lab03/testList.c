// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/*
functions name:
DLList newDLList(); // create a new empty DLList

void freeDLList(DLList L)// free up all space associated with list
void putDLList(FILE *out, DLList L)// display list to file, one item per line
                                    // assumes that the file is open for writing
int validDLList(DLList L)// check sanity of a DLList (for testing)
char *DLListCurrent(DLList L)//current line
int DLListMove(DLList L, int n)// move to n next
                               // return 1 if reach end of list during move
                              // if current is currently null, return 1

int DLListMoveTo(DLList L, int i)// move to specified position in list
                                 // i'th node, assuming first node has i==1

void DLListBefore(DLList L, char *it)// insert an item before current item
                                     // new item becomes current item
void DLListAfter(DLList L, char *it)// insert an item after current item
                                    // new item becomes current item
void DLListDelete(DLList L)// delete current item
                           // new item becomes item following current
                           // if current was last, current becomes new last
                           // if current was only item, current becomes null
int DLListLength(DLList L) // return number of elements in a list
int DLListIsEmpty(DLList L)// is the list empty?

*/
void print_state(DLList L);
void print_state(DLList L)
{
  
   assert(validDLList(L));
   //print all the items
   printf("The Lines are:\n");
   putDLList(stdout, L);
   //print nitems
   //printf("The number of nitems is %d\n",L->nitems);
   //print current item, first item and last item;
   printf("The current item in the list is: ");
   if(L->curr!=NULL)
   {
      printf("%s",L->curr->value);
   }
   printf("\nThe first item in the list is: ");
   if(L->first!=NULL)
   {
      printf("%s",L->first->value);
   }
   printf("\nThe last item in the list is: ");
   if(L->last!=NULL)
   {
      printf("%s",L->last->value);
   }
   printf("\n");
}


int main(int argc, char *argv[])
{
   // TODO: more tests needed here
   printf("TEST1: Test for funcion: void DLListBefore(DLList L, char *it);\n");
   printf("Make a new empty list:\n");
	DLList L=newDLList();
	print_state(L);
	
	printf("Insert a line 'LINE1' to the empty list:\n");
	DLListBefore(L, "LINE1");
	print_state(L);
	
	printf("Insert a line 'LINE2' before the one item list:\n");
	DLListBefore(L, "LINE2");
	print_state(L);
	
	printf("Insert a line 'LINE3' before the first item:\n");
	DLListBefore(L, "LINE3");
	print_state(L);
	
	
	printf("move current node to the next item\n");
	DLListMove(L, 1);
	printf("Insert a line 'LINE4' before the first item:\n");
	DLListBefore(L, "LINE4");
	print_state(L);
	
	printf("move current node to the last item\n");
	DLListMove(L, 2);
   print_state(L);
	printf("Insert a line 'LINE5' before the last item:\n");
	DLListBefore(L, "LINE5");
	print_state(L);
	
	

   printf("\n\n\n\nTEST2: Test for funcion: void DLListDelete(DLList L);\n");

   printf("Delete the item in the middle of the list:\n");
   DLListDelete(L);
   print_state(L);

   printf("Delete the item in the last of the list:\n");
   DLListDelete(L);
   print_state(L);

   printf("move current node to the first item\n");
	DLListMove(L, -2);
   print_state(L);

   printf("Delete the item in the first of the list:\n");
   DLListDelete(L);
   print_state(L);

   printf("Delete the item in the last of the list:\n");
   DLListDelete(L);
   print_state(L);

   printf("Delete the only item in the list:\n");
   DLListDelete(L);
   print_state(L);



	
	// TODO: more tests needed here
   printf("\n\n\n\nTEST3: Test for funcion: void DLListBefore(DLList L, char *it);\n");
	print_state(L);
	
	printf("Insert a line 'LINE1' to the empty list:\n");
	DLListAfter(L, "LINE1");
	print_state(L);
	
	printf("Insert a line 'LINE2' after the one item list:\n");
	DLListAfter(L, "LINE2");
	print_state(L);
	
   printf("move current node to the first item\n");
	DLListMove(L, -1);
   print_state(L);

	printf("Insert a line 'LINE3' after the first item:\n");
	DLListAfter(L, "LINE3");
	print_state(L);
	
	
	printf("Insert a line 'LINE4' after the current item:\n");
	DLListAfter(L, "LINE4");
	print_state(L);
	
	printf("move current node to the last item\n");
	DLListMove(L, 1);
   print_state(L);
	printf("Insert a line 'LINE5' before the last item:\n");
	DLListAfter(L, "LINE5");
	print_state(L);
	
	freeDLList(L);
	
	return 0;
}
