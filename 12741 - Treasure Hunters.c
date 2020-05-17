#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int key;
	struct _Node* next;
} Node;
typedef struct _List {
	Node* begin;
	Node* last;
} List;
typedef struct _Queue {
	int* items;
	int size;
} Queue;

void insertLast(List*, int);
void BFS(List*, int, int*, int*, int);
void QueuePush(Queue*, int);
void QueuePop(Queue*);

int main() {
	int n, m;
	scanf("%d", &n);
	List* adjList = (List*)calloc(1, n * sizeof(List));

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int vi, vj;
		scanf("%d%d", &vi, &vj);
		vi--; vj--;
		insertLast(&adjList[vj], vi);
	}

	int* hunters = (int*)malloc(n * sizeof(int)), k;
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int h;
		scanf("%d", &h);
		hunters[--h] = 1;
	}

	int treasure;
	scanf("%d", &treasure);
	treasure--;

	int* distance = (int*)calloc(1, n * sizeof(int));
	for (int i = 0; i < n; i++)
		distance[i] = n;
	BFS(adjList, treasure, hunters, distance, n);

	int min = n;
	for (int i = 0; i < n; i++) {
		if (hunters[i] == 1) {
			min = distance[i] < min ? distance[i] : min;
		}
	}

	printf("%d\n", min != 0 ? min : n);

	return 0;
}

void insertLast(List* l, int key) {
	Node* data = (Node*)calloc(1, sizeof(Node));
	data->key = key;
	if (l->begin == NULL && l->last == NULL) {
		l->begin = data;
		l->last = data;
	}
	else {
		l->last->next = data;
		l->last = data;
	}
}

void BFS(List* adjList, int src, int* hunters, int* distance, int size) {
	Queue q = { .items = (int*)malloc(size * sizeof(int)), .size = 0 };
	int* visited = (int*)calloc(1, size * sizeof(int));
	visited[src] = 1;
	distance[src] = 0;
	QueuePush(&q, src);
	while (q.size > 0) {
		int currentNode = q.items[0];
		QueuePop(&q);
		Node* current = adjList[currentNode].begin;
		while (current != NULL) {
			if (visited[current->key] == 0) {
				visited[current->key] = 1;
				distance[current->key] = distance[currentNode] + 1;
				QueuePush(&q, current->key);

				if (hunters[current->key] == 1) {
					return;
				}
			}
			current = current->next;
		}
	}
}
void QueuePush(Queue* q, int value) {
	q->items[q->size++] = value;
}
void QueuePop(Queue* q) {
	for (int i = 0; i < q->size - 1; i++) {
		q->items[i] = q->items[i + 1];
	}
	q->size--;
}
