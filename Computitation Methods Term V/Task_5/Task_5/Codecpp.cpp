/*
������� 5.
����������� ���������� ������������� ���������
�� ��������� ������������ ��������
*/

#include <iostream>
#include <math.h>

using namespace std;

// 1) ��������� ������
double A = 0;				// ������� �������������� � � �
double B = 1;
int m = 20		;			// ����� ����������� ������� [ A , B ]
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

// 2) ��� ������ w = 1 � ������� f(x) ��������� ����� � 
// ������� �� ������ �������� ��������� J �� w(x)*f(x) �� ��������� [ A , B ]
double J_Ub(double x)		// ������������� ��������
{
	//return pow(x, 1) / 1;
	//return pow(x, 2) / 2;
	//return pow(x, 3) / 3;
	//return pow(x, 4) / 4;
	//return pow(x, 5) / 5;
	return pow(x, 2) + cos(x);
}
double J(double A, double B)			// ����������� �������� �� [ A , B ]
{
	return J_Ub(B) - J_Ub(A);
}

// 3) ��������� ���������� � ������� �� ������ �������� ��������� �� w(x)*f(x) 
// ��� ������ ��������� ������ ���������������, ��������, �������� � ���������� m
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

// 4) ��������� � ����� �� �������� |J - J_h| - ���������� ����������� ����������� ��� ������ �������
double Error(double A, double B, double (*func)(double, double))
{
	return abs(J(A, B) - func(A, B))/2;
}

// ����/����� ���������� ������
void UserCin()
{
	cout<<"������� ��������� ������:\n������� �������������� ( A < B ) :\nA = ";
	cin>>A;
	cout<<"B = ";
	cin>>B;
	while( A >= B)
	{
		cout<<"�������� B > A ( A = "<<A<<" )\nB = ";
		cin>>B;
	}
	cout<<"����� ����������� ������� (m > 0)  \nm = ";
	cin>>m;
	while ( m < 1 )
	{
		cout<<"�������� m > 0 \nm = ";
		cin>>m;
	}
}
void ParamOut()
{
	cout<<"\n��������� ������:\n������� �������������� \t\t[ "<<A<<" ; "<<B<<" ]";
	cout<<"\n����� ����������� ������� \tm = "<<m<<endl;
	cout<<"��� ��������� \t\t\th = "<<( B - A) / m <<endl;
}
void AnswerOut()
{
	cout<<"\n\n������ ��� ���������� [ "<<A<<" ; "<<B<<" ]."<<endl;
	cout.precision(15);
	cout<<"������ �������� \tJ    = "<<J(A, B)<<endl<<endl;

	cout<<"����� �������������� \tJ(h) = "<<LeftRectangle(A, B, m, f)<<endl;
	cout<<fixed<<"\t\t\t|J - J(h)| = "<<abs(J(A, B) - LeftRectangle(A, B, m, f))<<"\n\n";

	cout<<"������ �������������� \tJ(h) = "<<RightRectangle(A, B, m, f)<<endl;	
	cout<<fixed<<"\t\t\t|J - J(h)| = "<<abs(J(A, B) - RightRectangle(A, B, m, f))<<"\n\n";

	cout<<"������� �������������� \tJ(h) = "<<MiddleRectangle(A, B, m, f)<<endl;
	cout<<fixed<<"\t\t\t|J - J(h)| = "<<abs(J(A, B) - MiddleRectangle(A, B, m, f))<<"\n\n";

	cout<<"�������� \t\tJ(h) = "<<Trapezoid(A, B, m, f)<<endl;
	cout<<fixed<<"\t\t\t|J - J(h)| = "<<abs(J(A, B) - Trapezoid(A, B, m, f))<<"\n\n";

	cout<<"������� \t\tJ(h) = "<<Sympson(A, B, m, f)<<endl;
	cout<<fixed<<"\t\t\t|J - J(h)| = "<<abs(J(A, B) - Sympson(A, B, m, f))<<"\n\n";

}

// ������������� ����������� (� ��������) 
// ��� ������������� ������ (� ����� ������)
void TheoryError()
{
	
	cout<<"����� � ������ �������. |Rm(f)| <= "<<(double) 1/2 * 1/20 * (2 - cos(1))<<endl;
	cout<<"������� ��������������. |Rm(f)| <= "<<(double) 1/24 * 1/400 * sin(1)<<endl;
	cout<<"�������� \t\t|Rm(f)| <= "<<(double) 1/12 * 1/400 * sin(1)<<endl;
	cout<<fixed<<"������� \t\t|Rm(f)| <= "<< (double) 1/2880 *(double) 1/400 *(double) 1/400 * (double) sin(1)<<endl;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	
	cout<<"\n������� 5.\n����������� ���������� ������������� ���������\n�� ��������� ������������ ��������.\n";
	cout<<"\n=========================================\n";
	
	

	bool ans = true;
	while (ans)
	{
	//UserCin();
	ParamOut();
	AnswerOut();
	TheoryError();
	cout<<"\n\n���? (1 - ��, 0 - ���)  ";
	cin>>ans;

	}
	
	return 0;
}