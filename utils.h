#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NO_ERROR 0
#define EXCEPTION_BUFFER_SIZE 15

typedef enum {
	false=0,true
} boolean;

//Strings
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
char * newBuffer(int i);

//Errors and exceptions
void newInsufficientMemoryException(char * filename);
void newException(char * filename,char * text);
void processErrors(int err);

//Printing and formatting
void printSeparator(char * reference);

#endif
