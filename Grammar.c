#include "Grammar.h"

Grammar newGrammar(){
	Grammar g=malloc(sizeof(grammar));
	if(g==NULL){
		printf("<LOG - tp.l>\n\tNull pointer.\n<end>\n");
	}
	g->dir=NONE;
	//esto puede ir en una funcion nueva "initProductions"
	g->productions=malloc(sizeof(llist));
	initList(g->productions);
	//hasta aca
	return g;
}

void addNonTerminal(Grammar g, char * from){
	g->nonTerminals=concat(g->nonTerminals,from);
}

void addTerminal(Grammar g, char * from){
	g->terminals=concat(g->terminals,from);
}

void setDirection(Grammar g, Directions d){
	if(g->dir!=d && g->dir!=NONE){
		printf("Error");
		return;
	};
	g->dir=d;
}
