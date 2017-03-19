/*Задание 5.
Численное решение интегрального уравнения Фредгольма второго рода.
Метод замены ядра на вырожденное.
Вариант 9.*/
#include <iostream>
#include <math.h>
#include "Gauss.h"

#define a	0
#define b	1
#define N2	10
#define step	10

using namespace std;

double fact(double k)
{
	if ((k == 1) || (k == 0))
		return 1;

	return k*fact(k - 1);
}

double f(double x)
{
	return 1 - x*x;
}
double alpha(int i, double x)
{
	return 0.2 * pow(x, i) / fact(i);
}
double beta(int j, double y)
{
	return pow(y, j);
}

//Нахождение интеграла методом Симпсона
double Sympson(double A, double B, int m, double(*f1)(int, double), int j, double(*f2)(int, double), int i)
{
	double h = (B - A) / m;
	double res = 0;

	for (int k = 0; k < m; k++)
		res += h / 6 * (f1(j, A + h * k)*f2(i, A + h * k) + f1(j, A + h * (k + 1))*f2(i, A + h * (k + 1)) + 4 * f1(j, A + h / 2 + h * k)*f2(i, A + h / 2 + h * k));

	return res;
}
double Sympson(double A, double B, int m, double(*f1)(int, double), int n, double(*f2)(double))
{
	double h = (B - A) / m;
	double res = 0;

	for (int k = 0; k < m; k++)
		res += h / 6 * (f1(n, A + h * k)*f2(A + h * k) + f1(n, A + h * (k + 1))*f2(A + h * (k + 1)) + 4 * f1(n, A + h / 2 + h * k)*f2(A + h / 2 + h * k));

	return res;
}
//------------------------------------------------------


// u(x) = f(x) -  I[a, b] ( G(x, y)*f(y) )dy
double u(double x, int n)
{
	double ** matrixA = new double*[n];
	for (int i = 0; i < n; i++)
		matrixA[i] = new double[n + 1];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				matrixA[i][j] = 1;
			else
				matrixA[i][j] = 0;
		}

	for (int i = 0; i < n; i++)
	{
		matrixA[i][n] = Sympson(a, b, step, beta, i, f);
		for (int j = 0; j < n; j++)
			matrixA[i][j] += Sympson(a, b, step, alpha, j, beta, i);
	}

	double* c_i = new double[n];
	GaussColumn(matrixA, c_i, n);

	double result = f(x);

	for (int i = 0; i < n; i++)
		result -= c_i[i] * alpha(i, x);
	return result;
}

double delta(double x, double y, double n)
{
	double sum = 0;
	for (int k = 0; k < n; k++)
		sum += alpha(k, x)*beta(k, y);
	return exp(x*y) / 5 - sum;
}
double maxdelta(int n)
{
	double max = 0;
	int h = (b - a) / 10;
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 11; j++)
			if (abs(max) < abs(delta(a + h*i, a + h*j, n)))
				max = abs(delta(a + h*i, a + h*j, n));
	return max;
}

int main()
{
	cout.precision(6);
	cout << fixed;
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Задание 5.\nЧисленное решение интегрального уравнения Фредгольма второго рода.\nМетод замены ядра на вырожденное.\nВариант 9.";
	cout << "\n________________________________________________________________________________\n";

	/*cout<< exp(x*y) / 5 - alpha(n, x)*beta(n, y)
	cout << delta(0.5, 0.5, 3) << endl;
	cout << "Максимальное отклонение вырожденного ядра 3-го порядка: " << maxdelta(3)<<endl;
	cout << "Максимальное отклонение вырожденного ядра 4-го порядка: " << maxdelta(4)<<"\n\n";
	cout << "\n________________________________________________________________________________\n";*/

	double H = (b - a) / (double)N2;
	printf("zk\t\tu_3\t\tu_4\n\n");
	for (int k = 0; k < N2 + 1; k++)	
		cout << a + k*H << "\t" << u(a + k*H, 3) << "\t" << u(a + k*H, 4) <<
		"\t" << endl;//abs(u(a + k*H, 3) - u(a + k*H, 4)) << "\n";

	double err = 0; 
	for (int k = 0; k < N2 + 1; k++)
		if (abs(u(a + k*H, 3) - u(a + k*H, 4)) > err)
		err = abs(u(a + k*H, 3) - u(a + k*H, 4));

	cout << "\nmax |u_3 - u_4| = " << err << endl;


	cout << "\n________________________________________________________________________________\n";

	system("PAUSE");
	return 0;
}
