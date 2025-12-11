#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int d;
    int g;
    struct node* next;
} *link;

typedef struct grafo{
    int N;
    int M;
    int K;
    link *v;
} *Grafo;

Grafo initG(int k){
    Grafo G = malloc(sizeof(struct grafo));
    G->N = 0;
    G->M = 0;
    G->K = k;
    G->v = calloc(k, sizeof(link));
    return G;
}

void redimensionar(Grafo G, int n){
    if (n >= G->K){
        int oldK = G->K;
        int newK = n * 2;

        G->v = realloc(G->v, newK * sizeof(link));

        for (int i = oldK; i < newK; i++)
            G->v[i] = NULL;

        G->K = newK;
    }
}

link addN(Grafo G, int n){
    redimensionar(G, n);

    if (G->v[n] == NULL){
        link no = malloc(sizeof(struct node));
        no->d = n;
        no->g = 0;
        no->next = NULL;
        G->v[n] = no;
        G->N++;
    }
    return G->v[n];
}

void addM(Grafo G, int a, int b){
    link A = addN(G, a);
    link B = addN(G, b);

    link la = malloc(sizeof(struct node));
    la->d = a;
    la->next = B->next;
    B->g += 2;
    B->next = la;

    link lb = malloc(sizeof(struct node));
    lb->d = b;
    lb->next = A->next;
    A->g += 2;
    A->next = lb;

    G->M++;
}

int bfs(Grafo G, int n) {
    int *dist = malloc(G->K * sizeof(int));

    for (int i = 0; i < G->K; i++)
        dist[i] = -1;

    int *queue = malloc(G->K * sizeof(int));
    int qs = 0, qt = 0;

    dist[n] = 0;
    queue[qt++] = n;

    int maxDist = 0;

    while (qs < qt) {
        int u = queue[qs++];

        link adj = G->v[u]->next;
        while (adj) {
            int v = adj->d;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                if (dist[v] > maxDist)
                    maxDist = dist[v];
                queue[qt++] = v;
            }
            adj = adj->next;
        }
    }

    free(dist);
    free(queue);
    return maxDist;
}

int diametro(Grafo G) {
    int diam = 0;

    for (int i = 0; i < G->K; i++) {
        if (G->v[i] != NULL) {
            int d = bfs(G, i);
            if (d > diam) diam = d;
        }
    }

    return diam;
}

void showMaxMedGrau(Grafo G){
	int max = 0, sum = 0;

	for (int i = 0; i < G->K; i++){
		if (G->v[i] != NULL){
			int grau = G->v[i]->g;
			if (grau > G->v[max]->g) max = i;
			sum += grau;
		}
	}
	printf("<k>: %f\n", (float) sum / G->N);
	printf("k_max: %d (%d)\n", max, G->v[max]->g);
}

int main(){
	Grafo G = initG(3);

	FILE* file = fopen("grafo1.txt", "r");
    if (!file){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
	int s, t, w;
	int i = 0;
	fscanf(file, "%*s %*s %*s");
	while(fscanf(file, "%d %d %d", &s, &t, &w) == 3){
		addM(G, s, t);
		i++;
	}

	printf("N: %d\n", G->N);
	printf("M: %d\n", G->M);

	showMaxMedGrau(G);

	printf("Diâmetro: %d\n", diametro(G));

	fclose(file);
	return 0;
}

