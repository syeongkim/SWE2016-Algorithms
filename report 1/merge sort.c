#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
int temp[MAX];
int cnt;

void merge(int list[], int start, int mid, int end) {
	int i = start;
	int j = mid + 1;
	int p = start;

	while (i <= mid && j <= end) {
		if (list[i] <= list[j]) {
			temp[p++] = list[j++];
		}
		else {
			temp[p++] = list[i++];
		}
		cnt++;
	}

	if (i > mid) {
		for (int l = j; l <= end; l++) {
			temp[p++] = list[l];
			cnt++;
		}
	}
	else {
		for (int l = i; l <= mid; l++) {
			temp[p++] = list[l];
			cnt++;
		}
	}

	for (int l = start; l <= end; l++) {
		list[l] = temp[l];
	}
}

void merge_sort(int list[], int start, int end) {
	int mid;

	if (start < end) {
		mid = (start + end) / 2;
		merge_sort(list, start, mid);
		merge_sort(list, mid + 1, end);
		merge(list, start, mid, end);
	}
}

void main() {
	srand((int)time(NULL));

	int A[MAX];
	for (int i = 0; i < MAX; i++) {
		A[i] = rand() % 1000;
		for (int j = 0; j < i; j++) {
			if (A[i] == A[j]) {
				i--;
				break;
			}
		}
	}
	printf("BEFORE SORTING: ");
	for (int i = 0; i < MAX; i++) {
		printf("%d ", A[i]);
	}

	merge_sort(A, 0, MAX - 1);

	printf("\n\nAFTER SORTING: ");
	for (int i = 0; i < MAX; i++) {
		printf("%d ", A[i]);
	}

	printf("\n\nnumber of operations: %d", cnt);

	cnt = 0;
	int B[MAX] = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91,
			90, 89, 88, 55, 86, 85, 84, 83, 62, 81,
			80, 79, 78, 77, 76, 75, 74, 73, 72, 71,
			70, 69, 68, 67, 66, 65, 64, 63, 19, 61,
			60, 59, 58, 57, 56, 87, 54, 53, 52, 51,
			50, 49, 48, 47, 46, 45, 44, 43, 42, 41,
			40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
			30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
			20, 82, 18, 17, 16, 15, 14, 13, 12, 11,
			10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	printf("\n\nBEFORE SORTING: ");
	for (int i = 0; i < MAX; i++) {
		printf("%d ", B[i]);
	}

	merge_sort(B, 0, MAX - 1);

	printf("\n\nAFTER SORTING: ");
	for (int i = 0; i < MAX; i++) {
		printf("%d ", B[i]);
	}

	printf("\n\nnumber of operations: %d", cnt);

	cnt = 0;
	int C[MAX] = {1, 2, 3, 4, 5, 94, 7, 8, 9, 10,
			11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
			21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
			31, 32, 33, 34, 35, 45, 37, 38, 39, 40,
			41, 42, 43, 44, 67, 46, 47, 48, 49, 50,
			51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
			61, 62, 63, 64, 65, 66, 36, 68, 69, 70,
			71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
			81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
			91, 92, 93, 6, 95, 96, 97, 98, 99, 100 };

	printf("\n\nBEFORE SORTING: ");
	for (int i = 0; i < MAX; i++) {
		printf("%d ", C[i]);
	}

	merge_sort(C, 0, MAX - 1);

	printf("\n\nAFTER SORTING: ");
	for (int i = 0; i < MAX; i++) {
		printf("%d ", C[i]);
	}

	printf("\n\nnumber of operations: %d", cnt);
}