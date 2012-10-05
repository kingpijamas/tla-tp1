#include "utils.h"

boolean containsChar(char * s, char c){
	int i;
	for(i = 0; s[i] !=0; i++){
		if(s[i] == c){
			return true;
		}
	}
	return false;
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
		if(!(s[i]=='\t'||s[i]=='\n'||s[i]==' '||s[i]==','||s[i]=='|'||s[i]=='}' || s[i]==')' || s[i]==']')){
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

char * stringify(char c){
	char * s = malloc(sizeof(char) * 2);
	if(s == NULL){
		printf("Not enough memory!");
		exit(1);
	}
	s[0] = c;
	s[1] = 0;
	return s;
}

void cleanBuffer(char * buffer, int i){
	free(buffer);
	buffer = malloc(i*sizeof(char));
	if(buffer == NULL){
		printf("Not enough memory!");
		exit(1);
	}
}

char getLast(char * s){
	if(s==NULL){
		printf("<LOG - utils.c>\n\tNull pointer.\n<end>\n");
	}
	return s[strlen(s)-1];
}

int getLastDigit(char * s){
	if(s==NULL){
		printf("<LOG - utils.c>\n\tNull pointer.\n<end>\n");
	}
	int i=0;
	int last=-1;
	while(s[i]!='\0'){
		if(isdigit(s[i])){
			last=ctoi(s[i]);
		}
		i++;
	}
	if(last==-1){
		printf("<LOG - utils.c>\n\tString %s does not contain digits.\n<end>\n",s);
	}
	return last;
}

int ctoi(char c){
	if(!isdigit(c)){
		printf("<LOG - utils.c>\n\t%c is not a digit.\n<end>\n",c);
	}
	return c%'0';
}
