#include "postProcessing.h"

ErrorCodes validate(Grammar g){
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
	return OK;
}

void removeUnreachableProductions(Grammar g){
	printf("HOLA\n");
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
	for(j=0;j<n;j++){
		if((t[i][j]).reachable==false){
			printf("Tiene que remover <%c>\n", g->nonTerminals[j]);
			//removeElemFromList(t[i][j].elem, g->productions);
			FOR_EACH(e, g->productions){
				p = (Production)e->data;
				if(p->from == g->nonTerminals[j]){
					removeElemFromList(e, g->productions);
				}
			}
		}
	}
	FOR_EACH(e, g->productions){
		p = (Production)e->data;
		char from = p->from;
		char first;
		char second;
		if(g->dir == RIGHT){
			first = p->terminal;
			second = p->nonTerminal;
		}else{
			first = p->nonTerminal;
			second = p->terminal;
		}
		printf("%c->%c%c\n", from, first, second);
	}
}

RelationMatrix generateRelationMatrix(Grammar g, int n){//n is the size of productions
	int i;
	RelationMatrix relM = malloc(n*sizeof(Relation));
	Element e;
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
	printf("\n");
}
