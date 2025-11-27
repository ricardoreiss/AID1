#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int* dados;
    int s;
    int t;
    int capacidade;
}Fila;

Fila* init(int capacidade){
    Fila* fila;
    fila->dados = (int*) malloc(capacidade * sizeof(int));
    fila->s = 0;
    fila->t = 0;
    fila->capacidade = capacidade;
}

void redimensionar(Fila* fila){
    printf("Redimensionando fila de %d para %d\n", fila->capacidade, fila->capacidade * 2);
    int n_capacidade = fila->capacidade * 2;
    fila->dados = (int*) realloc(fila->dados, n_capacidade * sizeof(int));
    
    if (fila->t < fila->s) {
        int f = 0;
        for (int z = fila->capacidade - 1; z >= fila->s; z--) {
            fila->dados[n_capacidade - 1 - f] = fila->dados[z];
            f++;
        }
        fila->s = n_capacidade - f;
    }
    
    fila->capacidade = n_capacidade;
}

int vazio(Fila* fila){
    return fila->t == fila->s;
}

void insert_f(Fila* fila, int num){
    if ((fila->t + 1)%fila->capacidade == fila->s) redimensionar(fila);
    fila->dados[fila->t] = num;
    fila->t = (fila->t + 1)%fila->capacidade;
}

int remove_f(Fila* fila){
    if (!vazio(fila)){
        int x = fila->dados[fila->s++];
        if (fila->s == fila->capacidade) fila->s = 0;
        return x;
    }
    printf("Fila vazia\n");
}

void show(Fila* fila){
    int s = fila->s;
    int t = fila->t;
    int N = fila->capacidade;
    if (s < t){
        for (int z = s; z < t; z++){
            printf("%d, ", fila->dados[z]);
        }
    } else if (t < s){
        for (int z = s; z < N; z++){
            printf("%d, ", fila->dados[z]);
        }
        for (int z = 0; z < t; z++){
            printf("%d, ", fila->dados[z]);
        }
    }
    printf("\n");
}

void free_f(Fila* fila){
    free(fila->dados);
    fila->s = 0;
    fila->t = 0;
}

int main(){
    Fila* fila = init(4);
    insert_f(fila, 1);
    insert_f(fila, 2);
    show(fila);
    insert_f(fila, 3);
    insert_f(fila, 4);
    insert_f(fila, 5);
    insert_f(fila, 6);
    show(fila);
    printf("%d\n", remove_f(fila));
    show(fila);
    printf("%d\n", remove_f(fila));
    show(fila);
    insert_f(fila, 7);
    insert_f(fila, 8);
    insert_f(fila, 9);
    insert_f(fila, 10);
    show(fila);
    printf("%d\n", remove_f(fila));
    printf("%d\n", remove_f(fila));
    printf("%d\n", remove_f(fila));
    insert_f(fila, 11);
    insert_f(fila, 12);
    show(fila);

    free(fila);
    return 0;
}


