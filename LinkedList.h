#if !defined( LinkedList_h )
#define LinkedList_h

typedef struct production{	
		char from;
		char nonTerminal;
		char terminal;
}production;

typedef production * Production;

//Generic list lelement
typedef struct lelement{
    struct lelement *  next;
    struct lelement *  prev;
    Production prod;
} lelement;

typedef lelement * Element;

//Generic List Structure
typedef struct llist {
    int NumEl;   //Number of lelement * s in list
    lelement *  pFirst;  //Ptr to first lelement *  in list
    lelement *  pLast;   //Ptr to last lelement *  in list
} llist;

typedef llist * List;

#define FOR_EACH(item_ptr, myList) \
     for (item_ptr = myList->pFirst; item_ptr != NULL; item_ptr=item_ptr->next)

void initList(List list);
Element AddToList(List list);
void AddElemToList(Element NewEl, List list);
void Remove(Element elem, List list);

#endif
