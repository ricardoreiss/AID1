#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node{
	char n;
	struct Node* left;
	struct Node* right;
}Node;

Node* pushT(Node* root, char num){
	if (root == NULL){
		Node* novo = (Node*) malloc(sizeof(Node));
		novo->n = num;
		novo->left = novo->right = NULL;
		return novo;
	}

	if (root->n > num) root->left = pushT(root->left, num);
	else root->right = pushT(root->right, num);

	return root;
}

int search(Node* root, char n){
	if (root == NULL) return 0;
	else if (root->n == n) return 1;
	else if (root->n > n) return search(root->left, n);
	else return search(root->right, n);
}

void prefixa(Node* root, int* f){
    if (root != NULL){
        if (!(*f)) printf(" ");
        *f = 0;

        printf("%c", root->n);

        prefixa(root->left, f);
        prefixa(root->right, f);
    }
}

void infixo(Node* root, int* f){
    if (root != NULL){
        infixo(root->left, f);

        if (!(*f)) printf(" ");
        *f = 0;

        printf("%c", root->n);

        infixo(root->right, f);
    }
}

void posfixo(Node* root, int* f){
    if (root != NULL){
        posfixo(root->left, f);
        posfixo(root->right, f);

        if (!(*f)) printf(" ");
        *f = 0;

        printf("%c", root->n);
    }
}

int main(){
	char n, c[8];
	int f;

	Node* tree = NULL;
	while(scanf("%s", c) != EOF){
		if (strcmp(c, "I") == 0){
			scanf(" %c", &n);
			tree = pushT(tree, n);
		}
		else if (strcmp(c, "INFIXA") == 0){
			f = 1;
			infixo(tree, &f);
			printf("\n");
		}
		else if (strcmp(c, "PREFIXA") == 0){
			f = 1;
			prefixa(tree, &f);
			printf("\n");
		}
		else if (strcmp(c, "POSFIXA") == 0){
			f = 1;
			posfixo(tree, &f);
			printf("\n");
		}
		else if (strcmp(c, "P") == 0){
			scanf(" %c", &n);
			f = search(tree, n);
			printf("%c ", n);
			if (f == 1) printf("existe\n");
			else printf("nao existe\n");
		}
	}

	return 0;
}