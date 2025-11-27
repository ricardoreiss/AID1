#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pearl{
    char p[1001];
    struct Pearl* left;
    struct Pearl* right;
}Pearl;

typedef struct E{
    char name[101];
    struct E* next;
}E;

Pearl* insertPearl(Pearl* root, char p[1001]){
    if (root == NULL){
        Pearl* novo = (Pearl*) malloc(sizeof(Pearl));
        strncpy(novo->p, p, 1001);
        novo->left = NULL;
        novo->right = NULL;
        return novo;
    }
    int cmp = strcmp(p, root->p);
    if (cmp == 0) return root;
    if (cmp < 0) root->left = insertPearl(root->left, p);
    else root->right = insertPearl(root->right, p);
    return root;
}

int isPerola(Pearl* root, char s[1001]){
    while (root != NULL){
        int cmp = strcmp(s, root->p);
        if (cmp == 0) return 1;
        if (cmp < 0) root = root->left;
        else root = root->right;
    }
    return 0;
}

E* pushe(E* cabeca, E* e){
    if (cabeca == NULL || strcmp(e->name, cabeca->name) < 0){
        e->next = cabeca;
        return e;
    }
    E* temp = cabeca;
    while (temp->next != NULL){
        if (strcmp(e->name, temp->next->name) < 0){
            e->next = temp->next;
            temp->next = e;
            return cabeca;
        }
        temp = temp->next;
    }
    e->next = NULL;
    temp->next = e;
    return cabeca;
}

void showm(E* cabeca){
    E* temp = cabeca;
    do{
        if (temp != cabeca) printf(", ");
        printf("%s", temp->name);
        temp = temp->next;
    }while(temp != NULL);
    printf("\n");
}

int main(){
    int P, A, R;
    char name[101], p[1001];

    while (1){
        scanf("%d %d %d", &P, &A, &R);
        if (P == 0 && A == 0 && R == 0) break;
        getchar();

        Pearl* perolas = NULL;
        for (int i = 0; i < P; i++){
            fgets(p, sizeof(p), stdin);
            p[strcspn(p, "\n")] = '\0';
            perolas = insertPearl(perolas, p);
        }

        E* alunos = NULL;
        int max_q = 0;
        for (int i = 0; i < A; i++){
            scanf("%101s", name);
            getchar();
            E* aluno = (E*) malloc(sizeof(E));
            strncpy(aluno->name, name, 101);
            int aq = 0;
            aluno->next = NULL;

            for (int j = 0; j < R; j++){
                char s[1001];
                fgets(s, sizeof(s), stdin);
                s[strcspn(s, "\n")] = '\0';
                if ((max_q == R && aq == j+1) || max_q != R) aq += isPerola(perolas, s);
            }
            if (alunos == NULL) {
                pushe(alunos, aluno);
                max_q = aq;
            }
            else if (max_q < aq) {
                alunos = aluno;
                max_q = aq;
            }
            else if (max_q = aq) alunos = pushe(alunos, aluno);
        }
        if (alunos != NULL) showm(alunos);
    }

    return 0;
}
