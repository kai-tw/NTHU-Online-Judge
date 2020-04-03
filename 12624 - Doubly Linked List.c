#include <stdio.h>
#include <stdlib.h>

typedef struct _DNode {
	int data;
	struct _DNode* prev;
	struct _DNode* next;
} DNode;
typedef struct _DList {
	int size;
	DNode* front;
	DNode* end;
} DList;

void DListDestroy(DList*);
void DListPush(DList*, int, DNode*);
void DListPop(DList*, int);
void DListPrint(DList*, int);

int main() {
	DList* L = (DList*)calloc(1, sizeof(DList));
	int m;
	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		DNode* temp = (DNode*)calloc(1, sizeof(DNode));
		int operation, pos;
		scanf("%d", &operation);
		switch (operation) {
		case 1:
			scanf("%d", &(temp->data));
			DListPush(L, 0, temp);
			break;
		case 2:
			scanf("%d%d", &pos, &(temp->data));
			DListPush(L, pos, temp);
			break;
		case 3:
			scanf("%d", &(temp->data));
			DListPush(L, L->size, temp);
			break;
		case 4:
			DListPop(L, 0);
			break;
		case 5:
			scanf("%d", &pos);
			DListPop(L, pos);
			break;
		case 6:
			DListPop(L, L->size - 1);
			break;
		case 7:
			DListPrint(L, 0);
			break;
		case 8:
			scanf("%d", &pos);
			DListPrint(L, pos);
			break;
		case 9:
			DListPrint(L, L->size - 1);
			break;
		}
	}

	DListDestroy(L);

	return 0;
}

void DListDestroy(DList* L) {
	DNode* temp;
	while (L->front != NULL) {
		temp = L->front;
		L->front = L->front->next;
		free(temp);
	}
	temp = NULL;
	free(L);
	L = NULL;
}
void DNodeDestroy(DNode* N) {
	free(N);
	N = NULL;
}
void DListPush(DList* L, int pos, DNode* N) {
	if (pos <= L->size) {
		if (L->size == 0) {
			L->front = N;
			L->end = N;
		}
		else if (pos == 0) {
			L->front->prev = N;
			L->front->prev->next = L->front;
			L->front = L->front->prev;
		}
		else if (pos == L->size) {
			L->end->next = N;
			L->end->next->prev = L->end;
			L->end = L->end->next;
		}
		else {
			DNode* current = L->front;
			for (int i = 1; i < pos; i++) {
				current = current->next;
			}
			N->prev = current;
			N->next = current->next;
			current->next->prev = N;
			current->next = N;
		}
		L->size += 1;
	}
}
void DListPop(DList* L, int pos) {
	if (L->size != 0 && pos <= L->size) {
		if (L->size == 1) {
			DNode* temp = L->front;
			L->front = NULL;
			L->end = NULL;
			free(temp);
			temp = NULL;
		}
		else if (pos == 0) {
			DNode* temp = L->front;
			L->front = L->front->next;
			L->front->prev = NULL;
			free(temp);
			temp = NULL;
		}
		else if (pos == L->size - 1) {
			DNode* temp = L->end;
			L->end = L->end->prev;
			L->end->next = NULL;
			free(temp);
			temp = NULL;
		}
		else {
			DNode* current = L->front, * temp;
			for (int i = 1; i < pos; i++) {
				current = current->next;
			}
			temp = current->next;
			current->next->next->prev = current;
			current->next = current->next->next;
			free(temp);
			temp = NULL;
		}
		L->size -= 1;
	}
}
void DListPrint(DList* L, int pos) {
	int output = 0;
	if (pos <= L->size) {
		DNode* current = L->front;
		if (L->size == 0) {
			output = 0;
		}
		else if (pos == 0) {
			output = L->front->data;
		}
		else if (pos == L->size - 1) {
			output = L->end->data;
		}
		else {
			for (int i = 0; i < pos; i++) {
				current = current->next;
			}
			output = current->data;
		}
	}
	printf("%d\n", output);
}
