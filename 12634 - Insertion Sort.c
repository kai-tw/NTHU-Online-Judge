#include <stdio.h>
#include <stdlib.h>

void insertionSort(int* list, int size);

unsigned long long count = 0;

int main() {
	int n, * a;
	scanf("%d", &n);
	a = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);

	insertionSort(a, n);

	printf("%lld\n", count);

	return 0;
}

void insertionSort(int* list, int size) {
	for (int i = 1; i < size; i++) {
		int key = list[i], j = i - 1;
		while (j > -1 && key < list[j]) {
			list[j + 1] = list[j];
			list[j--] = key;
			count++;
		}
	}
}
