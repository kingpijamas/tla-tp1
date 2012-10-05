#ifndef Automaton_h
#define Automaton_h

#include "utils.h"
#include "LinkedList.h"

#define INITIALSTATE 0

#define MARK 1
#define UNMARK 0

typedef enum {
	TWO_INITIAL_STATES=!NO_ERROR
} AutomatonErrorCodes;

typedef struct state {
	char K;
	int mark;

	boolean terminal;
	char number;
	char label;
}state;

typedef state * State;

typedef struct transition{
	State from;	//NT U {iniciales}
	char by;	//T U {lambda}
	List to;	//NT and Q_final
}transition;

typedef transition * Transition;

typedef struct automaton{
	boolean hasInitial;
	List stateList; //conjunto de estados
	char * sigma; //alfabeto
	List finals; //estados finales
	State q0; //inicial	
	List delta; //funcion de transicion; recordar hacer la list para deltas
}automaton;

typedef automaton * Automaton;

Automaton newAutomaton(void);
void addState(Automaton a,State s);
State newState(void);
Transition newTransition(void);
State getState(Automaton a,int number);
void addTo(Transition t, State s);
void addTransition(Automaton a,Transition t);

#endif
