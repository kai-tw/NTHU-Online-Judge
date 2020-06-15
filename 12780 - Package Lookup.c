#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_LENGTH 20

typedef struct list {
	char** content;
	int size;
} List;

int binarySearch(List* data, char* target);

int main() {
	int n;
	unsigned long long count = 0;
	scanf("%d", &n);

	List packages;
	packages.content = (char**)malloc(n * sizeof(char*));
	packages.size = 0;
	for (int i = 0; i < n; i++) {
		packages.content[packages.size] = (char*)malloc(DATE_LENGTH * sizeof(char));
		scanf("%s", packages.content[packages.size++]);
	}
	int m;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		char date[DATE_LENGTH];
		scanf("%s", date);
		int result = binarySearch(&packages, date);
		if (result != -1) {
			count++;
		}
	}

	printf("%llu\n", count);

	return 0;
}
int binarySearch(List* data, char* target) {
	int left = 0;
	int right = data->size - 1;
	while (left <= right) {
		int middle = (left + right) / 2;
		if (strcmp(data->content[middle], target) == 0) {
			return middle;
		}
		else if (strcmp(target, data->content[middle]) > 0) {
			left = middle + 1;
			right = right;
		}
		else {
			left = left;
			right = middle - 1;
		}
	}
	return -1;
}
