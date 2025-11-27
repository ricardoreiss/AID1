#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct Node{
	int dado;
	struct Node* left;
	struct Node* right;
}Node;

Node* pushT(Node* root, int num){
	if (root == NULL){
		Node* novo = (Node*) malloc(sizeof(Node));
		novo->dado = num;
		novo->left = novo->right = NULL;
		return novo;
	}

	if (root->dado > num) root->left = pushT(root->left, num);
	else root->right = pushT(root->right, num);

	return root;
}

void showRED(Node* root, int i){
	if (!root) return;
	printf(" "); 
	printf("%d", root->dado);
	showRED(root->left, i);
	showRED(root->right, i);
}

void showERD(Node* root, int i){
	if (!root) return;
	showERD(root->left, i);
	printf(" "); 
	printf("%d", root->dado, i);
	showERD(root->right, i);
}

void showEDR(Node* root, int i){
	if (!root) return;
	showEDR(root->left, i);
	showEDR(root->right, i);
	printf(" "); 
	printf("%d", root->dado);
}

void showT(Node* tree, int c){
	int i = tree->dado;
	printf("Case %d:\n", c);

	printf("Pre.:");
	showRED(tree, i);
	printf("\n");

	printf("In..:");
	showERD(tree, i);
	printf("\n");

	printf("Post:");
	showEDR(tree, i);
	printf("\n");
}

int main(){
	int q, n, num;
	scanf("%d", &q);

	for (int i = 0; i < q; i++){
		scanf("%d", &n);
		
		Node* tree = NULL;
		for(int j = 0; j < n; j++){
			scanf("%d", &num);
			tree = pushT(tree, num);
		}
		showT(tree, i+1);
		printf("\n");
	}



	return 0;
}