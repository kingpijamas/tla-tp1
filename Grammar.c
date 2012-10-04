#include "Grammar.h"

Grammar newGrammar(){
	Grammar g=malloc(sizeof(grammar));
	if(g==NULL){
		printf("<LOG - Grammar.c>\n\tInsufficient memory.\n<end>\n");
	}
	g->dir=NONE;
	//esto puede ir en una funcion nueva "initProductions"
	g->productions=newList();
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

Production newProduction(Grammar g){
	Production p=malloc(sizeof(production));	
	addProduction(g,p);
	return p;
}

void addProduction(Grammar g, Production p){
	addToList(p,g->productions);
}

Production getLastProduction(Grammar g){
	return ((Production)(g->productions->pLast)->data);
}
