#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

void initList(List list){
    list->NumEl = 0;
    list->pFirst = NULL;
    list->pLast = NULL;
}

Element AddToList(List list){
    //check inputs
  //  assert(item!=NULL); assert(list!=NULL);
    if(list == NULL){
		printf("<LOG - LinkedList.c>\n\tNull pointer.\n<end>\n");
		
	}
	//Create generic element to hold item ptr
    Element NewEl = (Element)malloc(sizeof(lelement));  //create generic element
	
	if(NewEl == NULL){
		return NULL;
	}

    list->NumEl = list->NumEl + 1;
    NewEl->prod = malloc(sizeof(production));
    if (list->NumEl == 1){
      list->pFirst = NewEl;
      NewEl->prev = NULL;
      NewEl->next = NULL;
    }else{
      NewEl->prev = list->pLast;
      NewEl->next = NULL;
      list->pLast->next = NewEl;
    }
    list->pLast = NewEl;
    return NewEl;
}

void AddElemToList(Element NewEl, List list){
	list->NumEl = list->NumEl + 1;
    if (list->NumEl == 1){
      list->pFirst = NewEl;
      NewEl->prev = NULL;
      NewEl->next = NULL;
    }else{
      NewEl->prev = list->pLast;
      NewEl->next = NULL;
      list->pLast->next = NewEl;
    }
    list->pLast = NewEl;
    return;
}

void Remove(Element elem, List list){
	Element item;
	int flag;

	FOR_EACH(item, list){
		if(item == elem){
			flag = 1;
			break;
		}
	}
	
	if(flag == 0){
		return;
	}
		
	/* Soy el primero */
	if(list->pFirst == elem){
		list->pFirst = elem->next;
		if(elem->next != NULL){
			elem->next->prev = NULL;
		}
	}
	/* Soy el ultimo */
	if(list->pLast == elem){
		list->pLast = elem->prev;
		if(elem->prev != NULL){
			elem->prev->next = NULL;
		}
	}
	if(elem->prev != NULL && elem->next != NULL){
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
	}
	
	elem->prev = NULL;
	elem->next = NULL;
	
	(list->NumEl)--;
	
	return;
}
