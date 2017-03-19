/*
��������� ������ ������� ���������� �������������� � ��������������� ���������.
��������� ������ ������� �������������.
��������� ������ ��������:
	����������� �������
	������� ������� (�����������)
	���������������� ������� �������
	������� ���� (�������)
*/
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

#define A -1		
#define	B 10		
#define E 1e-6		// �������� �����������
#define h 1e-2		// ��� �������������


double f(double x)
{
	return (pow(x, 3) - 5*pow(x,2) +7.638*x - 3.472);
}
double df(double x)
{
	return 3*pow(x, 2) - 10*x +7.638;
}


// 1. ��������� ������ ��������� f(x) �� ������� [A,B]
int separate(vector <double> &a, vector <double> &b)
{
	double beg = A;
	while (beg < B)
	{
		double end;
		if ( beg + h > B) end = B;
		else end = beg + h;
		if ( f(beg) < 0 && f (end) > 0 || f(beg)> 0 && f (end) < 0 )
		{
			cout<<"["<<beg<<"; "<<end<<"]"<<endl;
			a.push_back(beg);
			b.push_back(end);
		}
		beg = end;
	}
	cout<<"\n\n";
	return 0;
}

// 2. ��������� ������ ��������� �� ��������� �������� ������ ��������
void bisection_method(vector <double> a, vector <double> b)
{
	cout<<"1. ����� ��������.\n\n";

	for (int i = 0; i < a.size(); i++)
	{
		double beg = a[i], end = b[i];
		double mid = (beg + end) / 2;
		int n = 0;
		cout<<"�������  \t\t\t\t["<<beg<<"; "<<end<<"]"<<endl;
		cout<<"��������� �����������: \t\t\t"<<mid<<endl;
		while (1 > 0)
		{
			if ( f(beg) < 0 && f (mid) > 0 || f(beg)> 0 && f (mid) < 0 )
				end = mid;

			if ( f(mid) < 0 && f (end) > 0 || f(mid)> 0 && f (end) < 0 )
				beg = mid;
			n++;
			if ( abs( mid - (beg+end) / 2) < E)
			{
				cout<<"����� �����: \t\t\t\t"<<n<<endl;
				cout<<"������������ ��������: \t\t\t"<<mid<<endl;
				cout<<"���������� �������� �������: \t\t"<<abs(f(mid))<<endl<<endl;
				break;
			}
			else  mid = (beg + end) / 2;
			
		}
	}
	cout<<"\n\n";
}

void newtons_method(vector <double> a, vector <double> b)
{
	cout<<"2. ����� �������.\n\n";

	for (int i = 0; i < a.size(); i++)
	{
		double x0 = a[i], x_next;
		int n = 0;
		cout<<"�������  \t\t\t\t["<<a[i]<<"; "<<b[i]<<"]"<<endl;
		cout<<"��������� �����������: \t\t\t"<<x0<<endl;
		while (1 > 0)
		{
			if (df(x0) == 0)
			{
				cout<<"x = "<<x0<<" - ������ ������ ���������!!\n\n";
				break;
			}
			x_next = x0 - f(x0) / df(x0);
			n++;
			if ( abs(f(x_next)) < E)
			{
				cout<<"����� �����: \t\t\t\t"<<n<<endl;
				cout<<"������������ ��������: \t\t\t"<<x_next<<endl;
				cout<<"���������� �������� �������: \t\t"<<abs(f(x_next))<<endl<<endl;
				break;
			}
			else  x0 = x_next;
			
		}
	}
	cout<<"\n\n";
}

void modifate_newtons_method (vector <double> a, vector <double> b)
{
	cout<<"3. ���������������� ����� �������.\n\n";

	for (int i = 0; i < a.size(); i++) 
	{
		double x0 = a[i], x_next, deff = df(x0);
		int n = 0;
		cout<<"�������  \t\t\t\t["<<a[i]<<"; "<<b[i]<<"]"<<endl;
		cout<<"��������� �����������: \t\t\t"<<x0<<endl;
		if (df(x0) == 0)   cout<<"x = "<<x0<<" - ������ ������ ���������!!\n\n";
		while (1 > 0)
		{
			x_next = x0 - f(x0) / deff;
			n++;
			if ( abs(f(x_next)) < E)
			{
				cout<<"����� �����: \t\t\t\t"<<n<<endl;
				cout<<"������������ ��������: \t\t\t"<<x_next<<endl;
				cout<<"���������� �������� �������: \t\t"<<abs(f(x_next))<<endl<<endl;
				break;
			}
			else  x0 = x_next;
			
		}
	}
	cout<<"\n\n";
}

void secant_method(vector <double> a, vector <double> b)
{
	cout<<"4. ����� ����.\n\n";

	for (int i = 0; i < a.size(); i++)
	{
		double x0 = a[i], x_fix = b[i], fb = f(x_fix), x_next;
		int n = 0;
		cout<<"�������  \t\t\t\t["<<a[i]<<"; "<<b[i]<<"]"<<endl;
		cout<<"��������� �����������: \t\t\t"<<x0<<endl;
		while (1 > 0)
		{
			if (f(x0) - fb) x_next = x0 - f(x0)/(f(x0) - fb) * (x0 - x_fix);
			n++;
			if ( abs( x0 - x_next) < E)
			{
				cout<<"����� �����: \t\t\t\t"<<n<<endl;
				cout<<"������������ ��������: \t\t\t"<<x_next<<endl;
				cout<<"���������� �������� �������: \t\t"<<abs(f(x_next))<<endl<<endl;
				break;
			}
			else  x0 = x_next;
		}
	}
	cout<<"\n\n";
}

int main()
{
	setlocale(LC_ALL, "RUS");
	cout<<"��������� ������ ������� ���������� �������������� � ��������������� ���������"<<endl;
	cout<<"==============================================================================\n\n";
	cout<<"��������� ������:\n\nA = "<<A<<"\nB = "<<B<<"\nE = "<<E<<"\nh = "<<h;
	cout<<"\n\n==============================================================================\n\n";

	// �������, ���������� ������ � ����� �������� � ������
	vector <double> a;			
	vector <double> b;

	separate(a, b);
	bisection_method(a, b);
	newtons_method(a, b);
	modifate_newtons_method(a, b);
	secant_method(a, b);

	system("PAUSE");
	return 0;
}