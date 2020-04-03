#include <stdio.h>
#include <stdlib.h>

int josephus(int n, int k);

int main() {
	int n, k;

	scanf("%d%d", &n, &k);
	printf("%d\n", josephus(n, k));

	return 0;
}

int josephus(int n, int k) {
	int* arr = (int*)malloc((n + 1) * sizeof(int)), index = 1;
	for (int i = 0; i <= n; i++)
		arr[i] = i;
	while (n > 1) {
		index += k - 1;
		while (index > n) {
			index -= n;
		}
		for (int i = index; i < n; i++) {
			arr[i] = arr[i + 1];
		}
		n--;
	}
	return arr[1];
}
