/*
Задание 5.
Приближённые вычисления определенного интеграла
по составным квадратурным формулам
*/

#include <iostream>
#include <math.h>

using namespace std;

// 1) Параметры задачи
double A = 0;				// пределы интегрирования А и В
double B = 1;
int m = 20		;			// число промежутков деления [ A , B ]
double f (double x)
{
	//return pow(x, 0);
	//return pow(x, 1);
	//return pow(x, 2);
	//return pow(x, 3);
	//return pow(x, 4);
	return 2*x - sin(x);
}
double w (double x)
{
	return 1;
}

// 2) Для случая w = 1 и функции f(x) вычислить точно и 
// вывести на печать значение интеграла J от w(x)*f(x) по конечному [ A , B ]
double J_Ub(double x)		// неопределённый интеграл
{
	//return pow(x, 1) / 1;
	//return pow(x, 2) / 2;
	//return pow(x, 3) / 3;
	//return pow(x, 4) / 4;
	//return pow(x, 5) / 5;
	return pow(x, 2) + cos(x);
}
double J(double A, double B)			// определённый интеграл на [ A , B ]
{
	return J_Ub(B) - J_Ub(A);
}

// 3) Вычислить приближённо и вывести на печать значение интеграла от w(x)*f(x) 
// при помощи составных формул прямоугольников, трапеций, Симпсона с параметром m
double LeftRectangle(double A, double B, int m, double (*func)(double))
{
	double h = ( B - A ) / m;
	double res = 0;
	for (int i = 0; i < m; i++)
	{
		res += func(A + h*i);	
	}
	res *= h;
	return res;
}

double RightRectangle(double A, double B, int m, double (*func)(double))
{
	
	double h = ( B - A ) / m;
	double res = 0;
	for (int i = 0; i < m; i++)
	{
		res += h * func( A + h * (i + 1) );	
	}
	return res;
}

double MiddleRectangle(double A, double B, int m, double (*func)(double))
{
	double h = ( B - A ) / m;
	double res = 0;
	for (int i = 0; i < m; i++)
	{
		res += h * func( A + h/2 + h * i );	
	}
	return res;
}

double Trapezoid(double A, double B, int m, double (*func)(double))
{
	double h = ( B - A ) / m;
	double res = 0;
	for (int i = 0; i < m; i++)
	{
		res +=  h / 2 * ( func(A + h*i) + func( A + h * (i + 1) ) );	
	}
	return res;
}

double Sympson(double A, double B, int m, double (*func)(double))
{
	double h = ( B - A ) / m;
	double res = 0;
	for (int i = 0; i < m; i++)
	{
		res += h / 6 * (  func(A + h * i) + func( A + h * (i + 1)) + 4 * func( A + h/2 + h * i )  );	
	}
	return res;
}

// 4) Посчитать и вести на печаться |J - J_h| - абсолютную фактическую погрешность для каждой формулы
double Error(double A, double B, double (*func)(double, double))
{
	return abs(J(A, B) - func(A, B))/2;
}

// Ввод/вывод параметров задачи
void UserCin()
{
	cout<<"Введите параметры задачи:\nПределы интегрирования ( A < B ) :\nA = ";
	cin>>A;
	cout<<"B = ";
	cin>>B;
	while( A >= B)
	{
		cout<<"Выберите B > A ( A = "<<A<<" )\nB = ";
		cin>>B;
	}
	cout<<"Число промежутков деления (m > 0)  \nm = ";
	cin>>m;
	while ( m < 1 )
	{
		cout<<"Выберете m > 0 \nm = ";
		cin>>m;
	}
}
void ParamOut()
{
	cout<<"\nПараметры задачи:\nПределы интегрирования \t\t[ "<<A<<" ; "<<B<<" ]";
	cout<<"\nЧисло промежутков деления \tm = "<<m<<endl;
	cout<<"Шаг дробления \t\t\th = "<<( B - A) / m <<endl;
}
void AnswerOut()
{
	cout<<"\n\nОтветы для промежутка [ "<<A<<" ; "<<B<<" ]."<<endl;
	cout.precision(15);
	cout<<"Точное значение \tJ    = "<<J(A, B)<<endl<<endl;

	cout<<"Левые прямоугольники \tJ(h) = "<<LeftRectangle(A, B, m, f)<<endl;
	cout<<fixed<<"\t\t\t|J - J(h)| = "<<abs(J(A, B) - LeftRectangle(A, B, m, f))<<"\n\n";

	cout<<"Правые прямоугольники \tJ(h) = "<<RightRectangle(A, B, m, f)<<endl;	
	cout<<fixed<<"\t\t\t|J - J(h)| = "<<abs(J(A, B) - RightRectangle(A, B, m, f))<<"\n\n";

	cout<<"Средние прямоугольники \tJ(h) = "<<MiddleRectangle(A, B, m, f)<<endl;
	cout<<fixed<<"\t\t\t|J - J(h)| = "<<abs(J(A, B) - MiddleRectangle(A, B, m, f))<<"\n\n";

	cout<<"Трапеции \t\tJ(h) = "<<Trapezoid(A, B, m, f)<<endl;
	cout<<fixed<<"\t\t\t|J - J(h)| = "<<abs(J(A, B) - Trapezoid(A, B, m, f))<<"\n\n";

	cout<<"Симпсон \t\tJ(h) = "<<Sympson(A, B, m, f)<<endl;
	cout<<fixed<<"\t\t\t|J - J(h)| = "<<abs(J(A, B) - Sympson(A, B, m, f))<<"\n\n";

}

// Теоретическая погрешность (с листочка) 
// для фиксированных данных (в самом начале)
void TheoryError()
{
	
	cout<<"Левые и правые прямоуг. |Rm(f)| <= "<<(double) 1/2 * 1/20 * (2 - cos(1))<<endl;
	cout<<"Средние прямоугольники. |Rm(f)| <= "<<(double) 1/24 * 1/400 * sin(1)<<endl;
	cout<<"Трапеции \t\t|Rm(f)| <= "<<(double) 1/12 * 1/400 * sin(1)<<endl;
	cout<<fixed<<"Симпсон \t\t|Rm(f)| <= "<< (double) 1/2880 *(double) 1/400 *(double) 1/400 * (double) sin(1)<<endl;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	
	cout<<"\nЗадание 5.\nПриближённые вычисления определенного интеграла\nпо составным квадратурным формулам.\n";
	cout<<"\n=========================================\n";
	
	

	bool ans = true;
	while (ans)
	{
	//UserCin();
	ParamOut();
	AnswerOut();
	TheoryError();
	cout<<"\n\nЕщё? (1 - ДА, 0 - НЕТ)  ";
	cin>>ans;

	}
	
	return 0;
}