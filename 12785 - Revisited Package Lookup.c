#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LEN 33
#define LOOP_LEN 32

unsigned long binaryToNum(char* str);
void mergeSort(unsigned long* list, int left, int right);
int binarySearch(unsigned long* list, int size, unsigned long target);

int main() {
	int n, listLen = 0, k, count = 0;
	unsigned long* list;
	scanf("%d", &n);
	list = (unsigned long*)malloc(n * sizeof(*list));
	for (int i = 0; i < n; i++) {
		char temp[LEN];
		scanf("%s", temp);
		list[listLen++] = binaryToNum(temp);
	}
	mergeSort(list, 0, listLen);
	scanf("%d", &k);
	while (k--) {
		char temp[LEN];
		scanf("%s", temp);
		unsigned long target = binaryToNum(temp);
		count += binarySearch(list, listLen, target);
	}
	printf("%d\n", count);

	return 0;
}
unsigned long binaryToNum(char* str) {
	unsigned long output = 0;
	for (int i = 0; i < LOOP_LEN; i++) {
		output += (str[i] - '0') * pow(2, LOOP_LEN - 1 - i);
	}
	return output;
}void mergeSort(unsigned long* list, int left, int right) {
	if (left < right) {
		int middle = (left + right) / 2;
		mergeSort(list, left, middle);
		mergeSort(list, middle + 1, right);

		int leftIndex = left,
			rightIndex = middle + 1,
			tempSize = right - left + 1,
			tempIndex = 0;
		unsigned long* temp = (unsigned long*)malloc(tempSize * sizeof(*temp));
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
int binarySearch(unsigned long* list, int size, unsigned long target) {
	int left = 0, right = size, stat = 0;
	while (left <= right) {
		int middle = (left + right) / 2;
		if (target == list[middle]) {
			stat = 1;
			break;
		}
		else if (target > list[middle]) {
			left = middle + 1;
		}
		else if (target < list[middle]) {
			right = middle - 1;
		}
	}
	return stat;
}
