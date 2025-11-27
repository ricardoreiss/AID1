#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int valor;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int v) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->valor = v;
    n->left = n->right = NULL;
    return n;
}

Node* insertT(Node* root, int v) {
    if (root == NULL) {
        Node* n = (Node*) malloc(sizeof(Node));
        n->valor = v;
        n->left = n->right = NULL;
        return n;
    }

    if (v < root->valor)
        root->left = insertT(root->left, v);
    else
        root->right = insertT(root->right, v);

    return root;
}

int searchT(Node* root, int num) {
    while (root != NULL) {
        if (num == root->valor) return 1;
        if (num < root->valor) root = root->left;
        else root = root->right;
    }
    return 0;
}

int altura(Node* r) {
    if (r == NULL) return -1;
    int e = altura(r->left);
    int d = altura(r->right);
    return 1 + (e > d ? e : d);
}


void swap(int* a, int* b) {
    int x = *a;
    *a = *b;
    *b = x;
}

int partition(int v[], int low, int high) {
    int pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (v[j] <= pivot) {
            i++;
            swap(&v[i], &v[j]);
        }
    }
    swap(&v[i + 1], &v[high]);
    return i + 1;
}

void quickSort(int v[], int low, int high) {
    if (low < high) {
        int pi = partition(v, low, high);
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}


int binarySearch(int v[], int n, int num) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (v[mid] == num) return 1;
        if (num < v[mid]) right = mid - 1;
        else left = mid + 1;
    }

    return 0;
}


int main() {
    srand(time(NULL));
    int i;

    int N = 10000;
    int vet[N];
    int vetOrd[N];

    clock_t start, end;

    start = clock();
    for (i = 0; i < N; i++) {
        vet[i] = rand() % 10001;
    }
    end = clock();
    double tempoInsVetor = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    for (i = 0; i < N; i++) 
        vetOrd[i] = vet[i];
    quickSort(vetOrd, 0, N - 1);
    end = clock();
    double tempoOrdenar = (double)(end - start) / CLOCKS_PER_SEC;

    Node* root = NULL;
    start = clock();
    for (i = 0; i < N; i++) {
        root = insertT(root, vet[i]);
    }
    end = clock();
    double tempoInsT = (double)(end - start) / CLOCKS_PER_SEC;



    int elemento1 = 50;
    int elemento2 = 5000;

    start = clock();
    for (i = 0; i < N; i++) {
        if (vet[i] == elemento1) break;
    }
    end = clock();
    double tempoBuscaVetor_50 = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    for (i = 0; i < N; i++) {
        if (vet[i] == elemento2) break;
    }
    end = clock();
    double tempoBuscaVetor_5000 = (double)(end - start) / CLOCKS_PER_SEC;


    start = clock();
    binarySearch(vetOrd, N, elemento1);
    end = clock();
    double tempoBuscaOrdenado_50 = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    binarySearch(vetOrd, N, elemento2);
    end = clock();
    double tempoBuscaOrdenado_5000 = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    searchT(root, elemento1);
    end = clock();
    double tempoBuscaT_50 = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    searchT(root, elemento2);
    end = clock();
    double tempoBuscaT_5000 = (double)(end - start) / CLOCKS_PER_SEC;


    int altEsq = altura(root->left);
    int altDir = altura(root->right);


    printf("\n\n============= RESULTADOS =============\n\n");

    printf("Estrutura\t\tInserção\tBusca 50\tBusca 5000\n");
    printf("Vetor aleatório\t\t%.6f\t%.6f\t%.6f\n",
           tempoInsVetor, tempoBuscaVetor_50, tempoBuscaVetor_5000);

    printf("Vetor ordenado + BB\t%.6f\t%.6f\t%.6f\n",
           tempoOrdenar, tempoBuscaOrdenado_50, tempoBuscaOrdenado_5000);

    printf("Árvore binária\t\t%.6f\t%.6f\t%.6f\n",
           tempoInsT, tempoBuscaT_50, tempoBuscaT_5000);

    printf("\nAltura subárvore esquerda: %d\n", altEsq);
    printf("Altura subárvore direita:  %d\n", altDir);

    free(vet);
    free(vetOrd);

    return 0;
}
