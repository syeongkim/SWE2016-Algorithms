#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10


typedef struct Node {
	struct Node* parent;
	struct Node* left;
	struct Node* right;
	int data;
	char color;
} Node;

typedef struct RBTree {
	struct Node* root;
	struct Node* NIL;
} RBTree;

Node* createNode(int data) {
	Node* n = malloc(sizeof(Node));

	n->parent = NULL;
	n->left = NULL;
	n->right = NULL;
	n->data = data;
	n->color = 'R';

	return n;
}

RBTree* createRBTree() {
	RBTree* rbtree = malloc(sizeof(RBTree));
	Node* nilnode = malloc(sizeof(Node));

	nilnode->parent = NULL;
	nilnode->left = NULL;
	nilnode->right = NULL;
	nilnode->data = -1;
	nilnode->color = 'B';
	rbtree->NIL = nilnode;
	rbtree->root = rbtree->NIL;

	return rbtree;
}

void leftRotation(RBTree* t, Node* x) {
	Node* y = x->right;
	x->right = y->left;
	if (y->left != t->NIL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == t->NIL) {
		t->root = y;
	}
	else if (x == x->parent->left) {
		x->parent->left = y;
	}
	else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void rightRotation(RBTree* t, Node* y) {
	Node* x = y->left;
	y->left = x->right;
	if (x->right != t->NIL) {
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (y->parent == t->NIL) {
		t->root = x;
	}
	else if (y == y->parent->right) {
		y->parent->right = x;
	}
	else {
		y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
}

Node* Minimum(RBTree* t, Node* x) {
	while (x->left != t->NIL) {
		x = x->left;
	}
	return x;
}

Node* Successor(RBTree* t, Node* x) {
	if (x->right != t->NIL) {
		return Minimum(t, x->right);
	}
	else {
		Node* y = x->parent;
		while ((y != t->NIL) && (x == y->right)) {
			x = y;
			y = y->parent;
		}
		return y;
	}
}

double insertleftrotation = 0;
double insertrightrotation = 0;
double insertleftrotationsum = 0;
double insertrightrotationsum = 0;
double deleteleftrotation = 0;
double deleterightrotation = 0;
double deleteleftrotationsum = 0;
double deleterightrotationsum = 0;
double insert = 0;
double delete = 0;
void RBInsertFixup(RBTree* t, Node* z) {
	while (z->parent->color == 'R') {
		if (z->parent == z->parent->parent->left) {
			Node* y = z->parent->parent->right;
			if (y->color == 'R') {
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->right) {
					z = z->parent;
					leftRotation(t, z);
					insertleftrotation++;
				}
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				rightRotation(t, z->parent->parent);
				insertrightrotation++;
			}
		}
		else {
			Node* y = z->parent->parent->left;
			if (y->color == 'R') {
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					rightRotation(t, z);
					insertrightrotation++;
				}
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				leftRotation(t, z->parent->parent);
				insertleftrotation++;
			}
		}
	}
	t->root->color = 'B';
	insertleftrotationsum += insertleftrotation;
	insertrightrotationsum += insertrightrotation;
}

void RBTreeInsert(RBTree* t, Node* z) {
	insert++;
	insertleftrotation = 0;
	insertrightrotation = 0;
	Node* y = t->NIL;
	Node* x = t->root;
	while (x != t->NIL) {
		y = x;
		if (z->data < x->data) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}
	z->parent = y;
	if (y == t->NIL) {
		t->root = z;
	}
	else if (z->data < y->data) {
		y->left = z;
	}
	else {
		y->right = z;
	}
	z->left = t->NIL;
	z->right = t->NIL;
	z->color = 'R';
	RBInsertFixup(t, z);
	printf("number of left rotation: %f\n", insertleftrotation);
	printf("number of right rotation: %f\n", insertrightrotation);
}

void RBTreeDeleteFixup(RBTree* t, Node* x) {
	Node* w;
	while ((x != t->root) && (x->color == 'B')) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == 'R') {
				w->color = 'B';
				x->parent->color = 'R';
				leftRotation(t, x->parent);
				deleteleftrotation++;
				w = x->parent->right;
			}

			if ((w->left->color == 'B') && (w->right->color == 'B')) {
				w->color = 'R';
				x = x->parent;
			}
			else {
				if (w->right->color == 'B') {
					w->left->color = 'B';
					w->color = 'R';
					rightRotation(t, w);
					deleterightrotation++;
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->right->color = 'B';
				leftRotation(t, x->parent);
				deleteleftrotation++;
				x = t->root;
			}
		}
		else {
			w = x->parent->left;
			if (w->color == 'R') {
				w->color = 'B';
				x->parent->color = 'R';
				rightRotation(t, x->parent);
				deleterightrotation++;
				w = x->parent->left;
			}
			if ((w->left->color == 'B') && (w->right->color == 'B')) {
				w->color = 'R';
				x = x->parent;
			}
			else {
				if (w->left->color == 'B') {
					w->right->color = 'B';
					w->color = 'R';
					leftRotation(t, w);
					deleteleftrotation++;
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->left->color = 'B';
				rightRotation(t, x->parent);
				deleterightrotation++;
				x = t->root;
			}
		}
	}
	x->color = 'B';
	deleteleftrotationsum += deleteleftrotation;
	deleterightrotationsum += deleterightrotation;
}

