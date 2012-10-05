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
		printf("Incompatible productions (Both left and right productions detected)\nProgram terminated\n");
		exit(1);
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

void removeNonTerminal(Grammar g, char c){
	int i = indexOf(g->nonTerminals, c);
	int j;
	for(j = i; j < strlen(g->nonTerminals)-1; j++){
		g->nonTerminals[j] = g->nonTerminals[j+1];
	}
	g->nonTerminals[strlen(g->nonTerminals)-1] = 0;
}

void printGrammar(Grammar g){
	//TIRA SEGFAULT
	char * stringy;
	char * buffer = malloc(50);
	stringy = strdup("====================================================\nGramatica ");
	sprintf(buffer, "%s\nSimbolos no terminales: \n", g->name);
	//stringy = concat(stringy, g->name);
	//stringy = concat(stringy, "\nSimbolos no terminales: ");
	int i;
	stringy = concat(stringy, buffer);
	for(i = 0; i < strlen(g->nonTerminals); i++){
		cleanBuffer(buffer, 50);
		sprintf(buffer, "%c ", g->nonTerminals[i]);
		stringy = concat(stringy, buffer);
	}
	stringy = concat(stringy, "\nSimbolos terminales: \n");
	for(i = 0; i < strlen(g->terminals); i++){
		cleanBuffer(buffer, 50);
		sprintf(buffer, "%c ", g->terminals[i]);
		stringy = concat(stringy, buffer);
	}
	printf("%s\n", stringy);
}
