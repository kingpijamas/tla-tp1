#include "postProcessing.h"

/*
Algoritmo de Warshall
--------
Comienzo.
T←R
Para k:1 .. n
	Para i:1..n
		Para j:1..n
			T(i,j)=T(i,j)∨(T(i,k)∧T(k,j))
Fin.
*/

Relation newRelation(Element elem){
	Relation rel=malloc(sizeof(relation));
	if(rel==NULL){
		printf("<LOG - postProcessing.c>\n\tNull pointer.\n<end>\n");
	}
	rel->reachable=true;
	rel->elem=elem;
	return rel;
}

RelationMatrix generateRelationMatrix(Grammar g, int n){//n is the size of productions
	RelationMatrix relM=calloc(n*n,sizeof(relation));
	if(relM==NULL){
		printf("<LOG - postProcessing.c>\n\tNull pointer.\n<end>\n");
	}
	Element e;
	FOR_EACH(e,g->productions){
		relM[indexOf(g->nonTerminals, e->prod->from)][indexOf(g->nonTerminals, e->prod->nonTerminal)]=*newRelation(e);
	}
	return relM;
}

void findReachableProductions(RelationMatrix t,int n){//uses Warshall's algorithm
	int i,j,k;
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				t[i][j].reachable=t[i][j].reachable||(t[i][k].reachable&&t[k][j].reachable);
			}
		}
	}
}

void removeUnreachableProductions(Grammar g){
	int n=size(g->productions);//should be == size(nonTerminals) at this point;
	RelationMatrix t=generateRelationMatrix(g,n);
	findReachableProductions(t,n);
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(!t[i][j].reachable){
				removeElemFromList(t[i][j].elem, g->productions);
			}
		}
	}
}
