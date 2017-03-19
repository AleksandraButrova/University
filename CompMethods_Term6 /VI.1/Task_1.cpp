/* Задание 1.
Размностный метод для обыкновенного дифференциального уравнения второго порядка.
Метод прогонки.*/

#include <iostream>
#include <math.h>

using namespace std;

// Данные варианта 1
double alpha = 0.1, 
		A = 1 / alpha,
		B = 1 / (1 + alpha),
		alpha_0 = 1,
		alpha_1	= -2,
		betta_0 = 1,
		betta_1 = 0,
		a = 0,
		b = 1, 
		h;
int n;
double p(double x){
	return 1;
}
double q(double x){
	return -(x*x + alpha);
}
double r(double x){
	return -2*x;
}
double f(double x){
	return 2 * (3*x*x - alpha) / ( (x*x + alpha) * (x*x + alpha) * (x*x + alpha)); 
}

// Векторы, которые будем использовать
double	*diag_a,	// диагонали трехдиагональной матрицы А
		*diag_b,
		*diag_c,
		*d,			// вектор свободных членов
		*x,			// вектор неизвестных
		*m,			// поргоночные коэффициенты
		*k,
		*error;		// невязка
			
// Функции решения
void Thomas(){
	m[0] = -diag_c[0] / diag_b[0];
    k[0] = d[0] / diag_b[0];
    cout<<"\n\nПрогоночные коэффициенты:\n";
    cout<<"___m_______________k____\n";
    cout<<m[0]<<"\t"<<k[0]<<endl;
    for (int i = 0; i < n; i++)
    {
		m[i + 1] = (-diag_c[i]) / (diag_a[i] * m[i] + diag_b[i]);
        k[i + 1] = (d[i] - diag_a[i] * k[i]) / (diag_a[i] * m[i] + diag_b[i]);
        cout<<m[i+1]<<"  \t"<<k[i+1]<<endl;
    }
}
void samohT(){
	x[n-1] = (d[n] - diag_a[n] * k[n]) / (diag_a[n] * m[n] + diag_b[n]);
            for (int i = n-1; i > 0; i--)
                x[i - 1] = m[i] * x[i] + k[i];
}
void Error()
{
	for (int i = 0; i <= n; i++)
	{
		if (i > 0 && i < n)
			error[i] = (diag_a[i] * x[i - 1] + diag_b[i] * x[i] + diag_c[i] * x[i + 1]) - d[i];
		else
        {
			if (i == 0)
				error[i] = diag_b[i] * x[i] + diag_c[i] * x[i + 1] - d[i];
			else
				error[i] = diag_a[i] * x[i - 1] + diag_b[i] * x[i] - d[i];
		}
	}
}
void first()
{
	 diag_a[0] = 0;
     diag_b[0] = h * alpha_0 - alpha_1;
     diag_c[0] = alpha_1;
     d[0] = h * A;
     
	 diag_a[n] = -betta_1;
     diag_b[n] = h * betta_0 + betta_1;
     diag_c[n] = 0;
     d[n] = h * B;
            
	 for (int i = 1; i < n; i++)
     {
		 diag_a[i] = p(a + i * h) - 0.5 * q(a + i * h) * h;
		 diag_b[i] = - 2.0 * p(a + i * h) + r(a + i * h) * h * h;
		 diag_c[i] = p(a + i * h) + 0.5 * q(a + i * h) * h;
		 d[i] = f(a + i * h) * h * h;
     }

}
void second()
{
	 for (int i = 1; i < n; i++)
	{
		diag_a[i] = p(a + i * h) - 0.5 * q(a + i * h) * h;
        diag_b[i] = -2.0 * p(a + i * h) + r(a + i * h) * h * h;
        diag_c[i] = p(a + i * h) + 0.5 * q(a + i * h) * h;
		d[i] = f(a + i * h) * h * h;
    }
		diag_a[0] = 0;
        diag_b[0] = 2 * h * alpha_0 + alpha_1 * ((diag_a[1] / diag_c[1]) - 3);
        diag_c[0] = alpha_1 * ((diag_b[1] / diag_c[1]) + 4);
        d[0] = 2 * h * A + alpha_1 * (d[1] / diag_c[1]);
        
		diag_a[n] = -betta_1 * ((diag_b[n - 1] / diag_a[n - 1]) + 4);
        diag_b[n] = 2 * h * betta_0 + betta_1 * (3 - (diag_c[n - 1] / diag_a[n - 1]));
        diag_c[n] = 0;
        d[n] = 2 * h * B - betta_1 * (d[n - 1] / diag_a[n - 1]);
}
void coutAd()
{
	cout<<"Расширенная матрица (A|d):\n";
	for (int i = 0; i < n+1; i++)
	{
		for (int j = 0; j < n+2; j++)
		{
			if (i == j+1) cout<<diag_a[i]<<"   ";
			else if (i == j  ) cout<<diag_b[i]<<"   ";
			else if (i == j-1) cout<<diag_c[i]<<"   ";
			else if (j == n + 1 ) cout<<d[i]<<endl;
			else cout<<"0   ";
		}
}
}

