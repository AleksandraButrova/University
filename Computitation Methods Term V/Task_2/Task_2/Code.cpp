/*
������� 2.
������ ��������������� ����������������
����������������� ��������� � ����� ������� � � ����� ��������
*/

#include <iostream>
#include <cmath>
using namespace std;

//������ �� �������
int m=15;
int n=7;
double a=0;
double b=1;
double h=(b-a)/m;
double x0=0.7;
double func(double x)
{
	//return (sin(x)+x*x/2);
	return (x*x-0.4)*(x+1.1)*x;
}

double **RR = new double *[m+1];


void outData()
{
	cout<<"\n\n���������� ����� \t\t\tm = "<<m<<endl;
	cout<<"������� ���������� ���������������� \tn = "<<n<<endl;
	cout<<"������� ����������������: \t\t["<<a<<"; "<<b<<"]"<<endl;
	cout<<"����� ���������������  \t\t\tx0 = "<<x0<<endl;
	cout<<"\n\n";
}

// ������������ ������ ������
void cinData()
{
	cout<<"������� m : ";
	cin>>m;
	cout<<"������� ����� �������:\na = ";
	cin>>a;
	cout<<"b = ";
	cin>>b;
	h = (b-a)/m;
	cout<<"������� ������� ����������������� ���������� n : ";
	while (true) 
	{
	cin>>n;
	if (n>m) cout<<"��������! n �� ������ ������������ m = "<<m<<"!\n������� n ������ : ";
	else break;
	}
	
	h=(b-a)/m;
}


//�������� n ��������� ����� � x0
void Sorting(double **table)  
{
            for (int i = 0; i < m + 1; i++)
            {
                double min = b - a;
                int index = i;
                for (int j = i; j < m + 1; j++)
                {
					if (abs(table[j][0] - x0) < min)
                    {
                        index = j;
                        min = abs(table[j][0] - x0);
                    }
                }

				swap(table[i][0], table[index][0]);
				swap(table[i][1], table[index][1]);
            }
        }

//���������� ������� ����������� ���������
void FillingRR(double **RR)
{
	for (int j = 2; j < n ; j++)
	{
		for (int i = 0; i < n + 1 - j; i++)
		{
			RR[i][j] = (RR[i + 1][j - 1] - RR[i][j - 1])* 1.0 / (RR[i + j - 1][0] - RR[i][0]);
		}

	}
}

//	�������� �������� � ����� �������
double Newton(double **RR)
{
	double result = RR[0][1];
	double multiplication = 1;
	for (int i = 1; i < n - 1; i++)
	{
		multiplication *= x0 - RR[i - 1][0];
		result += RR[0][i + 1] * multiplication;
	}
	return result;
}

//	��������������� ������� ��� ������ ��������
double Phi(double x, int j, double **RR)
{
	double result = 1;
	for (int i = 0; i < n; i++)
	{
		if (j != i) 	result *= (x - RR[i][0]);
	}
	return result;
}

//	�������� �������� � ����� ��������
double Lagrange(double **RR)
{
	double result = 0;
	for (int j = 0; j < n; j++)
	{
		result += RR[j][1] * Phi(x0, j, RR) / Phi(RR[j][0], j, RR);
	}
	return result;
}

//���������������� ����
void Preparing()
{
	for(int i=0; i<m+1; i++)
	{
		RR[i] = new double [m+2];
	}

	//	����� �������� ���������� ������
	setlocale(LC_ALL, "RUSSIAN");
	cout<<"\n������ ��������������� ����������������.\n���������������� ��������� � ����� ������� � � ����� ��������.";
	cout<<"\n==============================================================================\n";
	
	//	�������������, ���� ����� ������� ��������� � ����������
	cinData();

	outData();

	//���������� � ����� ������ ������� x - f(x)
	cout<<"\n������� �� "<<m+1<<" �������� ������� � ������� ��������� ����� �� ���������� ["<<a<<"; "<<b<<"]:\n";
	cout<<"______________________________________________________________________________\n\tx\t\t\t\tf(x)\n"<<endl;
	cout.precision(5);
	for (int i=0; i<m+1; i++)
	{
		cout<<i<<")\t";
		RR[i][0] = a + h * i;
		RR[i][1] = func(a + h * i);
		cout<<RR[i][0]<<"       \t\t\t"<<RR[i][1]<<endl;
	}	
	cout<<"______________________________________________________________________________"<<endl;
	cout<<"������� ����� ���������������� � : ";
	cin>>x0;
}

int main()
{
	Preparing();	

//	�������
	Sorting(RR);

	cout<<"\n\n\n\n������� �� "<<n+1<<" ��������� � "<<x0<<" �����:\n";
	cout<<"_______________________________________________________\n\tx\t\t\t\tf(x)\n"<<endl;
	cout.precision(5);
	for (int i = 0; i < n + 1; i++)
	{
		cout<<i<<")\t";
		cout<<RR[i][0]<<"       \t\t\t"<<RR[i][1]<<endl;
	}
	cout<<"_______________________________________________________"<<endl;

	//	��������� ������� ���������� ��������
	FillingRR(RR);

	//	����� �����������
	cout.precision(2);
	cout<<fixed<<"\n\n\P("<<x0<<") � ����� �������:\t";
	cout.precision(25);
	cout<<Newton(RR);
	cout<<"\n����������� �����������:\t"<<abs(Newton(RR) - func(x0))<<endl;

	cout.precision(2);
	cout<<fixed<<"\n\n\P("<<x0<<") � ����� ��������:\t";
	cout.precision(25);
	cout<<Lagrange(RR);
	cout<<"\n����������� �����������:\t"<<abs(Lagrange(RR) - func(x0))<<endl<<endl;

	
	system("PAUSE");
	return 0;
}