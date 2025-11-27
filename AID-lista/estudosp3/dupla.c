#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
	int dado;
	struct No* proximo;
    struct No* anterior;
}No;

No* initp(){
	No* cabeca = malloc(sizeof(No));
	cabeca->proximo = cabeca;
    cabeca->anterior = cabeca;
	return cabeca;	
}

void addp(No** cabeca, int valor){
	No* novo = malloc(sizeof(No));
    novo->dado = valor;
    if (*cabeca == NULL){
        novo->proximo = novo;
        novo->anterior = novo;
        *cabeca = novo;
    } else {
        No* temp = *cabeca;
        novo->proximo = temp;
        novo->anterior = temp->anterior;
        temp->anterior->proximo = novo;
        temp->anterior = novo;
    }
//	cabeca->dado = valor;
//	novo->proximo = cabeca->proximo;
//	cabeca->proximo = novo;
	//return novo;
}

void popp(No* cabeca){
	No* r = cabeca->anterior;
    cabeca->anterior = r->anterior;
    r->anterior->proximo = cabeca;
	free(r);
}

void pops(No* cabeca, int v){
	No* temp = cabeca;
	do{
		if (temp->proximo->dado == v){
			No* r = temp->proximo;
			temp->proximo = r->proximo;
            r->proximo->anterior = temp;
			free(r);			
		}
		temp = temp->proximo;
	}while(temp != cabeca);
}

void show(No* cabeca){
	No* temp = cabeca;
	do{
		printf("%d ", temp->dado);
		temp = temp->proximo;
	}while(temp != cabeca);
	printf("\n");
}

void freep(No* cabeca){
	No* temp = cabeca->proximo;
	while (temp != cabeca){
		No* r = temp;
		temp = temp->proximo;
		free(r);
	}
	free(cabeca);
}

int main(){
	No* fila = NULL;
	addp(&fila, 2);
    show(fila);
	addp(&fila, 3);
	addp(&fila, 4);
    addp(&fila, 5);
    addp(&fila, 6);
	show(fila);

	popp(fila);
//	show(fila);
	pops(fila, 3);
//	show(fila);
	popp(fila);
    popp(fila);
    popp(fila);
//	show(fila);
    addp(&fila, 77);
    show(fila);

	addp(&fila, 9);
	addp(&fila, 11);
	addp(&fila, 12);
	pops(fila, 666);
	show(fila);

	freep(fila);
	return 0;
}