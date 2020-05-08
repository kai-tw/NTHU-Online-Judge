#include <stdio.h>
#include <stdlib.h>

typedef struct __Node {
	int id;
	struct __Node* next;
} Node;
typedef struct __List {
	Node* front;
	Node* last;
} List;
typedef struct __Graph {
	int* V;
	List* E;
} Graph;

void DFS(Graph*, int, int*, int*, int*);
void insertLast(List*, int);

int main() {
	int n, m, E[2], * visited, * finished, size = 1;
	Graph G;
	scanf("%d%d", &n, &m);
	G.E = (List*)calloc(1, n * sizeof(List));
	visited = (int*)calloc(1, n * sizeof(int));
	finished = (int*)calloc(1, n * sizeof(int));
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &E[0], &E[1]);
		insertLast(&G.E[E[0] - 1], E[1]);
		insertLast(&G.E[E[1] - 1], E[0]);
	}

	for (int i = 0; i < n; i++) {
		int temp = 1;
		if (visited[i] != 1) {
			DFS(&G, i + 1, visited, finished, &temp);
		}
		size = temp > size ? temp : size;
	}

	printf("%d\n", size);

	return 0;
}

void DFS(Graph* G, int id, int* visited, int* finished, int* size) {
	visited[id - 1] = 1;
	Node* current = G->E[id - 1].front;
	while (current != NULL) {
		if (visited[current->id - 1] == 1) {
			current = current->next;
			continue;
		}
		DFS(G, current->id, visited, finished, size);
		*size += 1;
		current = current->next;
	}
	finished[id - 1] = 1;
}
void insertLast(List* L, int id) {
	Node* N = (Node*)calloc(1, sizeof(Node));
	N->id = id;
	if (L->front == NULL && L->last == NULL) {
		L->front = N;
		L->last = N;
	}
	else {
		L->last->next = N;
		L->last = N;
	}
}