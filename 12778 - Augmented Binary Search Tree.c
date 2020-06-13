#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	int key;
	struct _Node* parent;
	struct _Node* left;
	struct _Node* right;
} Node;
typedef struct _Tree {
	Node* begin;
} Tree;
typedef struct _List {
	int* content;
	int size;
} List;

void treeInsert(Tree* tree, int key);
void keyToRank(Node* tree, int key, int* count);
void rankToKey(Node* tree, int rank, int* count, int* key);
void DFS(Node* node) {
	if (node != NULL) {
		DFS(node->left);
		printf("%d\t", node->key);
		DFS(node->right);
	}
}

int main() {
	Tree* tree = (Tree*)calloc(1, sizeof(*tree));

	int moves;
	scanf("%d", &moves);
	for (int i = 0; i < moves; i++) {
		int operation, key, rank;
		scanf("%d", &operation);
		switch (operation) {
		case 1:
			scanf("%d", &key);
			treeInsert(tree, key);
			break;
		case 2:
			scanf("%d", &key);
			int count = 0;
			keyToRank(tree->begin, key, &count);
			printf("%d\n", count);
			break;
		case 3:
			scanf("%d", &rank);
			int counting = 0, key = 0;
			rankToKey(tree->begin, rank, &counting, &key);
			printf("%d\n", key);
			break;
		}
	}

	return 0;
}
void treeInsert(Tree* tree, int key) {
	Node* newNode = (Node*)calloc(1, sizeof(*newNode));
	newNode->key = key;
	if (tree->begin == NULL) {
		tree->begin = newNode;
	}
	else {
		Node* current = tree->begin;
		while (1) {
			if (current->key == key) {
				return;
			}
			else if (current->key > key) {
				if (current->left == NULL) {
					current->left = newNode;
					newNode->parent = current->left;
					break;
				}
				current = current->left;
			}
			else {
				if (current->right == NULL) {
					current->right = newNode;
					newNode->parent = current->right;
					break;
				}
				current = current->right;
			}
		}
	}
}
void keyToRank(Node* node, int key, int* count) {
	if (node != NULL) {
		keyToRank(node->left, key, count);
		if (node->key <= key) {
			*count += 1;
		}
		keyToRank(node->right, key, count);
	}
}
void rankToKey(Node* node, int rank, int* count, int* key) {
	if (node != NULL) {
		rankToKey(node->left, rank, count, key);
		*count += 1;
		if (*count <= rank) {
			*key = node->key;
		}
		rankToKey(node->right, rank, count, key);
	}
}
