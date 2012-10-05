#include "Automaton.h"

Automaton newAutomaton(){
	Automaton a=malloc(sizeof(automaton));
	if(a==NULL){
		printf("<LOG - Automaton.c>\n\tInsufficient memory.\n<end>\n");
	}
	a->hasInitial=false;
	a->stateList=newList();
	a->finals=newList();
	a->delta=newList();
	return a;
}

AutomatonErrorCodes addState(Automaton a,State s){
	if(s->number==INITIALSTATE){
		if(a->hasInitial){
			return TWO_INITIAL_STATES;
		}else{
			a->hasInitial=true;
		}
	}
	addToList(s,a->stateList);
	return NO_ERROR;
}

State newState(){
	State s=malloc(sizeof(state));
	if(s==NULL){
		printf("<LOG - Automaton.c>\n\tInsufficient memory.\n<end>\n");
	}
	s->mark=0;
	return s;
}
