/* listIteratorG.c ... Generic List Iterator implementation
   Written by .... 


    You need to submit ONLY this file.... 

*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorG.h"

typedef struct Node {
   void *element;
   struct Node *next;
   struct Node *prev;

 

} Node;

typedef struct IteratorGRep {

  ElmCompareFp cmpFp;//int
  ElmNewFp newFp;//void *
  ElmFreeFp freeFp;//void *
  

  
  Node *first;
  Node *last;
  Node *cursprev;
  Node *cursnext;
  Node *last_return;
 
  
  // implement struct here .. 

} IteratorGRep;




//  Your  functions here .... 
IteratorG IteratorGNew(ElmCompareFp cmpFp, ElmNewFp newFp, ElmFreeFp freeFp)
{
   IteratorG new = malloc(sizeof(IteratorGRep));
   new->cmpFp = cmpFp;
   new->newFp = newFp;
   new->freeFp = freeFp;
   new->first=new->last=new->cursprev=new->cursnext=new->last_return=NULL;
   return new;
}

int add(IteratorG it, void *vp)//Inserts the specified value poined by vp into the list iterator it. The element is inserted immediately before the element that would be returned by next(), if any, and after the element that would be returned by previous(), if any. (If the list contains no elements, the new element becomes the sole element on the list.) 
//The new element is inserted before the implicit cursor: a subsequent call to next would be unaffected, and a subsequent call to previous would return the new element. Returns 1 if successful, 0 otherwise.
{
   if(it==NULL)
   {
      return 0;
   }
   else
   {
      
      Node *new_node = malloc(sizeof(Node));
      new_node->element = it->newFp(vp);
      
      if(it->first==NULL)
      {
         it->cursnext=new_node->next = new_node->prev = NULL;
         it->cursprev=it->first = it->last = new_node;
      }
      else
      {
         if(it->cursprev!=NULL)              //LEFT SIDE
         {
            it->cursprev->next = new_node;   //link the new_node to the cursprev
         }
         else
         {
            it->first = new_node;
         }
         new_node->prev = it -> cursprev;
         
         
         
         if(it->cursnext!=NULL)            //RIGHT SIDE
         {
            it->cursnext->prev = new_node; //link the new_node to the cursnext
         }
         else
         {
            it->last = new_node;
         }
         new_node->next = it-> cursnext;
         
         
         
         if(it->cursnext!=NULL)
         {
            it->cursprev = it->cursnext->prev; // adjust the cursprev
            //printf("haha\n");
         }
         else
         {
            it->cursprev = it->cursprev->next;
            //printf("hehe\n");
         }
         
         
      }
      return 1;
   }

}
int hasNext(IteratorG it)
//Returns 1 if the given list iterator has more elements when traversing the list in the forward direction, returns 0 otherwise.
{
   assert(it);
   if(it==NULL)
   {
      return 0;
   }
   if(it->cursnext==NULL)
   {
      return 0;
   }
   else
   {
      return 1;
   }

}
int hasPrevious(IteratorG it)
//Returns 1 if the given list iterator has more elements when traversing the list in the reverse direction, returns 0 otherwise.
{
   assert(it);
   if(it==NULL)
   {
      return 0;
   }
   if(it->cursprev==NULL)
   {
      return 0;
   }
   else
   {
      return 1;
   }
}

void * next(IteratorG it)
//Returns the pointer to the next value in the given list iterator and advances the cursor position. This method may be called repeatedly to iterate through the list, or intermixed with calls to previous to go back and forth. (Note that alternating calls to next and previous will return the same element repeatedly.) The method returns NULL if it has no next value.
{
   if(hasNext(it))
   {
         it->last_return = it->cursnext;
         it->cursprev=it->cursnext;
         it->cursnext=it->cursnext->next;
      return it->last_return->element;
   }
   return NULL;
}

void * previous(IteratorG it)
//Returns the pointer to the previous value in the given list iterator and moves the cursor position backwards. This method may be called repeatedly to iterate through the list backwards, or intermixed with calls to next to go back and forth. (Note that alternating calls to next and previous will return the same element repeatedly.) The method returns NULL if it has no previous value.
{
   if(hasPrevious(it))
   {
      it->last_return = it->cursprev;
      it->cursnext=it->cursprev;
      it->cursprev=it->cursprev->prev;
      return it->last_return->element;
   
   }
   return NULL;

}

int delete(IteratorG it)
//Deletes from the list iterator the last value that was returned by next or previous or findNext or findPrevious. Precondition: A call to delete must be IMMEDIATELY preceded by a successful call to one of next or previous or findNext or findPrevious. Returns 1 if successful, 0 otherwise (for example, invalid delete call).
{
   if(it==NULL)
   {
      return 0;
   }
   if(it->last_return!=NULL)
   {
         Node *left = NULL;
         Node *right = NULL;
         //modify the last and the first
         if(it->last_return == it->first)//we are going to delete the first 
         {
            if(it->first->next!=NULL)
            {
               it->first = it->first->next;
            }
            else
            {
               it->first = NULL;
            }
         }
         else
         if(it->last_return ==it->last)//we are going to delete the last
         {
            if(it->last->prev!=NULL)
            {
               it->last = it->last->prev;
            }
            else
            {
               it ->last = NULL;
            }
         }
         
         
      if(it->last_return == it->cursprev)//delete the left cursor
      {
         //printf("deleting left cursor\n");
         left = it->cursprev->prev;
         right = it ->cursnext;
         it->freeFp(it->last_return->element);
         free(it->last_return);
         if(left!=NULL)
         {
            left->next = right;
         }
         if(right!=NULL)
         {
            right->prev =left;
         }
         it->cursnext = right;
         it->cursprev = left;
      }
      else
      
      if(it->last_return == it -> cursnext)//delete the right cursor
      {
         //printf("deleting right cursor\n");
         left = it->cursprev;
         right = it ->cursnext->next;
         it->freeFp(it->last_return->element);
         free(it->last_return);
         if(left!=NULL)
         {
            left->next= right;
         }
         if(right!=NULL)
         {
            right->prev=left;
         }
         it->cursnext = right;
         it->cursprev = left;
      }
      else
      {
         fprintf(stderr,"WARNING:what should I delete? its neither left or right leg\n");
      }
      it->last_return = NULL;
      return 1;
   }
   else
   {
      return 0;
   }
}

int set(IteratorG it, void * vp)
//Replaces the last element returned by next or previous or findNext or findPrevious with the specified element (*vp). Precondition: A call to set must be IMMEDIATELY preceded by a successful call to one of next or previous or findNext or findPrevious. Returns 1 if successful, 0 otherwise (for example, invalid set call).
{
   if(it==NULL||it->last_return==NULL)
   {
      return 0;
   }
   else
   {
      it->last_return->element=it->newFp(vp);
      return 1;
   }
   
}
void * findNext(IteratorG it, void * vp)
//Returns pointer to the next value in it that matches the value pointed to by vp. and advances the cursor position past the value returned. The method returns NULL if there is no such next value and the cursor is not moved from the current position.
{
   if(it == NULL||it->first == NULL)
   {
      return NULL;
   }

   Node *current = it -> cursnext;
   while(current!=NULL)
     {
         if(it->cmpFp(vp,current->element)==0)//compare each node with vp, if found it
         {
            it->last_return=current;
            it->cursprev= current;
            it->cursnext= it-> cursprev->next;
            return current->element;
         }
         current = current->next;
     }
   return NULL;
}



void * findPrevious(IteratorG it, void * vp)
//Returns pointer to the previous value in it that matches the value pointed to by vp and moves the cursor position backwards before the value returned. The method returns NULL if there is no such previous value and the cursor is not moved from the current position. 
{
   if(it == NULL||it->first == NULL)
   {
      return NULL;
   }
   Node *current = it -> cursprev;
   while(current!=NULL)
     {
         if(it->cmpFp(vp,current->element)==0)//compare each node with vp, if found it
         {
            it->cursnext = current;
            it->cursprev = it-> cursnext->prev;
            
            return current->element;
         }
         current = current->prev;
     }
    return NULL;
}

void reset(IteratorG it)
//Resets it to the start of the list.
{
   if(it == NULL||it->first == NULL)
   {
      return;
   }
   else
   {
      it->cursprev = NULL;
      it->cursnext = it->first;
   }
}

void freeIt(IteratorG it)
//Deletes all the nodes in it and frees associated memory.
{
   if(it==NULL)
   {
      return;
   }
   if(it->first==NULL)
   {
      free(it);
      return;
   }
   else
   {
      Node* current = it->first;
      Node* right = current->next;
      while(right!=NULL)
      {
         it->freeFp(current->element);
         free(current);
         current = right;
      }
      free(current);
   }

}





// --------------------------------------













