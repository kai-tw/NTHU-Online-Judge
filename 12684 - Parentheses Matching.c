#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1100

short parenthesesMatching(char*);

int main() {
	int n;
	char **T;
	scanf("%d", &n); getchar();

	T = (char**)malloc(n * sizeof(char*));

	for (int i = 0; i < n; i++) {
		T[i] = (char*)malloc(SIZE * sizeof(char));
		fgets(T[i], SIZE, stdin);
	}

	for (int i = 0; i < n; i++) {
		printf("%s%c", parenthesesMatching(T[i]) ? "yes" : "no", i != n - 1 ? ' ' : '\n');
	}
	return 0;
}

short parenthesesMatching(char* arr) {
	int err = 0, len = -1;
	char stack[SIZE];
	for (int i = 0; arr[i] != '\n'; i++) {
		if (arr[i] == '(' || arr[i] == '[' || arr[i] == '{' || arr[i] == '<') {
			len++;
			stack[len] = arr[i];
			stack[len + 1] = '\0';
		}
		else if ((arr[i] == ')' && stack[len] == '(') || (arr[i] == ']' && stack[len] == '[') || (arr[i] == '}' && stack[len] == '{') || (arr[i] == '>' && stack[len] == '<')) {
			stack[len] = '\0';
			len--;
		}
		else err = 1;
	}
	return err || len > -1 ? 0 : 1;
}
