#include <stdio.h>
#include <stdlib.h>

typedef struct _GNode {
	int key;
	int* linked;
	size_t linkedCount;
} GNode;
typedef struct _Graph {
	GNode** nodes;
	size_t nodesSize;
} Graph;

Graph* createGraph();
GNode* createGNode();
void deleteGraph(Graph*);
void deleteGNode(GNode*);

int main() {
	int n, m, first, second;
	Graph* G = createGraph();
	scanf("%d%d", &n, &m);
	G->nodes = (GNode**)calloc(1, n * sizeof(GNode*));
	G->nodesSize = (size_t)n;
	for (size_t i = 0; i < G->nodesSize; i++) {
		G->nodes[i] = (GNode*)calloc(1, sizeof(GNode));
		G->nodes[i]->key = i + 1;
		G->nodes[i]->linked = (int*)calloc(1, n * sizeof(int));
		G->nodes[i]->linkedCount = (size_t)n;
	}
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &first, &second);
		if (first < second) {
			G->nodes[first - 1]->linked[second - 1] = 1;
		}
		else {
			G->nodes[second - 1]->linked[first - 1] = 1;
		}
	}
	for (size_t i = 0; i < G->nodesSize; i++) {
		for (size_t j = i; j < G->nodes[i]->linkedCount; j++) {
			if (G->nodes[i]->linked[j] == 1) {
				printf("%d %d\n", i + 1, j + 1);
			}
		}
	}

	deleteGraph(G);

	return 0;
}

Graph* createGraph() {
	Graph* G = (Graph*)calloc(1, sizeof(Graph));
	return G;
}
GNode* createGNode() {
	GNode* N = (GNode*)calloc(1, sizeof(GNode));
	return N;
}
void deleteGraph(Graph* G) {
	for (size_t i = 0; i < G->nodesSize; i++) {
		deleteGNode(G->nodes[i]);
		G->nodes[i] = NULL;
	}
	G->nodes = NULL;
	free(G);
}
void deleteGNode(GNode* N) {
	free(N->linked);
	N->linked = NULL;
	free(N);
}
