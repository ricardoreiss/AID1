#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int* dados;
    int topo;
    int capacidade;
}Pilha;

Pilha* init(int capacidade){
    Pilha* pilha;
    pilha->dados = (int*) malloc(capacidade * sizeof(int));
    pilha->topo = -1;
    pilha->capacidade = capacidade;
    return pilha;
}

void redimensionar(Pilha* pilha){
    pilha->capacidade *= 2;
    pilha->dados = (int*) realloc(pilha->dados, pilha->capacidade * sizeof(int));
}

int vazio(Pilha* pilha){
    return (pilha->topo == -1);
}

void push(Pilha* pilha, int num){
    if (++pilha->topo == pilha->capacidade) redimensionar(pilha);
    pilha->dados[pilha->topo] = num;
}

int pop(Pilha* pilha){
    if (!vazio(pilha)) return pilha->dados[pilha->topo--];
    printf("Pilha Vazia\n");
}

void show(Pilha* pilha){
    for (int z = 0; z <= pilha->topo; z++) printf("%d, ", pilha->dados[z]);
    printf("\n");
}

void free_p(Pilha* pilha){
    free(pilha->dados);
    pilha->topo = -1;
}

int main(){
    Pilha* pilha = init(3);
    push(pilha, 5);
    show(pilha);
    push(pilha, 7);
    push(pilha, 9);
    push(pilha, 3);
    push(pilha, 1);
    show(pilha);
    printf("%d\n", pop(pilha));
    printf("%d\n", pop(pilha));
    push(pilha, 10);
    show(pilha);

    free(pilha);
    return 0;
}
