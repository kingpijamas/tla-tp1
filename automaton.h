

typedef transition{
	char from;	//NT U {iniciales}
	char by;	//T U {lambda}
	char * to;	//NT and Q_final
}transition;

typedef transition * Transition;

typedef automaton{
	char * k; //conjunto de estados
	char * sigma; //alfabeto
	char * f; //estados finales
	char q0; //inicial	
	List delta; //funcion de transicion; recordar hacer la list para deltas
}