int main(){
	cout.precision(6);
	setlocale (LC_ALL, "RUSSIAN");
	cout<<"Задание 1.\nРазностный метод для обыкновенного дифференциального уравнения второго порядка.\nМетод прогонки.\n";
	cout<<"==============================================================================\n\n";
	
	n = 0;
	h = 0;

	while ( n < 1 ){
		cout<<"Введите подрядок системы или введите 0 для выхода:\t";
		cin>>n;
		if (n == 0) return 0;
		if (n < 1 ) 
			cout<<"Введите значение n > 0 !\n";
	}

	while (n != 0)
	{
		
		h = (b - a) / n;
		n++;

		diag_a = new double [n + 1];	
		diag_b = new double [n + 1];
		diag_c = new double [n + 1];
		d = new double [n + 1];
		x = new double [n + 1];
		m = new double [n + 1];			
		k = new double [n + 1];
		error = new double [n + 1];

	
		cout<<"Способ 1.\n\n";
		first();
		//coutAd();
		Thomas();
		samohT();
		Error();
		cout<<"\nТочка_____Вектор неизвестных______Невязка\n";
		for (int i = 0; i < n; i++)
			cout<<a+i*h<<"\t"<<x[i]<<"  \t\t"<<error[i]<<endl;
		cout<<"\nТочное решение:\n";
		for (double i = 0; i < n; i ++){
			cout<<a + i*h<<"\t"<< 1.0 / ((a+i*h) * (a+i*h) + alpha)<<endl;	
		}
		//cout<<1.0 / (a * a + alpha)<<"\t"<<1.0 / (b * b + alpha)<<endl;
		

	
		cout<<"\n\nСпособ 2.\n";
   
		second();
		//coutAd();
		Thomas();
		for (int i = 0; i < n+1; i++)
			x[i] = 0;

		samohT();
		Error();
		cout<<"\nТочка_____Вектор неизвестных______Невязка\n";
		for (int i = 0; i < n; i++)
			cout<<a+i*h<<"\t"<<x[i]<<"  \t\t"<<error[i]<<endl;
		//cout<<h<<endl;
		cout<<"\nТочное решение:\n";
		for (double i = 0; i < n; i ++){
			cout<<a + i*h<<"\t"<< 1.0 / ((a+i*h) * (a+i*h) + alpha)<<endl;	
		} 
		//cout<<1.0 / (a * a + alpha)<<"\t"<<1.0 / (b * b + alpha)<<endl;
		
		n = 0;
		while ( n < 1 ){
			cout<<"Введите подрядок системы или введите 0 для выхода:\t";
			cin>>n;
			if (n == 0) return 0;
			if (n < 1 ) 
				cout<<"Введите значение n > 0 !\n";
		}
	}
	return 0;
}