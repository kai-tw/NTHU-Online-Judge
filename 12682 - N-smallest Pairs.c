#include <stdio.h>
#include <stdlib.h>

void heapSort(unsigned int* arr, size_t size);
void buildMaxHeap(unsigned int* arr, size_t size);
void heapMaxify(unsigned int* arr, unsigned int root, size_t size);
void swap(unsigned int* a, unsigned int* b);

void printHeap(unsigned int* arr, size_t size) {
	for (unsigned int i = 1; i <= size; i++) {
		printf("%d%c", arr[i], i != size ? ' ' : '\n');
	}
}

int main() {
	unsigned int n, * A, * B, * W;

	scanf("%d", &n);
	A = (unsigned int*)malloc((n + 1) * sizeof(int));
	B = (unsigned int*)malloc((n + 1) * sizeof(int));
	W = (unsigned int*)malloc((n + 1) * sizeof(int));

	for (unsigned int i = 1; i <= n; i++)
		scanf("%d", &A[i]);
	for (unsigned int i = 1; i <= n; i++)
		scanf("%d", &B[i]);

	heapSort(A, n);
	heapSort(B, n);

	for (unsigned int i = n; i > 0; i--) {
		W[n - i + 1] = A[1] + B[i];
	}

	for (unsigned int i = 2; i <= n; i++) {
		if (A[i] < W[1]) {
			for (unsigned int j = 1; j <= n; j++) {
				if (A[i] + B[j] < W[1]) {
					W[1] = A[i] + B[j];
					heapMaxify(W, 1, n);
				}
				else {
					break;
				}
			}
		}
		else {
			break;
		}
	}

	heapSort(W, n);
	printHeap(W, n);

	return 0;
}

void heapSort(unsigned int* arr, size_t size) {
	buildMaxHeap(arr, size);
	for (unsigned int i = size; i > 1; i--) {
		swap(arr + 1, arr + i);
		heapMaxify(arr, 1, i - 1);
	}
}
void buildMaxHeap(unsigned int* arr, size_t size) {
	for (unsigned int i = size / 2; i > 0; i--)
		heapMaxify(arr, i, size);
}
void heapMaxify(unsigned int* arr, unsigned int root, size_t size) {
	unsigned int left = 2 * root;
	unsigned int right = 2 * root + 1;
	unsigned int largest = root;

	largest = left <= size && arr[left] > arr[largest] ? left : largest;
	largest = right <= size && arr[right] > arr[largest] ? right : largest;

	if (root != largest) {
		swap(arr + root, arr + largest);
		heapMaxify(arr, largest, size);
	}
}
void swap(unsigned int* a, unsigned int* b) {
	unsigned int temp = *a;
	*a = *b;
	*b = temp;
}
