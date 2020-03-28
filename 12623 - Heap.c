#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void buildMinHeap(int* arr, size_t size);
void heapMinify(int* arr, int root, size_t size);
void swap(int* a, int* b);

int main() {
	unsigned int m, * H, operation, key;
	size_t hSize = 0;
	
	scanf("%d", &m);

	H = (int*)malloc((m + 1) * sizeof(int));

	for (int i = 0; i < m; i++) {
		scanf("%d", &operation);
		switch (operation) {
		case 1:
			scanf("%d", H + ++hSize);
			buildMinHeap(H, hSize);
			break;
		case 2:
			if(hSize > 0)
				buildMinHeap(++H, --hSize);
			break;
		case 3:
			printf("%d\n", hSize == 0 ? 0 : H[1]);
			break;
		}
	}

	return 0;
}

void buildMinHeap(int* arr, size_t size) {
	for (int i = floor(size / 2); i > 0 ; i--)
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
