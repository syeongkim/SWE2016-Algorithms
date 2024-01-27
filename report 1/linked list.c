#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define MAX 50
#define ITERATION 5

typedef struct node {
	int data;
	struct node *next;
} node;

int getsize(node* head) {
	int cnt = 0;
	for (node* p = head; p != NULL; p = p->next) {
		cnt++;
	}
	return cnt;
}

void print(node* head) {
	int sizeoflist = getsize(head);
	int mid = sizeoflist / 2;
	node* p = head;

	for (int i = 0; i < mid; i++) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	for (int i = mid; i < sizeoflist; i++) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

node* findmax(node* head) {
	node* maxnode;
	maxnode = head;
	for (node* p = head; p != NULL; p = p->next) {
		if (maxnode->data < p->data) {
			maxnode = p;
		}
	}
	return maxnode;
}

node* findbeforenode(node* head, int x) {
	node* p = (node*)malloc(sizeof(node));
	node* beforenode = (node*)malloc(sizeof(node));
	p = head;
	while (p->data != x) {
		beforenode = p;
		p = p->next; 
	}
	return beforenode;
}

node* insert(node* head, int x) {
	int sizeoflist = getsize(head);
	if (sizeoflist == 0) {
		node* p = (node*)malloc(sizeof(node));
		p->data = x;
		p->next = head;
		head = p;
	}
	else {
		node* k = (node*)malloc(sizeof(node));
		node* maxnode = findmax(head);
		k->data = x;
		k->next = maxnode->next;
		maxnode->next = k;
	}
	return head;
}

node* delete(node* head) {
	node* deletenode;
	node* max = findmax(head);
	node* beforenode = findbeforenode(head, max->data);
	deletenode = beforenode->next;
	beforenode->next = deletenode->next;
	free(deletenode);
	return head;
}

int main() {
	node *head = NULL;
	int temp[50];

	srand((int)time(NULL));

	for (int i = 0; i < MAX; i++) {
		int data = rand() % 1000;
		temp[i] = data;
		for (int j = 0; j < i; j++) {
			if (temp[j] == data) {
				data = rand() % 100;
				j = 0;
			}
		}
		temp[i] = data;
		head = insert(head, data);
	}

	printf("*****AFTER INSERT 50 INTEGERS*****\n");
	print(head);
	printf("\n*****START DELETE*****\n");

	for (int i = 0; i < ITERATION; i++) {
		delete(head);
		printf("- DELETE %d -\n", i+1);
		print(head);
	}
	return 0;
}