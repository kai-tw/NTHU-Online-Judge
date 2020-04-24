#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void mergeSort(int* list, int left, int right, unsigned long long* count);

int main() {
	int n, * a;
	unsigned long long count = 0;
	scanf("%d", &n);
	a = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
		scanf("%d", a + i);

	mergeSort(a, 0, n, &count);

	printf("%lld\n", count);
	return 0;
}

void mergeSort(int* list, int left, int right, unsigned long long* count) {
	if (left + 1 < right) {
		int middle = (left + right) / 2;
		mergeSort(list, left, middle, count);
		mergeSort(list, middle, right, count);

		int nL = middle - left,
			nR = right - middle,
			* l = (int*)malloc((nL + 1) * sizeof(int)),
			* r = (int*)malloc((nR + 1) * sizeof(int));
		for (int i = 0; i < nL; i++)
			l[i] = list[left + i];
		for (int i = 0; i < nR; i++)
			r[i] = list[middle + i];
		l[nL] = INT_MAX, r[nR] = INT_MAX;
		int i = 0, j = 0;
		for (int k = left; k < right; k++)
			if (l[i] > r[j])
				list[k] = r[j++];
			else
				list[k] = l[i++], *count += nR - j;
		free(l);
		free(r);
	}
}
