#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int key;
	struct _Node* left;
	struct _Node* right;
} Node;

void construct(Node* node, int* postorder, int* inorder, int size);
void DFS(Node* node, int* preorder, int* pSize);

int main() {
	int n;
	scanf("%d", &n);

	int* postorder = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &postorder[i]);
	}

	int* inorder = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &inorder[i]);
	}

	Node* tree = (Node*)calloc(1, sizeof(Node));

	construct(tree, postorder, inorder, n);

	int* preorder = (int*)malloc(n * sizeof(int)), pSize = 0;

	DFS(tree, preorder, &pSize);

	for (int i = 0; i < pSize; i++) {
		printf("%d%c", preorder[i], i != pSize - 1 ? ' ' : '\n');
	}

	return 0;
}

void construct(Node* node, int* postorder, int* inorder, int size) {
	if (size > 0) {
		int toggle = 0, position;
		int* inLeft = (int*)malloc(size * sizeof(int)), inLSize = 0;
		int* inRight = (int*)malloc(size * sizeof(int)), inRSize = 0;
		node->key = postorder[size - 1];
		for (int i = 0; i < size; i++) {
			if (inorder[i] == node->key) {
				toggle = 1;
				position = i;
				continue;
			}
			if (toggle == 0) {
				inLeft[inLSize++] = inorder[i];
			}
			else {
				inRight[inRSize++] = inorder[i];
			}
		}
		int* poLeft = (int*)malloc(inLSize * sizeof(int));
		int* poRight = (int*)malloc(inRSize * sizeof(int));
		if (inLSize > 0) {
			for (int i = 0; i < position; i++) {
				poLeft[i] = postorder[i];
			}
			node->left = (Node*)calloc(1, sizeof(Node));
			construct(node->left, poLeft, inLeft, inLSize);
		}
		if (inRSize > 0) {
			for (int i = position; i < size - 1; i++) {
				poRight[i - position] = postorder[i];
			}
			node->right = (Node*)calloc(1, sizeof(Node));
			construct(node->right, poRight, inRight, inRSize);
		}
	}
}
void DFS(Node* node, int* preorder, int* pSize) {
	preorder[*pSize] = node->key;
	*pSize += 1;
	if (node->left != NULL) {
		DFS(node->left, preorder, pSize);
	}
	if (node->right != NULL) {
		DFS(node->right, preorder, pSize);
	}
}
