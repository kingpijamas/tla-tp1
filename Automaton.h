#ifndef Automaton_h
#define Automaton_h

#include "LinkedList.h"

#define MARK 1
#define UNMARK 0

typedef struct state {
	char K;
	int mark;
}state;

typedef state * State;

typedef struct transition{
	state from;	//NT U {iniciales}
	char by;	//T U {lambda}
	List to;	//NT and Q_final
}transition;

typedef transition * Transition;

typedef struct automaton{
	List stateList; //conjunto de estados
	char * sigma; //alfabeto
	List finals; //estados finales
	state q0; //inicial	
	List delta; //funcion de transicion; recordar hacer la list para deltas
}automaton;

typedef automaton * Automaton;

Automaton newAutomaton(void);
State newState(void);

#endif
