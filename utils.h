#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
	false=0,true
} boolean;

typedef enum {
	OK=0,INVALID_DIST,INVALID_FROM,INVALID_NONTERMINAL,INVALID_TERMINAL,DIST_NOT_USED
} ErrorCodes;

boolean containsChar(char * s, char c);
int indexOf(char * s, char c);
int indexOfLast(char * s);
char * concat(char * s, char * t);
char * strdup(const char * s);

#endif
