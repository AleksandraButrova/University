/* Задание 2.
Точные методы решения систем СЛАУ. Метод Гаусса.
Вариант 3.1.*/

#include <iostream>
#include <math.h>

using namespace std;

#define N 3
#define eps	1e-7


void initA(float **A)
{
	A[0][0] =  6.7528e-6;
	A[0][1] = -7.5944e-3;
	A[0][2] = 4.30584;
	A[0][3] = 3.80430;
	A[1][0] = 6.1528e-3;
	A[1][1] = -0.75944;
	A[1][2] = 1.53584; 
	A[1][3] = 1.64243;
	A[2][0] = 0.89528;
	A[2][1] = 0.84056; 
	A[2][2] = 0.98584;
	A[2][3] = 1.96424;
}
void init(float **A, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0 ; j < m; j++)
			A[i][j] = 0;
}
void coutMatrix(float **Matrix, int n, int m){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++)
			cout<<Matrix[i][j]<<"\t";
		cout<<endl;
	}
}
void coutMatrixd(float **Matrix, int n, int m){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++)
		{
			if (i == j )
				cout<<"1\t\t";
			if (i < j)
				cout<<Matrix[i][j]<<"\t";
			if (i > j)
				cout<<"0\t\t";
		}
		cout<<endl;
	}
}
void error(float **A, float *x)
{
	float R[N];
	initA(A);
	//cout << endl;

	for (int i = 0; i < N; i++)
	{
		R[i] = A[i][N];
		//cout << R[i] << endl;

		for (int j = 0; j < N; j++)
			R[i] = R[i] - (A[i][j]*x[j]);
	}

	cout<<"\nНевязка: \n";
	for (int i = 0; i < N; i++)
		cout<<abs(R[i])<<endl;
}
float norm(float **A)
{
	float max_sum = 0, 
			sum = 0;

	for (int i = 0 ; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			sum += abs(A[i][j]);

		if (sum > max_sum) max_sum = sum;
		sum = 0;
	}

	return max_sum;
}

// 1. Обычный метод Гаусса
int ForwardElimination(float **A){
	for( int k = 0; k < N; k++)
	{
		float A_kk = A[k][k];

		if (abs(A_kk) < eps) {
			cout<<"Схема единственного деления не работает, так как элемент А["<<k<<" ;"<<k<<"] < "<<eps<<endl;
			return -1;
		}
		else
			for (int j = k + 1; j < N+1; j++)
				A[k][j] = A[k][j]/A_kk;

		for (int i = k + 1; i < N; i++)
		{
			float A_ik = A[i][k];
			for (int j = k; j < N+1; j++)
			{
				A[i][j] = A[i][j] - A[k][j]*A_ik;
			}
		}
	}
		return 0;
}
void  BackSubstitution(float **A, float *x){
	for (int i = N - 1; i >= 0; i--)
	{
		x[i] = A[i][N];
		for (int j = i + 1; j < N; j++)
			x[i] -= A[i][j]*x[j];
	}
}
void Gauss(float **A, float *x)
{
	cout<<"1. Метод Гаусса (схема единственного деления).\n";
	cout<<"\nИсходная матрица:\n";
	coutMatrix(A, N, N+1);
	
	cout<<"\nМатрица после прямого хода:\n";
	ForwardElimination(A);
	coutMatrix(A, N, N+1);
	
	cout<<"\nСтолбец решения:\n";
	BackSubstitution(A, x);
	for (int i = 0; i < N; i++)
		cout<<x[i]<<endl;

	error(A, x);


	cout<<"\n________________________________________________________________________________\n";
}

