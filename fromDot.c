#include "fromDot.h"

Grammar fromAFDtoGR(Automaton M){

	Grammar G = malloc(sizeof(grammar));
	
	char * nonTerminals = malloc(1 + M->stateList->NumEl);
	int i,j, isFinal;
	char q,a,r,f;
	Transition tran;
	Production prod;
	Element ptr,ptr2,ptr3;

	//0_ Cargo q0 como dist
	G->name = "G";
	G->dist = M->q0->K;
	G->productions = malloc(sizeof(llist));
	G->dir = RIGHT;
	

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

void printAutomaton(Automaton M){

	int i;
	Element elem,elem2,elem3;
	Transition tran;
	State s;
	printf("ALFABETO: Los simbolos terminales son:\n");

	for(i=0; (M->sigma)[i]!= 0; i++){
		printf("%c  ",(M->sigma)[i]);
	}
	printf("\n");

	printf("ESTADOS:\n");

	FOR_EACH(elem, M->stateList){
		printf("%c  ",((State)elem->data)->K);
	}
	printf("\n");

	printf("ESTADO INICIAL: %c\n", M->q0.K);

	printf("ESTADOS FINALES:\n");

	FOR_EACH(elem, M->finals){
		printf("%c  ",((State)elem->data)->K);
	}
	printf("\n");

	printf("  DELTA  ||");

	for(i=0; (M->sigma)[i] != 0; i++){
		printf("  %c  |",(M->sigma)[i]);		
	}

	FOR_EACH(elem, M->stateList){
	
		s = (State)elem->data;
		printf("    %c    ||\n", s->K);

		FOR_EACH(elem2, M->delta){
			tran = (Transition)elem2->data;
			if(tran->from.K == s->K){
				for(i=0; (M->sigma)[i] != 0; i++){
					if((M->sigma)[i] == tran->by){
						FOR_EACH(elem3, tran->to){
							printf("  %c  |",((State)elem->data)->K);
						
						}
					}else{
						printf("      |");
					}
				}
			}
		}

	}

	return;
}
