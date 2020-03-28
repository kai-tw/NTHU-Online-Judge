#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void buildMaxHeap(int* arr, size_t size);
void heapMaxify(int* arr, int root, size_t size);
void swap(int* a, int* b);

void printHeap(int* arr, size_t size) {
	for (int i = 1; i <= size; i++) {
		printf("%d%c", arr[i], i != size ? ' ' : '\n');
	}
}

int main() {
	unsigned int m, * H, operation, key, show = 0;
	unsigned long long sum = 0;
	size_t hSize = 0;
	
	scanf("%d", &m);

	H = (int*)malloc((m + 100) * sizeof(int));

	for (int i = 0; i < m; i++) {
		scanf("%d", &operation);
		switch (operation) {
		case 1:
			scanf("%d", H + ++hSize);
			buildMaxHeap(H, hSize);
			break;
		case 2:
			if (hSize > 0)
				buildMaxHeap(++H, --hSize);
			break;
		case 3:
			show = 1;
			sum += hSize == 0 ? 0 : H[1];
			break;
		}
	}

	if (show == 1)
		printf("%lld\n", sum);

	return 0;
}

void buildMaxHeap(int* arr, size_t size) {
	for (int i = floor(size / 2); i > 0; i--)
		heapMaxify(arr, i, size);
}
void heapMaxify(int* arr, int root, size_t size) {
	int left = 2 * root;
	int right = 2 * root + 1;
	int largest = root;

	largest = left <= size && arr[left] > arr[largest] ? left : largest;
	largest = right <= size && arr[right] > arr[largest] ? right : largest;

	if (root != largest) {
		swap(arr + root, arr + largest);
		heapMaxify(arr, largest, size);
	}
}
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
