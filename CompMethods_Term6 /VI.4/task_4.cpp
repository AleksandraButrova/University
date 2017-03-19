/*Задание 4.
Решение полной и частичной проблемы собственных значений.
Найти методом Якоби все собственные числа матрицы А
с точностью eps = 1e-5. Найти соответствующие собственные векторы.
Вариант 4.*/
#include <iostream>
#include <cmath>
#include <vector>
#include "Gauss.h"

#define N 3
#define eps		1e-5

using namespace std;

void initMatrix(double ** A)
{
	//A = {	{ -0.907011, -0.277165, 0.445705} , 
	//		{ -0.277165, 0.633725,  0.077739} , 
	//		{  0.445705, 0.077739, -0.955354}  };

	A[0][0] = -0.907011;
	A[0][1] = -0.277165;
	A[0][2] = 0.445705;
	A[1][0] = -0.277165;
	A[1][1] = 0.633725;
	A[1][2] = 0.077739;
	A[2][0] = 0.445705;
	A[2][1] = 0.077739;
	A[2][2] = -0.955354;
}
double **MultMatrix(double **A, double **B)
{
	double **C = new double *[N];
	for (int i = 0; i < N; i++)
		C[i] = new double[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			C[i][j] = 0;
			for (int k = 0; k < N; k++)
				C[i][j] += A[i][k] * B[k][j];
		}

	return C;
}
void FindMaxInUpperTrianMatrix(double **A, int &i_max, int &j_max)
{
	i_max = -1;
	j_max = -1;
	double max = 0;

	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
			if (abs(A[i][j]) > max) {
				max = abs(A[i][j]);
				i_max = i;
				j_max = j;
			}
}
double ** BuidA_next(double **A, double **V, int &i_max, int &j_max)
{
	
	double **A_s = new double*[N];
	for (int i = 0; i < N; i++)
		A_s[i] = new double[N];

	double ii_jj = A[i_max][i_max] - A[j_max][j_max]
		, ij = A[i_max][j_max]
		, d = sqrt(ii_jj*ii_jj + 4 * ij*ij)
		, c = sqrt(0.5 * (1 + abs(ii_jj) / d))
		, s = (ij * (ii_jj)) / (abs(ij * (ii_jj))) * sqrt(0.5 * (1 - abs(ii_jj) / d));
	

	//cout << "\nc s 1\n"<<c << endl << s << endl<<c*c + s*s<<endl;
	for (int m = 0; m < N; m++)
		for (int n = 0; n < N; n++)
			V[m][n] = 0;

	for (int m = 0; m < N; m++)
		for (int n = 0; n < N; n++)
		{
			if ( (m != i_max) && (m != j_max) && (n != i_max) && (n != j_max) ) {
				A_s[m][n] = A[m][n];
			}

			if ((m != i_max) && (m != j_max)) {
				A_s[m][j_max] = -s * A[m][i_max] + c *A[m][j_max];
				A_s[j_max][m] = -s * A[m][i_max] + c *A[m][j_max];
				
				V[m][m] = 1;
			}

			A_s[m][i_max] = c * A[m][i_max] + s * A[m][j_max];
			A_s[i_max][m] = c * A[m][i_max] + s * A[m][j_max];
		}

	A_s[i_max][i_max] = c*c *  A[i_max][i_max] + 2 * c * s * A[i_max][j_max] + s*s * A[j_max][j_max];
	A_s[j_max][j_max] = s*s *  A[i_max][i_max] - 2 * c * s * A[i_max][j_max] + c*c * A[j_max][j_max];
	A_s[i_max][j_max] = 0;
	A_s[j_max][i_max] = 0;

	V[i_max][i_max] = c;
	V[j_max][j_max] = c;
	V[i_max][j_max] = -s;
	V[j_max][i_max] = s;

	return A_s;
}
void coutMatrix(double **Matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << Matrix[i][j] << "\t";
		cout << endl;
	}
}
double Normalization(double *x)
{
	double max = 0;
	for (int i = 0; i < N; i++)
		if (abs(x[i]) > max)
			max = abs(x[i]);
	for (int i = 0; i < N; i++)
			x[i] /= max;
	
	return max;
}
double error(double lamda, double x[3])
{
	// r = Ax - lx
	double **A = new double *[N];
	for (int i = 0; i < N; i++)
		A[i] = new double[N];

	initMatrix(A);

	double err[3];
	for (int i = 0; i < N; i++)
	{
		err[i] = 0;

		for (int j = 0; j < N; j++)
		{
			err[i] += A[i][j] * x[j];
		}
		err[i] -= lamda*x[i];
	}
	
	double max = 0;
	for (int i = 0; i < N; i++)
	{
		if (max < abs(err[i]))
			max = err[i];
	}

	return max;
}

