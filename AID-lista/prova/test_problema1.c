#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

// Test helper functions
void capture_output(char* buffer, int size, void (*func)(Fila*), Fila* fila) {
    freopen("output.txt", "w", stdout);
    func(fila);
    freopen("CON", "w", stdout);
    FILE* f = fopen("output.txt", "r");
    fgets(buffer, size, f);
    fclose(f);
}

int main() {
    printf("Testing problema1.c...\n\n");
    
    // Test 1: Basic ADD and LIST
    printf("Test 1: Basic ADD and LIST\n");
    Fila* f1 = init_f(3);
    add(f1, 1);
    add(f1, 2);
    listar(f1);  // Should print: 1 2
    free_f(f1);
    
    // Test 2: Queue full replacement
    printf("\nTest 2: Queue full replacement (K=3, can store 2)\n");
    Fila* f2 = init_f(3);
    add(f2, 1);
    add(f2, 2);
    add(f2, 3);  // Should replace oldest (1)
    listar(f2);  // Should print: 2 3
    free_f(f2);
    
    // Test 3: REMOVE from empty
    printf("\nTest 3: REMOVE from empty\n");
    Fila* f3 = init_f(3);
    remove_f(f3);  // Should print: CLEAR
    free_f(f3);
    
    // Test 4: REMOVE normal
    printf("\nTest 4: REMOVE normal\n");
    Fila* f4 = init_f(3);
    add(f4, 1);
    add(f4, 2);
    remove_f(f4);  // Should print: 1
    listar(f4);    // Should print: 2
    free_f(f4);
    
    // Test 5: INCREASE when s < tam (normal case)
    printf("\nTest 5: INCREASE when s < tam\n");
    Fila* f5 = init_f(3);
    add(f5, 1);
    add(f5, 2);
    increase(f5, 2);  // K becomes 5
    printf("After increase:\n");
    show(f5);
    listar(f5);  // Should print: 1 2
    free_f(f5);
    
    // Test 6: INCREASE when s > tam (wrapped case)
    printf("\nTest 6: INCREASE when wrapped (s > tam)\n");
    Fila* f6 = init_f(3);
    add(f6, 1);
    add(f6, 2);
    add(f6, 3);  // Queue wraps, s might be > tam
    remove_f(f6);  // Remove one, s increases
    add(f6, 4);
    printf("Before increase:\n");
    show(f6);
    listar(f6);
    increase(f6, 2);
    printf("After increase:\n");
    show(f6);
    listar(f6);
    free_f(f6);
    
    // Test 7: PRINT with empty slots
    printf("\nTest 7: PRINT with empty slots\n");
    Fila* f7 = init_f(4);
    add(f7, 1);
    add(f7, 2);
    show(f7);  // Should show: 1 2 - -
    free_f(f7);
    
    // Test 8: Edge case - K=1
    printf("\nTest 8: Edge case K=1 (can store 0 elements)\n");
    Fila* f8 = init_f(1);
    add(f8, 1);
    listar(f8);  // Should print: EMPTY (because K=1, can store 0)
    show(f8);
    free_f(f8);
    
    // Test 9: Multiple REMOVE operations
    printf("\nTest 9: Multiple REMOVE\n");
    Fila* f9 = init_f(3);
    add(f9, 1);
    add(f9, 2);
    remove_f(f9);
    remove_f(f9);
    remove_f(f9);  // Should print: CLEAR
    free_f(f9);
    
    // Test 10: Full cycle wrap
    printf("\nTest 10: Full cycle wrap\n");
    Fila* f10 = init_f(3);
    add(f10, 1);
    add(f10, 2);
    add(f10, 3);  // Full
    add(f10, 4);  // Replaces 1
    add(f10, 5);  // Replaces 2
    listar(f10);  // Should print: 3 4 5
    free_f(f10);
    
    return 0;
}


