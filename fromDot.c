#include "fromDot.h"

void printAutomaton(Automaton M){

	int i;
	Element elem,elem2,elem3;
	Transition tran,tran2;
	State s;
	printf("\n\n ALFABETO: Los simbolos terminales son:\n");

	for(i=0; (M->sigma)[i]!= 0; i++){
		printf("%c  ",(M->sigma)[i]);
	}
	printf("\n\n");

	printf(" ESTADOS:\n");
	FOR_EACH(elem, M->stateList){
		printf("%c  ",((State)elem->data)->K);
	}
	printf("\n\n");

	printf(" ESTADO INICIAL: \n%c\n\n", M->q0->K);
	
	printf(" ESTADOS FINALES:\n");
	FOR_EACH(elem, M->finals){
		printf("%c  ",((State)elem->data)->K);
	}
	printf("\n");
	

 	printf("\n\n Transiciones:\n\n");	
	FOR_EACH(elem, M->delta){
		tran2 = (Transition)elem->data;
		FOR_EACH(elem2,tran2->to){
			printf("%c -> %c %c\n", tran2->from->K, tran2->by,((State)elem2->data)->K);	
		}
	}


	// printf("\n\n Tabla de transiciones\n\n");
	// printf("  DELTA  ||");
	// for(i=0; (M->sigma)[i] != 0; i++){
	// 	printf("  %c  |",(M->sigma)[i]);		
	// }

	// FOR_EACH(elem, M->stateList){
	// 	printf("\n");
	// 	s = (State)elem->data;
	// 	printf("    %c    ||", s->K);

	// 	FOR_EACH(elem2, M->delta){

	// 		tran = (Transition)elem2->data;
	// 		if(tran->from->K == s->K){
	// 			for(i=0; (M->sigma)[i] != 0; i++){
	// 				if((M->sigma)[i] == tran->by){
	// 					FOR_EACH(elem3, tran->to){
			
	// 						printf("  %c  |",((State)elem->data)->K);
						
	// 					}
	// 				}else{
	// 					printf("     |");
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	printf("\n");

	return;
}

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
		q = (G->nonTerminals)[i];		
		for(j = 0; (M->sigma)[j]; j++){			
			a = (M->sigma)[j];
			FOR_EACH(ptr, M->delta){
				tran = (Transition)ptr->data;
				if(tran->from->K==q && tran->by==a){			
					// Agrego todos los r
					FOR_EACH(ptr2, tran->to){
						r = ((State)ptr2->data)->K; 
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
							prod->terminal = tolower(a);
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


char * GrammarToString(Grammar G){

	char * string = NULL;
	char * aux = malloc(3);
	int i = 0;
	Element elem;
	Production prod;

	//G = ({
	string = concat(string, G->name);
	string = concat(string, " = ({");

	//G = ({A,B,C}
	for(i = 0; (G->nonTerminals)[i] != 0; i++){

		aux[0] = (G->nonTerminals)[i];
		if((G->nonTerminals)[i+1] == 0){
			aux[1] = '}';
		}else{
			aux[1] = ',';
		}
		aux[2] = 0;
		string = concat(string, aux);
	}

	//G = ({A,B,C},{
	string = concat(string,",{");
	
	//G = ({A,B,C},{a,b,c}
	for(i = 0; (G->terminals)[i] != 0; i++){

		aux[0] = (G->terminals)[i];
		if((G->terminals)[i+1] == 0){
			aux[1] = '}';
		}else{
			aux[1] = ',';
		}
		aux[2] = 0;
		string = concat(string, aux);
	}
	//G = ({A,B,C},{a,b,c},
	string = concat(string, ",");

	free(aux);
	aux = malloc(4);
	aux[0] = G->dist;
	aux[1] = ',';
	aux[2] = '{';
	aux[3] = 0;

	//G = ({A,B,C},{a,b,c},A,{
	string = concat(string,aux);
	free(aux);


	for(i = 0,elem = G->productions->pFirst; elem != NULL; i++, elem = elem->next){
		prod = (Production)elem->data;
		if(prod->nonTerminal == 0 || prod->terminal == 0){
			aux = malloc(6);
			if(prod->nonTerminal != 0){
				aux[3] = prod->nonTerminal;
			}else{
				aux[3] = prod->terminal;
			}
			//es la ultima
			if(i + 1 == G->productions->NumEl){
				aux[4] = '}';	
			}else{
				aux[4] = ',';
			}	
			aux[5] = 0;
		}else{
			aux = malloc(7);
			aux[3] = prod->terminal;
			aux[4] = prod->nonTerminal;
			//es la ultima
			if(i + 1 == G->productions->NumEl){
				aux[5] = '}';	
			}else{
				aux[5] = ',';
			}
			aux[6] = 0;
		}

		aux[0] = prod->from;
		aux[1] = '-';
		aux[2] = '>';

		string = concat(string,aux);

		free(aux);
	}
	string = concat(string, ")");

	return string;

}

void printGrammar(Automaton a){
	FILE *fp;
	fp=fopen("out.gr", "w");
	fprintf(fp, "%s", GrammarToString(fromAFDtoGR(a)));
	fclose(fp);
}
