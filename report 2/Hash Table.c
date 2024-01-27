#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50

typedef struct Node {
	int id;
	struct Node* next;
} Node;

typedef struct hashTable {
	int hashsize;
	Node** table;
} hashTable;

int hashfunction(int k, int m) {
	return k % m;
}

void addHash(hashTable* hashtable, int key, Node* node) {
	int hashkey = hashfunction(key, hashtable->hashsize);
	if (hashtable->table[hashkey] == NULL) {
		hashtable->table[hashkey] = node;
	}
	else {
		Node* temp = hashtable->table[hashkey];
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = node;
	}
}

void printHash(hashTable* hashtable) {
	printf("Print Hash Table%d\n", hashtable->hashsize);
	int max = 0;
	double cnt = 0;
	for (int i = 0; i < hashtable->hashsize; i++) {
		printf("[%d] ", i);
		if (hashtable->table[i] != NULL) {
			int len = 0;
			Node* node = hashtable->table[i];
			while (node) {
				printf("-> %3d ", node->id);
				len++;
				cnt++;
				node = node->next;
			}
			if (max < len) {
				max = len;
			}
		}
		printf("\n");
	}
	printf("The longest length of the chains: %d\n", max);
	printf("The average length of the chains: %f\n", cnt / hashtable->hashsize);
}

int main() {

	srand((int)time(NULL));

	int A[MAX];
	for (int i = 0; i < MAX; i++) {
		A[i] = rand() % 500;
		for (int j = 0; j < i; j++) {
			if (A[i] == A[j]) {
				i--;
				break;
			}
		}
	}

	hashTable ht7;
	ht7.hashsize = 7;
	ht7.table = (Node**)malloc(ht7.hashsize * sizeof(Node*));

	for (int i = 0; i < ht7.hashsize; i++) {
		ht7.table[i] = NULL;
	}

	for (int i = 0; i < MAX; i++) {
		Node* node = (Node*)malloc(sizeof(Node));
		node->id = A[i];
		node->next = NULL;
		addHash(&ht7, node->id, node);
	}

	printHash(&ht7);

	for (int i = 0; i < ht7.hashsize; i++) {
		Node* current = ht7.table[i];
		while (current) {
			Node* temp = current;
			current = current->next;
			free(temp);
		}
	}
	free(ht7.table);

	hashTable ht11;
	ht11.hashsize = 11;
	ht11.table = (Node**)malloc(ht11.hashsize * sizeof(Node*));

	for (int i = 0; i < ht11.hashsize; i++) {
		ht11.table[i] = NULL;
	}

	for (int i = 0; i < MAX; i++) {
		Node* node = (Node*)malloc(sizeof(Node));
		node->id = A[i];
		node->next = NULL;
		addHash(&ht11, node->id, node);
	}

	printHash(&ht11);

	for (int i = 0; i < ht11.hashsize; i++) {
		Node* current = ht11.table[i];
		while (current) {
			Node* temp = current;
			current = current->next;
			free(temp);
		}
	}
	free(ht11.table);

	hashTable ht17;
	ht17.hashsize = 17;
	ht17.table = (Node**)malloc(ht17.hashsize * sizeof(Node*));

	for (int i = 0; i < ht17.hashsize; i++) {
		ht17.table[i] = NULL;
	}

	for (int i = 0; i < MAX; i++) {
		Node* node = (Node*)malloc(sizeof(Node));
		node->id = A[i];
		node->next = NULL;
		addHash(&ht17, node->id, node);
	}

	printHash(&ht17);

	for (int i = 0; i < ht17.hashsize; i++) {
		Node* current = ht17.table[i];
		while (current) {
			Node* temp = current;
			current = current->next;
			free(temp);
		}
	}
	free(ht17.table);

	return 0;
}