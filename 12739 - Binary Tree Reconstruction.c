#include <stdio.h>
#include <stdlib.h>

typedef struct __Node {
	int key;
	struct __Node* left;
	struct __Node* right;
} Node;

void construct(Node*, int*, int*, int);
void DFS(Node*, int*, int*);

int main() {
	int n, * preorder = 0, * inorder = 0, * postorder = 0, pSize = 0;
	Node* tree = (Node*)calloc(1, sizeof(Node));
	scanf("%d", &n);

	preorder = (int*)malloc(n * sizeof(int));
	inorder = (int*)malloc(n * sizeof(int));
	postorder = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		scanf("%d", &preorder[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &inorder[i]);
	}

	construct(tree, preorder, inorder, n);
	DFS(tree, postorder, &pSize);

	for (int i = 0; i < n; i++) {
		printf("%d%c", postorder[i], i != n - 1 ? ' ' : '\n');
	}

	return 0;
}
void construct(Node* node, int* preorder, int* inorder, int size) {
	if (size > 0) {
		int toggle = 0, index;
		int* il = (int*)malloc(size * sizeof(int)), * ir = (int*)malloc(size * sizeof(int)), lSize = 0, rSize = 0;
		node->key = preorder[0];
		for (int i = 0; i < size; i++) {
			if (inorder[i] == node->key) {
				index = i;
				toggle = 1;
				continue;
			}
			if (toggle == 0) {
				il[lSize++] = inorder[i];
			}
			else {
				ir[rSize++] = inorder[i];
			}
		}
		int* pl = (int*)malloc(lSize * sizeof(int)), * pr = (int*)malloc(rSize * sizeof(int));
		if (lSize > 0) {
			for (int i = 1; i <= index; i++) {
				pl[i - 1] = preorder[i];
			}
			node->left = (Node*)calloc(1, sizeof(Node));
			construct(node->left, pl, il, lSize);
		}
		if (rSize > 0) {
			for (int i = index + 1; i < size; i++) {
				pr[i - index - 1] = preorder[i];
			}
			node->right = (Node*)calloc(1, sizeof(Node));
			construct(node->right, pr, ir, rSize);
		}
	}
}
void DFS(Node* node, int* postorder, int* pSize) {
	if (node->left != NULL) {
		DFS(node->left, postorder, pSize);
	}
	if (node->right != NULL) {
		DFS(node->right, postorder, pSize);
	}
	postorder[*pSize] = node->key;
	*pSize += 1;
}
