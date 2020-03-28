#include <stdio.h>
#include <stdlib.h>

void mergeSort(int* list, int left, int right);

int main() {
	int n, * a;
	scanf("%d", &n);
	a = malloc(n * sizeof(int));

	for (int i = 0; i < n; i++)
		scanf("%d", a + i);

	mergeSort(a, 0, n - 1);

	for (int i = 0; i < n; i++)
		printf("%d%c", *(a + i), i < n - 1 ? ' ' : '\n');

	return 0;
}

void mergeSort(int* list, int left, int right) {
	if (left < right) {
		int middle = (left + right) / 2;
		mergeSort(list, left, middle);
		mergeSort(list, middle + 1, right);

		int leftIndex = left,
			rightIndex = middle + 1,
			tempSize = right - left + 1,
			* temp = malloc(tempSize * sizeof(int)),
			tempIndex = 0;
		while (leftIndex <= middle && rightIndex <= right)
			if (list[leftIndex] > list[rightIndex])
				temp[tempIndex++] = list[rightIndex++];
			else
				temp[tempIndex++] = list[leftIndex++];
		if (leftIndex > middle)
			while (rightIndex <= right)
				temp[tempIndex++] = list[rightIndex++];
		else
			while (leftIndex <= middle)
				temp[tempIndex++] = list[leftIndex++];
		leftIndex = left;
		for (tempIndex = 0; tempIndex < tempSize; tempIndex++)
			list[leftIndex++] = temp[tempIndex];
	}
}
