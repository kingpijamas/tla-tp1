#include "grammarProcessing.h"

GrammarErrorCodes validateGrammar(Grammar g){
	//Validacion que los "from" esten contenidos en NoTerm y el dist esta en algun from	
	char useDist = false;
	Element e;
	Production p;
	if(!containsChar(g->nonTerminals,g->dist)){
		/*distinguido no es noTerm*/
		return INVALID_DIST;
	}	
	FOR_EACH(e,g->productions){
		p=(Production)e->data;
		if(p->from == g->dist){
			useDist = true;
		}	
		if(!containsChar(g->nonTerminals,p->from)){
			// From no esta en non terminals
			return INVALID_FROM;			
		}
		if(p->nonTerminal != 0){
			if(!containsChar(g->nonTerminals,p->nonTerminal)){
				//non terminal no esta en non terminal
				return INVALID_NONTERMINAL;
			}
		}	
		if(p->terminal != 0){
			if(p->terminal != '\\' && !containsChar(g->terminals,p->terminal)){
				//terminal no esta en terminal
				return INVALID_TERMINAL;
			}
		}
	}
	if(useDist == false){
		return DIST_NOT_USED;
	}
	return NO_ERROR;
}

Grammar removeUnreachableProductions(Grammar g){
	int i,j;
	Production p;
	Element e;
	//int n=g->productions->NumEl;//should be == size(nonTerminals) at this point;
	int n = strlen(g->nonTerminals);
	RelationMatrix t=generateRelationMatrix(g,n);
	findReachableProductions(t,n);
	/*for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if((t[i][j]).reachable!=false){
				removeElemFromList(t[i][j].elem, g->productions);
			}
		}
	}*/
	i = indexOf(g->nonTerminals, g->dist);
	int k;
	for(k=0,j=0;j<n;j++, k++){
		if((t[i][j]).reachable==false && g->nonTerminals[k] != 0){
			//removeElemFromList(t[i][j].elem, g->productions);
			List aux = malloc(sizeof(llist));
			FOR_EACH(e, g->productions){
				p = (Production)e->data;
				//Element aux;
				if(p->from != g->nonTerminals[k]){
					addToList(p, aux);
				}
			}
			free(g->productions);
			g->productions = aux;
			removeNonTerminal(g, g->nonTerminals[k]);
			k--;
		}
	}
	return g;
}

RelationMatrix generateRelationMatrix(Grammar g, int n){//n is the size of productions
	int i;
	RelationMatrix relM = malloc(n*sizeof(Relation));
	int row,col;
	
	if(relM==NULL){
		printf("<LOG - postProcessing.c>\n\tNull pointer.\n<end>\n");
	}
	for(i=0; i<n; i++){
		relM[i]=malloc(n*sizeof(relation));
		if(relM[i]==NULL){
			printf("<LOG - postProcessing.c>\n\tNull pointer.\n<end>\n");
		}
	}
	Production p;
	Element e;
	FOR_EACH(e,g->productions){
		p=(Production)e->data;
		if(p->nonTerminal != 0){
			row=indexOf(g->nonTerminals, p->from);
			col=indexOf(g->nonTerminals, p->nonTerminal);
			relM[row][col].reachable=true;
			relM[row][col].elem=e;
		}
	}
	i = indexOf(g->nonTerminals, g->dist);
	relM[i][i].reachable=true;
	relM[i][i].elem=e;


	return relM;
}

void findReachableProductions(RelationMatrix t,int n){//uses Warshall's algorithm
	int i,j,k;
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				(t[i][j]).reachable=(t[i][j]).reachable || (t[i][k].reachable && t[k][j].reachable);
			}
		}
	}
}

Grammar removeUnproductiveNodes(Grammar g){
	Element e;
	Production p;
	boolean changes = true;
	boolean * isProductive = malloc(sizeof(boolean) * strlen(g->nonTerminals));
	int i;
	for(i = 0; i < strlen(g->nonTerminals); i++){
		isProductive[i] = false;
	}
	while(changes){
		changes = false;
		FOR_EACH(e, g->productions){
			p = (Production)e->data;
			if(isProductive[indexOf(g->nonTerminals, p->from)] == false){
				if((p->nonTerminal == 0 && p->terminal == '\\') || (p->nonTerminal != 0 && isProductive[indexOf(g->nonTerminals, p->nonTerminal)])){
					isProductive[indexOf(g->nonTerminals, p->from)] = true;
					changes = true;
				}
			}
		}
	}
	int k;
	int n = strlen(g->nonTerminals);
	for(k=0,i=0;i<n;i++, k++){
		if(!isProductive[i] && g->nonTerminals[k] != 0){
			List aux = malloc(sizeof(llist));
			FOR_EACH(e, g->productions){
				p = (Production)e->data;
				if(p->from != g->nonTerminals[k] && p->nonTerminal != g->nonTerminals[k]){
					addToList(p, aux);
				}
			}
			free(g->productions);
			g->productions = aux;
			removeNonTerminal(g, g->nonTerminals[k]);
			k--;
		}
	}
	return g;
}

