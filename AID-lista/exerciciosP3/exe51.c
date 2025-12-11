#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char c;
	struct node* next;
}* link;

typedef struct grafo{
	int N;
	int M;
	link *v;
}* Grafo;

Grafo initG(int n, int m){
	Grafo G = malloc(sizeof(struct grafo));
	G->N = n;
	G->M = m;
	G->v = calloc(n, sizeof(link));
	return G;
}

link addN(Grafo G, char c){
	int index = c - 97;
	if (G->v[index] == NULL){
		link no = malloc(sizeof(struct node));
		no->c = c;
		no->next = NULL;
		G->v[index] = no;
	}
	return G->v[index];
}

void addM(Grafo G, char a, char b){
	link A = addN(G, a);
	link B = addN(G, b);

	link la = malloc(sizeof(struct node));
	la->c = a;
	la->next = B->next;
	B->next = la;

	link lb = malloc(sizeof(struct node));
	lb->c = b;
	lb->next = A->next;
	A->next = lb;
}

int bfs(Grafo G, char c, int* visited, char* result){
	char* queue = malloc(G->N * sizeof(char));
	int qs = 0, qt = 0;

	visited[c - 97] = 1;
	queue[qt++] = c;

	if (G->v[c - 97]){
		while(qs < qt){
			char u = queue[qs++];
			int uindex = u - 97;

			link adj = G->v[uindex]->next;
			while(adj){
				int index = adj->c - 97;
				if (!visited[index]){
					visited[index] = 1;
					queue[qt++] = adj->c;
				}
				adj = adj->next;
			}
		}
	}
	memcpy(result, queue, qt);
	return qt;
}

int cmpchar(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

void conexo(Grafo G, int c){
	int* visited = calloc(G->N, sizeof(int));

	int s = 0;
	printf("Case #%d:\n", c+1);
	for (int i = 0; i < G->N; i++){
		if(!visited[i]){
			char* queue = malloc(G->N * sizeof(char));
			int size = bfs(G, i + 97, visited, queue);
			qsort(queue, size, sizeof(char), cmpchar);

            for (int i = 0; i < size; i++){
            	printf("%c,", queue[i]);
            }
            printf("\n");
            s++;
		}
	}

	printf("%d connected components\n\n", s);

}

int main(){
	int c, n, m;

	scanf("%d", &c);
	for (int j = 0; j < c; j++){
		scanf(" %d %d", &n, &m);
		Grafo G = initG(n, m);
		for (int i = 0; i < m; i++){
			char a, b;
			scanf(" %c %c", &a, &b);
			addM(G, a, b);
		}

		conexo(G, j);
	}


	return 0;
}