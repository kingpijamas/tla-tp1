%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "LinkedList.h"
	
	#define LEFT 0
	#define RIGHT 1
	#define NONE 2	

	char* concat(char* s, char* t);
		
	char dir=NONE;
	char * gramName;
	char dist;
	char * nonTerminals;
	char * terminals;
	List productions;
	Production *p;
%}

digit	[0-9]
letter	[a-zA-Z]
upper	[A-Z]
lower	[a-z]
lambda	\\
blank	[ \t\n]

%option noyywrap

%s GRAMNAME
%s START
%s DIST
%s NONTERMINALS
%s TERMINALS
%s PRODF
%s PRODT


%%
{blank}+ ;
<INITIAL>{letter}(^{blank})* {gramName=strdup(yytext);printf("\nyytext: %s gramName:%s\n",yytext,gramName); BEGIN START;}
<START>\={blank}*\({blank}*\{ {printf("START\n"); BEGIN NONTERMINALS;}
<NONTERMINALS>{upper}{blank}*, {yytext[1]=0; nonTerminals=concat(nonTerminals,yytext);printf("nonTerminals %s\n",nonTerminals);}
<NONTERMINALS>{upper}{blank}*\}{blank}*,{blank}*\{ {yytext[1]=0; nonTerminals=concat(nonTerminals,yytext); printf("nonTerminals %s\n",nonTerminals);BEGIN TERMINALS;}
<TERMINALS>{lower}{blank}*, {yytext[1]=0; terminals=concat(terminals,yytext);printf("terminals %s\n",terminals);}
<TERMINALS>{lower}{blank}*\}{blank}*, {yytext[1]=0; terminals=concat(terminals,yytext); printf("terminals %s\n",terminals);BEGIN DIST;}
<DIST>{upper}{blank}*,{blank}*\{ {dist = yytext[0];printf("Dist: %c\n",dist); productions=malloc(sizeof(llist)); initList(productions); BEGIN PRODF;}
<PRODF>{upper}{blank}*\-> {p=AddToList(productions);p->prod->from=yytext[0]; BEGIN PRODT;}
<PRODT>{lower}{blank}*{upper}{blank}*, {if(dir==LEFT){printf("Error");return 1;};dir=RIGHT;p=AddToList(productions);p->prod->terminal=yytext[0];p->prod->nonTerminal=yytext[indexOfLast(yytext)];}
<PRODT>{upper}{blank}*{lower}{blank}*, {if(dir==RIGHT){printf("Error");return 1;};dir=LEFT;p=AddToList(productions);p->prod->terminal=yytext[indexOfLast(yytext)];p->prod->nonTerminal=yytext[0];}


%%

int indexOfLast(char *s){
	int i=strlen(s)-1;	
	while(i>0){
		if(!(s[i]=='\t'||s[i]=='\n'||s[i]==' ')){
			return i;
		}		
		i--;	
	}
	return i;
}



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
