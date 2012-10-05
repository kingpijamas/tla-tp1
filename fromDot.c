#include "fromDot.h"

List clausuraLambda(List Q, Automaton M){

	List L = malloc(sizeof(llist));
	Element ptr, ptr2, ptr3, ptr4;
	Transition tran;
	State s;
	char t;
	int contains;

	FOR_EACH(ptr, Q){

		s = malloc(sizeof(state));
		s->K = ((State)ptr->data)->K;
		addToList(s,L);
	}

	FOR_EACH(ptr, L){

		((State)ptr->data)->mark = MARK;
		t = ((State)ptr->data)->K;
		

		FOR_EACH(ptr2, M->delta){
			
			tran = (Transition)ptr2->data;
			if(tran->from->K == t && tran->by == '\\'){

				FOR_EACH(ptr3, tran->to){
					contains = 0;
					FOR_EACH(ptr4, L){
						if(((State)ptr3->data)->K == ((State)prt4->data)->K){
							contains = 1;
						}
					}
					s = malloc(sizeof(state));
					s->K = ((State)ptr3->data)->K;
					s->mark = UNMARK;
					addToList(s,L);
				}
			}

		}
	}

	return L;
}

List mover(List T, char a, Automaton M){




}

