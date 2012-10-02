#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
	false=0,true
} boolean;

boolean containsChar(char * s, char c);
int indexOf(char * s, char c);
int indexOfLast(char * s);
char * concat(char * s, char * t);
char * strdup(const char * s);

#endif