Grammar normalize(Grammar g){
	Production p;
	Element e;
	Production p2;
	Element e2;
	Production aux;
	boolean hasEnd = false;
	boolean addedTerminal = false;
	boolean modified = false;
	Grammar auxi;
	do{
		auxi = newGrammar();
		modified = false;
		FOR_EACH(e,g->productions){
			p=(Production)e->data;
			if(p->from == p->nonTerminal && p->terminal == 0){
				removeElemFromList(e, g->productions);
				modified = true;
			}else if(p->nonTerminal == 0 && p->terminal !='\\' ){
				p->nonTerminal = '1';
				hasEnd = true;
				addedTerminal = true;
				modified = true;
			}else if(p->nonTerminal != 0 && (p->terminal == 0 || p->terminal == '\\')){
				modified = true;
				FOR_EACH(e2,g->productions){
					p2=(Production)e2->data;
					if(p2->from == p->nonTerminal){
						aux = newProduction(auxi);
						aux->from = p->from;
						aux->nonTerminal = p2->nonTerminal;
						aux->terminal = p2->terminal;
					}
				}
				FOR_EACH(e2,auxi->productions){
					p2=(Production)e2->data;
					aux = newProduction(g);
					aux->from = p2->from;
					aux->nonTerminal = p2->nonTerminal;
					aux->terminal = p2->terminal;
				}
				removeElemFromList(e, g->productions);
			}else if(p->nonTerminal == 0 && p->terminal =='\\' ){
				hasEnd=true;
			}
		}
	}while(modified);
	if(addedTerminal){
		addNonTerminal(g, stringify('1'));
		p = newProduction(g);
		p->from = '1';
		p->terminal = '\\';
	}
	if(!hasEnd){
		printf("There's no production for the grammar\n");
		exit(1);
	}
	g = removeUnreachableProductions(g);
	return g;

}

Grammar toNormalRight(Grammar g){
	Production p;
	Element e;
	Production p2;
	Element e2;
	Grammar g2 = newGrammar();
	Production aux;
	g = normalize(g);
	if(g->dir == LEFT){
		//boolean isEmptyChain = false;
		addNonTerminal(g2, stringify('0'));
		FOR_EACH(e,g->productions){
			p=(Production)e->data;
			if(p->nonTerminal == 0 && p->terminal == '\\'){
				if(p->from == g->dist){
					aux = newProduction(g2);
					aux->from = '0';
					aux->terminal = '\\';
					//isEmptyChain = true;
				}
				FOR_EACH(e2,g->productions){
					p2=(Production)e2->data;
					if(p2->nonTerminal == p->from){
						aux=newProduction(g2);
						aux->from = '0';
						aux->terminal = p2->terminal;
						aux->nonTerminal = p2->from;
					}
				}
			}
		}
		int i;
		char c;

		for(i = 0; i < strlen(g->nonTerminals); i++){
			c = g->nonTerminals[i];
			if(!containsChar(g2->nonTerminals, c)){
				FOR_EACH(e2,g->productions){
					p2=(Production)e2->data;
					if(p2->nonTerminal == c){
						aux=newProduction(g2);
						aux->from = c;
						aux->terminal = p2->terminal;
						aux->nonTerminal = p2->from;
					}
				}
				addNonTerminal(g2, stringify(c));
			}
		}
		//if(!isEmptyChain){
			if(!containsChar(g2->nonTerminals, g->dist)){
				addNonTerminal(g2, stringify(g->dist));
			}
			aux = newProduction(g2);
			aux->from = g->dist;
			aux->terminal = '\\';
		//}
		g2->dist = '0';
		g2->dir = RIGHT;
		g2->name = g->name;
		g2->productions = g->productions;
	}else{
		g2 = g;
	}
	return g2;
}


void printAutomatonFromGrammar(Grammar g){
	char * dot;
	char * buffer = malloc(50);
	dot = strdup("digraph {\nrankdir = \"LR\";\t //De izquierda a derecha\n\n//Nodos\n");
	int i = 0;
	Element e;
	Production p;
	while(g->nonTerminals[i] != '\0'){
		boolean flag = false;
		FOR_EACH(e, g->productions){
			p=(Production)e->data;
			if(p->from == g->nonTerminals[i] && p->nonTerminal == 0 && p->terminal == '\\'){
				flag = true;
			}
		}
		cleanBuffer(buffer, 50);
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
		p=(Production)e->data;
		cleanBuffer(buffer, 50);
		if(p->terminal != '\\'){
			sprintf(buffer, "Node%c -> Node%c [label=\"%c\"];\n", p->from, p->nonTerminal, p->terminal);
		}
		dot = concat(dot, buffer);
	}
	dot = concat(dot, "\n}");
	free(buffer);

	//TESTEO
	FILE *fp;
	fp=fopen("out.dot", "w");
	fprintf(fp, "%s", dot);
	fclose(fp);
	system("dot -Tpng out.dot > out.png");
}
