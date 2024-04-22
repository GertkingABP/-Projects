// Ter_ver_lab1_part_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <math.h>
#include <stdio.h> 
#include <conio.h>

//BOOST
#include <boost/variant.hpp>
#include <boost\any.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
using namespace boost::multiprecision;

#include <string.h>

using namespace std;

/*!Функция для вычисления факториала числа
* n[in] – число, факториал которого нужно вычислить
* return - факториал числа
*/
 

cpp_bin_float_100 Fact(cpp_bin_float_100 n);

int main()
{
	setlocale(LC_ALL, "Russian");
	int number;                    //номер задачи  
	int m, n;

	//Вывод на экран текcта задач
	printf("3. В отделение связи поступило m телеграмм, которые случайным образом распределяются по n каналам связи (n>m).\n");
	printf("Найти вероятность события А – на каждый канал придется не больше одной телеграммы.\n\n");
	printf("4. В отделение связи поступило m телеграмм, которые случайным образом распределяются по n каналом связи.\n");
	printf("Каналы перенумерованы. Найти вероятность того, что на 1 - ый канал попадет ровно k1 телеграмм, на 2 - ой канал – k2 телеграмм,…,\n");
	printf("на n - ый канал – kn телеграмм, причем сумма от i = 1 до n ki элементов равна m.\n\n");
	printf("Введите номер необходимой задачи:\n");
	//scanf_s("%d", &number);
	cin >> number;

	//Проверка правильности введенного номера задачи
	if ((number < 3) || (number > 4))
	{
		printf("Invalid input data");
	}

	//Выбрана задача 3
	if (number == 3)
	{
		printf("Формула для решения задачи 3: n!/((n-m!)*(n^m))\n");
		printf("Введите число n:\n");
		//scanf_s("%lf", &n);
		cin >> n;
		printf("Введите число m:\n");
		//scanf_s("%lf", &m);
		cin >> m;

		if (n < m)
		{
			printf("Invalid input data");
		}

		cpp_bin_float_100 a, b, c, d, res;
		a = Fact(n);
		b = Fact(n - m);
		c = pow(n, m);
		d = b * c;
		res = a / d;

		//printf("Результат вычислений = %lf", res);
		cout << fixed << "Результат вычислений = " << res << endl;
	}

	//Выбрана задача 4
	if (number == 4)
	{
		printf("Формула для решения задачи 3: (C из m по k1) * (C из m - k1 по k2) * ... * (C из m - k1 - ... - k(n-1) по k(n))/(n^m)\n");
		printf("Введите число каналов n:\n");
		cin >> n;

		printf("Введите число телеграмм m:\n");
		cin >> m;
		int* Mass = new int[n];

		printf("Введите распределение телеграмм(k1, k2, ...kn) по каналам\n");

		for (int i = 0; i < n; i++)
		{

			cin >> Mass[i];

			if (Mass[i] < 0)
			{
				printf("Invalid input data");
			}
		}

		cpp_bin_float_100 sum = 0;

		for (int i = 0; i < n; i++)
		{
			sum += (cpp_bin_float_100)Mass[i];
		}

		if (sum != m)
		{
			printf("Сумма кол-ва телеграмм не равна m");
			return 0;
		}

		cpp_bin_float_100 chis = 1;
		cpp_bin_float_100 znam = pow(n, m);

		for (int i = 0; i < n; i++)//числитель
		{
			chis *= Fact(m) / (Fact(Mass[i]) * Fact(m - Mass[i]));
			m -= Mass[i];
		}

		 

		cpp_bin_float_100 res;
		res = chis / znam;
		cout << fixed << "Результат вычислений = " << res;
	}
}

cpp_bin_float_100 Fact(cpp_bin_float_100 n)
{
	cpp_bin_float_100 res = 1;
	cpp_bin_float_100 i;

	for (i = n; i > 0; i--)
	{
		res *= i;
	}

	return res;
}






 