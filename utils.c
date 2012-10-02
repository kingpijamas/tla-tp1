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
	return -1;
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
			printf("Not enough memory!");
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
		printf("Not enough memory!");
		exit(1);
	}
	strcpy(d,s);
	return d;
}
