#ifndef Grammar_h
#define Grammar_h

#include "LinkedList.h"
#include "utils.h"

typedef enum{
	LEFT=0,RIGHT,NONE
}Directions;

typedef struct production{
	char from;
	char nonTerminal;
	char terminal;
}production;

typedef production * Production;

typedef struct grammar{
	Directions dir;
	char * name;
	char dist;
	char * nonTerminals;
	char * terminals;
	List productions;
}grammar;

typedef grammar * Grammar;

Grammar newGrammar(void);
void addNonTerminal(Grammar g, char * from);
void addTerminal(Grammar g, char * from);
void setDirection(Grammar g, Directions d);
Production newProduction(Grammar g);
void addProduction(Grammar g, Production p);
Production getLastProduction(Grammar g);
void removeNonTerminal(Grammar g, char c);
void printGrammar(Grammar g);

#endif
