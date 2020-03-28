#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, * a = NULL, m, q;
	scanf("%d", &n);
	a = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", a + i);
	}

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &q);
		int left = 0, right = n, middle, stat = 0;
		while (left <= right) {
			middle = (left + right) / 2;
			if (q == a[middle]) {
				stat = 1;
				break;
			}
			else if (q > a[middle]) {
				left = middle + 1;
			}
			else if (q < a[middle]) {
				right = middle - 1;
			}
		}
		printf("%s%c", stat ? "yes" : "no", i != m - 1 ? ' ' : '\n');
	}
	free(a);
	a = NULL;
	return 0;
}
