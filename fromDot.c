#include "fromDot.h"

Grammar fromAFDtoGR(Automaton M){

	Grammar G = malloc(sizeof(grammar));
	G->productions = malloc(sizeof(llist));
	char * nonTerminals = malloc(1 + M->stateList->NumEl);
	int i,j, isFinal;
	char q,a,r,f;
	Transition tran;
	Production prod;
	Element ptr,ptr2,ptr3;

	//0_ Cargo q0 como dist
	G->dist = M->q0.K;

	//1_ Cargo los terminales
	addTerminal(G,M->sigma);

	//2_ Cargo los no terminales en nonTerminals con mayusculas
	// y luego los cargo en la gramatica
	for(i = 0, ptr = M->stateList->pFirst ; ptr!=NULL; i++, ptr=ptr->next){
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
				if(tran->from.K==q && tran->by==a){			
					// Agrego todos los r
					FOR_EACH(ptr2, tran->to){
						r = ((State)ptr->data)->K; 
						prod = malloc(sizeof(prod));
						prod->from = toupper(q);
						prod->nonTerminal = toupper(r);
						prod->terminal = tolower(a);
						addToList(prod,G->productions);
						// Si r pertenece a finales
						isFinal = 0;	
						for(ptr3 = M->finals->pFirst; ptr3!=NULL && !isFinal; ptr3=ptr3->next){
							f = ((State)ptr3->data)->K;
							if(f == r){
								isFinal = 1;
							}
						}
						if(isFinal){
						prod = malloc(sizeof(prod));
						prod->from = toupper(q);
						prod->terminal = toupper(a);
						addToList(prod,G->productions);
						}

					}
				}
			}
		}
	}

	//4_ si q0 es final, agrego esa tran
	FOR_EACH(ptr3, M->finals){
		f = ((State)ptr3->data)->K;
		if(f == G->dist){
			prod = malloc(sizeof(prod));
			prod->from = G->dist;
			prod->terminal = '\\';
			addToList(prod,G->productions);
		}
	}

	return  G;
}
