%{
	#include "tp.h"

	Grammar g;
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
<INITIAL>{letter}(^{blank})* {g->name=strdup(yytext);printf("\nyytext: %s gramName:%s\n",yytext,g->name); BEGIN START;}
<START>\={blank}*\({blank}*\{ {printf("START\n"); BEGIN NONTERMINALS;}
<NONTERMINALS>{upper}{blank}*, {yytext[1]=0; addNonTerminal(g,yytext);printf("nonTerminals %s\n",g->nonTerminals);}
<NONTERMINALS>{upper}{blank}*\}{blank}*,{blank}*\{ {yytext[1]=0; addNonTerminal(g,yytext); printf("nonTerminals %s\n",g->nonTerminals);BEGIN TERMINALS;}

<TERMINALS>{lower}{blank}*, {yytext[1]=0; addTerminal(g,yytext); printf("terminals %s\n",g->terminals);}
<TERMINALS>{lower}{blank}*\}{blank}*, {yytext[1]=0; addTerminal(g,yytext); printf("terminals %s\n",g->terminals);BEGIN DIST;}
<DIST>{upper}{blank}*,{blank}*\{ {g->dist = yytext[0];printf("Dist: %c\n",g->dist); BEGIN PRODF;}
<PRODF>{upper}{blank}*\-> {p=addToList(g->productions)->prod;p->from=yytext[0]; BEGIN PRODT;}

<PRODT>{lower}{blank}*{upper}{blank}*, {setDirection(g, RIGHT);p->terminal=yytext[0];p->nonTerminal=yytext[indexOfLast(yytext)]; printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN PRODF;}
<PRODT>{upper}{blank}*{lower}{blank}*, {setDirection(g, LEFT);p->terminal=yytext[indexOfLast(yytext)];p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN PRODF;}
<PRODT>{upper}{blank}*, {p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN PRODF;}
<PRODT>({lower}|{lambda}){blank}*, {p->terminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN PRODF;}

<PRODT>{lower}{blank}*{upper}{blank}*\| {setDirection(g, RIGHT);p->terminal=yytext[0];p->nonTerminal=yytext[indexOfLast(yytext)];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal);p=addToList(g->productions)->prod;p->from=g->productions->pLast->prev->prod->from; BEGIN PRODT;}
<PRODT>{upper}{blank}*{lower}{blank}*\| {setDirection(g, LEFT);p->terminal=yytext[indexOfLast(yytext)];p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal);p=addToList(g->productions)->prod;p->from=g->productions->pLast->prev->prod->from; BEGIN PRODT;}
<PRODT>{upper}{blank}*\| {p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal);p=addToList(g->productions)->prod;p->from=g->productions->pLast->prev->prod->from; BEGIN PRODT;}
<PRODT>({lower}|{lambda}){blank}*\| {p->terminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal);p=addToList(g->productions)->prod;p->from=g->productions->pLast->prev->prod->from; BEGIN PRODT;}

<PRODT>{lower}{blank}*{upper}{blank}*\}{blank}*\) {setDirection(g, RIGHT);p->terminal=yytext[0];p->nonTerminal=yytext[indexOfLast(yytext)]; printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN END;}
<PRODT>{upper}{blank}*{lower}{blank}*\}{blank}*\) {setDirection(g, LEFT);p->terminal=yytext[indexOfLast(yytext)];p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN END;}
<PRODT>{upper}{blank}*\}{blank}*\) {p->nonTerminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN END;}
<PRODT>({lower}|{lambda}){blank}*\}{blank}*\) {p->terminal=yytext[0];printf("from: %c nonTerminal: %c terminal: %c\n",p->from,p->terminal,p->nonTerminal); BEGIN END;}

<END>. {printf("RESULTADO NUMERO: %d\n", validate(g));}

. {printf("Error! Not a valid Grammar"); return 1;}

%%

void errorFound(ErrorCodes err){
	//TODO SUPER SWITCH
	//TODO FREE?
	return ;
}

int main(void){
	g=newGrammar();
	yylex();
	return 0;
}
