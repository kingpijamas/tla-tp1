#ifndef grammarProcessing_h
#define grammarProcessing_h

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "LinkedList.h"
#include "Grammar.h"

typedef struct relation{
	char reachable;
	Element elem;
}relation;

typedef relation * Relation;
typedef Relation * RelationMatrix;

typedef enum {
	INVALID_DIST=!NO_ERROR,INVALID_FROM,INVALID_NONTERMINAL,INVALID_TERMINAL,DIST_NOT_USED
} GrammarErrorCodes;

RelationMatrix generateRelationMatrix(Grammar g, int n);//n is the size of production
void findReachableProductions(RelationMatrix t,int n);//uses Warshall's algorithm
Grammar removeUnreachableProductions(Grammar g);
Grammar removeUnproductiveNodes(Grammar g);
Grammar toNormalRight(Grammar g);
Grammar normalize(Grammar g);
GrammarErrorCodes validateGrammar(Grammar g);
void printAutomatonFromGrammar(Grammar g);

#endif
