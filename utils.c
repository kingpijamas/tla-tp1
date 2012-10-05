#include "utils.h"

boolean containsChar(char * s, char c){
	if(s==NULL){
		newException("utils.c","Null pointer.");
	}
	int i;
	for(i=0;s[i]!='\0';i++){
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
	char * buffer=newBuffer(EXCEPTION_BUFFER_SIZE);
	sprintf(buffer,"No such element: %c in %s.", c, s);
	newException("utils",buffer);
	return -1;
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
			newInsufficientMemoryException("utils");
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
		newInsufficientMemoryException("utils");
	}
	strcpy(d,s);
	return d;
}

char * stringify(char c){
	char * s = malloc(sizeof(char) * 2);
	if(s == NULL){
		newInsufficientMemoryException("utils");
	}
	s[0] = c;
	s[1] = '\0';
	return s;
}

void cleanBuffer(char * buffer, int i){
	free(buffer);
	buffer = malloc(i*sizeof(char));
	if(buffer == NULL){
		newInsufficientMemoryException("utils");
	}
}

char getLast(char * s){
	if(s==NULL){
		newException("utils","Null pointer.");
	}
	return s[strlen(s)-1];
}

int getLastDigit(char * s){
	if(s==NULL){
		newException("utils","Null pointer.");
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
		char * buffer=newBuffer(EXCEPTION_BUFFER_SIZE);
		sprintf(buffer,"String %s does not contain digits.",s);
		newException("utils",buffer);
		exit(1);
	}
	return last;
}

char * newBuffer(int i){
	char * buffer=malloc(sizeof(char)*i+1);
	buffer[i]='\0';
	if(buffer==NULL){
		newInsufficientMemoryException("utils");
	}
	return buffer;
}

int ctoi(char c){
	if(!isdigit(c)){
		char * buffer=newBuffer(EXCEPTION_BUFFER_SIZE);
		sprintf(buffer,"%c is not a digit.",c);
		newException("utils",buffer);
	}
	return c%'0';
}

void newInsufficientMemoryException(char * filename){
	newException(filename,"Insufficient memory.");
}

void newException(char * filename,char * text){
	printf("<LOG - %s.c>\n\t%s\n<end>\n", filename, text);
	exit(1);
}

void underline(char * s){
	if(s==NULL){
		newException("utils","Null pointer");
	}
	char * buffer;
	int i;
	for(i=0;s[i]!='\0';i++){
		buffer=concat(buffer,"=");
	}
	printf("%s,%s\n",s,buffer);
}
