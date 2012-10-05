#ifndef fromDot_h
#define fromDot_h

#include <ctype.h>
#include "Automaton.h"
#include "LinkedList.h"
#include "Grammar.h"

Grammar fromAFDtoGR(Automaton M);
void printAutomaton(Automaton M);

#endif
