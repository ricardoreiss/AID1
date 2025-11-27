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


void showPercurso(Node* tree, int n, int c){
	printf("Case %d:\n", c);
	int MAX_LINE = n;
	Node* temp[MAX_LINE];
	temp[0] = tree;
	int t = 1;
	do{
		Node* temp2[MAX_LINE];
		int t2 = 0;
		for (int i = 0; i < t; i++){
			Node* p = temp[i];
			if (p->dado != tree->dado) printf(" ");
			printf("%d", p->dado);

			if (p->left != NULL) temp2[t2++] = p->left;
			if (p->right != NULL) temp2[t2++] = p->right;
		}
		memcpy(temp, temp2, sizeof(temp2));
		t = t2;
	}while(t != 0);

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
		showPercurso(tree, n, i+1);
		printf("\n\n");
	}



	return 0;
}