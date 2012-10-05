%{
	#include "tp.h"

	Automaton a;
	State s;
	Transition t;	

	Grammar g;
	Production p;
	Production aux;
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
%s TRANSITIONEND

%%
{blank}+ ;

<INITIAL>digraph{blank}*\{{blank}*rankdir{blank}*={blank}*"LR"{blank}*; {a=newAutomaton();printf("Parsing DOT\n"); BEGIN EXPECTINGNODESSTART;}

\/\/.*[\n] ;

<EXPECTINGNODESSTART>\/\/{blank}*Nodos{blank}+ {printf("Parsing Nodes\n");BEGIN EXPECTINGNODES;}
<EXPECTINGNODES>node{blank}*\[{blank}*shape{blank}*={blank}* {s=newState();printf("Parsing states\n");BEGIN DOTSTATETYPE;}
<DOTSTATETYPE>circle {s->terminal=false;printf("Parsing non terminal state\n"); BEGIN DOTSTATENO;}
<DOTSTATETYPE>doublecircle {s->terminal=true;printf("Parsing terminal state\n"); BEGIN DOTSTATENO;}
<DOTSTATENO>{blank}*\]{blank}*Node{digit}+ {s->number=getLastDigit(yytext);printf("Parsing number:%s Loaded:%d\n",yytext,s->number); BEGIN DOTSTATELABEL;}
<DOTSTATELABEL>{blank}*\[{blank}*label{blank}*={blank}* {BEGIN DOTSTATELABELNO;}

<DOTSTATELABELNO>{letter} {s->K=getLast(yytext);printf("Parsing label %s Loaded:%c\n",yytext,s->K); BEGIN DOTSTATEEND;}
<DOTSTATEEND>{blank}*\]{blank}*; {addState(a,s);printf("Done parsing state\n"); BEGIN EXPECTINGNODES;}

<EXPECTINGNODES>\/\/{blank}*Transiciones{blank}+ {printf("Parsing transitions\n"); BEGIN EXPECTINGTRANSITIONS;}
<EXPECTINGTRANSITIONS>Node{blank}*{digit}+{blank}*-\> {t=newTransition();t->from=getState(a,getLastDigit(yytext));printf("Parsing transition from: %s\n", yytext);BEGIN TRANSITIONTO;}
<TRANSITIONTO>Node{blank}*{digit} {addTo(t,getState(a,getLastDigit(yytext)));printf("Parsing transition to %s\n",yytext); BEGIN TRANSITIONBY;}
<TRANSITIONBY>\[{blank}*label{blank}*={blank}*{letter} {addBy(t,getLast(yytext));addTransition(a,t);printf("Done parsing transition\n"); BEGIN TRANSITIONEND;}
<TRANSITIONEND>\]{blank}*; {BEGIN EXPECTINGTRANSITIONS;}
<EXPECTINGTRANSITIONS>\} {printf("Done parsing automaton\n"); printAutomaton(a);}

<INITIAL>{letter}([^ \n\t])* {g = newGrammar(); g->name=strdup(yytext); BEGIN START;}
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

<PRODT>{lower}{blank}*{upper}{blank}*\| {setDirection(g, RIGHT);p->terminal=yytext[0];p->nonTerminal=yytext[indexOfLast(yytext)];aux=p;p=newProduction(g);p->from=aux->from; BEGIN PRODT;}
<PRODT>{upper}{blank}*{lower}{blank}*\| {setDirection(g, LEFT);p->terminal=yytext[indexOfLast(yytext)];p->nonTerminal=yytext[0];aux=p;p=newProduction(g);p->from=aux->from; BEGIN PRODT;}
<PRODT>{upper}{blank}*\| {p->nonTerminal=yytext[0];aux=p;p=newProduction(g);p->from=aux->from; BEGIN PRODT;}
<PRODT>({lower}|{lambda}){blank}*\| {p->terminal=yytext[0];aux=p;p=newProduction(g);p->from=aux->from; BEGIN PRODT;}

<PRODT>{lower}{blank}*{upper}{blank}*\}{blank}*\) {setDirection(g, RIGHT);p->terminal=yytext[0];p->nonTerminal=yytext[indexOfLast(yytext)]; processGrammar(g);}
<PRODT>{upper}{blank}*{lower}{blank}*\}{blank}*\) {setDirection(g, LEFT);p->terminal=yytext[indexOfLast(yytext)];p->nonTerminal=yytext[0]; processGrammar(g);}
<PRODT>{upper}{blank}*\}{blank}*\) {p->nonTerminal=yytext[0]; processGrammar(g);}
<PRODT>({lower}|{lambda}){blank}*\}{blank}*\) {p->terminal=yytext[0]; processGrammar(g);}

. {printf("Error! Not well written grammar.\n", yytext); return 1;}

%%

void processErrors(int err){
	if(err == NO_ERROR){
		return;
	}
	switch( err ) {
    case INVALID_DIST:
        printf("Error! El distinguido no es parte de los no terminales.\n");
        break;
    case INVALID_FROM:
        printf("Error! Al menos uno de los no terminales que producen no esta declarado.\n");
        break;
    case INVALID_NONTERMINAL:
        printf("Error! Al menos uno de los no terminales producidos no esta declarado.\n");
        break;
    case INVALID_TERMINAL:
        printf("Error! Al menos uno de los terminales en la produccion no esta en el alfabeto.\n");
        break;
    case DIST_NOT_USED:
        printf("Error! El no terminal distinguido no tiene produccion.\n");
        break;
    default :
        ;
	}
	exit(1);
}

void processGrammar(Grammar g){
	printGrammar(g);
	processErrors(validate(g));
	g = toNormalRight(g);
	g = removeUnreachableProductions(g);
	g = removeUnproductiveNodes(g);
	g->name = "Nueva Gramatica";
	printGrammar(g);
	printAutomatonFromGrammar(g);
}

int main(void){
	yylex();
	return 0;
}
