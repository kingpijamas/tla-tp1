#include "utils.h"

boolean containsChar(char * s, char c){
	return indexOf(s,c)>=0;
}

int indexOf(char * s, char c){
	int i;
	for(i = 0; s[i] !=0; i++){
		if(s[i] == c){
			return i;
		}
	}
	printf("<LOG - utils.c>\n\tNo such element: %c in %s\n<end>\n", c, s);
	exit(1);
}

int indexOfLast(char * s){
	int i=strlen(s)-1;	
	while(i>0){
		if(!(s[i]=='\t'||s[i]=='\n'||s[i]==' '||s[i]==','||s[i]=='|'||s[i]=='}' || s[i]==')')){
			return i;
		}		
		i--;	
	}
	return i;
}

char * concat(char * s, char * t){
	if(s==NULL){
		s=strdup(t);
	}else{
		char * aux = realloc(s,strlen(s)+strlen(t)+1);
		if(aux == NULL){
			printf("<LOG - utils.c>\n\tInsufficient memory.\n<end>\n");
			exit(1);
		}else if (aux != s){
			free(s);
			s = aux;
		}
		s = strcat(s,t);	
	}
	return s;
}

char * strdup(const char * s){
	char * d = malloc(strlen(s)+1);
	if(d == NULL){
		printf("<LOG - utils.c>\n\tInsufficient memory.\n<end>\n");
		exit(1);
	}
	strcpy(d,s);
	return d;
}

char getLast(char * s){
	if(s==NULL){
		printf("<LOG - utils.c>\n\tNull pointer.\n<end>\n");
	}
	return s[strlen(s)-1];
}
