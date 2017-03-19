#include "Gauss.h"
#include <iostream>
#include <math.h>

using namespace std;

void  BackSubstitution(double **A, double *x, int N) {
	for (int i = N - 1; i >= 0; i--)
	{
		x[i] = A[i][N];
		for (int j = i + 1; j < N; j++)
			x[i] -= A[i][j] * x[j];
	}
}

//2. Метод Гаусса с выбором главного элемента по столбцу
void SwapLine(double **A, int i, int minInd, int N)
{
	for (int j = 0; j < N + 1; j++)
		swap(A[i][j], A[minInd][j]);
}
void ChooseColumn(double **A, int i, int N)
{
	int minInd = i;
	for (int j = i + 1; j < N; j++)
		if (abs(A[i][j]) > abs(A[i][minInd]))
			minInd = j;
	if (i != minInd)
		SwapLine(A, i, minInd, N);

}
void ForwardEliminationColumn(double **A, int N)
{
	for (int k = 0; k < N; k++)
	{
		ChooseColumn(A, k, N);

		double A_kk = A[k][k];

		if (abs(A_kk) < eps) {
			cout << "Схема единственного деления не работает, так как элемент А[" << k << " ;" << k << "] < " << eps << endl;
		}
		else
			for (int j = k + 1; j < N + 1; j++)
				A[k][j] = A[k][j] / A_kk;

		for (int i = k + 1; i < N; i++)
		{
			double A_ik = A[i][k];
			for (int j = k; j < N + 1; j++)
			{
				A[i][j] = A[i][j] - A[k][j] * A_ik;
			}
		}
	}
}
void GaussColumn(double **A, double *x, int N)
{
	/*cout << "\nМетод Гаусса с выбором главного элемента по столбцу.\n";
	cout << "\nИсходная матрица:\n";
	printMatrix(A, N, N + 1);
	*/
	//cout << "\nМатрица после прямого хода:\n";
	ForwardEliminationColumn(A, N);
	//printMatrix(A, N, N + 1);
	//cout << endl;
	//cout << "\nСтолбец решения:\n";*/
	BackSubstitution(A, x, N);
	/*
	for (int i = 0; i < N; i++)
	cout << x[i] << endl;
	cout << endl;
	*/

	//error(A, x);


}

void printMatrix(double **Matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << Matrix[i][j] << "\t";
		cout << endl;
	}
}
void error(double **A, double *x, int N)
{
	double *R = new double[N];

	for (int i = 0; i < N; i++)
	{
		R[i] = A[i][N];
		//cout << R[i] << endl;
		double sum = 0;
		for (int j = 0; j < N; j++)
			sum += (A[i][j] * x[j]);
		R[i] -= sum;
	}

	cout << "\nНевязка: \n";
	for (int i = 0; i < N; i++)
		cout << abs(R[i]) << endl;
}

//4. Нахождение обратной матрицы методом Гаусса с выбором
void MtoA_withI(double **M, double **A, int I, int N)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			A[i][j] = M[i][j];
		A[i][N] = 0;
	}
	A[I][N] = 1;
}
double ** InverseA(double **A, int N)
{
	double **des = new double *[N];
	for (int i = 0; i < N; i++)
		des[i] = new double[N];
	double *x = new double[N];

	for (int j = 0; j < N; j++)
	{
		MtoA_withI(A, A, j, N);

		ForwardEliminationColumn(A, N);
		BackSubstitution(A, x, N);

		for (int i = 0; i < N; i++)
			des[i][j] = x[i];
	}
	return des;
}




void SwapRaws(double **matrix, int first, int second, int n)
{
	for (int j = 0; j < n; j++)
	{
		double temp = matrix[j][first];
		matrix[j][first] = matrix[j][second];
		matrix[j][second] = temp;
	}
}

double* GaussRow(double** matrix, int n)
{
	int * newPositions = new int[4];
	for (int i = 0; i < 4; i++)
		newPositions[i] = i;

	for (int k = 0; k < n; k++)
	{
		int maxInd = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(matrix[i][k]) > abs(matrix[maxInd][k]))
				maxInd = i;
		}
		if (k != maxInd)
		{
			SwapRaws(matrix, k, maxInd, n);
			int temp = newPositions[k];
			newPositions[k] = newPositions[maxInd];
			newPositions[maxInd] = temp;
		}

		double dioganalElement = matrix[k][k];
		for (int j = k; j < n + 1; j++)
			matrix[k][j] /= dioganalElement;
		for (int i = k + 1; i < n; i++)
		{
			double temp = matrix[i][k];
			for (int j = k + 1; j < n + 1; j++)
				matrix[i][j] -= matrix[k][j] * temp;
		}
	}

	double* x = new double[n];

	for (int i = n - 1; i >= 0; i--)
		x[i] = matrix[i][n];

	for (int i = n - 1; i >= 0; i--)
	{
		double temp = matrix[i][n];
		for (int j = n - 1; j > i; --j)
			temp -= matrix[i][j] * x[j];

		x[newPositions[i]] = temp / matrix[i][i];
	}

	return x;
}