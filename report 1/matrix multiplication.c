#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define N 4

int mul_cnt;
int add_cnt;
int sub_cnt;

int** newmatrix(int n) {
	int** matrix;
	matrix = (int**)malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * n);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

int** fillmatrix(int** matrix) {
	for (int j = 0; j < N; j++) {
		for (int k = 0; k < N; k++) {
			matrix[j][k] = rand() % 1000;
		}
	}
	return matrix;
}

void printmatrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int** mul(int** matrixa, int** matrixb, int n) {
	int** matrix = newmatrix(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				matrix[i][j] += matrixa[i][k] * matrixb[k][j];
				mul_cnt++;
				add_cnt++;
			}
		}
	}
	return matrix;
}

int** add(int** matrixa, int** matrixb, int n) {
	int** matrix = newmatrix(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = matrixa[i][j] + matrixb[i][j];
			add_cnt++;
		}
	}
	return matrix;
}

int** sub(int** matrixa, int** matrixb, int n) {
	int** matrix = newmatrix(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = matrixa[i][j] - matrixb[i][j];
			sub_cnt++;
		}
	}
	return matrix;
}

int** divandcon(int** matrixa, int** matrixb, int** matrixc, int x) {
	if (x == 2) {
		matrixc = mul(matrixa, matrixb, x);
		return matrixc;
	}
	else {
		int** a11 = newmatrix(x / 2);
		int** a12 = newmatrix(x / 2);
		int** a21 = newmatrix(x / 2);
		int** a22 = newmatrix(x / 2);
		int** b11 = newmatrix(x / 2);
		int** b12 = newmatrix(x / 2);
		int** b21 = newmatrix(x / 2);
		int** b22 = newmatrix(x / 2);
		int** p1 = newmatrix(x / 2);
		int** p2 = newmatrix(x / 2);
		int** p3 = newmatrix(x / 2);
		int** p4 = newmatrix(x / 2);
		int** p5 = newmatrix(x / 2);
		int** p6 = newmatrix(x / 2);
		int** p7 = newmatrix(x / 2);
		int** c11 = newmatrix(x);
		int** c12 = newmatrix(x);
		int** c21 = newmatrix(x);
		int** c22 = newmatrix(x);

		int m = 0;
		int n = 0;

		for (int i = 0; i < x; i++) {
			n = 0;
			for (int j = 0; j < x; j++) {
				if (i < x / 2 && j < x / 2) {
					a11[i][j] = matrixa[i][j];
					b11[i][j] = matrixb[i][j];
				}
				else if (i < x / 2 && j >= x / 2) {
					a12[i][n] = matrixa[i][j];
					b12[i][n] = matrixb[i][j];
				}
				else if (i >= x / 2 && j < x / 2) {
					a21[m][j] = matrixa[i][j];
					b21[m][j] = matrixb[i][j];
				}
				else if (i >= x / 2 && j >= x / 2) {
					a22[m][n] = matrixa[i][j];
					b22[m][n] = matrixb[i][j];
				}
				if (j >= x / 2) {
					n++;
				}
			}
			if (i >= x / 2) {
				m++;
			}
		}

		printmatrix(a11, x / 2);
		printmatrix(a12, x / 2);
		printmatrix(a21, x / 2);
		printmatrix(a22, x / 2);
		printmatrix(b11, x / 2);
		printmatrix(b12, x / 2);
		printmatrix(b21, x / 2);
		printmatrix(b22, x / 2);

		p1 = divandcon(a11, sub(b12, b22, x / 2), p1, x / 2);
		p2 = divandcon(add(a11, a12, x / 2), b22, p2, x / 2);
		p3 = divandcon(add(a21, a22, x / 2), b11, p3, x / 2);
		p4 = divandcon(a22, sub(b21, b11, x / 2), p4, x / 2);
		p5 = divandcon(add(a11, a22, x / 2), add(b11, b22, x / 2), p5, x / 2);
		p6 = divandcon(sub(a12, a22, x / 2), add(b21, b22, x / 2), p6, x / 2);
		p7 = divandcon(sub(a11, a21, x / 2), add(b11, b12, x / 2), p7, x / 2);

		c11 = add(sub(add(p5, p4, x / 2), p2, x / 2), p6, x / 2);
		c12 = add(p1, p2, x / 2);
		c21 = add(p3, p4, x / 2);
		c22 = sub(sub(add(p5, p1, x / 2), p3, x / 2), p7, x / 2);

		int a = 0;
		int b = 0;
		for (int i = 0; i < x; i++) {
			b = 0;
			for (int j = 0; j < x; j++) {
				if (i < x / 2 && j < x / 2) {
					matrixc[i][j] = c11[i][j];
				}
				else if (i < x / 2 && j >= x / 2) {
					matrixc[i][j] = c12[i][b];
				}
				else if (i >= x / 2 && j < x / 2) {
					matrixc[i][j] = c21[a][j];
				}
				else if (i >= x / 2 && j >= x / 2) {
					matrixc[i][j] = c22[a][b];
				}
				if (j >= x / 2) {
					b++;
				}
			}
			if (i >= x / 2) {
				a++;
			}
		}
		return matrixc;
	}
}

void main() {
	srand((int)time(NULL));
	printf("***** MATRIX 1 *****\n");
	int** matrixA = newmatrix(N);
	matrixA = fillmatrix(matrixA);
	printmatrix(matrixA, N);
	printf("***** MATRIX 2 *****\n");
	int** matrixB = newmatrix(N);
	matrixB = fillmatrix(matrixB);
	printmatrix(matrixB, N);
	printf("***** AFTER STANDARD MULTIPLICATION *****\n");
	int** matrixmul1 = mul(matrixA, matrixB, N);
	printmatrix(matrixmul1, N);
	printf("number of multiplication operations: %d\n", mul_cnt);
	printf("number of addition operations: %d\n", add_cnt);
	printf("number of subtraction operations: %d\n", sub_cnt);
	mul_cnt = 0;
	add_cnt = 0;
	sub_cnt = 0;
	printf("\n***** AFTER DIVIDE AND CONQUER ALGORITHM *****\n");
	int** matrixC = newmatrix(N);
	divandcon(matrixA, matrixB, matrixC, N);
	printmatrix(matrixC, N);
	printf("number of multiplication operations: %d\n", mul_cnt);
	printf("number of addition operations: %d\n", add_cnt);
	printf("number of subtraction operations: %d\n", sub_cnt);
}