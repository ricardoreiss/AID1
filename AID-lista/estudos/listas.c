#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int* dados;
    int tam;
    int capacidade;
} Lista;

Lista* init(int capacidade){
    Lista* lista;
    lista->dados = (int*) malloc(capacidade * sizeof(int));
    lista->tam = 0;
    lista->capacidade = capacidade;
    return lista;
}

void redimensionar(Lista* lista){
    lista->capacidade *= 2;
    lista->dados = (int*) realloc(lista->dados, lista->capacidade * sizeof(int));
}

int vazio(Lista* lista){
    return (lista->tam == 0);
}

void insert_l(Lista* lista, int num){
    if (lista->tam == lista->capacidade) redimensionar(lista);
    lista->dados[lista->tam++] = num;
}

void remove_l(Lista* lista, int num){
    if (vazio(lista)) printf("Lista Vazia\n");
    else lista->dados[num] = lista->dados[--lista->tam];
}

void show(Lista* lista){
    for (int z = 0; z < lista->tam; z++){
        printf("%d, ", lista->dados[z]);
    }
    printf("\n");
}

void free_list(Lista* lista){
    free(lista->dados);
    lista->tam = 0;
}

int main(){
    Lista* lista = init(3);
    insert_l(lista, 3);
    insert_l(lista, 4);
    show(lista);
    insert_l(lista, 3);
    insert_l(lista, 4);
    insert_l(lista, 3);
    insert_l(lista, 4);
    show(lista);
    remove_l(lista, 5);
    show(lista);
    remove_l(lista, 1);
    show(lista);

    free(lista);
    return 0;
}
