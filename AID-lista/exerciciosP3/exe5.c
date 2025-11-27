#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int num;
    struct No* left;
    struct No* right;
} No;

No* pushp(No* root, int n) {
    if (!root) {
        No* novo = malloc(sizeof(No));
        novo->num = n;
        novo->left = novo->right = NULL;
        return novo;
    }

    if (n < root->num) root->left = pushp(root->left, n);
    else root->right = pushp(root->right, n);

    return root;
}

void ERD(No* root) {
    if (!root) return;
    ERD(root->left);
    printf("%d\n", root->num);
    ERD(root->right);
}

void DRE(No* root) {
    if (!root) return;
    DRE(root->right);
    printf("%d\n", root->num);
    DRE(root->left);
}

int main() {
    int c, n;

    No* pares = NULL;
    No* impares = NULL;

    scanf("%d", &c);
    for (int i = 0; i < c; i++) {
        scanf("%d", &n);

        if (n % 2 == 0) pares = pushp(pares, n);
        else impares = pushp(impares, n);
    }

    ERD(pares); 
    DRE(impares);
    return 0;
}
