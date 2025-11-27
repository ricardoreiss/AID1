#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

No* initp(){
	No* cabeca = malloc(sizeof(No));
	cabeca->proximo = cabeca;
	return cabeca;	
}

No* addp(No* cabeca, Product valor){
	No* novo = malloc(sizeof(No));
	cabeca->dado = valor;
	novo->proximo = cabeca->proximo;
	cabeca->proximo = novo;
	return novo;
}

void popp(No* cabeca){
	No* temp = cabeca->proximo;
	while(temp->proximo->proximo != cabeca){
		temp = temp->proximo;
	}
	free(temp->proximo);
	temp->proximo = cabeca;
}

void pops(No* cabeca, char name[50]){
	No* temp = cabeca->proximo;
	while(temp != cabeca){
		if (strcmp(temp->proximo->dado.name, name) == 0){
			No* r = temp->proximo;
			temp->proximo = r->proximo;
			free(r);			
		}
		temp = temp->proximo;
	}
}

void show(No* cabeca){
	No* temp = cabeca->proximo;
	while(temp != cabeca){
		printf("%s ", temp->dado.name);
		temp = temp->proximo;
	}
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