#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char* data;
	int topo;
	int n;
}Pilha;

Pilha* init_p(int n){
	Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
	pilha->data = (char*) malloc(n * sizeof(char));
	pilha->topo = -1;
	pilha->n = n;
	return pilha;
}

void push(Pilha* pilha, char c){
	pilha->data[++pilha->topo] = c;
}

char pop(Pilha* pilha){
	if (pilha->topo == -1) return ' ';
	return pilha->data[pilha->topo--];
}

void free_p(Pilha* pilha){
	free(pilha->data);
	free(pilha);
}

#define T 50
int main(){
	char s[T];

	scanf("%s", s);
	Pilha* pilha = init_p(T);
	int is = 1;
	for (int z = 0; z < T; z++){
		int c = s[z];
		if (c == '(' || c == '{' || c == '['){
			push(pilha, c);
		}
		if (c == ')' || c == '}' || c == ']'){
			int cp = pop(pilha);
			if (!((c == ')' && cp == '(') || (c == '}' && cp == '{') || (c == ']' && cp == '['))){
				is = 0;
				break;
			}
		}
	}
	if (pilha->topo != -1) is = 0;
	printf("%d\n", is);
	free(pilha);
	return 0;
}