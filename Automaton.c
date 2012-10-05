#include "Automaton.h"

Automaton newAutomaton(){
	Automaton a=malloc(sizeof(automaton));
	if(a==NULL){
		newInsufficientMemoryException("Automaton");
	}
	a->sigma="";
	a->hasInitial=false;
	a->stateList=newList();
	a->finals=newList();
	a->delta=newList();
	return a;
}

State newState(){
	State s=malloc(sizeof(state));
	if(s==NULL){
		newInsufficientMemoryException("Automaton");
	}
	s->visited=false;
	return s;
}

AutomatonErrorCodes addState(Automaton a,State s){
	if(s->number==INITIALSTATE){
		if(a->hasInitial){
			return TWO_INITIAL_STATES;
		}else{
			a->hasInitial=true;
			a->q0 = s;
			s->visited = true;
		}
	}
	if(s->terminal){
		addToList(s,a->finals);
	}
	addToList(s,a->stateList);
	return NO_ERROR;
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
	return NULL;
}

AutomatonErrorCodes validateState(State s){
	if(s==NULL){
		return REFERENCING_UNEXISTENT_STATE;
	}
	return NO_ERROR;
}

Transition newTransition(){
	Transition t=malloc(sizeof(transition));
	if(t==NULL){
		newInsufficientMemoryException("Automaton");
	}
	t->to=newList();
	return t;
}

void addBy(Transition t, char c){
	t->by=c;
}

AutomatonErrorCodes addTo(Transition t, State s){
	if(s==NULL){
		return REFERENCING_UNEXISTENT_STATE;
	}
	s->visited=true;
	addToList(s,t->to);
	return NO_ERROR;
}

void addTransition(Automaton a,Transition t){
	int i,contains;
	contains = 0;
	for(i = 0; (a->sigma)[i] !=0 && !contains; i++){
		if(a->sigma[i] == t->by){
			contains = 1;
		}
	}
	if(!contains){
		a->sigma = concat(strdup(a->sigma), stringify(t->by));
		
	}	
	addToList(t,a->delta);
}


