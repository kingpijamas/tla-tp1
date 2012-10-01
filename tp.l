%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	char* concat(char* s, char* t);

	typedef struct Production{	
		char from;
		char nonTerminal;
		char terminal;
	}Production;

	char * gramName;
	char dist;
	char * nonTerminals;
	char * terminals;
	Production * productions;
%}

digit	[0-9]
letter	[a-zA-Z]
upper	[A-Z]
lower	[a-z]
lambda	\
blank	[ \t\n]

%option noyywrap

%s GRAMNAME
%s START
%s DIST
%s NONTERMINALS
%s TERMINALS
%s PRODUCTIONS

%%
{blank}+ ;
<INITIAL>{letter}({letter}|{digit})* {gramName=strdup(yytext);printf("\nyytext: %s gramName:%s\n",yytext,gramName); BEGIN START;}
<START>\={blank}*\({blank}*\{ {printf("START\n"); BEGIN NONTERMINALS;}
<NONTERMINALS>{upper}{blank}*, {yytext[1]=0; nonTerminals=concat(nonTerminals,yytext);printf("nonTerminals %s\n",nonTerminals);}
<NONTERMINALS>{upper}{blank}*\}{blank}*,{blank}*\{ {yytext[1]=0; nonTerminals=concat(nonTerminals,yytext); printf("nonTerminals %s\n",nonTerminals);BEGIN TERMINALS;}
<TERMINALS>{lower}{blank}*, {yytext[1]=0; terminals=concat(terminals,yytext);printf("terminals %s\n",terminals);}
<TERMINALS>{lower}{blank}*\}{blank}*, {yytext[1]=0; terminals=concat(terminals,yytext); printf("terminals %s\n",terminals);BEGIN DIST;}
<DIST>{upper}{blank}*,{blank}*\{ {dist = yytext[0];printf("Dist: %c\n",dist); BEGIN PRODUCTIONS;}

%%

char * concat(char *s, char * t){
	if(s==0){
		s=strdup(t);
	}else{
		s = realloc(s,strlen(s)+strlen(t)+1);
		s = strcat(s,t);	
	}
	return s;
}

char *strdup(const char *s){
	char *d = malloc(strlen(s)+1);
	if(d == 0) return 0;
	strcpy(d,s);
	return d;
}

int main(void){
	yylex();
	return 0;
}