int main()
{
	cout.precision(12);
	cout << fixed;
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Задание 4.\nРешение полной и частичной проблемы собственных значений. Метод Якоби.\nВариант 4.";
	cout << "\n________________________________________________________________________________\n";
	
	// 1. Подготовительный шаг. 
	double **A = new double* [N]
		 , **U = new double* [N]
		 , **V = new double* [N];

	for (int i = 0; i < N; i++)
	{
		A[i] = new double[N];
		U[i] = new double[N];
		V[i] = new double[N];

		for (int j = 0; j < N; j++)
			U[i][j] = 0;
		U[i][i] = 1;
	}

	cout <<"Параметр eps = "<< eps << endl;
	cout << "\nИсходная матрица:\n\n";
	initMatrix(A);
	coutMatrix(A, N, N);

	cout << "\n________________________________________________________________________________\n";
	
	U = MultMatrix(U, A);

	// Строим А_(s+1) для s = 0, 1,...
	int n = 1;
	while (1)
	{
		n++;

		// 2. Ищем максимум по модулю среду элементов верхнего треугольника матрицы.
		int i_max = -1,
			j_max = -1;

		FindMaxInUpperTrianMatrix(A, i_max, j_max);

		// 3. Проверка
		if (abs(A[i_max][j_max]) < eps)
			break;
		else {
			// 4. Строим А_(s+1) по формулам
			A = BuidA_next(A, V, i_max, j_max);
			U = MultMatrix(U, V);
		}
		// 5. Идём на шаг 2
	}
	
	cout << "\nА:\n\n";
	coutMatrix(A, N, N);
	
	cout << "\nU:\n\n";
	coutMatrix(U, N, N);

	cout << "\n________________________________________________________________________________\n";
	
	// Занесем собственные числа и векторы в нормальные структуры
	double x1[3], x2[3], x3[3]
		, lamda1 = A[0][0]
		, lamda2 = A[1][1]
		, lamda3 = A[2][2];
	for (int i = 0; i < N; i++)
	{
		x1[i] = U[i][0];
		x2[i] = U[i][1];
		x3[i] = U[i][2];
	}

	// Нормируем
	Normalization(x1);
	Normalization(x2);
	Normalization(x3);
		
	cout << "\nКоличество итераций: " << n << endl;
	cout << "\n--------------------------------------------------------------------------------\n";

	cout<<"\nСобственное значение:\t"<<lamda1<<endl;
	cout << "\n\nCобственный вектор:\n\t\t\t";
	for (int i = 0; i < N; i++)
		cout << x1[i] << "\n\t\t\t";
	cout<<"\nНевязка:\t\t"<< error(lamda1, x1);
	cout << "\n--------------------------------------------------------------------------------\n";

	cout<<"Собственное значение: "<< lamda2;
	cout << "\n\nCобственный вектор:\n\t\t\t";
	for (int i = 0; i < N; i++)
		cout << x2[i] << "\n\t\t\t";
	cout<<"\nНевязка:\t\t"<<error(lamda2, x2);
	cout << "\n--------------------------------------------------------------------------------\n";

	cout<<"Собственное значение: \t"<< lamda3;
	cout << "\n\nCобственный вектор:\n\t\t\t";
	for (int i = 0; i < N; i++)
		cout << x3[i] << "\n\t\t\t";

	cout<<"\nНевязка:\t\t"<<error(lamda3, x3);

	cout << "\n________________________________________________________________________________\n";

	return 0;
}