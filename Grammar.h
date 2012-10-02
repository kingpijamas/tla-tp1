#ifndef Grammar_h
#define Grammar_h

#include "LinkedList.h"
#include "utils.h"

typedef enum{
	LEFT=0,RIGHT,NONE
}Directions;

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

#endif
