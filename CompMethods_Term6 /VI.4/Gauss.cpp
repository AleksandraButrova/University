#include "Gauss.h"
#include <iostream>

using namespace std;

void  BackSubstitution(double **A, double *x) {
	for (int i = N - 1; i >= 0; i--)
	{
		x[i] = A[i][N];
		for (int j = i + 1; j < N; j++)
			x[i] -= A[i][j] * x[j];
	}
}

//2. Метод Гаусса с выбором главного элемента по столбцу
void SwapLine(double **A, int i, int minInd)
{
	for (int j = 0; j < N + 1; j++)
		swap(A[i][j], A[minInd][j]);
}
void ChooseColumn(double **A, int i)
{
	int minInd = i;
	for (int j = i + 1; j < N; j++)
		if (abs(A[i][j]) > abs(A[i][minInd]))
			minInd = j;
	if (i != minInd)
		SwapLine(A, i, minInd);

}
void ForwardEliminationColumn(double **A)
{
	for (int k = 0; k < N; k++)
	{
		ChooseColumn(A, k);

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
void GaussColumn(double **A, double *x)
{
	cout << "\n1. Метод Гаусса с выбором главного элемента по столбцу.\n";
	cout << "\nИсходная матрица:\n";
	coutMatrix(A, N, N + 1);

	cout << "\nМатрица после прямого хода:\n";
	ForwardEliminationColumn(A);
	coutMatrix(A, N, N + 1);

	cout << "\nСтолбец решения:\n";
	BackSubstitution(A, x);
	for (int i = 0; i < N; i++)
		cout << x[i] << endl;
	cout << endl;

	
	//error(A, x);

	
}

void coutMatrix(double **Matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << Matrix[i][j] << "\t";
		cout << endl;
	}
}
void error(double **A, double *x)
{
	double R[N];

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
void MtoA_withI(double **M, double **A, int I)
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			A[i][j] = M[i][j];
		A[i][N] = 0;
	}
	A[I][N] = 1;
}
double ** InverseA(double **A)
{
	double **des = new double * [N];
	for (int i = 0; i < N; i++)
		des[i] = new double[N];
	double *x = new double[N];

	for (int j = 0; j < N; j++)
	{
		MtoA_withI(A, A, j);

		ForwardEliminationColumn(A);
		BackSubstitution(A, x);

		for (int i = 0; i < N; i++)
			des[i][j] = x[i];
	}
	return des;
}