#include <vector>



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

// 2. ��������� ������ ��������� �� ��������� ��������
void BisectionMethod (vector <double> a, vector <double> b)
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

void FindRoot()
{;}
	int main()
{return 0;}