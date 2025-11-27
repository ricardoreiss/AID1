#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor;
    struct No* proximo;
}No;

void addi(No* cabeca, int v){
    No* novo = malloc(sizeof(No));
    novo->valor = v;
    novo->proximo = cabeca->proximo;
    cabeca->proximo = novo;
} 

No* addf(No* cabeca, int v){
    No* novo = malloc(sizeof(No));
    cabeca->valor = v;
    novo->proximo = cabeca->proximo;
    cabeca->proximo = novo;
    return novo;
}

int popi(No* cabeca){
    No* temp = cabeca->proximo;
    cabeca->proximo = temp->proximo;
    int z = temp->valor;
    free(temp);
    return z;
}

int popf(No* cabeca){
    No* temp = cabeca->proximo;
    while (temp->proximo->proximo != cabeca){
        temp = temp->proximo;
    }
    int z = temp->proximo->valor;
    free(temp->proximo);
    temp->proximo = cabeca;
    return z;
}

int pops(No* cabeca, int v){
    No* temp = cabeca->proximo;
    while (temp != cabeca){
        if (temp->proximo->valor == v){
            No* r = temp->proximo;
            temp->proximo = temp->proximo->proximo;
            int z = r->valor;
            free(r);
            return z;
        }
        temp = temp->proximo;
    }
    return NULL;
}

void show(No* cabeca){
    No* temp = cabeca->proximo;
    while(temp != cabeca){
        printf("%d ", temp->valor);
        temp = temp->proximo;
    }
    printf("\n");
}

void freef(No* cabeca){
    No* temp = cabeca->proximo;
    while(temp != cabeca){
        No* r = temp;
        temp = temp->proximo;
        free(r);
    }
    free(cabeca);
}

int main(){
    No* fila = malloc(sizeof(No));
    fila->proximo = fila;
    addi(fila, 3);
    addi(fila, 4);
    addi(fila, 5);
    fila = addf(fila, 10);
    fila = addf(fila, 12);
    fila = addf(fila, 13);
    addi(fila, 6);
    show(fila);
    
    printf("%d\n", popi(fila));
    printf("%d\n", popi(fila));
    printf("%d\n", pops(fila, 3));
    show(fila);
    printf("%d\n", popf(fila));
    printf("%d\n", popf(fila));
    show(fila);

    freef(fila);
    return 0;
}