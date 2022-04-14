#include <stdio.h>
#pragma warning(disable : 4996)
#define MAX_TERMS 100


typedef struct {
	int row;
	int col;
	int value;
}element;

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
}SparseMatrix;

void printMatrix(int a[][5], int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}

void toSparseMatrix(int src[][5], SparseMatrix* dst, int row, int col) {
	dst->rows = row;
	dst->cols = col;
	dst->terms = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (src[i][j] != 0) {
				dst->data[dst->terms].row = i;
				dst->data[dst->terms].col = j;
				dst->data[dst->terms].value = src[i][j];
				dst->terms++;
			}
		}
	}
}
void printSparseMatrix(SparseMatrix A) {
	printf("Rows = %d, cols : %d, nums : %d\n", A.rows, A.cols, A.terms);

	for (int i = 0; i < A.terms; i++) {
		printf("%d %d %d", A.data[i].row, A.data[i].col, A.data[i].value);
		printf("\n");
	}


}


void printOriginalMatrix(SparseMatrix A) {
	int p = 0;
	for (int i = 0; i < A.rows; i++) {
		for (int j = 0; j < A.cols; j++) {
			if ((i == A.data[p].row) &&( j == A.data[p].col)) {
				printf("%d ", A.data[p].value);
				p++;
			}
			else
				printf("0 ");
			
		}
		printf("\n");
	}
}
int main() {

	int Mat[5][5] = {
		{0,0,0,2,0},
		{0,0,5,0,0},
		{4,0,0,0,0},
		{0,0,0,0,0},
		{0,0,0,0,1}
	};

	SparseMatrix A;
	toSparseMatrix(Mat, &A, 5, 5);
	printSparseMatrix(A);
	
	printf("\n\n원래 행렬:\n");
	printMatrix(Mat, 5, 5);
	printf("\n\n");

	printOriginalMatrix(A);
}
