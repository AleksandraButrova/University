/*
Задание 4.
Задача обратного итнерполирования.
Нахождение таблично-заданной функции
по формулам численного дифференцирования
*/

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//	Данные из примера
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

/*-----Всё для подготовительного этапа-----*/

//Вывод параметров на экран
void outData()
{
	cout << "\n\nКоличество узлов \t\t\tm = " << m << endl;
	cout << "Степень многочлена интерполирования \tn = " << n << endl;
	cout << "Отрезок интерполирования: \t\t[" << a << "; " << b << "]" << endl;
	//cout << "Точка обратного интеполирования\t\tF = " << F << endl;
	cout << "\n\n";
}
// Считываем данные с консоли
void cinData()
{
	cout << "Введите m : ";
	cin >> m;
	cout << "Введите концы отрезка:\na = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	h = (b - a) / m;
	cout << "Введите степени интерполяционного многочлена n : ";
	while (true)
	{
		cin >> n;
		if (n > m) cout << "Внимание! n не должно превосходить m = " << m << "!\nВведите n занова : ";
		else break;
	}
	h = (b - a) / m;
}
//	Подготовительный этап
void Preparing(double **table)
{
	bool ans;

	cout<<"Введите 0, чтобы воспользоваться данными из примера.\nВведите 1, чтобы ввести свои данные.\n";
	cin>>ans;
	if ( ans ) cinData();
	outData();

	//	Заполнение и вывод полной таблицы x - f(x)
	cout << "\nТаблица из " << m + 1 << " значений функции в попарно различных узлах из промежутка [" << a << "; " << b << "]:\n";
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

/*------------------Часть 1.---------------*/
/*-----------Обратная интерполяция.--------*/

// Вспомогательные функции
//	Меняем столбцы x и f(x) местами для первого метода решения
void SwapColumn(double **table)
{
	for (int i = 0; i < m + 1; i++)
		swap(table[i][0], table[i][1]);
}
// Сортируем таблицу по ближайшим к x0 точкам
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
//	Вспомогательная функция для метода Лагранжа
double Phi(double x, int j, double **table)
{
	double result = 1;
	for (int i = 0; i < n; i++)
	{
		if (j != i) 	result *= (x - table[i][0]);
	}
	return result;
}
//	Значение полинома в форме Лагранжа
double Lagrange(double **table, double x0)
{
	double result = 0;
	for (int j = 0; j < n; j++)
	{
		result += table[j][1] * Phi(x0, j, table) / Phi(table[j][0], j, table);
	}
	return result;
}


/*--------------Первый способ.-------------*/
//	Меняем столбцы x и f(x) местами
//	Находим Pn для f(x)
//	Интерполируем методом Лагранжа
void WayOne(double **table)
{
	SwapColumn(table);
	Sorting(table, 0, F);

	//	Выводим ответ
	cout.precision(15);
	double calculate = Lagrange(table, F);
	cout << fixed << "\n1 способ: " << calculate << endl;
	cout << fixed << "Модуль невязки:\t" << abs(f(calculate) - F) << endl;

	SwapColumn(table);
	Sorting(table, 0, a);
}



/*--------------Второй способ.-------------*/
//	Строим интерполяционный многочлен Pn для данной таблицы
//	Решаем уравнение Pn(x) = F методом бисекций
double Сlarification(double **table, double start, double end)
{
	if (abs(Lagrange(table, end) - Lagrange( table, start)) < E)
		return start;

	double mid = (start + end) / 2.0;

	if ((Lagrange(table, start) - F) * (Lagrange(table, mid) - F) < 0)
		return Сlarification(table, start, mid);
	else
	{
		if ( Lagrange(table, start) - F == 0 )
			return start;
		else if ( Lagrange(table, end) - F == 0 )
			return end;
	}
	return Сlarification(table, mid, end);
}
double Bisection (double **table)
{	
	for (int i = 0; i < n ; i++)
	{
		if ((table[i][1] - F) * (table[i + 1][1] - F) <= 0)
			return Сlarification(table, table[i][0], table[i + 1][0]);
	}

}
double WayTwo(double **table)
{
	double min = INT_MAX, max = INT_MIN;


	//	Выводим ответ
	for (int i = 0; i < m + 1; i++ )
	{
		if (table[i][1] < min ) min = table[i][1];
		if (table[i][1] > max ) max = table[i][1];
	}
	
	Sorting(table, 1, F);

	if ( ( F < min ) || (max < F ) ) 
	{
		cout<<fixed<<"\n2 способ.\nДанным способом невозможно интерполировать значение F = "<<F<<".\nВыберете значение из промежутка [ "<< min <<" ; "<<max<<" ] :"<<endl;
		return -1;
	}
	
	cout.precision(15);
	double calculate = Bisection(table);
	cout << fixed << "\n2 способ: " << calculate << endl;
	cout << fixed << "Модуль невязки:\t" << abs(f(calculate) - F) << endl;
	return 0;
}



/*------------------Часть 2.---------------*/
//	Формулы численного дифференцирования
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

//	Вывод таблицы из части 2
void CoutTableDiff(double **table)
{
	cout<<"Таблица производных данной функции во всех узлах"<<endl;
	cout.precision(8);
	//cout << "Rf(a) = " << h*h << endl;
	cout << "\nx\tf\t f'чд\t(f'чд-f')  f''чд  (f''чд-f'')\n";

	for (int i = 0; i < m + 1; i++)
	{

		// x и f(x)
		cout.precision(3);
		cout << fixed << table[i][0];
		cout.precision(5);
		cout << " | " << table[i][1] << " | ";
		// f', f'' и невязки
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
	//	Вывод названия лаборатной работы
	setlocale(LC_ALL, "RUSSIAN");
	cout << "\nЗадание 4.\nЗадача обратного интерполирования.\nНахождение таблично-заданной функции\nпо формулам численного дифференцирования";
	cout << "\n=========================================\n";


	// Таблица из  x и y;
	double **table = new double *[m + 1];
	for (int i = 0; i < m + 1; i++) table[i] = new double[2];

	Preparing(table);

	int ans = 1; 

	// Обратная интерполяция
	while (ans != 0)
	{
		cout << "\nВведите точку обратного интерполирования F : ";
		cin >> F;
		WayOne(table);
		WayTwo(table);
		cout<<"\nЕщё точку? (1 - да; 0 - нет):   ";
		cin >> ans;
		cout<<endl;
	}
	

	// Талица со значениями производных
	//CoutTableDiff(table);



	return 0;
}