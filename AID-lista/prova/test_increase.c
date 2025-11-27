#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int* data;
	int tam;
	int s;
	int K;
}Fila;

Fila* init_f(int k){
	Fila* fila = (Fila*) malloc(sizeof(Fila));
	fila->data = (int*) calloc(k, sizeof(int));
	fila->tam = 0;
	fila->s = 0; 
	fila->K = k;
	return fila;
}

void add(Fila* fila, int n){
	fila->data[fila->tam] = n;
	if ((fila->tam+1)%fila->K == fila->s){
		fila->data[(fila->tam+1)%fila->K] = 0;
		fila->s++;
		if (fila->s == fila->K) fila->s = 0;
	}
	fila->tam = (fila->tam+1)%fila->K;
}

void increase(Fila* fila, int n){
	int n_k = fila->K + n;
	fila->data = (int*) realloc(fila->data, n_k * sizeof(int));
	// Initialize new memory to 0
	for (int i = fila->K; i < n_k; i++) {
		fila->data[i] = 0;
	}
	if (fila->tam < fila->s){
		int k = fila->K;
		int s = fila->s;
		int t = fila->tam;
    
		if ((t <= (k - s))){
			int z;
			for(z = 0; z < t ; z++){
				fila->data[(k + z)%n_k] = fila->data[z];
				fila->data[z] = 0;
			}
            fila->tam = (k + z)%n_k;

		} else {
			int i = 0;
			for(int z = k-1; z >= s; z--){
				fila->data[n_k -1 -i] = fila->data[z];
				fila->data[z] = 0;
				i++;
			}
			fila->s = n_k - i;
		}
	}
	fila->K = n_k;
}

void listar(Fila* fila){
    int t = fila->tam;
    int s = fila->s;
    int k = fila->K;
    if (fila->tam != s) {
    	if (s <= t){
            for (int z = s; z < t; z++){
                printf("%d ", fila->data[z]);
            }
        } else {
            for (int z = s; z < k; z++){
                printf("%d ", fila->data[z]);
            }
            for (int z = 0; z < t; z++){
                printf("%d ", fila->data[z]);
            }
        } 
        printf("\n");
    } else printf("EMPTY\n");
}

void show(Fila* fila){
	for (int z = 0; z < fila->K; z++){
		int n = fila->data[z];
		if (n) printf("%d ", fila->data[z]);
		else printf("- ");
	}
	printf("\n");
}

void remove_f(Fila* fila){
    int s = fila->s;
    if (fila->tam != s) {
        printf("%d\n", fila->data[s]);
        fila->data[s] = 0;
        fila->s = (s+1)%fila->K;
    } else printf("CLEAR\n");
}

int main() {
    printf("Test: INCREASE with s < tam (normal case)\n");
    Fila* f1 = init_f(3);
    add(f1, 1);
    add(f1, 2);
    printf("Before: ");
    show(f1);
    printf("List: ");
    listar(f1);
    increase(f1, 2);
    printf("After increase by 2: ");
    show(f1);
    printf("List: ");
    listar(f1);
    printf("s=%d, tam=%d, K=%d\n\n", f1->s, f1->tam, f1->K);
    
    printf("Test: INCREASE with s > tam (wrapped case)\n");
    Fila* f2 = init_f(3);
    add(f2, 1);
    add(f2, 2);
    add(f2, 3);  // Full, wraps
    remove_f(f2);  // Remove one
    add(f2, 4);
    printf("Before: ");
    show(f2);
    printf("List: ");
    listar(f2);
    printf("s=%d, tam=%d, K=%d\n", f2->s, f2->tam, f2->K);
    increase(f2, 2);
    printf("After increase by 2: ");
    show(f2);
    printf("List: ");
    listar(f2);
    printf("s=%d, tam=%d, K=%d\n\n", f2->s, f2->tam, f2->K);
    
    printf("Test: INCREASE when empty\n");
    Fila* f3 = init_f(3);
    increase(f3, 2);
    printf("After: ");
    show(f3);
    printf("List: ");
    listar(f3);
    printf("s=%d, tam=%d, K=%d\n", f3->s, f3->tam, f3->K);
    
    return 0;
}

