#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
	int key;
	int height;
	struct node* left;
	struct node* right;
} Node;

int Max(int a, int b) { return a > b ? a : b; }
int getHeight(Node* x) { return x == NULL ? 0 : x->height; }
int getBalance(Node* x) { return x == NULL ? 0 : (getHeight(x->left) - getHeight(x->right)); }
int predecessor(Node* root, int target);
int successor(Node* root, int target);

Node* create(int key);
Node* rightRotate(Node* x);
Node* leftRotate(Node* x);
Node* insert(Node* x, int key);

int main() {
	unsigned long long sum = 0;
	int moves;
	scanf("%d", &moves);
	Node* root = NULL;
	while (moves--) {
		int operation, key;
		scanf("%d%d", &operation, &key);
		switch (operation) {
		case 1:
			root = insert(root, key);
			break;
		case 2:
			if (root != NULL) {
				int pred = predecessor(root, key);
				int succ = successor(root, key);
				int target = 0;
				if (pred > 0 && succ < INT_MAX) {
					target = (key - pred) <= (succ - key) ? pred : succ;
				}
				else if (pred == 0) {
					target = succ;
				}
				else if (succ == INT_MAX) {
					target = pred;
				}
				sum += target;
			}
			break;
		}
	}

	printf("%llu\n", sum);
	return 0;
}
Node* rightRotate(Node* x) {
	Node* y = x->left;
	x->left = y->right;
	y->right = x;
	x->height = Max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = Max(getHeight(y->left), getHeight(y->right)) + 1;
	return y;
}
Node* leftRotate(Node* x) {
	Node* y = x->right;
	x->right = y->left;
	y->left = x;
	x->height = Max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = Max(getHeight(y->left), getHeight(y->right)) + 1;
	return y;
}
Node* insert(Node* x, int key) {
	if (x == NULL) {
		return create(key);
	}

	if (key < x->key) {
		x->left = insert(x->left, key);
	}
	else if (key > x->key) {
		x->right = insert(x->right, key);
	}
	else {
		return x;
	}
	x->height = Max(getHeight(x->left), getHeight(x->right)) + 1;
	int bf = getBalance(x);
	if (bf > 1 && key < x->left->key) {
		return rightRotate(x);
	}
	if (bf > 1 && key > x->left->key) {
		x->left = leftRotate(x->left);
		return rightRotate(x);
	}
	if (bf < -1 && key < x->right->key) {
		x->right = rightRotate(x->right);
		return leftRotate(x);
	}
	if (bf < -1 && key > x->right->key) {
		return leftRotate(x);
	}
	return x;
}
Node* create(int key) {
	Node* node = (Node*)calloc(1, sizeof(Node));
	node->key = key;
	node->height = 1;
	return node;
}
int predecessor(Node* root, int target) {
	int pred = 0;
	while (root) {
		if (target < root->key) {
			root = root->left;
		}
		else if (target > root->key) {
			pred = root->key;
			root = root->right;
		}
	}
	return pred;
}
int successor(Node* root, int target) {
	int succ = INT_MAX;
	while (root) {
		if (target < root->key) {
			succ = root->key;
			root = root->left;
		}
		else {
			root = root->right;
		}
	}
	return succ;
}
