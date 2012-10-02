#include <stdio.h>

void printAutomaton(){
	char * dot;
	char buffer[100];
	dot = concat(dot, sprintf(buffer, "digraph {\nrankdir = \"LR\";\t De izquierda a derecha\n\n//Nodos\n"));
	int i = 0;
	while(nonTerminals[i] != '\0'){
		//if(existe produccion tal que nonTerminals[i] -> lambda){
		dot = concat(dot, sprintf(buffer, "node	[shape=doublecircle] Node%c [label=\"%c\"];\n", nonTerminals[i], nonTerminals[i]));
		//}else{
		dot = concat(dot, sprintf(buffer, "node	[shape=circle] Node%c [label=\"%c\"];\n", nonTerminals[i], nonTerminals[i]));
		//}
	}
	dot = concat(dot, "\n\n//Transiciones\n");
	production * p;
	FOR_EACH(p, productions){
		dot = concat(dot, sprintf(buffer, "Node%c -> Node%c [label=\"%c\"];\n", p->from, p->nonTerminal, p->terminal));
	}
	dot = concat(dot, "\n}");

	//TESTEO
	printf("%s",dot);
}
