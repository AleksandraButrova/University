/*
������� 4.
������ ��������� ����������������.
���������� ��������-�������� �������
�� �������� ���������� �����������������
*/

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//	������ �� �������
int m = 10;
double E = pow(10, -12);
int n = 10;
double a = 0;
double b = 1;
double h = (b - a) / m;
double F = 0.34;
double f(double x)
{
	//return ((x-0.1)*x*(0.3*x - 0.6));
	return (sin(x) + x*x / 2);
}
double df(double x)
{
	return (cos(x) + x);
}
double ddf(double x)
{
	return (-sin(x) + 1);
}

/*-----�� ��� ����������������� �����-----*/

//����� ���������� �� �����
void outData()
{
	cout << "\n\n���������� ����� \t\t\tm = " << m << endl;
	cout << "������� ���������� ���������������� \tn = " << n << endl;
	cout << "������� ����������������: \t\t[" << a << "; " << b << "]" << endl;
	//cout << "����� ��������� ���������������\t\tF = " << F << endl;
	cout << "\n\n";
}
// ��������� ������ � �������
void cinData()
{
	cout << "������� m : ";
	cin >> m;
	cout << "������� ����� �������:\na = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	h = (b - a) / m;
	cout << "������� ������� ����������������� ���������� n : ";
	while (true)
	{
		cin >> n;
		if (n > m) cout << "��������! n �� ������ ������������ m = " << m << "!\n������� n ������ : ";
		else break;
	}
	h = (b - a) / m;
}
//	���������������� ����
void Preparing(double **table)
{
	bool ans;

	cout<<"������� 0, ����� ��������������� ������� �� �������.\n������� 1, ����� ������ ���� ������.\n";
	cin>>ans;
	if ( ans ) cinData();
	outData();

	//	���������� � ����� ������ ������� x - f(x)
	cout << "\n������� �� " << m + 1 << " �������� ������� � ������� ��������� ����� �� ���������� [" << a << "; " << b << "]:\n";
	cout << "______________________________________________________________________________\n\tx\t\tf(x)\n" << endl;
	cout.precision(5);
	for (int i = 0; i<m + 1; i++)
	{
		cout << i << ")\t";
		table[i][0] = a + h * i;
		table[i][1] = f(a + h * i);
		cout << table[i][0] << "\t\t" << table[i][1] << endl;
	}
	cout << "______________________________________________________________________________\n" << endl;

}

/*------------------����� 1.---------------*/
/*-----------�������� ������������.--------*/

// ��������������� �������
//	������ ������� x � f(x) ������� ��� ������� ������ �������
void SwapColumn(double **table)
{
	for (int i = 0; i < m + 1; i++)
		swap(table[i][0], table[i][1]);
}
// ��������� ������� �� ��������� � x0 ������
void Sorting(double **table, int column, double x0)  
{
            for (int i = 0; i < m + 1; i++)
            {
                double min = b - a;
                int index = i;
                for (int j = i; j < m + 1; j++)
                {
					if (abs(table[j][column] - x0) < min)
                    {
                        index = j;
                        min = abs(table[j][column] - x0);
                    }
                }

				swap(table[i][column], table[index][column]);
				swap(table[i][(column + 1)%2], table[index][(column + 1)%2]);
            }
        }
//	��������������� ������� ��� ������ ��������
double Phi(double x, int j, double **table)
{
	double result = 1;
	for (int i = 0; i < n; i++)
	{
		if (j != i) 	result *= (x - table[i][0]);
	}
	return result;
}
//	�������� �������� � ����� ��������
double Lagrange(double **table, double x0)
{
	double result = 0;
	for (int j = 0; j < n; j++)
	{
		result += table[j][1] * Phi(x0, j, table) / Phi(table[j][0], j, table);
	}
	return result;
}


/*--------------������ ������.-------------*/
//	������ ������� x � f(x) �������
//	������� Pn ��� f(x)
//	������������� ������� ��������
void WayOne(double **table)
{
	SwapColumn(table);
	Sorting(table, 0, F);

	//	������� �����
	cout.precision(15);
	double calculate = Lagrange(table, F);
	cout << fixed << "\n1 ������: " << calculate << endl;
	cout << fixed << "������ �������:\t" << abs(f(calculate) - F) << endl;

	SwapColumn(table);
	Sorting(table, 0, a);
}



