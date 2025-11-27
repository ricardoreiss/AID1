#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

void aumentar_capacidade(Products* produtos){
    produtos->capacidade *= 2;
    produtos->produtos = (Product*) realloc(produtos->produtos, produtos->capacidade * sizeof(Product));
}

int vazia(Products* produtos){
    return (produtos->topo == -1);
}

void push(Products* produtos, Product produto){
    if (produtos->capacidade - 1 == produtos->topo){
        aumentar_capacidade(produtos);
    }
    produtos->produtos[++produtos->topo] = produto;
    printf("Adicionado: %s\n", produto.name);
}

Product pop(Products* produtos){
    if (!vazia(produtos)){
        return produtos->produtos[produtos->topo--];
    }
}

Products* init(int capacidade_i, char* arquivo_nome){
    Products* produtos;
    produtos->produtos = (Product*) malloc(capacidade_i * sizeof(Product));
    produtos->topo = -1;
    produtos->capacidade = capacidade_i;

    FILE* file = fopen(arquivo_nome, "r");
    if (!file){
        printf("Erro ao abrir arquivo %s\n", arquivo_nome);
        exit(1);
    }
    int i = 0;
    Product produto;
    while(fscanf(file, "%s %d %f", produto.name, &produto.estoque, &produto.preco) == 3){
        push(produtos, produto);
        i++;
    }
    fclose(file);
    return produtos;
}

void salvar(Products* produtos, char* arquivo_nome){
    FILE* file = fopen(arquivo_nome, "w");
    if (!file){
        printf("Erro ao abrir arquivo %s\n", arquivo_nome);
        exit(1);
    }
    for (int z = 0; z <= produtos->topo; z++){
        fprintf(file, "%s %d %f\n", produtos->produtos[z].name, produtos->produtos[z].estoque, produtos->produtos[z].preco);
    }
    fclose(file);
}

void show(Products* produtos){
    for (int i = produtos->topo; i > -1; i-- ){
            Product produto = produtos->produtos[i];
            printf("Nome: %s; Estoque: %d; Valor: %f\n", produto.name, produto.estoque, produto.preco);
    }
}

void free_v(Products* produtos){
    free(produtos->produtos);
    produtos->topo = -1;
}
