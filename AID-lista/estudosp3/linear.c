#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* proximo;
}No;

void push(No** cabeca, int v){
    No* novo = malloc(sizeof(No));
    novo->valor = v;
    novo->proximo = *cabeca;
    *cabeca = novo;
}

int pop(No** cabeca){
    if (*cabeca != NULL){
        No* temp = *cabeca;
        int z = temp->valor;
        *cabeca = temp->proximo;
        free(temp);
        return z;
    }
}

void show(No** cabeca){
    No* temp = *cabeca;
    while(temp != NULL){
        printf("%d ", temp->valor);
        temp = temp->proximo;
    }
    printf("\n");
}

No* copiar(No* cabeca){
    if (cabeca == NULL){
        return NULL;
    }

    No* novo = malloc(sizeof(No));
    novo->valor = cabeca->valor;
    novo->proximo = copiar(cabeca->proximo);
    return novo;
}

No* inverter(No* cabeca){
    No* ant;
    No* novo = NULL;
    No* atual = cabeca;
    while (atual != NULL){
        ant = atual;
        atual = atual->proximo;
        ant->proximo = novo;
        novo = ant;
    }
    return novo;
}

No* concatenar(No* pri, No* seg){
    if(pri == NULL){
        return seg;
    }
    pri->proximo = concatenar(pri->proximo, seg);
    return pri;
}

int main(){
    No* pilha = NULL;
    push(&pilha, 2);
    push(&pilha, 3);
    push(&pilha, 4);
    push(&pilha, 5);
    push(&pilha, 6);
    show(&pilha);
    printf("%d\n", pop(&pilha));
    show(&pilha);

    No* copia = copiar(pilha);
    copia = inverter(copia);
    concatenar(copia, pilha);
    show(&copia);


    return 0;
}