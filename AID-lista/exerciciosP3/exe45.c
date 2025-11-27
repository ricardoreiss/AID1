#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node{
	int n;
	struct Node* left;
	struct Node* right;
}Node;

Node* pushT(Node* root, int num){
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

Node* maior(Node* root){
    while (root->right != NULL)
        root = root->right;
    return root;
}

Node* removeT(Node* root, int valor){
    if (root == NULL) return NULL;

    if (valor < root->n) root->left = removeT(root->left, valor);

    else if (valor > root->n) root->right = removeT(root->right, valor);

    else {
        if (root->left == NULL && root->right == NULL) {
            return NULL;
        }

        if (root->left == NULL) {
            Node* temp = root->right;
            return temp;
        }
        if (root->right == NULL) {
            Node* temp = root->left;
            return temp;
        }

        Node* temp = maior(root->left);
        root->n = temp->n;
        root->left = removeT(root->left, temp->n);
    }

    return root;
}

int search(Node* root, int n){
	if (root == NULL) return 0;
	else if (root->n == n) return 1;
	else if (root->n > n) return search(root->left, n);
	else return search(root->right, n);
}

void prefixa(Node* root, int* f){
    if (root != NULL){
        if (!(*f)) printf(" ");
        *f = 0;

        printf("%d", root->n);

        prefixa(root->left, f);
        prefixa(root->right, f);
    }
}

void infixo(Node* root, int* f){
    if (root != NULL){
        infixo(root->left, f);

        if (!(*f)) printf(" ");
        *f = 0;

        printf("%d", root->n);

        infixo(root->right, f);
    }
}

void posfixo(Node* root, int* f){
    if (root != NULL){
        posfixo(root->left, f);
        posfixo(root->right, f);

        if (!(*f)) printf(" ");
        *f = 0;

        printf("%d", root->n);
    }
}

int main(){
	char c[8];
	int f, n;

	Node* tree = NULL;
	while(scanf("%s", c) != EOF){
		if (strcmp(c, "I") == 0){
			scanf(" %d", &n);
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
			scanf(" %d", &n);
			f = search(tree, n);
			printf("%d ", n);
			if (f == 1) printf("existe\n");
			else printf("nao existe\n");
		}
		else if (strcmp(c, "R") == 0){
			scanf(" %d", &n);
			tree = removeT(tree, n);
		}
	}

	return 0;
}