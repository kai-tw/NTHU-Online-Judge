#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void infixToPostfix(char*, int);
int calculate(char*, int);
int compare(int x, int y) { return x < y ? x - y : x + y; }
int minimum(int x, int y) { return x < y ? x : y; }
int maximum(int x, int y) { return x > y ? x : y; }

int main() {
	int moves;
	char expr[1001];
	scanf("%d", &moves);

	for (int i = 0; i < moves; i++) {
		scanf("%s", expr);
		infixToPostfix(expr, strlen(expr));
		printf("%d\n",calculate(expr, strlen(expr)));
	}

	return 0;
}

void infixToPostfix(char* str, int size) {
	int outputSize = 0, stackSize = 0;
	char* output, * stack;
	stack = (char*)malloc(size * sizeof(char));
	output = (char*)calloc(1, size * sizeof(char));

	for (int i = 0; i < size; i++) {
		switch (str[i]) {
		case '(':
			stack[stackSize++] = str[i];
			break;
		case ')':
			while (stackSize > 0 && stack[--stackSize] != '(') {
				output[outputSize++] = stack[stackSize];
			}
			break;
		case 'c':
			stack[stackSize++] = str[i];
			break;
		case 'M':
		case 'm':
			if (stackSize > 0) {
				switch (stack[stackSize - 1]) {
				case 'c':
				case 'M':
				case 'm':
					while (stackSize > 0 && (stack[stackSize - 1] == 'c' || stack[stackSize - 1] == 'M' || stack[stackSize - 1] == 'm')) {
						output[outputSize++] = stack[--stackSize];
					}
					stack[stackSize++] = str[i];
					break;
				case '(':
				case '+':
				case '-':
					stack[stackSize++] = str[i];
				}
			}
			else {
				stack[stackSize++] = str[i];
			}
			break;
		case '+':
		case '-':
			if (stackSize > 0) {
				switch (stack[stackSize - 1]) {
				case 'c':
				case 'M':
				case 'm':
				case '+':
				case '-':
					while (stackSize > 0 && stack[stackSize - 1] != '(') {
						output[outputSize++] = stack[--stackSize];
					}
					stack[stackSize++] = str[i];
					break;
				case '(':
					stack[stackSize++] = str[i];
				}
			}
			else {
				stack[stackSize++] = str[i];
			}
			break;
		default:
			output[outputSize++] = str[i];
		}
	}
	while (stackSize > 0) {
		output[outputSize++] = stack[--stackSize];
	}

	strcpy(str, output);

	free(stack);
}

int calculate(char* str, int size) {
	int* stack, stackSize = 0;
	stack = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		switch (str[i]) {
		case 'c':
			stack[stackSize - 2] = compare(stack[stackSize - 2], stack[stackSize - 1]);
			stackSize--;
			break;
		case 'M':
			stack[stackSize - 2] = maximum(stack[stackSize - 2], stack[stackSize - 1]);
			stackSize--;
			break;
		case 'm':
			stack[stackSize - 2] = minimum(stack[stackSize - 2], stack[stackSize - 1]);
			stackSize--;
			break;
		case '+':
			stack[stackSize - 2] = stack[stackSize - 2] + stack[stackSize - 1];
			stackSize--;
			break;
		case '-':
			stack[stackSize - 2] = stack[stackSize - 2] - stack[stackSize - 1];
			stackSize--;
			break;
		default:
			stack[stackSize++] = (int)str[i] - '0';
		}
	}

	int result = stack[0];
	free(stack);
	return result;
}