void RBTreeChange(RBTree* t, Node* u, Node* v) {
	if (u->parent == t->NIL) {
		t->root = v;
	}
	else if (u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void RBTreeDelete(RBTree* t, int key) {
	delete++;
	deleteleftrotation = 0;
	deleterightrotation = 0;
	Node* target = t->root;
	Node* temp = NULL;
	Node* x = NULL;
	char color;

	while (key != target->data) {
		if (target->data > key) {
			target = target->left;
		}
		else {
			target = target->right;
		}
	}
	color = target->color;

	if (target->left == t->NIL) {
		x = target->right;
		RBTreeChange(t, target, target->right);
	}
	else if (target->right == t->NIL) {
		x = target->left;
		RBTreeChange(t, target, target->left);
	}
	else {
		temp = target->right;
		while (temp->left != t->NIL) {
			temp = temp->left;
		}
		color = temp->color;
		x = temp->right;
		RBTreeChange(t, temp, temp->right);
		temp->right = target->right;
		temp->right->parent = temp;
		RBTreeChange(t, target, temp);
		temp->left = target->left;
		temp->left->parent = temp;
		temp->color = target->color;
	}
	if (color == 'B') {
		RBTreeDeleteFixup(t, x);
	}
	printf("number of left rotation: %f\n", deleteleftrotation);
	printf("number of right rotation: %f\n", deleterightrotation);
	free(target);
}


void printTree(Node* root, int level) {
	if (root != NULL) {
		printTree(root->right, level + 1);
		for (int i = 0; i < level; i++) {
			printf("   ");
		}
		if (root->data != -1) {
			if (root->color == 'B') {
				printf("%2d \n", root->data);
			}
			else {
				printf("\033[31m%2d \033[0m\n", root->data);
			}
		}
		else {
			printf("   \n");
		}
		printTree(root->left, level + 1);
	}
}

void printBST(Node* root, int level) {
	printTree(root, level);
	if (delete == 0) {
		printf("average number of left rotations per insertion: %f\n", insertleftrotationsum / insert);
		printf("average number of right rotations per insertion: %f\n", insertrightrotationsum / insert);
	}
	if (delete != 0) {
		printf("average number of left rotations per deletion: %f\n", deleteleftrotationsum / delete);
		printf("average number of right rotations per deletion: %f\n", deleterightrotationsum / delete);
	}
}

int findNode(RBTree* t, int value) {
	Node* current = t->root;

	while (current != t->NIL) {
		if (value == current->data) {
			return 1;
		}
		else if (value < current->data) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	return 0;
}

int main() {
	RBTree* tree = createRBTree();

	srand((int)time(NULL));

	int A[MAX];
	for (int i = 0; i < MAX; i++) {
		A[i] = rand() % 50;
		for (int j = 0; j < i; j++) {
			if (A[i] == A[j]) {
				i--;
				break;
			}
		}
	}

	for (int i = 0; i < MAX; i++) {
		printf("%d insert\n", A[i]);
		Node* temp;
		temp = createNode(A[i]);
		RBTreeInsert(tree, temp);
	}

	printBST(tree->root, 0);

	int B[5] = { 17, 22, 2, 38, 16 };
	for (int i = 0; i < 5; i++) {
		if (findNode(tree, B[i]) == 1) {
			printf("%d is already in tree\n", B[i]);
		}
		else {
			printf("%d insert\n", B[i]);
			Node* temp;
			temp = createNode(B[i]);
			RBTreeInsert(tree, temp);
			printBST(tree->root, 0);
		}
	}

	int C[2] = { 17, 38 };
	for (int i = 0; i < 2; i++) {
		printf("%d delelte\n", C[i]);
		RBTreeDelete(tree, C[i]);
		printBST(tree->root, 0);
		printf("root key delete\n");
		RBTreeDelete(tree, tree->root->data);
		printBST(tree->root, 0);
	}

	printf("root key delete\n");
	RBTreeDelete(tree, tree->root->data);
	printBST(tree->root, 0);
	return 0;
}