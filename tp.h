#ifndef tp_h
#define tp_h

#include "utils.h"
#include "LinkedList.h"
#include "Grammar.h"
#include "postProcessing.h"

void errorFound(ErrorCodes err);
ErrorCodes validate(Grammar g);

#endif
