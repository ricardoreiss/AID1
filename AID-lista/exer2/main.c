#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

int main(){
    int capacidade_i = 10;
    Products* produtos = init(capacidade_i, "produtos.txt");
    show(produtos);

    Product produto1 = pop(produtos);
    printf("Removido: %s\n", produto1.name);
    Product produto = pop(produtos);
    printf("Removido: %s\n", produto.name);
    produto = pop(produtos);
    printf("Removido: %s\n", produto.name);
    show(produtos);

    push(produtos, produto1);
    show(produtos);

    salvar(produtos, "produtos.txt");

    free_v(produtos);
    return 0;
}
