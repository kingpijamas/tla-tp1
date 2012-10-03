#include "toDot.h"

void printAutomaton(Grammar g){
	char * dot;
	char * buffer = malloc(50);
	dot = strdup("digraph {\nrankdir = \"LR\";\t //De izquierda a derecha\n\n//Nodos\n");
	int i = 0;
	Element e;
	while(g->nonTerminals[i] != '\0'){
		boolean flag = false;
		FOR_EACH(e, g->productions){
			cleanBuffer(buffer);
			if(e->prod->from == g->nonTerminals[i] && e->prod->nonTerminal == '\0' && e->prod->terminal == '\\'){
				flag = true;
			}
		}
		if(flag){
			sprintf(buffer, "node	[shape=doublecircle] Node%c [label=\"%c\"];\n", g->nonTerminals[i], g->nonTerminals[i]);
			dot = concat(dot, buffer);
		}else{
			sprintf(buffer, "node	[shape=circle] Node%c [label=\"%c\"];\n", g->nonTerminals[i], g->nonTerminals[i]);
			dot = concat(dot, buffer);
		}
		i++;
	}
	dot = concat(dot, "\n\n//Transiciones\n");
	FOR_EACH(e, g->productions){
		cleanBuffer(buffer);
		if(e->prod->terminal != '\\'){
			sprintf(buffer, "Node%c -> Node%c [label=\"%c\"];\n", e->prod->from, e->prod->nonTerminal, e->prod->terminal);
		}
		dot = concat(dot, buffer);
	}
	dot = concat(dot, "\n}");

	//TESTEO
	printf("%s",dot);
	FILE *fp;
	fp=fopen("out.dot", "w");
	fprintf(fp, dot);
	fclose(fp);
	system("dot -Tpng out.dot > out.png");

}

void cleanBuffer(char * buffer){
	free(buffer);
	buffer = malloc(50);
}
