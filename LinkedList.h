#ifndef LinkedList_h
#define LinkedList_h

#include <stdio.h>
#include <stdlib.h>

//Generic list lelement
typedef struct lelement{
    struct lelement *  next;
    struct lelement *  prev;
    void * data;
} lelement;

typedef lelement * Element;

//Generic List Structure
typedef struct llist {
    int NumEl;   //Number of lelement * s in list
    Element  pFirst;  //Ptr to first lelement *  in list
    Element  pLast;   //Ptr to last lelement *  in list
} llist;

typedef llist * List;

#define FOR_EACH(item_ptr, myList) \
     for (item_ptr = myList->pFirst; item_ptr != NULL; item_ptr=item_ptr->next)

void initList(List list);
Element addToList(void *item, List list);
void addElemToList(Element NewEl, List list);
void removeElemFromList(Element elem, List list);
#endif
