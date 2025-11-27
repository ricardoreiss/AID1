#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int num;
	struct No* next;
	struct No* past;
}No;

No* pushf(No* cabeca, int n){
	No* novo = (No*) malloc(sizeof(No));
	novo->next = cabeca->next;
	novo->num = cabeca->num;
	novo->past = cabeca;

	cabeca->num = n;
	cabeca->next->past = novo;
	cabeca->next = novo;
	return novo;
}

// void show(No* cabeca){
// 	printf("%d ", cabeca->num);
// 	No* temp = cabeca->past;
// 	do{
// 		printf("%d ", temp->num);
// 		temp = temp->past;
// 	}while(temp != cabeca);
// 	printf("\n");
// }

No* pops(No* cabeca){
	No* temp = cabeca;
	printf("Discarded cards: ");
	while(temp->next != temp){
		if (temp != cabeca) printf(", ");
		No* r = temp;
		temp->past->next = r->next;
		temp->next->past = r->past; 
		printf("%d", r->num);
		temp = r->next->next;
		free(r);
	}
	printf("\n");
	return temp;
}

int lcard(int n){
	No* cabeca = (No*) malloc(sizeof(No));
	cabeca->num = 1;
	cabeca->next = cabeca;
	cabeca->past = cabeca;

	for(int i = 2; i <= n; i++){
		cabeca = pushf(cabeca, i);
	}
	cabeca = pops(cabeca);
	return cabeca->num;
}

int main(){
	int n;
	while(1){
		scanf("%d", &n);
		if (n == 0) break;
		printf("Remaining card: %d\n", lcard(n));
	}

	return 0;
}