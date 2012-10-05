#ifndef fromDot_h
#define fromDot_h
#include <stdio.h>
#include <ctype.h>
#include "Automaton.h"
#include "LinkedList.h"
#include "Grammar.h"

Grammar fromAFDtoGR(Automaton M);
void printAutomaton(Automaton M);
char * GrammarToString(Grammar G);
void printGrammar(Automaton a);

#endif
