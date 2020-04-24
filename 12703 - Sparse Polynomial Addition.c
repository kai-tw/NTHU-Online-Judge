#include <stdio.h>
#include <stdlib.h>

typedef struct _Polynomial {
	int** data;
	size_t size;
} Polynomial;

Polynomial* polynomialAddition(Polynomial* P1, Polynomial* P2);

int main() {
	Polynomial P1, P2, * result;
	scanf("%zu", &P1.size);
	P1.data = (int**)malloc(P1.size * sizeof(int*));
	for (size_t i = 0; i < P1.size; i++) {
		P1.data[i] = (int*)malloc(2 * sizeof(int));
		scanf("%d%d", &P1.data[i][0], &P1.data[i][1]);
	}
	scanf("%zu", &P2.size);
	P2.data = (int**)malloc(P2.size * sizeof(int*));
	for (size_t i = 0; i < P2.size; i++) {
		P2.data[i] = (int*)malloc(2 * sizeof(int));
		scanf("%d%d", &P2.data[i][0], &P2.data[i][1]);
	}

	result = polynomialAddition(&P1, &P2);

	for (size_t i = 0; i < result->size; i++) {
		printf("%d %d%c", result->data[i][0], result->data[i][1], i != result->size - 1 ? ' ' : '\n');
	}

	free(result);

	return 0;
}

Polynomial* polynomialAddition(Polynomial* P1, Polynomial* P2) {
	Polynomial* result;
	result = (Polynomial*)calloc(1, sizeof(Polynomial));
	result->data = (int**)malloc((P1->size + P2->size + 1) * sizeof(int*));
	size_t i = 0, j = 0;
	while (i < P1->size && j < P2->size) {
		result->data[result->size] = (int*)malloc(2 * sizeof(int));
		if (P1->data[i][1] == P2->data[j][1]) {
			result->data[result->size][0] = P1->data[i][0] + P2->data[j][0];
			result->data[result->size][1] = P1->data[i][1];
			i++, j++;
		}
		else if (P1->data[i][1] < P2->data[j][1]) {
			result->data[result->size][0] = P1->data[i][0];
			result->data[result->size][1] = P1->data[i][1];
			i++;
		}
		else {
			result->data[result->size][0] = P2->data[j][0];
			result->data[result->size][1] = P2->data[j][1];
			j++;
		}
		result->size += 1;
	}
	if (j < P2->size) {
		while (j < P2->size) {
			result->data[result->size] = (int*)malloc(2 * sizeof(int));
			result->data[result->size][0] = P2->data[j][0];
			result->data[result->size][1] = P2->data[j][1];
			result->size += 1;
			j++;
		}
	}
	else {
		while (i < P1->size) {
			result->data[result->size] = (int*)malloc(2 * sizeof(int));
			result->data[result->size][0] = P1->data[i][0];
			result->data[result->size][1] = P1->data[i][1];
			result->size += 1;
			i++;
		}
	}
	return result;
}
