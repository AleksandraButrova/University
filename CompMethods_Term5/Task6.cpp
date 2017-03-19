/*
Задание 6.
Приближённые вычисления интегралов
при помощи квадратурных формул 
наивысшей алгебраической степени чётности
(КФ НАСТ или КФ гауссова типа)
*/

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//	Данные из примера
double	a = 0;
double	b = 1;
int		N = 2;
double f ( double x )
{
	return sin(x);
}
double w ( double x )
{
	return pow(x, 1/4);
}

void UserCin ( int &N, double &a, double &b )
{
	//cout<<"Введите количество узлов : ";
	//cin>>N;

	cout<<"Введите промежуток интегрирования [ a ; b ] :"<<endl;
	cout<<"a = ";
	cin>>a;
	cout<<"b = ";
	cin>>b;

}

// Шаг 1.
// Рассмотрим w2(x) = x^2 + c*x + d 
// и найдём коэффициенте при условии ортогональности w2(x) 1 и x
// В итоге надо решить систему из 2х уравнений:
// c * m1 + d * m0 = - m2
// c * m2 + d * m1 = - m3 

// m0 = J(w(x)) по [ a ; b ]
double m0 (double a , double b)
{
	return 4.0/5 * ( pow(b, 5/4) - pow(a, 5/4));
}

// m1 = J( w(x) * x ) по [ a ; b ]
double m1 (double a , double b)
{
	return 4.0/9 * ( pow(b, 9/4) - pow(a, 9/4));
}

// m2 = J( w(x) * x^2 ) по [ a ; b ]
double m2 (double a , double b)
{
	return 4.0/13 * ( pow(b, 13/4) - pow(a, 13/4));
}

// m3 = J( w(x) * x^3 ) по [ a ; b ]
double m3 (double a , double b)
{
	return 4.0/17 * ( pow(b, 17/4) - pow(a, 17/4));
}

double Calc_d ( double a , double b )
{
	return ( pow( m2(a, b), 2) - m1(a, b) * m3(a, b)) / ( pow( m1(a, b), 2) - m0(a, b) * m2(a, b)) ;
}

double Calc_c ( double a , double b )
{
	return (-m2(a, b) - Calc_d(a, b) * m0(a, b)) / m1(a, b);	
}

// Шаг 2.
// Найдём корни уравнения w(x) = 0 методом бисекций.
double FindRoots( double a , double b , double &x1 ,double &x2 )
{
	double discr = pow (Calc_c(a, b), 2) - 4 * Calc_d(a, b);

	if (discr > 0 ) {
		x1 = (- Calc_c(a, b) - sqrt(discr)) / 2 ;
		cout<<"\tx1 = " << x1 << endl;

		x2 = (- Calc_c(a, b) + sqrt(discr)) / 2 ;
		cout<<"\tx2 = " << x2 << endl;
		
		return 0;
	}

	else {
		cout<<"Найдено меньше двух корней!"<<endl;
		return -1;
	}
	return -1;

}

// Шаг 3.
// Найдем коэффициенты А1 и А2 
// из условия точности ИКФ для 1 и х
// А1 + А2 = m0
// A1 * x1 + A2 * x2 = m1

double Calc_A2 ( double a , double b , double x1 , double x2 )
{
	return ( m1(a, b) - m0(a, b) * x1 ) / ( x2 - x1 );
}

double Calc_A1 ( double a , double b,  double x1 , double x2 )
{
	return m0(a, b) - Calc_A2(a, b, x1, x2);
}

int main()
{
	setlocale(LC_ALL, "RUS");

	cout<<"\nЗадание 6.\nПриближённые вычисления интегралов\nпри помощи квадратурных формул\nнаивысшей алгебраической степени чётности\n(КФ НАСТ или КФ гауссова типа)\n";
	cout<<"\n=========================================\n\n";
	
	bool UserAnsw = 1; 
	while ( UserAnsw == 1 )
	{
		UserCin(N, a, b);

		// Моменты весовой функции
		cout<<"Моменты весовой функции w(x) = x^(1/4): "<<endl;
		cout<<"\tm0 = "<<m0(a, b)<<endl;
		cout<<"\tm1 = "<<m1(a, b)<<endl;
		cout<<"\tm2 = "<<m2(a, b)<<endl;
		cout<<"\tm3 = "<<m3(a, b)<<endl;

		// вид ортогонального многочлена
		double c = Calc_c(a, b);
		double d = Calc_d(a, b);
		cout<<"\nВид орготонального многочлена:\n\tw2(x) = x^2";
		(c > 0) ? cout << " +" << c : cout << " - " << abs(c);
		cout << " * x";
		(d > 0) ? cout << " + " << d : cout << " - " << abs(d);
		cout << endl;

		// узлы КФ НАСТ
		cout<<"\nУзлы КФ:"<<endl;
		double x1, x2;
		FindRoots(a, b, x1, x2);

		// коэффициенты КФ НАСТ
		cout<<"\nКоэффициенты КФ НАСТ: "<<endl;
		double A1 = Calc_A1(a, b, x1, x2);
		cout<<"\tA1 = "<<A1<<endl;
		double A2 = Calc_A2(a, b, x1, x2);
		cout<<"\tA2 = "<<A2<<endl;

		// Проверка для x^3
		float check_x3 = A1 * pow(x1, 3) + A2 * pow(x2, 3);
		float check_m3 = m3(a, b);
		cout<<"Проверка: A1 * (x1)^3 + A2 * (x2)^3 = m3 ?"<<endl;
		cout.precision(15);
		cout<<"\t"<<check_x3<<endl;
		cout<<"\t"<<check_m3<<endl;
		( check_m3 == check_x3 ) ? cout << "Проверка выполнена успешно!\n" : cout << "Проверка провалилась...\n";
		
	
		// ответ
		double res = A1 * f (x1) + A2 * f (x2);
		cout<<"\nОтвет:\n\t"<<res<<endl;

		cout<<"\n\nДругой промежуток? (0 - нет, 1 - да)\t";
		cin>>UserAnsw;
	}
	return 0;
}