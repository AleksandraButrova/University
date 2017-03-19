/*Задание 3.
Решение алгебраических уравнений итерационными методами.
Вариант 8.*/

#include <iostream>
#include <cmath>
#include <vector>
#include "Gauss.h"

#define N 3
double epsilon = 0.001;

using namespace std;

// 2.
double FindMin(double **matrix)
{
	double min = INT_MAX;
	for (int i = 0; i < N; i++)
	{
		double currentValue = matrix[i][i];

		for (int j = 0; j < N; j++)
			if (i != j)
				currentValue -= abs(matrix[i][j]);

		if (currentValue < min)
			min = currentValue;
	}

	return min;
}
double FindMax(double **matrix)
{
	double max = 0;
	for (int i = 0; i < N; i++)
	{
		double currentValue = matrix[i][i];

		for (int j = 0; j < N; j++)
			if (i != j)
				currentValue += abs(matrix[i][j]);

		if (currentValue > max)
			max = currentValue;
	}

	return max;
}
/*void MultyArrayByNumber(double *matrix, double number)
{
	for (int i = 0; i < N; i++)
		matrix[i] *= number;
}*/

// 3.
double **CalcEMinusMultMatrix(double **A, double **B)
{
	double **C = new double *[N];
	for (int i = 0; i < N; i++)
		C[i] = new double[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			C[i][j] = 0;
			if (i == j)
				C[i][j] = 1;
			for (int k = 0; k < N; k++)
				C[i][j] -= A[i][k] * B[k][j];
		}

	return C;
}
double ** calcD_inv(double **A)
{
	double **D = new double*[N];
	for (int i = 0; i < N; i++)
		D[i] = new double[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			D[i][j] = 0;
	
	for (int i = 0; i < N; i++)
		D[i][i] = A[i][i];

	//cout << "\nD:\n";
	//coutMatrix(D, N, N);

	D = InverseA(D);

	return D;
}
double ** CalcB_D(double **A, double n)
{
//	// B_D = E - D(-1)*A
//	
//	double **D = calcD_inv(A); 
//
//	//cout << "D_inv:\n";
//	//coutMatrix(D, N, N);
//
//	D = CalcEMinusMultMatrix(A, D);
//	cout << "\nB_D:\n";
//	coutMatrix(D, N, N);
//

	double **B = new double *[n];
	for (int i = 0; i < n; i++)
		B[i] = new double[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				B[i][j] = 0;
			else
				B[i][j] = -A[i][j] / A[i][i];
		}

	return B;
}
double * CalcC_D(double **A, int n)
{
	
	// C_D = D_inv * b

	//double **D = calcD_inv(A);

	double *C = new double[n];

	/*for (int i = 0; i < n; i++)
	{
		C[i] = 0;
		for (int k = 0; k < N; k++)
			C[i] += D[i][k] * A[k][N];
	}*/
	for (int i = 0; i < n; i++)
		C[i] = A[i][n] / A[i][i];

	return C;
}
double calculateMatrixNorm(double** matrix)
{
	double maxNorm = 0;

	for (int i = 0; i < N; i++)
	{
		double temp = 0;
		for (int j = 0; j < N; j++)
			temp += abs(matrix[i][j]);

		if (temp > maxNorm)
			maxNorm = temp;
	}

	return maxNorm;
}

//
double calculateVectorNorm(double *vector)
{
	double maxNorm = 0;//abs(vector[0]);
	for (int j = 1; j < N; j++)
		if (maxNorm < abs(vector[j]))
			maxNorm = abs(vector[j]);

	return maxNorm;
}
double CalculatePriori(double NormB_alpha, double vectorNorm, int start)
{
	int k = 1;
	
	double priori = NormB_alpha * vectorNorm / (1 - NormB_alpha);
	double valueForPriori = vectorNorm / (1.0 - NormB_alpha);

	//cout << "Введите eps = ";
	//cin >> epsilon;

	while (priori > epsilon)
	{
		priori = ((double)pow(((double)NormB_alpha), start)) * valueForPriori;
		k++;
		start++;
	}

	return k;
}
double Difference(double *arrayk, double *arrayk1)
{
	double sum = 0;
	for (int i = 0; i < N; i++)
		sum += abs(arrayk[i] - arrayk1[i]);

	return sum;
}
double *SubOfVectors(double *vector1, double *vector2)
{
	double *result = new double[N];
	for (int i = 0; i < N; i++)
		result[i] = vector1[i] - vector2[i];

	return result;
}
double *MultyMatrixByVector(double **matrix, double *vector)
{
	double *result = new double[N];
	for (int i = 0; i < N; i++)
		result[i] = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			result[i] += matrix[i][j] * vector[j];

	return result;
}
double *SumOfVectors(double *vector1, double *vector2)
{
	double *result = new double[N];
	for (int i = 0; i < N; i++)
		result[i] = vector1[i] + vector2[i];

	return result;
}

double functionForZeydel(double **matrixA, double *x, int a, int b, int i)
{
	double result = 0;

	for (int j = a; j < b; j++)
		result += matrixA[i][j] * x[j];

	return result;
}
double *MethodOfZeydel(double **matrixA, double *b)
{
	double *x_0 = new double[N]
			,*x_1 = new double[N];

	for (int i = 0; i < N; i++)
	{	
		x_0[i] = 0;
		x_1[i] = 0;
	}
	int counter = 0;
	do
	{
		counter++;
		double* temp = x_0;
		for (int i = 0; i < N; i++)
			x_0[i] = x_1[i];

		for (int i = 0; i < N; i++)
			x_1[i] = (1.0 / matrixA[i][i]) * (b[i] - functionForZeydel(matrixA, x_1, 0, i, i) - functionForZeydel(matrixA, temp, i + 1, N, i));

	} while (Difference(x_0, x_1) > epsilon);
	cout << "Количество итераций: " << counter << endl;
	cout << "Норма вектора невязки:\n" << calculateVectorNorm(SubOfVectors(MultyMatrixByVector(matrixA, x_1), b)) << endl;

	return x_1;
}

// 5.
double * CalcX_k(double *x_prev, double **B, double *C)
{
	// x_k = B * x_prev + C

	double *x_k = new double[N];

	for (int i = 0; i < N; i++)
	{
		x_k[i] = C[i];
		for (int k = 0; k < N; k++)
			x_k[i] += B[i][k] * x_prev[k];
	}

	return x_k;
}

void initA(double **A)
{
	A[0][0] = 2.20886;
	A[0][1] = 0.31984;
	A[0][2] = 0.15751;
	A[0][3] = 2.18310;
	A[1][0] = 0.31984;
	A[1][1] = 3.18182;
	A[1][2] = 0.52629;
	A[1][3] = 6.63605;
	A[2][0] = 0.15751;
	A[2][1] = 0.52629;
	A[2][2] = 4.98873;
	A[2][3] = 6.44335;
}

int main()
{
	cout.precision(10);
	cout << fixed;
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Задание 3.\nРешение алгебраических уравнений итерационными методами.\nВариант 8.";
	cout << "\n________________________________________________________________________________\n";

	double **A = new double*[N];
	for (int i = 0; i < N; i++) 
		A[i] = new double[N + 1];

	double *x = new double[N]
		,*x_Gauss = new double[N];

	// 1.
	initA(A);
	GaussColumn(A, x_Gauss);
	initA(A);
	error(A, x_Gauss);
	cout << "\n________________________________________________________________________________\n";

	// 2.
	initA(A);
	double min = FindMin(A);
	double max = FindMax(A);
	double alpha = 2.0 / (min + max);
	printf("\n2.\nalpha = %f\nm = %f\nM = %f\n", alpha, min, max);
	cout << "\n________________________________________________________________________________\n";

	// 3.
	initA(A);
	cout << "\n3.\n\n";

	double **B_D = CalcB_D(A, N);

	double *C_D = CalcC_D(A, N);
	cout << "\nB_D:\n";
	printMatrix(B_D, N, N);
	cout << "\nC_D:\n";
	for(int i = 0; i < N; i++)
		cout << C_D[i] << endl;

	double NormB_D = calculateMatrixNorm(B_D);
	printf("\n\n||B_D|| = %f\n", NormB_D);
	cout << "\n________________________________________________________________________________\n";

	// 4.
	double *x_0 = new double[N];		// начальное приближение 
	for (int i = 0; i < N; i++)
		x_0[i] = 0;

	double *x_1 = CalcX_k(x_0, B_D, C_D); 

	double vectorNorm = calculateVectorNorm(x_1);

	cout<<"\n4.\nАприорная оценка: "<<CalculatePriori(NormB_D, vectorNorm, 1)<<endl;
	cout << "\n________________________________________________________________________________\n";

	// 5. Метод итераций
	cout << "\n5.\nМетод итераций.\n";
	initA(A);
	double *b = new double[N];
	for (int i = 0; i < N; i++)
		b[i] = A[i][N];
	int counter = 0;

	vector <double*> X;
	//X.push_back(x_0);

	double valueForAposter = NormB_D / (1.0 - NormB_D);
	double valueForPriori = vectorNorm / (1.0 - NormB_D);

	while (Difference(x_0, x_1) > epsilon)
	{
		X.push_back(x_1);

		cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ";
		counter++;
		cout << "\nНомер итерации: "<<counter << endl;
		
		cout << "\nНорма вектора невязки:\t\t" << calculateVectorNorm(SubOfVectors(MultyMatrixByVector(A, x_1),b));
		cout << "\nФактическая погрешность:\t" << calculateVectorNorm(SubOfVectors(x_1, x_Gauss));
		cout << "\nАприорная оценка:\t\t" << ((double)pow(((double)NormB_D), counter)) * valueForPriori;
		cout << "\nАпостериорная оценка: \t\t" << valueForAposter * calculateVectorNorm(SubOfVectors(x_0, x_1));
		cout << "\n\nСтолбец решения:\n";
		
		for (int i = 0; i < N; i++)
			cout << x_1[i] << endl;

		double *temp = x_0;
		for (int i = 0; i < N; i++)
			x_0[i] = x_1[i];
		x_1 = CalcX_k(x_1, B_D, C_D);
	}
	cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ";
	cout << "\nРешение методом итераций:\n";
	for (auto i = 0; i < X.size(); i++)
	{
		cout << i + 1 << ")\t";
		for (int j = 0; j < N; j++)
			cout << X[i][j] << "  ";
		cout << endl;
	}
	cout << "\nИтого, количество итераций: " << counter << endl;
	cout << "\n________________________________________________________________________________\n";

	// 6.
	cout<<"\n6.\nМетод Зейделя.\n\n";
	double *zeydel = MethodOfZeydel(A, b);
	cout << endl;
	for (int i = 0; i < N; i++)
		cout << zeydel[i] << endl;
	cout << "\nФактическая погрешность:\n" << calculateVectorNorm(SubOfVectors(x_Gauss, zeydel)) << endl;
	cout << "\n________________________________________________________________________________\n";

	system("PAUSE");
	return 0;
}