#ifndef Automaton_h
#define Automaton_h

#include "utils.h"
#include "LinkedList.h"

#define INITIALSTATE 0

#define MARK 1
#define UNMARK 0
#define EQUALS 1


typedef enum {
	TWO_INITIAL_STATES=1
} AutomatonErrorCodes;

typedef struct state {
	char K;
	int mark;
	boolean terminal;
	char number;
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
	List delta; //funcion de transicion;
}automaton;

typedef automaton * Automaton;

Automaton newAutomaton(void);
State newState(void);
AutomatonErrorCodes addState(Automaton a,State s);
Transition newTransition(void);
State getState(Automaton a,int number);
void addTo(Transition t, State s);
void addBy(Transition t, char c);
void addTransition(Automaton a,Transition t);

#endif
