#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudante.h"

Estudante* incluir_estudante(Estudante* students, int* tam, char* name){
    students = (Estudante*) realloc(students, (*tam + 1) * sizeof(Estudante));
    students[*tam].age = 20;
    strcpy(students[*tam].name, name);
    (*tam)++;
    return students;
}

Estudante* apagar_estudante(Estudante* students, char* name, int* tam){
    for (int z = 0; z < *tam; z++){
        if (strcmp(students[z].name, name) == 0){
            (*tam)--;
            students[z] = students[*tam];
            students = (Estudante*) realloc(students, *tam * sizeof(Estudante));
            break;
        }
    }
    return students;
}

void listar_estudantes(Estudante* students, int tam){
    for (int z = 0; z < tam; z++){
        printf("Nome: %s; Idade: %d\n", students[z].name, students[z].age);
    }
}

Estudante* carregar_estudantes_arquivo(int* tam, char* nomeArquivo){
    FILE* file = fopen(nomeArquivo, "rb");
    if (!file){
        printf("Erro ao abrir o arquivo");
        return NULL;
    }
    Estudante* estudantes = NULL;
    Estudante estudante;
    while(fread(&estudante, sizeof(Estudante), 1, file) == 1){
        estudantes = incluir_estudante(estudantes, tam, estudante.name);
    }
    fclose(file);
    return estudantes;
}

void salvar_estudantes_arquivo(Estudante* students, int tam, char* nomeArquivo){
    FILE* file = fopen(nomeArquivo, "wb");
    if (!file){
        printf("Erro ao abrir o arquivo");
        return;
    }
    for (int z = 0; z < tam; z++){
        fwrite(&students[z], sizeof(Estudante), 1, file);
    }
    fclose(file);
}