//2. Метод Гаусса с выбором главного элемента по столбцу
void SwapLine(float **A, int i, int minInd)
{
	for (int j = 0; j < N+1; j++)
		swap( A[i][j], A[minInd][j]);
}
void ChooseColumn(float **A, int i)
{
	int minInd = i;
	for (int j = i+1; j < N; j++)
		if (abs(A[i][j]) > abs(A[i][minInd]))
			minInd = j;
	if (i != minInd)
		SwapLine(A, i, minInd);

}
void ForwardEliminationColumn(float **A)
{
	for( int k = 0; k < N; k++)
	{
		ChooseColumn(A, k);

		float A_kk = A[k][k];

		if (abs(A_kk) < eps) {
			cout<<"Схема единственного деления не работает, так как элемент А["<<k<<" ;"<<k<<"] < "<<eps<<endl;
		}
		else
			for (int j = k + 1; j < N+1; j++)
				A[k][j] = A[k][j]/A_kk;

		for (int i = k + 1; i < N; i++)
		{
			float A_ik = A[i][k];
			for (int j = k; j < N+1; j++)
			{
				A[i][j] = A[i][j] - A[k][j]*A_ik;
			}
		}
	}
}
void GaussColumn(float **A, float *x)
{
	cout<<"\n2. Метод Гаусса с выбором главного элемента по столбцу.\n";
	cout<<"\nИсходная матрица:\n";
	coutMatrix(A, N, N+1);
	
	cout<<"\nМатрица после прямого хода:\n";
	ForwardEliminationColumn(A);
	coutMatrix(A, N, N+1);
	
	cout<<"\nСтолбец решения:\n";
	BackSubstitution(A, x);
	for (int i = 0; i < N; i++)
		cout<<x[i]<<endl;
	cout<<endl;
	
	error(A, x);

	cout<<"\n________________________________________________________________________________\n";
}

//3. Вычисление определителя матрицы А
float det(float **A)
{
	ForwardElimination(A);
	float det = 1;

	for (int i = 0; i < N; i++)
		det *= A[i][i];

	cout<<"\n3. det(A) = "<<det<<endl;
	cout<<"\n________________________________________________________________________________\n";

	return det;
}

//4. Нахождение обратной матрицы методом Гаусса с выбором
void MtoA_withI(float **M, float **A, int I)
{
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++)
			A[i][j] = M[i][j];
		A[i][N] = 0;
	}
	A[I][N] = 1;
}
void InverseA(float **A, float **L, float **U, float **des)
{
	cout<<"\n4. Обратная матрица.\n";
	float *x = new float [N];
	
	for (int j = 0; j < N; j++)
	{
		initA(A);
		MtoA_withI(A, A, j);

		ForwardEliminationColumn(A);
		BackSubstitution(A, x);

		for (int i = 0; i < N; i++)
			des[i][j] = x[i];
	}
	cout<<"\nОбратная матрица:\n";
	coutMatrix(des, N, N);

	cout<<"\n________________________________________________________________________________\n";
}

//5. Нахождение решения системы с помощью обратной матрицы.
void SolveWithInverse(float **A, float **A_inv, float *x)
{
	cout<<"\n5. Нахождение решения системы с помощью обратной матрицы.\n";

	for (int i = 0; i < N; i++)
	{
		x[i] = 0;
		for (int j = 0; j < N; j++)
			x[i] += A_inv[i][j] * A[j][N];		// A[j][N] == b[j]
	}

	cout<<"\nСтолбец решения:\n";
	for (int i = 0; i < N; i++)
		cout<<x[i]<<endl;
	cout<<endl;

	error(A, x);

	cout<<"\n________________________________________________________________________________\n";

}

//6. Нахождение числа обусловленности
float cond(float **A, float **A_inv)
{
	cout<<"6. cond(A) = "<<norm(A) * norm(A_inv)<<endl;
	cout<<"\n________________________________________________________________________________\n";

	return norm(A) * norm(A_inv);
}


int main(){
	cout.precision(6);
	cout<<fixed;
	setlocale (LC_ALL, "RUSSIAN");
	cout<<"Задание 2.\nТочные методы решения систем СЛАУ. Метод Гаусса.";
	cout<<"\n________________________________________________________________________________\n";
	
	float **A = new float *[N],
		*x = new float [N],
		**L = new float *[N],
		**U = new float *[N],
		**A_inv = new float*[N];
	
	for (int i = 0 ; i < N; i++){
		A[i] = new float [N+1];
		L[i] = new float [N];
		U[i] = new float [N];
		A_inv[i] = new float [N];
	}

	// 1.
	initA(A);
	Gauss(A, x);

	// 2.
	initA(A);
	GaussColumn(A, x);

	// 3.
	initA(A);
	det(A);

	// 4.
	InverseA(A, L, U, A_inv);

	// 5.
	initA(A);
	SolveWithInverse(A, A_inv, x);

	// 6.
	cond(A, A_inv);

	return 0;
}