#ifndef automaton_h
#define automaton_h

#define MARK 1
#define UNMARK 0

typedef state{
	char K;
	int mark = 0;
}

typedef transition{
	state from;	//NT U {iniciales}
	char by;	//T U {lambda}
	List to;	//NT and Q_final
}transition;

typedef transition * Transition;

typedef automaton{
	List stateList; //conjunto de estados
	char * sigma; //alfabeto
	List finals; //estados finales
	state q0; //inicial	
	List delta; //funcion de transicion; recordar hacer la list para deltas
}

#endif
