#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PEROLAS 10000
#define MAX_ALUNOS 10000
#define MAX_RESPOSTAS 10000
#define MAX_PEROLA_LEN 1001
#define MAX_NOME_LEN 101

typedef struct {
    char name[MAX_NOME_LEN];
    int score;
} E;

typedef struct VencedorNode {
    char name[MAX_NOME_LEN];
    struct VencedorNode* next;
} VencedorNode;

int comparar_alunos(const void *a, const void *b) {
    const E *alunoA = (const E *)a;
    const E *alunoB = (const E *)b;
    return strcmp(alunoA->name, alunoB->name);
}

char* ler_linha(char *buffer, int max_len) {
    if (fgets(buffer, max_len, stdin) == NULL) {
        return NULL;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == max_len - 1 && buffer[max_len - 2] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    return buffer;
}

int isPerola(char **perolas, int P, char *s) {
    for (int k = 0; k < P; k++) {
        if (strcmp(s, perolas[k]) == 0) {
            return 1;
        }
    }
    return 0;
}

VencedorNode* pushe(VencedorNode* cabeca, const char* name) {
    VencedorNode* novo_node = (VencedorNode*) malloc(sizeof(VencedorNode));
    if (novo_node == NULL) {
        return cabeca; 
    }
    strncpy(novo_node->name, name, MAX_NOME_LEN - 1);
    novo_node->name[MAX_NOME_LEN - 1] = '\0';
    
    novo_node->next = cabeca;
    return novo_node;
}

void showm(E* vencedores_array, int num_vencedores) {
    if (num_vencedores > 0) {
        printf("%s", vencedores_array[0].name);
    }

    for (int i = 1; i < num_vencedores; i++) {
        if (strcmp(vencedores_array[i].name, vencedores_array[i-1].name) == 0) {
            continue;
        }
        printf(", %s", vencedores_array[i].name);
    }
    printf("\n");
}


void processar_caso_teste(int P, int A, int R) {
    char **perolas = (char **)malloc(P * sizeof(char *));
    if (perolas == NULL) return;
    
    char buffer[MAX_PEROLA_LEN];
    
    for (int i = 0; i < P; i++) {
        perolas[i] = (char *)malloc(MAX_PEROLA_LEN * sizeof(char));
        if (perolas[i] == NULL) return;
        if (ler_linha(perolas[i], MAX_PEROLA_LEN) == NULL) return;
    }

    E *alunos = (E *)malloc(A * sizeof(E));
    if (alunos == NULL) return;
    
    int max_q = -1;

    for (int i = 0; i < A; i++) {
        if (ler_linha(alunos[i].name, MAX_NOME_LEN) == NULL) return;
        
        int aq = 0;
        for (int j = 0; j < R; j++) {
            if (ler_linha(buffer, MAX_PEROLA_LEN) == NULL) return;
            
            if (isPerola(perolas, P, buffer)) {
                aq++;
            }
        }
        alunos[i].score = aq;
        
        if (alunos[i].score > max_q) {
            max_q = alunos[i].score;
        }
    }

    VencedorNode* lista_vencedores = NULL;
    int num_vencedores = 0;

    for (int i = 0; i < A; i++) {
        if (alunos[i].score == max_q) {
            lista_vencedores = pushe(lista_vencedores, alunos[i].name);
            num_vencedores++;
        }
    }
    
    if (num_vencedores == 0) return;

    E *vencedores_array = (E *)malloc(num_vencedores * sizeof(E));
    if (vencedores_array == NULL) return;
    
    VencedorNode* atual = lista_vencedores;
    int k = 0;
    while (atual != NULL) {
        strcpy(vencedores_array[k].name, atual->name); 
        atual = atual->next;
        k++;
    }
    
    qsort(vencedores_array, num_vencedores, sizeof(E), comparar_alunos);
    showm(vencedores_array, num_vencedores);
}

int main() {
    int P, A, R;
    
    while (scanf("%d %d %d", &P, &A, &R) == 3) {
        if (P == 0 && A == 0 && R == 0) {
            break;
        }
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        processar_caso_teste(P, A, R);
    }

    return 0;
}