/*--------------������ ������.-------------*/
//	������ ���������������� ��������� Pn ��� ������ �������
//	������ ��������� Pn(x) = F ������� ��������
double �larification(double **table, double start, double end)
{
	if (abs(Lagrange(table, end) - Lagrange( table, start)) < E)
		return start;

	double mid = (start + end) / 2.0;

	if ((Lagrange(table, start) - F) * (Lagrange(table, mid) - F) < 0)
		return �larification(table, start, mid);
	else
	{
		if ( Lagrange(table, start) - F == 0 )
			return start;
		else if ( Lagrange(table, end) - F == 0 )
			return end;
	}
	return �larification(table, mid, end);
}
double Bisection (double **table)
{	
	for (int i = 0; i < n ; i++)
	{
		if ((table[i][1] - F) * (table[i + 1][1] - F) <= 0)
			return �larification(table, table[i][0], table[i + 1][0]);
	}

}
double WayTwo(double **table)
{
	double min = INT_MAX, max = INT_MIN;


	//	������� �����
	for (int i = 0; i < m + 1; i++ )
	{
		if (table[i][1] < min ) min = table[i][1];
		if (table[i][1] > max ) max = table[i][1];
	}
	
	Sorting(table, 1, F);

	if ( ( F < min ) || (max < F ) ) 
	{
		cout<<fixed<<"\n2 ������.\n������ �������� ���������� ��������������� �������� F = "<<F<<".\n�������� �������� �� ���������� [ "<< min <<" ; "<<max<<" ] :"<<endl;
		return -1;
	}
	
	cout.precision(15);
	double calculate = Bisection(table);
	cout << fixed << "\n2 ������: " << calculate << endl;
	cout << fixed << "������ �������:\t" << abs(f(calculate) - F) << endl;
	return 0;
}



/*------------------����� 2.---------------*/
//	������� ���������� �����������������
double formula3(double a)
{
	return (f(a + h) - f(a - h)) / (2 * h);
}
double formula4(double a)
{
	return (-3.0* f(a) + 4.0 * f(a + h) - f(a + 2 * h)) / (2 * h);
}
double formula5(double a)
{
	return (3.0 * f(a) - 4.0 * f(a - h) + f(a - 2 * h)) / (2 * h);
}
double formula6(double a)
{
	return (f(a + h) - 2 * f(a) + f(a - h)) / (h * h);
}

//	����� ������� �� ����� 2
void CoutTableDiff(double **table)
{
	cout<<"������� ����������� ������ ������� �� ���� �����"<<endl;
	cout.precision(8);
	//cout << "Rf(a) = " << h*h << endl;
	cout << "\nx\tf\t f'��\t(f'��-f')  f''��  (f''��-f'')\n";

	for (int i = 0; i < m + 1; i++)
	{

		// x � f(x)
		cout.precision(3);
		cout << fixed << table[i][0];
		cout.precision(5);
		cout << " | " << table[i][1] << " | ";
		// f', f'' � �������
		if (i == 0) cout << formula4(table[i][0]) << " | " << abs(formula4(table[i][0]) - df(table[i][0])) << endl;
		else {
			if (i == m) cout << formula5(table[i][0]) << " | " << abs(formula4(table[i][0]) - df(table[i][0])) << endl;
			else cout << fixed << formula3(table[i][0]) << " | " << abs(formula3(table[i][0]) - df(table[i][0])) << " | " << formula6(table[i][0]) << " | " << abs(formula6(table[i][0]) - ddf(table[i][0])) << endl;
		}
	}
	cout<<endl;
}



int main()
{
	//	����� �������� ���������� ������
	setlocale(LC_ALL, "RUSSIAN");
	cout << "\n������� 4.\n������ ��������� ����������������.\n���������� ��������-�������� �������\n�� �������� ���������� �����������������";
	cout << "\n=========================================\n";


	// ������� ��  x � y;
	double **table = new double *[m + 1];
	for (int i = 0; i < m + 1; i++) table[i] = new double[2];

	Preparing(table);

	int ans = 1; 

	// �������� ������������
	while (ans != 0)
	{
		cout << "\n������� ����� ��������� ���������������� F : ";
		cin >> F;
		WayOne(table);
		WayTwo(table);
		cout<<"\n��� �����? (1 - ��; 0 - ���):   ";
		cin >> ans;
		cout<<endl;
	}
	

	// ������ �� ���������� �����������
	//CoutTableDiff(table);



	return 0;
}