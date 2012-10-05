#ifndef tp_h
#define tp_h

#include "utils.h"
#include "LinkedList.h"
#include "Grammar.h"
#include "toDot.h"
#include "postProcessing.h"
#include "Automaton.h"
#include "fromDot.h"

typedef enum {
	INGRAMMAR, INAUTOMATON, NOWHERE
} location;

location whereAmI(void);
void newSyntaxError(void);
void processGrammar(Grammar g);
void processAutomaton(Automaton a);

#endif
