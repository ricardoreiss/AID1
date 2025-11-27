#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
	char s[21];
	struct No* next;
}No;

No* pushp(No* cabeca, char s[21]){
	if (cabeca == NULL || strcmp(s, cabeca->s) < 0){
		No* novo = (No*) malloc(sizeof(No));
		strcpy(novo->s, s);
		novo->next = cabeca;
		return novo;
	}

	if (strcmp(s, cabeca->s) == 0) return cabeca;
	No* temp = cabeca;
	while(temp->next != NULL){
		int c = strcmp(s, temp->next->s);
		if (c == 0) return cabeca;
		if (c < 0){
			No* novo = (No*) malloc(sizeof(No));
			strcpy(novo->s, s);
			novo->next = temp->next;
			temp->next = novo;
			return cabeca;
		}
		temp = temp->next;
	}

	No* novo = (No*) malloc(sizeof(No));
	strcpy(novo->s, s);
	novo->next = NULL;
	temp->next = novo;
	return cabeca;
}

void show(No* cabeca){
	No* temp = cabeca;
	while(temp != NULL){
		if (temp != cabeca) printf(" ");
		printf("%s", temp->s);
		temp = temp->next;
	}
	printf("\n");
}

int main(){
	int c;
	scanf("%d", &c);
	getchar();
	if (c < 100) for (int i = 0; i < c; i++){
		char linha[21000];
		fgets(linha, sizeof(linha), stdin);
		linha[strcspn(linha, "\n")] = '\0';

		No* fila = NULL;
		char* w = strtok(linha, " ");
		while(w != NULL){
			fila = pushp(fila, w);
			w = strtok(NULL, " ");
		}
		if (fila != NULL) show(fila);
	}

	return 0;
}