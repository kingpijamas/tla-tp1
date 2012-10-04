#include "fromDot.h"
#include "Grammar.h"

// List clausuraLambda(List Q, Automaton M){

// 	List L = malloc(sizeof(llist));
// 	Element ptr, ptr2, ptr3, ptr4;
// 	Transition tran;
// 	State s;
// 	char t;
// 	int contains;

// 	FOR_EACH(ptr, Q){

// 		s = malloc(sizeof(state));
// 		s->K = ((State)ptr->data)->K;
// 		addToList(s,L);
// 	}

// 	FOR_EACH(ptr, L){

// 		((State)ptr->data)->mark = MARK;
// 		t = ((State)ptr->data)->K;
		
// 		FOR_EACH(ptr2, M->delta){
			
// 			tran = (Transition)ptr2->data;
// 			if(tran->from->K == t && tran->by == '\\'){

// 				FOR_EACH(ptr3, tran->to){
// 					contains = 0;
// 					FOR_EACH(ptr4, L){
// 						if(((State)ptr3->data)->K == ((State)prt4->data)->K){
// 							contains = 1;
// 						}
// 					}
// 					if(!contains){
// 						s = malloc(sizeof(state));
// 						s->K = ((State)ptr3->data)->K;
// 						s->mark = UNMARK;
// 						addToList(s,L);
// 					}
// 				}
// 			}

// 		}
// 	}

// 	return L;
// }

// List mover(List T, Automaton M, char a){

// 	List L;
// 	Element ptr,ptr2,ptr3,ptr4;
// 	State s;
// 	char t;
// 	Transition tran;
// 	int contains;

// 	L = malloc(sizeof(llist));

	
// 	FOR_EACH(ptr, T){

// 		t =	((State)ptr->data)->K;

// 		FOR_EACH(prt2, M->delta){
		
// 			tran = (Transition)ptr->data;
// 			if(t == tran->from->K && tran->by == a){
				
// 				FOR_EACH(ptr3, tran->to){

// 					contains = 0;
// 					FOR_EACH(ptr4 = L->pFirst; ptr4!=NULL && !contains; ptr4=ptr4->next){
// 						if(((State)ptr3->data)->K == ((State)prt4->data)->K){
// 							contains = 1;
// 						}
// 					}
// 					if(!contains){
// 						s = malloc(sizeof(state));
// 						s->K = ((State)ptr->data)->K;
// 						addToList(s,L);
// 					}
// 				}
// 			}
// 		}
// 	}

// 	return clausuraLambda(L,M);

// }

// Automaton fromAFNDLtoAFD(Automaton M){

// 	List auxL = malloc(sizeof(llist));
// 	List Kp = malloc(sizeof(llist));
// 	List U;
// 	State s,s2;
// 	Transition tran, tran2;
// 	Element ptr,ptr2,ptr3,ptr4,ptr5;
// 	char a, newName = 'A'- 1;
// 	int i, contains, existTran;

// 	Automaton F = malloc(sizeof(automaton));
	
// 	F->stateList = malloc(sizeof(llist));
// 	F->sigma = M->sigma;
// 	F->finals = malloc(sizeof(llist));
// 	F->delta = F->stateList = malloc(sizeof(llist));
// 	F->q0->K = A;



// 	s = malloc(sizeof(state));
// 	s->K = M->q0->K;
// 	addToList(s,auxL);

// 	List Q0 = clausuraLambda(auxL);
// 	Q0->name = newName;
// 	//freeStatesFromList(auxL);
// 	addToList(Q0,Kp);

// 	FOR_EACH(ptr,Kp){
// 		// El nombre del nuevo nodo sera la posicion en la lista
// 		if(ptr->mark == UNMARK){
// 			ptr->mark = MARK;

// 			FOR_EACH(){
				
// 			}

// 			for(i = 0; (M->sigma)[i] != 0; i++){
// 				U = mover(ptr,(M->sigma)[i]);
// 				if(U->NumEl != 0){
// 					contains = 0;
// 					FOR_EACH(ptr2 = L->pFirst; ptr2!=NULL && !contains; ptr2=ptr2->next){
// 						if(compareStateList(ptr2,U)==EQUALS){
// 							contains = 1;
// 						}
// 					}
// 					if(!contains){
// 						U->name = ++newName;
// 						addToList(U,Kp);
// 					}	

// 					s = malloc(sizeof(state));
// 					s->K = newName;
// 					addToList(s,F->stateList);	

// 					existTran = 0;
// 					FOR_EACH(ptr3 = F->delta->pFirst; ptr3!=NULL && !existTran; ptr3=ptr3->next){
// 						if(((Transition)ptr3->data)->from->K == ((List)ptr->data)->name){
// 							existTran = 1;
// 						}
// 					}
// 					s2 = malloc(sizeof(state));
// 					s2->K = U->name;
// 					if(!existTran){
// 						tran = malloc(sizeof(transition));
// 						tran->from = ((List)ptr->data)->name;
// 						tran->by = (M->sigma)[i];
// 						tran->to = malloc(sizeof(llist));				
// 						addToList(s2,tran->to);
// 					}else{// Si existe es porque ptr3 apunta a esa transicion
// 						addToList(s2,(Transition)ptr3->data)->to);
// 					}	
					
// 				}

// 			} 
// 		}
// 	}



// 	return F;
// }

// void freeStatesList(List L){

// 	Element elem;
// 	FOR_EACH(elem, L){
// 		free(elem->data);
// 	}
	

// 	//liberar elementos

// 	return;
// }

Grammar fromAFDtoGR(Automaton M){

	Grammar G = malloc(sizeof(grammar));
	G->productions = malloc(sizeof(llist));
	char * nonTerminals = malloc(1 + M->stateList->NumEl);
	int i,j;
	char q,a;
	Transition tran;
	Production prod;
	Element ptr,ptr2;

	//1_ Cargo los terminales
	addTerminal(G,M->sigma);
	
	//2_ Cargo los no terminales en nonTerminals con mayusculas
	// y luego los cargo en la gramatica
	for(i = 0, ptr = M->stateList ; ptr!=NULL; i++, ptr=ptr->next){
		nonTerminals[i] = toupper(((State)ptr->data)->K);
	}
	nonTerminals[i] = 0;
	
	addNonTerminal(G, nonTerminals);

	//3_ 
	for(i = 0; (G->nonTerminals)[i]; i++){
		a = (G->nonTerminals)[i];
		
		for(j = 0; (M->sigma)[j]; j++){			
			q = (M->sigma)[j];
			
			FOR_EACH(ptr, M->delta){
				tran = (Transition)ptr->data;
				if(tran->from->K==q && tran->by==a){			
					// Agrego todos los r
					FOR_EACH(ptr2;tran->to){
						prod = malloc(sizeof(prod));
						prod->from = toupper(q);
						prod->terminal = a;
						prod->to = toupper((()ptr2->data))
					}
				}
			}
		}
	}

	return  G;
}
