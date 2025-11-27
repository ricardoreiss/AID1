#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int dado;
	struct No* proximo;
	struct No* anterior;
}No;

No* addf(No* cabeca, int v){
	No* novo = malloc(sizeof(No));
	novo->dado = v;
	if (cabeca == NULL){
		novo->proximo = novo;
		novo->anterior = novo;
		return novo;
	} else {
		novo->anterior = cabeca->anterior;
		cabeca->anterior->proximo = novo;
		cabeca->anterior = novo;
		novo->proximo = cabeca;
		return cabeca;
	}
}

int somoP(No* fila, No* cabeca){
	No* temp = fila->proximo;
	if (temp == cabeca){
		return fila->dado;
	}
	return temp->dado + somoP(temp->proximo, cabeca);
}

void show(No* cabeca){
	No* temp = cabeca;
	do{
		printf("%d ", temp->dado);
		temp = temp->proximo;
	}while(temp != cabeca);
	printf("\n");
}

void freef(No* cabeca){
	No* temp = cabeca;
	do{
		No* r = temp;
		temp = temp->proximo;
		free(r);
	}while(temp != cabeca);
}

int main(){
	No* fila = NULL;
	int n;
	while(1){
		scanf("%d", &n);
		if (n == -1) break;
		fila = addf(fila, n);
	}
	show(fila);

	freef(fila);
	return 0;
}