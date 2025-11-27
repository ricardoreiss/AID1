#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudante.h"
int main() {

Estudante* students = NULL;
int tam = 0;
students = carregar_estudantes_arquivo(&tam, "students.dat");
char name[50];
int opcao;
do {
printf("1. Adicionar Estudante\n2. Remover Estudante\n3. Listar Estudantes\n4. Sair\n");
scanf("%d", &opcao);
if (opcao == 1) {
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    students = incluir_estudante(students, &tam, name);
}
else if (opcao == 2){
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    students = apagar_estudante(students,name, &tam);
}
else if (opcao == 3) listar_estudantes(students, tam);
} while (opcao != 4);
salvar_estudantes_arquivo(students, tam, "students.dat");
free(students);
return 0;
}
