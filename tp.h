#ifndef tp_h
#define tp_h

#include "utils.h"
#include "LinkedList.h"
#include "Grammar.h"
#include "grammarProcessing.h"
#include "Automaton.h"
#include "automatonProcessing.h"

typedef enum {
	INGRAMMAR, INAUTOMATON, NOWHERE
} location;

location whereAmI(void);
void newSyntaxError(void);
void processGrammar(Grammar g);
void processAutomaton(Automaton a);

#endif
