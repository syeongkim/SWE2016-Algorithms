#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 43
#define MAX 30

typedef struct Node {
	int hashkey;
	int value;
	int flag;
} Node;


int linearprobing(int k, int i) {
	int hprime = k % M;
	return (hprime + i) % M;
}

double linearprobe = 0;
void addLinearProbe(Node* hashtable, int value) {
	int j = 0;
	int hashkey = linearprobing(value, j);
	if (hashtable[hashkey].flag == -1) {
		hashtable[hashkey].hashkey = hashkey;
		hashtable[hashkey].value = value;
	}
	else if (hashtable[hashkey].flag == 0) {
		while (hashtable[hashkey].flag != -1) {
			j++;
			hashkey = linearprobing(value, j);
			linearprobe++;
		}
		hashtable[hashkey].hashkey = hashkey;
		hashtable[hashkey].value = value;
	}
	hashtable[hashkey].flag = 0;
	linearprobe++;
}

int quadraticprobing(int k, int i) {
	int hprime = k % M;
	return (hprime + i + 3 * i * i) % M;
}

double quadraticprobe = 0;
void addQuadraticProbe(Node* hashtable, int value) {
	int j = 0;
	int hashkey = quadraticprobing(value, j);
	if (hashtable[hashkey].flag == -1) {
		hashtable[hashkey].hashkey = hashkey;
		hashtable[hashkey].value = value;
	}
	else if (hashtable[hashkey].flag == 0) {
		while (hashtable[hashkey].flag != -1) {
			j++;
			hashkey = quadraticprobing(value, j);
			quadraticprobe++;
		}
		hashtable[hashkey].hashkey = hashkey;
		hashtable[hashkey].value = value;
	}
	hashtable[hashkey].flag = 0;
	quadraticprobe++;
}

int doublehashing(int k, int i) {
	int h1 = k % M;
	int h2 = 1 + (k % (M - 1));
	return (h1 + i * h2) % M;
}

double doubleprobe = 0;
void adddoubleProbe(Node* hashtable, int value) {
	int j = 0;
	int hashkey = doublehashing(value, j);
	if (hashtable[hashkey].flag == -1) {
		hashtable[hashkey].hashkey = hashkey;
		hashtable[hashkey].value = value;
	}
	else if (hashtable[hashkey].flag == 0) {
		while (hashtable[hashkey].flag != -1) {
			j++;
			hashkey = doublehashing(value, j);
			doubleprobe++;
		}
		hashtable[hashkey].hashkey = hashkey;
		hashtable[hashkey].value = value;
	}
	hashtable[hashkey].flag = 0;
	doubleprobe++;
}

void printhashTable(Node* hashtable) {
	int primarycluster = 0;
	int maxprimarycluster = 0;
	for (int i = 0; i < M; i++) {
		if (hashtable[i].value != -1) {
			printf("%d ", hashtable[i].hashkey);
			printf("%d \n", hashtable[i].value);
			primarycluster++;
		}
		else if (hashtable[i].value == -1) {
			printf("%d ", hashtable[i].hashkey);
			printf("empty\n");
			primarycluster = 0;
		}
		if (maxprimarycluster < primarycluster) {
			maxprimarycluster = primarycluster;
		}
	}
	printf("primary cluster length: %d\n", maxprimarycluster);
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

	Node linearht[M];

	for (int i = 0; i < M; i++) {
		linearht[i].hashkey = i;
		linearht[i].value = -1;
		linearht[i].flag = -1;
	}

	for (int i = 0; i < MAX; i++) {
		addLinearProbe(&linearht, A[i]);
	}
	
	printf("Print Hash Table of Linear Probing\n");
	printhashTable(linearht);
	printf("Average number of probes: %.2f\n", linearprobe / MAX);

	Node quadraticht[M];

	for (int i = 0; i < M; i++) {
		quadraticht[i].hashkey = i;
		quadraticht[i].value = -1;
		quadraticht[i].flag = -1;
	}

	for (int i = 0; i < MAX; i++) {
		addQuadraticProbe(&quadraticht, A[i]);
	}

	printf("Print Hash Table of Quadratic Probing\n");
	printhashTable(quadraticht);
	printf("Average number of probes: %.2f\n", quadraticprobe / MAX);

	Node doubleht[M];

	for (int i = 0; i < M; i++) {
		doubleht[i].hashkey = i;
		doubleht[i].value = -1;
		doubleht[i].flag = -1;
	}

	for (int i = 0; i < MAX; i++) {
		adddoubleProbe(&doubleht, A[i]);
	}

	printf("Print Hash Table of Double Hashing\n");
	printhashTable(doubleht);
	printf("Average number of probes: %.2f", doubleprobe / MAX);

	return 0;
}