#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct _Node {
	int key;
	int length;
	struct _Node* next;
} Node;
typedef struct _List {
	Node* begin;
	Node* last;
} List;

void listInsertLast(List*, int, int);
void BFS(List*, int, int*, int*, int*);

int main() {
	int n, root, * distance, * visited, *leaf;
	List* V;
	scanf("%d", &n);
	V = (List*)calloc(1, n * sizeof(List));
	for (int i = 0; i < n - 1; i++) {
		int vi = 0, vj = 0, l = 0;
		scanf("%d%d%d", &vi, &vj, &l);
		vi--; vj--;
		listInsertLast(&V[vi], vj, l);
		listInsertLast(&V[vj], vi, l);
		if (vj == 0 && l == 0) {
			break;
		}
	}
	scanf("%d", &root);
	root--;

	visited = (int*)calloc(1, n * sizeof(int));
	distance = (int*)calloc(1, n * sizeof(int));
	leaf = (int*)calloc(1, n * sizeof(int));
	BFS(V, root, distance, visited, leaf);

	int minLen = INT_MAX;

	for (int i = 0; i < n; i++) {
		if (leaf[i] == 1) {
			minLen = minLen > distance[i] && distance[i] != 0 ? distance[i] : minLen;
		}
	}

	printf("%d\n", minLen);

	free(V);
	free(visited);
	free(distance);
	free(leaf);

	return 0;
}
void listInsertLast(List* list, int key, int length) {
	Node* data = (Node*)calloc(1, sizeof(Node));
	data->key = key;
	data->length = length;
	if (list->begin == NULL && list->last == NULL) {
		list->begin = data;
		list->last = data;
	}
	else {
		list->last->next = data;
		list->last = data;
	}
}
void BFS(List* list, int root, int* distance, int* visited, int* leaf) {
	if (visited[root] == 0) {
		Node* current = list[root].begin;
		while (current != NULL) {
			if (visited[current->key] == 0) {
				distance[current->key] = distance[root] + current->length;
			}
			current = current->next;
		}
		visited[root] = 1;
		int last = 0;
		current = list[root].begin;
		while (current != NULL) {
			BFS(list, current->key, distance, visited, leaf);
			current = current->next;
		}
		if (list[root].begin == list[root].last) {
			leaf[root] = 1;
		}
	}
}
