#ifndef PRODUCT_H
#define PRODUCT_H

typedef struct {
    char name[50];
    int estoque;
    float preco;
} Product;

typedef struct {
    Product* produtos;
    int topo;
    int capacidade;
}Products;

Products* init(int capacidade, char* arquivo_nome);
void push(Products* produtos, Product produto);
Product pop(Products* produtos);
Product peek(Products* produtos);
void free_v(Products* produtos);
void show(Products* produtos);
void salvar(Products* produtos, char* arquivo_nome);

#endif
