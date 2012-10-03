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
	int n=g->productions->NumEl;//should be == size(nonTerminals) at this point;
	RelationMatrix t=generateRelationMatrix(g,n);
	findReachableProductions(t,n);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if((t[i][j]).reachable!=false){
				removeElemFromList(t[i][j].elem, g->productions);
			}
		}
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
	
	FOR_EACH(e,g->productions){
		row=indexOf(g->nonTerminals, ((Production)e->data)->from);
		col=indexOf(g->nonTerminals, ((Production)e->data)->nonTerminal);		
		relM[row][col].reachable=true;
		relM[row][col].elem=e;	
	}
	return relM;
}

void findReachableProductions(RelationMatrix t,int n){//uses Warshall's algorithm
	int i,j,k;
	for(k=0;k<n;k++){
		printf("K");
		for(i=0;i<n;i++){
			printf("I");
			for(j=0;j<n;j++){
				printf("J");
				(t[i][j]).reachable=(t[i][j]).reachable || (t[i][k].reachable && t[k][j].reachable);
			}
		}
	}
	printf("\n");
}
