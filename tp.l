%{
	#include "tp.h"

//	Automaton a;

	Grammar g;
	Production p;
	Production aux;
//<DOTSTATESTART>. {printf("%s",yytext);}

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

%s EXPECTINGNODESSTART
%s EXPECTINGNODES
%s DOTSTATETYPE
%s DOTSTATENO
%s DOTSTATELABEL
%s DOTSTATELABELNO
%s DOTSTATEEND
%s EXPECTINGTRANSITIONS
%s TRANSITIONTO
%s TRANSITIONBY

%%
{blank}+ ;

<INITIAL>digraph{blank}*\{{blank}*rankdir{blank}*={blank}*"LR"{blank}*; {printf("Parsing DOT\n");BEGIN EXPECTINGNODESSTART;}
<EXPECTINGNODESSTART>\/\/{blank}+Nodos{blank}+ {printf("Parsing Nodes\n");BEGIN EXPECTINGNODES;}
<EXPECTINGNODES>node{blank}*\[{blank}*shape{blank}*={blank}* {printf("Parsing states\n");BEGIN DOTSTATETYPE;}
<DOTSTATETYPE>circle {printf("Parsing non terminal state\n"); BEGIN DOTSTATENO;}
<DOTSTATETYPE>doublecircle {printf("Parsing terminal state\n"); BEGIN DOTSTATENO;}
<DOTSTATENO>{blank}*\]{blank}*Node{digit}+ {printf("Parsing number %s\n",yytext); BEGIN DOTSTATELABEL;}
<DOTSTATELABEL>{blank}*\[{blank}*label{blank}*={blank}* {BEGIN DOTSTATELABELNO;}
<DOTSTATELABELNO>{digit}+ {printf("Parsing label %s\n",yytext); BEGIN DOTSTATEEND;}
<DOTSTATEEND>{blank}*\]{blank}*; {printf("Done parsing state\n"); BEGIN EXPECTINGNODES;}

<EXPECTINGNODES>\/\/{blank}*Transiciones{blank}+ {printf("Parsing transitions\n"); BEGIN EXPECTINGTRANSITIONS;}
<EXPECTINGTRANSITIONS>Node{blank}*{digit}+{blank}*-\> {printf("Parsing transition from %s\n", yytext);BEGIN TRANSITIONTO;}
<TRANSITIONTO>Node{blank}*{digit} {printf("Parsing transition to %s\n",yytext); BEGIN TRANSITIONBY;}
<TRANSITIONBY>\[{blank}*label{blank}*={letter}{blank}*\]{blank}*; {printf("Done parsing transition\n"); BEGIN EXPECTINGTRANSITIONS;}

<EXPECTINGTRANSITIONS>\} {printf("Done parsing automaton\n");}

\/\/([^\n])*\n {printf("Comentario");}

<INITIAL>{letter}([^ \n\t])* {g->name=strdup(yytext); BEGIN START;}
<START>={blank}*\({blank}*\{ { BEGIN NONTERMINALS;}
<NONTERMINALS>{upper}{blank}*, {yytext[1]=0; addNonTerminal(g,yytext);}
<NONTERMINALS>{upper}{blank}*\}{blank}*,{blank}*\{ {yytext[1]=0; addNonTerminal(g,yytext);BEGIN TERMINALS;}

<TERMINALS>{lower}{blank}*, {yytext[1]=0; addTerminal(g,yytext);}
<TERMINALS>{lower}{blank}*\}{blank}*, {yytext[1]=0; addTerminal(g,yytext); BEGIN DIST;}
<DIST>{upper}{blank}*,{blank}*\{ {g->dist = yytext[0];BEGIN PRODF;}
<PRODF>{upper}{blank}*\-> {p=newProduction(g);p->from=yytext[0]; BEGIN PRODT;}

<PRODT>{lower}{blank}*{upper}{blank}*, {setDirection(g, RIGHT);p->terminal=yytext[0];p->nonTerminal=yytext[indexOfLast(yytext)]; BEGIN PRODF;}
<PRODT>{upper}{blank}*{lower}{blank}*, {setDirection(g, LEFT);p->terminal=yytext[indexOfLast(yytext)];p->nonTerminal=yytext[0]; BEGIN PRODF;}
<PRODT>{upper}{blank}*, {p->nonTerminal=yytext[0]; BEGIN PRODF;}
<PRODT>({lower}|{lambda}){blank}*, {p->terminal=yytext[0]; BEGIN PRODF;}

<PRODT>{lower}{blank}*{upper}{blank}*\| {setDirection(g, RIGHT);p->terminal=yytext[0];p->nonTerminal=yytext[indexOfLast(yytext)]; BEGIN PRODT;}
<PRODT>{upper}{blank}*{lower}{blank}*\| {setDirection(g, LEFT);p->terminal=yytext[indexOfLast(yytext)];p->nonTerminal=yytext[0];aux=p;p=newProduction(g);p->from=aux->from; BEGIN PRODT;}
<PRODT>{upper}{blank}*\| {p->nonTerminal=yytext[0];aux=p;p=newProduction(g);p->from=aux->from; BEGIN PRODT;}
<PRODT>({lower}|{lambda}){blank}*\| {p->terminal=yytext[0];aux=p;p=newProduction(g);p->from=aux->from; BEGIN PRODT;}

<PRODT>{lower}{blank}*{upper}{blank}*\}{blank}*\) {setDirection(g, RIGHT);p->terminal=yytext[0];p->nonTerminal=yytext[indexOfLast(yytext)]; processGrammar(g);}
<PRODT>{upper}{blank}*{lower}{blank}*\}{blank}*\) {setDirection(g, LEFT);p->terminal=yytext[indexOfLast(yytext)];p->nonTerminal=yytext[0]; processGrammar(g);}
<PRODT>{upper}{blank}*\}{blank}*\) {p->nonTerminal=yytext[0]; processGrammar(g);}
<PRODT>({lower}|{lambda}){blank}*\}{blank}*\) {p->terminal=yytext[0]; processGrammar(g);}

. {printf("%s Error! Not a valid Grammar\n", yytext); return 1;}

%%

void processErrors(ErrorCodes err){
	printf("RESULTADO NUMERO: %d\n", err);
}

void processGrammar(Grammar g){
	processErrors(validate(g));
	printGrammar(g);
	g = removeUnreachableProductions(g);
	g = toNormalRight(g);
	g = removeUnreachableProductions(g);
	g = removeUnproductiveNodes(g);
	g->name = "Nueva Gramatica";
	printGrammar(g);
	printAutomaton(g);
}

int main(void){
	g=newGrammar();
	yylex();
	return 0;
}
