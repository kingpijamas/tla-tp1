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

State newState(){
	State s=malloc(sizeof(state));
	if(s==NULL){
		printf("<LOG - Automaton.c>\n\tInsufficient memory.\n<end>\n");
	}
	s->mark=0;
	return s;
}

void addState(Automaton a,State s){
	if(s->number==INITIALSTATE){
		if(a->hasInitial){
			printf("<LOG - Automaton.c>\n\tTWO_INITIAL_STATES.\n<end>\n");
		}else{
			a->hasInitial=true;
		}
	}
	addToList(s,a->stateList);
}

State getState(Automaton a,int number){
	Element e;
	State s;	
	FOR_EACH(e,a->stateList){
		s=(State)e->data;
		if(s->number==number){
			return s;
		}
	}
	printf("<LOG - Automaton.c>\n\tUnexistent state %d.\n<end>\n",number);	
	return NULL;
}

Transition newTransition(){
	Transition t=malloc(sizeof(transition));
	if(t==NULL){
		printf("<LOG - Automaton.c>\n\tInsufficient memory.\n<end>\n");
	}
	t->to=newList();
	return t;
}

void addTo(Transition t, State s){
	addToList(s,t->to);
}

void addTransition(Automaton a,Transition t){
	addToList(t,t->to);
}
