#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int num;
	struct No* next;
}No;

No* pushf(No* cabeca, int n){
	No* novo = (No*) malloc(sizeof(No));
	novo->next = cabeca->next;
	novo->num = cabeca->num;
	cabeca->num = n;
	cabeca->next = novo;
	return novo;
}

No* definet(No* cabeca, int k){
	No* temp = cabeca;
	for(int i = 2; i < k; i++) temp = temp->next;
	return temp;
}

// void show(No* cabeca){
// 	printf("%d ", cabeca->num);
// 	No* temp = cabeca->next;
// 	do{
// 		printf("%d ", temp->num);
// 		temp = temp->next;
// 	}while(temp != cabeca);
// 	printf("\n");
// }

No* pops(No* cabeca, int k){
	No* temp = cabeca;
	while(temp->next != temp){
		temp = definet(temp, k);
		No* r = temp->next;
		temp->next = r->next;
		free(r);
		temp = temp->next;
	}
	return temp;
}

int flavius(int n, int k){
	No* cabeca = (No*) malloc(sizeof(No));
	cabeca->num = 1;
	cabeca->next = cabeca;

	for(int i = 2; i <= n; i++){
		cabeca = pushf(cabeca, i);
	}

	cabeca = pops(cabeca, k);
	return cabeca->num;
}

int main(){
	int c, n, k;
	scanf("%d", &c);

	for(int i = 1; i <= c; i++){
		scanf("%d %d", &n, &k);
		printf("Case %d: %d\n", i, flavius(n, k));
	}

	return 0;
}