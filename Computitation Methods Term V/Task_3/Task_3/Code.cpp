/*
������� 3.
���������������� �� �������������� �����.
*/

#include <iostream>
#include <cmath>
using namespace std;

//������ �� �������
int m=10;
int n=6;
double a=0;
double b=1;
double h=(b-a)/m;
double x0=0.05;
double func(double x)
{
	return (sqrt(1+x*x));
}

/*int m=16;
int n=10;
double a=0;
double b=1;
double h=(b-a)/m;
double x0=0.65;
double func(double x)
{
	return (sin(x)-x*x/2);
}*/

double **KP = new double *[m+1]; //������� �������� ���������

//������������ ������ ������
void cinData()
{
	cout<<"������� m : ";
	cin>>m;
	cout<<"������� ����� �������:\na = ";
	cin>>a;
	cout<<"b = ";
	cin>>b;
	h = (b-a)/m;
	cout<<"������� ������� ����������������� ���������� n (n < "<<m+1<<") : ";
	while (true) 
	{
	cin>>n;
	if (n>m) cout<<"��������! n �� ������ ������������ m = "<<m<<"!\n������� n ������ : ";
	else break;
	}
	
	h=(b-a)/m;
}

//����� �� ����� ���������� ������
void outData()
{
	cout<<"\n\n���������� ����� \t\t\tm = "<<m<<endl;
	cout<<"������� ���������� ���������������� \tn = "<<n<<endl;
	cout<<"������� ����������������: \t\t["<<a<<"; "<<b<<"]"<<endl;
	//cout<<"����� ���������������  \t\t\tx0 = "<<x0<<endl;
	cout<<"\n\n";
}


void ForBegin(double **KP)
{
	double answer = KP[0][1];
	double t = (x0 - KP[0][0]) / h;
	double multi = t;

	for (int i=2; i < n+2; i++)
	{
		answer += KP[0][i] * multi;
		multi *= (t + 1 - i) / i;
	}

	cout<<"\n\n���������������� ������� ������� ��� ������ �������"<<endl;
	cout<<"�������� ���������� P("<<x0<<"):\t";
	cout.precision(15);
	cout<<answer<<endl;
	cout<<fixed<<"����������� �����������:\t"<<abs(answer-func(x0))<<endl;
}

void ForEnd(double **KP)
{
	double answer = KP[m][1];
	double t = (x0 - KP[m][0]) / h;
	double multi = t;

	for (int i=2; i < n+2; i++)
	{
		answer += KP[m+1-i][i] * multi;
		multi *= (t + i - 1) / i;
	}

	cout<<"\n\n���������������� ������� ������� ��� ����� �������"<<endl;
	cout<<"�������� ���������� P("<<x0<<"):\t";
	cout.precision(15);
	cout<<answer<<endl;
	cout<<fixed<<"����������� �����������:\t"<<abs(answer-func(x0))<<endl;
}

int FindZ(double **KP)
{
	for (int i = 0; i < m+1; i++)
	{
		if (x0 < KP[i][0]) return i-1;
	}
}

void ForMiddle(double **KP)
{
	int z0 = FindZ(KP);

	double answer = KP[z0][1];
	double t = (x0 - KP[z0][0]) / h;
	double multi = t;

	for (int i=2; i < n+2; i++)
	{
		answer += KP[z0 - (int)((i - 1) / 2) ][i] * multi;
		multi *= (t + pow(-1, i-1)*( (int)((i)/2) )) / i;
	}


	cout<<"\n\n���������������� ������� ������ ��� �������� �������"<<endl;
	cout<<"�������� ���������� P("<<x0<<"):\t";
	cout.precision(15);
	cout<<answer<<endl;
	cout<<fixed<<"����������� �����������:\t"<<abs(answer-func(x0))<<endl;
}

bool ChooseWay(double **table)
{
	double delta = ((n + 1)/2) * h;
	cout.precision(5);
	cout<<"������� ����� ���������������� �  � ���������:\n";
	cout<<"["<<table[0][0]<<"; "<<table[1][0]<<"]  or  ";
	cout<<"["<<a + delta<<"; "<<b - delta<<"]  or  ";
	cout<<"["<<table[m-1][0]<<"; "<<table[m][0]<<"]"<<endl;
	cin>>x0;
	cout.precision(15);
	
	if ( (x0 >= table[0][0]) && (x0 <= table[1][0]) ) ForBegin(table);
	else 
	{
		if ( (x0 >= a + delta) && (x0 <= b - delta) ) ForMiddle(table);
		else 
		{
			if ( (x0 >= table[m-1][0]) && (x0 <= table[m][0]) ) ForEnd(table);
			else {
				cout.precision(5);
				cout<<"���������� ��������������� ����� "<<x0<<" �� ������������ �����."<<endl;
				cout.precision(15);
			}
		}
	}
	bool ans = false;
	cout<<"\n������ ������ ��� ���� �����?(1 - yes; 0 - no)  "<<endl;
	cin>>ans;

	return ans;
}

void FillingKP(double **KP)
{
	for (int j = 2; j < m + 2; j++)
	{
		for (int i = 0; i < m + 2 - j; i++)
		{
			KP[i][j] = KP[i+1][j-1]-KP[i][j-1];
		}
	}
}

void Preparing()
{
	setlocale(LC_ALL, "RUSSIAN");
	cout<<"\n���������������� �� �������������� �����.";
	cout<<"\n=========================================\n";

	//cinData();
	outData();


	cout<<"\n������� �� "<<m+1<<" �������� ������� � ������� ��������� ����� �� ���������� ["<<a<<"; "<<b<<"]:\n";
	cout<<"______________________________________________________________________________\n\tx\t\tf(x)\n"<<endl;
	cout.precision(5);

	
	for(int i=0; i<m+1; i++)
	{
		KP[i] = new double [m+2];
	}
	for (int i=0; i<m+1; i++)
	{
		cout<<i<<")\t";
		KP[i][0]=a + h * i;
		KP[i][1]=func(a + h * i);
		cout<<KP[i][0]<<"\t\t"<<KP[i][1]<<endl;
	}
	cout<<"______________________________________________________________________________"<<endl;
	
}

int main()
{
	Preparing();

	//--�������
	FillingKP(KP);
	bool ans = true;
	while (ChooseWay(KP));
	cout<<endl;
	return 0;
}