#include "Grammar.h"

Grammar newGrammar(){
	Grammar g=malloc(sizeof(grammar));
	if(g==NULL){
		printf("<LOG - tp.l>\n\tNull pointer.\n<end>\n");
	}
	g->dir=NONE;
	g->nonTerminals = malloc(sizeof(char)*27);
	g->terminals = malloc(sizeof(char)*27);
	//esto puede ir en una funcion nueva "initProductions"
	g->productions=malloc(sizeof(llist));
	initList(g->productions);
	//hasta aca
	return g;
}

void addNonTerminal(Grammar g, char * from){
	if(containsChar(g->nonTerminals, *from)){
		printf("Duplicate non terminal detected.\n Program terminated.\n");
		exit(1);
	}
	g->nonTerminals=concat(g->nonTerminals,from);
}

void addTerminal(Grammar g, char * from){
	if(containsChar(g->terminals, *from)){
		printf("Duplicate terminal detected.\n Program terminated.\n");
		exit(1);
	}
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
	cleanBuffer(buffer, 50);
	sprintf(buffer, "\nSimbolo inicial:\n%c\nLa gramatica es valida y es de ", g->dist );
	stringy = concat(stringy, buffer);
	if(g->dir == RIGHT){
		stringy = concat(stringy, "DERECHA");
	}else if(g->dir == LEFT){
		stringy = concat(stringy, "IZQUIERDA");
	}else{
		stringy = concat(stringy, "DERECHA o IZQUIERDA (las producciones valen para cualquier sentido)");
	}
	printf("%s\n", stringy);
}
