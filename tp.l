%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "LinkedList.h"

	#define LEFT 0
	#define RIGHT 1
	#define NONE 2	

	#define FALSE 0
	#define TRUE 1

	#define OK 0
	#define INVALID_DIST 1
	#define INVALID_FROM 2
	#define INVALID_NONTERMINAL 3
	#define INVALID_TERMINAL 4
	#define DIST_NOT_USED 5

	int validate(void);
	char containsChar(char * string, char c);
	char* concat(char* s, char* t);
	void errorFound(int errNo);
	
	char dir=NONE;
	char * gramName;
	char dist;
	char * nonTerminals;
	char * terminals;
	List productions;
	Production p;
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
%s FROMPIPE
%s END


%%
{blank}+ ;
<INITIAL>{letter}(^{blank})* {gramName=strdup(yytext);printf("\nyytext: %s gramName:%s\n",yytext,gramName); BEGIN START;}
<START>\={blank}*\({blank}*\{ {printf("START\n"); BEGIN NONTERMINALS;}
<NONTERMINALS>{upper}{blank}*, {yytext[1]=0; nonTerminals=concat(nonTerminals,yytext);printf("nonTerminals %s\n",nonTerminals);}
<NONTERMINALS>{upper}{blank}*\}{blank}*,{blank}*\{ {yytext[1]=0; nonTerminals=concat(nonTerminals,yytext); printf("nonTerminals %s\n",nonTerminals);BEGIN TERMINALS;}
<TERMINALS>{lower}{blank}*, {yytext[1]=0; terminals=concat(terminals,yytext);printf("terminals %s\n",terminals);}
<TERMINALS>{lower}{blank}*\}{blank}*, {yytext[1]=0; terminals=concat(terminals,yytext); printf("terminals %s\n",terminals);BEGIN DIST;}
<DIST>{upper}{blank}*,{blank}*\{ {dist = yytext[0];printf("Dist: %c\n",dist); productions=malloc(sizeof(llist)); initList(productions); BEGIN PRODF;}
<PRODF>{upper}{blank}*\-> {p=AddToList(productions)->prod;p->from=yytext[0]; BEGIN PRODT;}

<PRODT>{lower}{blank}*{upper}{blank}*, {if(dir==LEFT){printf("Error");return 1;};dir=RIGHT;p->terminal=yytext[0];p->nonTerminal=yytext[indexOfLast(yytext)]; printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN PRODF;}
<PRODT>{upper}{blank}*{lower}{blank}*, {if(dir==RIGHT){printf("Error");return 1;};dir=LEFT;p->terminal=yytext[indexOfLast(yytext)];p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN PRODF;}
<PRODT>{upper}{blank}*, {p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN PRODF;}
<PRODT>({lower}|{lambda}){blank}*, {p->terminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN PRODF;}

<PRODT>{lower}{blank}*{upper}{blank}*\| {if(dir==LEFT){printf("Error"); return 1;};dir=RIGHT;p->terminal=yytext[0];p->nonTerminal=yytext[indexOfLast(yytext)];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal);p=AddToList(productions)->prod;p->from=productions->pLast->prev->prod->from; BEGIN PRODT;}
<PRODT>{upper}{blank}*{lower}{blank}*\| {if(dir==RIGHT){printf("Error"); return 1;};dir=LEFT;p->terminal=yytext[indexOfLast(yytext)];p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal);p=AddToList(productions)->prod;p->from=productions->pLast->prev->prod->from; BEGIN PRODT;}
<PRODT>{upper}{blank}*\| {p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal);p=AddToList(productions)->prod;p->from=productions->pLast->prev->prod->from; BEGIN PRODT;}
<PRODT>({lower}|{lambda}){blank}*\| {p->terminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal);p=AddToList(productions)->prod;p->from=productions->pLast->prev->prod->from; BEGIN PRODT;}

<PRODT>{lower}{blank}*{upper}{blank}*\}{blank}*\) {if(dir==LEFT){printf("Error");return 1;};dir=RIGHT;p->terminal=yytext[0];p->nonTerminal=yytext[indexOfLast(yytext)]; printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN END;}
<PRODT>{upper}{blank}*{lower}{blank}*\}{blank}*\) {if(dir==RIGHT){printf("Error");return 1;};dir=LEFT;p->terminal=yytext[indexOfLast(yytext)];p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN END;}
<PRODT>{upper}{blank}*\}{blank}*\) {p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN END;}
<PRODT>({lower}|{lambda}){blank}*\}{blank}*\) {p->terminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN END;}

<END>. {printf("RESULTADO NUMERO: %d\n", validate());}

. {printf("Error! Not a valid Grammar"); return 1;}

%%

void errorFound(int errNo){
	//TODO SUPER SWITCH
	//TODO FREE?
	return ;
}

int validate(){
	
	//Validacion que los "from" esten contenidos en NoTerm y el dist esta en algun from
	
	char useDist = FALSE;
	Element e;
	int i; 

	if(!containsChar(nonTerminals,dist)){
		/*distinguido no es noTerm*/
		return INVALID_DIST;
	}	
	
	FOR_EACH(e,productions){
		
		if(e->prod->from == dist){
			useDist = TRUE;
		}	

		if(!containsChar(nonTerminals,e->prod->from)){
			// From no esta en non terminals
			return INVALID_FROM;			
		}
		if(e->prod->nonTerminal != 0){
			if(!containsChar(nonTerminals,e->prod->nonTerminal)){
				//non terminal no esta en non terminal
				return INVALID_NONTERMINAL;
			}
		}	
		if(e->prod->terminal != 0){

			if(e->prod->terminal == '\\'){;}
			else if(!containsChar(terminals,e->prod->terminal)){
				//terminal no esta en terminal
				return INVALID_TERMINAL;
			}
		}	

	}
	
	if(useDist == FALSE){
	
		return DIST_NOT_USED;
	}

	return OK;
}

char containsChar(char * string, char c){
	
	int i;
	for(i = 0; string[i] !=0; i++){
		if(string[i] == c)
			return TRUE;
	}
	return FALSE;

}

int indexOfLast(char *s){
	int i=strlen(s)-1;	
	while(i>0){
		if(!(s[i]=='\t'||s[i]=='\n'||s[i]==' '||s[i]==','||s[i]=='|'||s[i]=='}' || s[i]==')')){
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
