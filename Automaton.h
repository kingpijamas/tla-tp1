#ifndef Automaton_h
#define Automaton_h

#include "utils.h"
#include "LinkedList.h"

#define INITIALSTATE 0

#include "LinkedList.h"

#define MARK 1
#define UNMARK 0
#define EQUALS 1


typedef enum {
	TWO_INITIAL_STATES=!NO_ERROR
} AutomatonErrorCodes;

typedef struct state {
	char K;
	int mark;

	boolean terminal;
	int number;
	char label;
}state;

typedef state * State;

typedef struct transition{
	state from;	//NT U {iniciales}
	char by;	//T U {lambda}
	List to;	//NT and Q_final
}transition;

typedef transition * Transition;

typedef struct automaton{
	boolean hasInitial;
	List stateList; //conjunto de estados
	char * sigma; //alfabeto
	List finals; //estados finales
	state q0; //inicial	
	List delta; //funcion de transicion; recordar hacer la list para deltas
}automaton;

typedef automaton * Automaton;

Automaton newAutomaton(void);
AutomatonErrorCodes addState(Automaton a,State s);
State newState();

#endif
