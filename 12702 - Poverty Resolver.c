#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void buildMinHeap(int* arr, size_t size);
void heapMinify(int* arr, int root, size_t size);
void swap(int* a, int* b);

int main() {
	int n, * S, M;
	scanf("%d", &n);
	S = (int*)malloc((n + 1) * sizeof(int));
	for (int i = 1; i <= n; i++) {
		scanf("%d", &S[i]);
	}
	buildMinHeap(S, n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &M);
		S[1] += M;
		heapMinify(S, 1, n);
	}
	printf("%d\n", S[1]);

	free(S);
	return 0;
}
void buildMinHeap(int* arr, size_t size) {
	for (int i = floor(size / 2); i > 0; i--)
		heapMinify(arr, i, size);
}
void heapMinify(int* arr, int root, size_t size) {
	int left = 2 * root;
	int right = 2 * root + 1;
	int smallest = root;

	smallest = left <= size && arr[left] < arr[smallest] ? left : smallest;
	smallest = right <= size && arr[right] < arr[smallest] ? right : smallest;

	if (root != smallest) {
		swap(arr + root, arr + smallest);
		heapMinify(arr, smallest, size);
	}
}
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
