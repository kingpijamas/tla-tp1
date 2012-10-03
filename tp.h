#ifndef tp_h
#define tp_h

#include "utils.h"
#include "LinkedList.h"
#include "Grammar.h"
#include "postProcessing.h"

void processErrors(ErrorCodes err);
ErrorCodes processGrammar(Grammar g);

#endif
