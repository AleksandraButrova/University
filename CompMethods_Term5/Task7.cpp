/*
Задание 7.
Численное решение Задачи Коши  
для уравнения y'( x ) = f( x , y )
с начальным условием y( x0 ) = y0 

Дано Д.У.	y'( x ) = - y(x) + sin(x) 
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

// Данные из примера
double x_0 = 0;
double y_0 = 1;
double h = 0.1;
int N = 10;


// Вспомогательные структуры
double *x = new double [ N + 3 ];
double *y = new double [ N + 3 ];
double f(int k)
{
	return (-y[k] + sin(x[k]));	
}
double f(double x, double y)
{
	return (-y + sin(x));	
}

// 1) Точное решение Д.У. 
double ExactSolution( double x )
{
	return 0.5 * ( 3 * exp(-x) + sin(x) - cos(x) );
}
void PrintFirstMethod()
{
	cout<<"\n\n1) Таблица точных значений в равноотстойщих узлах с шагом h = "<<h<<endl;
	for (int k = -2; k < N + 1; k++)
	{
		x[k] = x_0 + k*h;
		cout<<"x_"<<k<<"\t"<<x[k]<<"\ty = "<<ExactSolution(x[k])<<endl;
	}
	cout<<endl;
}

// 2) Метод разложения в ряд Тейлора
double TaylorSerias( double x )
{
	return 1 - 1 * x + pow(x, 2.0) - 1/3 * pow(x, 3.0) + 1/24 * pow(x, 4.0);
}
void PrintTaylorsMethod()
{
	// На всякий случай добавлю возможность выводить dy_k, найденное из н.у. (0, 1) :
	//cout<<"Пять ненулевых значений производных y,\nполученных дифференцированием исходного Д.У. с подстановкой x = x0\ny = 1\ny' = -1\ny'' = 2\ny''' = -2\ny_IV = 1"<<endl;
	cout<<"\n\n2) Метод разложения в ряд Тейлора:"<<endl;
	for (int k = -2; k < 3; k++)
	{
		y[k] = TaylorSerias(x[k]);
		cout<<"x_"<<k<<"\t"<<x[k]<<"\ty = "<<y[k]<<endl;
	}
	cout<<endl;
}

// 3) Вывести абсолютную погрешность первых двух способов для k = -2, ..., 2
void PrintAbsError()
{
	cout<<"\n\n3) Вывод абсолютной погрешности ряда Тейлора:"<<endl;
	for (int k = -2; k < 3; k++)
	{
		cout<<"x_"<<k<<"\t"<<x[k]<<"\ty = "<<abs( y[k] - ExactSolution(x[k]) )<<endl;
	}
	cout<<endl;
}

// 4) Метод Адамса 4-го порядка k = 3, ..., N, используя п.2 (метод Тейлора) O(h^6)

void FillTable(double ** table)
{
	// Пять значений из точного значения
	for ( int i = 0; i < 5; i++ )
	{
		table[i][0] = x_0 + ( i - 2 ) * h;
		table[i][1] = ExactSolution(x_0 + ( i - 2 ) * h);
		table[i][2] = h*f(table[i][0], table[i][1]);
		//cout<<<table[i][0]<<"  "<<table[i][1]<<"  "<<table[i][2]<<endl;
	}

	for ( int i = 5 ; i < N + 3 ; i++ ) table[i][0] = x_0 + ( i - 2 )*h ;


	// Дозаполним таблицу по этим значениям
	for ( int j = 3; j < 7; j++ )
	{
		for ( int i = 0; i < 7 - j; i++ )
		{
			table[i][j] = table[ i + 1 ][ j - 1 ] - table[ i ][ j - 1 ] ;
		}
	}

}
	void PrintAdamsMethod()
{
	cout<<"\n\n4) Метод Адамса 4-го порядка"<<endl;

	double adams;
	double **table = new double *[N + 3];
	for ( int i = 0; i < N + 3 ; i++ ) table[i] = new double [7];

	FillTable(table);

	for ( int k = 4 ; k < N + 2 ; k++ )
	{
		adams = table[ k ][ 2 ] + 1.0/2.0 * table[ k - 1 ][ 3 ] + 5.0/12.0 * table[ k - 2 ][ 4 ] 
				+ 3.0/8.0 * table[ k - 3 ][ 5 ] + 251.0/720.0 * table[ k - 4 ][ 6 ];

		
		table[k + 1][1] = table[k][1] + adams;

		cout<<"x_"<<k-1<<"\t"<<table[k + 1][0]<<"\ty = "<<table[k + 1][1]<<endl;

		if ( k + 1 == N + 2 ) break;

		table[ k + 1 ][2] = h * f( table[k + 1][0] , table[k + 1][1]);

		for (int i = k ; i > k - 4; i--) 
		{
			table[ i ][ k + 3 - i ] = table[ i + 1 ][ k + 2 - i ] - table[i][ k + 2 - i];
		}
	}
	cout.precision(15);
	cout<<fixed<<"\nАбсолютная погрешность метода Адамса:\n\t\t\t"<<abs(table[N + 2][1] - ExactSolution(x[N]))<<endl;
	
}

// 5) Метод Рунге-Кутта 4-го порядка O(h^5)
void PrintRungeKuttMethod()
{
	cout<<"\n\n5) Метод Рунге-Кутта 4-го порядка"<<endl;
	double k1, k2, k3, k4;
	for(int k = 0; k < N; k++)
	{
		k1 = h*f (x[k], y[k]); 
		k2 = h*f (x[k] + h/2 , y[k] + k1/2 );  
		k3 = h*f (x[k] + h/2 , y[k] + k2/2 ); 
		k4 = h*f (x[k] + h , y[k] + k3 );
		
		y[k+1] = y[k] + 1.0/6.0 * (k1 + 2*k2 + 2*k3 + k4);

		cout<<"x_"<<k+1<<"\t"<<x[k+1]<<"\ty = "<<y[k+1]<<endl;
	}
	cout.precision(15);
	cout<<fixed<<"\nАбсолютная погрешность метода Рунге-Кутта:\n\t\t\t"<<fabs(y[N] - ExactSolution(x[N]))<<endl;
	cout.precision(6);
}

// 6) Методы Эйлера

// Обычный метод Эйлера O(h^2)
void PrintEulerMethod()
{
	cout<<"\n6.1) Метод Эйлера"<<endl;
	for (int k = 0; k < N ; k++)
	{
		y[k+1] = y[k] + h*f(k);
		cout<<"x_"<<k+1<<"\t"<<x[k+1]<<"\ty = "<<y[k+1]<<endl;
	}
	cout<<"\nАбсолютная погрешность метода Эйлера:\n\t\t\t"<<abs(y[N] - ExactSolution(x[N]))<<endl;
}

// Усовершенствованный метод Эйлера O(h^3)
void PrintAdvancedEulerMethod()
{
	cout<<"\n6.2) Усовершенствованный метод Эйлера"<<endl;
	for (int k = 0; k < N ; k++)
	{
		y[k+1] = y[k] + h*( - y[k] - h/2 * f(k) + sin(x[k] + h/2));
		cout<<"x_"<<k+1<<"\t"<<x[k+1]<<"\ty = "<<y[k+1]<<endl;
	}
	cout<<"\nАбсолютная погрешность усовершенствованного метода Эйлера:\n\t\t\t"<<abs(y[N] - ExactSolution(x[N]))<<endl;
}

// Метод Эйлера-Коши O(h^3)
void PrintEulerCauchyMethod()
{
	cout<<"\n6.3) Метод Эйлера-Коши"<<endl;
	double Y;
	for (int k = 0; k < N ; k++)
	{
		Y = y[k] + h * f(k);
		y[k+1] = y[k] + h/2 * ( f(k) + sin(x[k+1]) - Y);
	
		cout<<"x_"<<k+1<<"\t"<<x[k+1]<<"\ty = "<<y[k+1]<<endl;
	}
	cout<<"\nАбсолютная погрешность метода Эйлера-Коши:\n\t\t\t";
	cout<<fixed<<abs(y[N] - ExactSolution(x[N]))<<endl;
}

int main()
{

	cout.precision(6);
	setlocale (LC_ALL, "RUSSIAN");
	cout<<"Задание 7.\nЧисленное решение Задачи Коши\nдля уравнения вида y'( x ) = f( x , y )\nс начальным условием y( x0 ) = y0"<<endl;
	cout<<"=======================================\n\n";
	cout<<"Данные из примера:\nД.У.\ty'( x ) = - y(x) + sin(x)\nН.Д.\ty(0) = 1\n\th = "<<h<<"\n\tN = "<<N<<endl;
	//bool ans = 1;
	//cout<<"Хотите проверить на других данных? (1 - да, 0 - нет):\t";
	//cin>>ans;

	PrintFirstMethod();
	//PrintTaylorsMethod();
	//PrintAbsError();
	PrintAdamsMethod();
	//PrintRungeKuttMethod();
	//PrintEulerMethod();
	//PrintAdvancedEulerMethod();
	//PrintEulerCauchyMethod();
	return 0;
}