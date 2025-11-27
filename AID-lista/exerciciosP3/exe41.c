#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	char c;
	struct Node* left;
	struct Node* right;
}Node;

void substring(char dest[27], char src[27], int inicio, int fim) {
    int j = 0;
    for (int i = inicio; i < fim && src[i] != '\0'; i++) {
        dest[j++] = src[i];
    }
    dest[j] = '\0';
}

Node* gerarT(char pre[27], char in[27]){
	int tam = strlen(pre);
    if (tam == 0) {
        return NULL;
    }
	char root[2];
	root[0] = pre[0];
	root[1] = '\0';
	Node* novo = (Node*) malloc(sizeof(Node));
	novo->c = pre[0];
	novo->left = NULL;
	novo->right = NULL;

	int tam_in = strlen(in);
	if (1 < tam_in){
		int index_p = strcspn(in, root);

		char in_l[27];
		substring(in_l, in, 0, index_p);
		char in_r[27];
		substring(in_r, in, index_p+1, tam_in);
		//printf("%s %s\n", in_l, in_r);

		int tam_pre = strlen(pre);
		char pre_l[27];
		substring(pre_l, pre, 1, 1+strlen(in_l));
		char pre_r[27];
		substring(pre_r, pre, 1+strlen(in_l), tam_pre);
		//printf("%s %s\n", pre_l, pre_r);

		novo->left = gerarT(pre_l, in_l);
		novo->right = gerarT(pre_r, in_r);
	}

	return novo;
}

void showEDR(Node* root){
	if (!root) return;
	showEDR(root->left);
	showEDR(root->right);
	printf("%c", root->c);
}

int main(){
	char pre[27], in[27];
	while(scanf("%s %s", pre, in) != EOF){
		Node* tree = gerarT(pre, in);

		showEDR(tree);
		printf("\n");
	}
	return 0;
}