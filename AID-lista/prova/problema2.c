#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char* data;
	int topo;
	int n;
}Pilha;

Pilha* init_p(){
	Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
	pilha->data = (char*) malloc(3 * sizeof(char));
	pilha->topo = -1;
	pilha->n = 3;
	return pilha;
}

void redimensionar(Pilha* pilha){
	pilha->n *= 2;
	pilha->data = (char*) realloc(pilha->data, pilha->n * sizeof(char));
}

void push(Pilha* pilha, char c){
	if (++pilha->topo == pilha->n) redimensionar(pilha);
	pilha->data[pilha->topo] = c;
}

char pop(Pilha* pilha){
	if (pilha->topo == -1) return ' ';
	return pilha->data[pilha->topo--];
}

void free_p(Pilha* pilha){
	free(pilha->data);
	free(pilha);
}

int main(){
	char c;
	Pilha* pilha = init_p();
	int is = 1;
	do{
		scanf("%c", &c);
		if (is == 1){
			if (c == '(' || c == '{' || c == '['){
				push(pilha, c);
			}
			if (c == ')' || c == '}' || c == ']'){
				int cp = pop(pilha);
				if (!((c == ')' && cp == '(') || (c == '}' && cp == '{') || (c == ']' && cp == '['))){
					is = 0;
				}
			}
		}
	}while(c != '!');
    if (pilha->topo != -1) is = 0;
	if (is == 1) printf("bem formada");
	else printf("mal formada");
	free_p(pilha);
	return 0;
}