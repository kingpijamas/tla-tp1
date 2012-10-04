#include "Automaton.h"

Automaton newAutomaton(){
	Automaton a=malloc(sizeof(automaton));
	if(a==NULL){
		printf("<LOG - Automaton.c>\n\tInsufficient memory.\n<end>\n");
	}
	a->stateList=newList();
	a->finals=newList();
	a->delta=newList();
	return a;
}

State newState(){
	State s=malloc(sizeof(state));
	if(s==NULL){
		printf("<LOG - Automaton.c>\n\tInsufficient memory.\n<end>\n");
	}
	s->mark=0;
	return s;
}
