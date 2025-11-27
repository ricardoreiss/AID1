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

void remove_f(Fila* fila){
    int s = fila->s;
    if (fila->tam != s) {
        printf("%d\n", fila->data[s]);
        fila->data[s] = 0;
        fila->s = (s+1)%fila->K;
    } else printf("CLEAR\n");
}

void increase(Fila* fila, int n){
	int n_k = fila->K + n;
	fila->data = (int*) realloc(fila->data, n_k * sizeof(int));
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

void show(Fila* fila){
	for (int z = 0; z < fila->K; z++){
		int n = fila->data[z];
		if (n) printf("%d ", fila->data[z]);
		else printf("- ");
	}
	printf("\n");
    // printf("%d %d %d\n", fila->s, fila->tam, fila->K);
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

void free_f(Fila* fila){
	free(fila->data);
	free(fila);
}

int main(){
	int K, n;
	scanf("%d", &K);
	Fila* fila = init_f(K);
	char command[10];
	while(strcmp(command, "END") != 0){
        scanf("%s", command);
		if (strcmp(command, "ADD") == 0){
			scanf("%d", &n);
			add(fila, n);
		} else if (strcmp(command, "PRINT") == 0) {
			show(fila);
		} else if (strcmp(command, "LIST") == 0) {
			listar(fila);
        } else if (strcmp(command, "INCREASE") == 0) {
			scanf("%d", &n);
			increase(fila, n);
		} else if (strcmp(command, "REMOVE") == 0) {
			remove_f(fila);
        }
	}

	free_f(fila);
	return 0;
}

