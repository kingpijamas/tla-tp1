#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NO_ERROR 0

typedef enum {
	false=0,true
} boolean;

boolean containsChar(char * s, char c);
int indexOf(char * s, char c);
int indexOfLast(char * s);
char * concat(char * s, char * t);
char * strdup(const char * s);
void cleanBuffer(char * buffer, int i);
char getLast(char * s);
char * stringify(char c);
int ctoi(char c);
int getLastDigit(char * s);
#endif
