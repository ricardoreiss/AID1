#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int* data;
	int tam;
	int s;
	int K;
}Fila;

Fila* init_f(int k){
	Fila* fila = (Fila*) malloc(sizeof(Fila));
	fila->data = (int*) calloc(k, sizeof(int));
	fila->tam = 0;
	fila->s = 0; 
	fila->K = k;
	return fila;
}

void add(Fila* fila, int n){
	fila->data[fila->tam] = n;
	if ((fila->tam+1)%fila->K == fila->s){
		fila->data[(fila->tam+1)%fila->K] = 0;
		fila->s++;
		if (fila->s == fila->K) fila->s = 0;
	}
	fila->tam = (fila->tam+1)%fila->K;
}

void listar(Fila* fila){
    int t = fila->tam;
    int s = fila->s;
    int k = fila->K;
    printf("DEBUG: s=%d, tam=%d, K=%d\n", s, t, k);
    if (fila->tam != s) {
    	if (s <= t){
            for (int z = s; z < t; z++){
                printf("%d ", fila->data[z]);
            }
        } else {
            for (int z = s; z < k; z++){
                printf("%d ", fila->data[z]);
            }
            for (int z = 0; z < t; z++){
                printf("%d ", fila->data[z]);
            }
        } 
        printf("\n");
    } else printf("EMPTY\n");
}

void show(Fila* fila){
	for (int z = 0; z < fila->K; z++){
		printf("%d ", fila->data[z]);
	}
	printf("\n");
}

int main() {
    Fila* f = init_f(3);
    printf("After init: ");
    show(f);
    printf("s=%d, tam=%d\n\n", f->s, f->tam);
    
    add(f, 1);
    printf("After ADD 1: ");
    show(f);
    printf("s=%d, tam=%d\n", f->s, f->tam);
    listar(f);
    printf("\n");
    
    add(f, 2);
    printf("After ADD 2: ");
    show(f);
    printf("s=%d, tam=%d\n", f->s, f->tam);
    listar(f);
    printf("\n");
    
    add(f, 3);
    printf("After ADD 3: ");
    show(f);
    printf("s=%d, tam=%d\n", f->s, f->tam);
    listar(f);
    printf("\n");
    
    add(f, 4);
    printf("After ADD 4: ");
    show(f);
    printf("s=%d, tam=%d\n", f->s, f->tam);
    listar(f);
    printf("\n");
    
    return 0;
}


