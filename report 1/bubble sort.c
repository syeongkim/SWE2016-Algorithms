#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 100
#define DIVIDE 1000

void bubble_sort(int list[], int n) {
	int temp;
	int cnt = 0;

	printf("BEFORE SORTING: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (list[j] > list[j + 1]) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
				cnt = cnt + 1;
			}
		}
	}
	printf("\nAFTER SORTING: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}

	printf("\n numbers of operation: %d\n\n", cnt);
}

void main() {
	
	// int A[100] filled with rand() % 1000
	srand(time(NULL));

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

	bubble_sort(A, MAX);
	
	// int B[100] almost already sorted
	int B[MAX] = {1, 2, 3, 4, 5, 94, 7, 8, 9, 10,
			11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
			21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
			31, 32, 33, 34, 35, 45, 37, 38, 39, 40,
			41, 42, 43, 44, 67, 46, 47, 48, 49, 50,
			51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
			61, 62, 63, 64, 65, 66, 36, 68, 69, 70,
			71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
			81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
			91, 92, 93, 6, 95, 96, 97, 98, 99, 100 };

	bubble_sort(B, MAX);

	//int C[100] almost reversely sorted
	int C[MAX] = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91,
			90, 89, 88, 55, 86, 85, 84, 83, 62, 81,
			80, 79, 78, 77, 76, 75, 74, 73, 72, 71,
			70, 69, 68, 67, 66, 65, 64, 63, 19, 61,
			60, 59, 58, 57, 56, 87, 54, 53, 52, 51,
			50, 49, 48, 47, 46, 45, 44, 43, 42, 41,
			40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
			30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
			20, 82, 18, 17, 16, 15, 14, 13, 12, 11,
			10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	bubble_sort(C, MAX);
}