// Ter_ver_lab_3_all.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//ПРОГРАММА ДЛЯ ВЫЧИСЛЕНИЯ 1 ИЗ 5 ФОРМУЛ ВСЕЙ ЛАБЫ
#include <iostream>
#include <math.h>
#include <stdio.h> 
#include <conio.h>

#define M_PI 3.14159265358979323846 

//BOOST
#include <boost/variant.hpp>
#include <boost\any.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
using namespace boost::multiprecision;

using namespace std;

//Функция факториала
cpp_bin_float_100 Fact(int n)
{
	cpp_bin_float_100 resF = 1;
	int i;

	for (i = n; i > 0; i--)
	{
		resF *= i;
	}

	return resF;
}

//Функция сочетания без повторений
cpp_bin_float_100 C(int n, int m)
{
	cpp_bin_float_100 resC = (Fact(n)) / ((Fact(m) * Fact(n - m)));
	return resC;
}

//Функция формулы Бернулли
cpp_bin_float_100 Bernully(int m, int n, cpp_bin_float_100 p)
{
	cpp_bin_float_100 q = 1 - p;
	cpp_bin_float_100 resB = C(n, m) * pow(p, m) * pow(q, n - m);
	return resB;
}

//Функция Пуассона
cpp_bin_float_100 Puasson(int m, cpp_bin_float_100 n, cpp_bin_float_100 p)
{
	cpp_bin_float_100 L = n * p;

	cpp_bin_float_100 resP = ((pow(L, m)) / Fact(m)) * exp(-L);
	return resP;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cpp_bin_float_100 result;//результат программы
	int number;//переменная на определение того, какую формулу решать(ВСЯ 3 ЛАБА)
	cout << "Введите формулу, по которой хотите решить" << endl;
	cout << "(1 - Бернулли, 2 - Полиномиальная, 3 - Пуассона," << endl;
	cout << "4 - Локальная теорема Муавра - Лапласа,\n5 - Интегральная теорема Муавра - Лапласа):" << endl;

	cin >> number;

	if (number == 1)//Бернулли
	{
		cpp_bin_float_100 p;
		int n, m, m1, m2;

		cout << "Введите p:" << endl;
		cin >> p;
		cout << "Введите n:" << endl;
		cin >> n;
		cout << "Введите m:" << endl;
		cin >> m;
		cout << "Введите m1:" << endl;
		cin >> m1;
		cout << "Введите m2:" << endl;
		cin >> m2;

		//Проверка данных
		if ((p < 0) || (p > 1) || (m1 >= m) || (m2 >= m) || (m1 == m2))
		{
			printf("invalid input data");
			return 0;
		}

		int bern;//переменная для разновидности Бернулли
		cout << "Выберите, какой случай Бернулли хотите рассмотреть:" << endl;
		cout << "1: k = m, 2: k < m, 3: k >= m, 4: m1 <= k <= m2" << endl;
		cin >> bern;

		if (bern == 1)//1 тип Бернулли(обычный, k = m)
		{
			result = Bernully(m, n, p);
			cout << result << endl;
		}

		else if (bern == 2)//2 тип Бернулли(при k < m)
		{
			//Вычисление суммы нужных исходов
			cpp_bin_float_100 sum = 0;

			for (int i = 0; i < m; i++)
			{
				sum += Bernully(i, n, p);
			}

			//Счёт нужной вероятности
			result = sum;
			cout << result << endl;
		}

		else if (bern == 3)//3 тип Бернулли(при k >= m)
		{
			//Вычисление суммы ненужных исходов
			cpp_bin_float_100 sum = 0;

			for (int i = 0; i < m; i++)
			{
				sum += Bernully(i, n, p);
			}

			//Счёт нужной вероятности
			result = 1 - sum;
			cout << result << endl;
		}

		else if (bern == 4)//4 тип Бернулли(m1 <= k <= m2)
		{
			result = 0;
			for (int i = m1; i <= m2; i++)
			{
				result += Bernully(i, n, p);
			}

			cout << result << endl;
		}
	}

	else if (number == 2)//полиномиальная
	{
		//Формула и ввод параметров
		cout << "Pn(m1, m2, ... mk) = (n! / (m1! * m2! *...*mk!)) * p1^m1 * p2^m2 *... * pk^mk" << endl;
		int n, a;
		cout << "Введите n:" << endl;
		cin >> n;

		if (n < 1)
		{
			printf("invalid input data");
			return 0;
		}

		cout << "Введите a(количество элементов, сумма которых должна быть n):" << endl;
		cin >> a;

		//Создаём массивы для дальнейшей формулы
		int* m = new int[a];
		cpp_bin_float_100* p = new cpp_bin_float_100[a];

		cout << "Введите само распределение как m1, m2, ...mk:" << endl;

		//m1, m2, ...mk
		int sum_m = 0;
		for (int i = 1; i < a + 1; i++)//
		{
			cin >> m[i];

			if (m[i] < 0)
			{
				printf("invalid input data");
				return 0;
			}

			sum_m += m[i];
		}

		if (sum_m != n)
		{
			printf("invalid input data");
			return 0;
		}

		cout << "Введите само распределение как p1, p2, ...pk:" << endl;

		//p1, p2, ...pk
		cpp_bin_float_100 sum_p = 0;
		for (int i = 1; i < a + 1; i++)//
		{
			cin >> p[i];

			if ((p[i] < 0) || (p[i] > 1))
			{
				printf("invalid input data");
				return 0;
			}

			sum_p += p[i];
		}

		if (sum_p > 1)
		{
			printf("invalid input data");
			return 0;
		}

		result = Fact(n);//предварительное значение ответа 

		for (int i = 1; i < a + 1; i++)
		{
			result *= pow(p[i], m[i]) / Fact(m[i]);
		}

		cout << result << endl;//ответ
	}

	else if (number == 3)//Пуассон
	{
		int m;
		cpp_bin_float_100 n, p;

		//Формула
		cout << "Pn(x = m) = (L^m / m!) * e^-L, где L = n*p" << endl;

		//Ввод параметров
		cout << "Введите n, затем p(желательно, чтобы их произведение было <= 10 и чтобы p было <= 0.1):" << endl;
		cin >> n;
		cin >> p;

		cpp_bin_float_100 L;

		//Выбор случая Пуассона
		int puas;
		cout << "Выберите случай Пуассона(1 - обычный, 2 - в виде неравенства a <= m <= b, где a < b):" << endl;
		cin >> puas;
		L = n * p;

		if (puas == 1) //обычный
		{
			cout << "Введите m:" << endl;
			cin >> m;
			result = Puasson(m, n, p);
			cout << result << endl;
		}

		else if (puas == 2) //неравенство
		{
			int a, b; //для неравенства
			cout << "Введите левое и правое числа для неравенства:" << endl;
			cin >> a;
			cin >> b;

			if ((a > b) || (a == b))
			{
				printf("invalid input data");
				return 0;
			}

			else
			{
				L = n * p;
				result = Puasson(a, n, p) + Puasson(b, n, p);
				cout << result << endl;
			}
		}

		else //сообщение об ошибке ввода
		{
			printf("invalid input data");
			return 0;
		}
	}

	else if (number == 4)//Локальная теорема Муавра-Лапласа
	{
		int m;
		cpp_bin_float_100 n, p, q;

		//Формула
		cout << "Pn(m) = P(x0) / sqrt(n*p*q), где x0 = (m - n*p) / sqrt(n*p*q), P(x) = exp(-x^2 / 2) / sqrt(2 * pi)" << endl;

		//Ввод данных для задачи
		cout << "Введите n(желательно > 100):" << endl;
		cin >> n;
		cout << "Введите p(чтобы n * p > 20):" << endl;
		cin >> p;
		cout << "Введите q:" << endl;
		cin >> q;
		cout << "Введите m:" << endl;
		cin >> m;

		//Проверки
		if ((p + q) != 1)
		{
			printf("invalid input data");
			return 0;
		}

		else
		{
			//Находим x0
			cpp_bin_float_100 x0 = (m - (n * p)) / (sqrt(n * p * q));

			//Находим P(x0)
			cpp_bin_float_100 P_x0 = (exp((-pow(x0,  2)) / 2)) / sqrt(2 * M_PI);

			result = P_x0 / sqrt(n * p * q);

			cout << result << endl;
		}
	}

	else if (number == 5)//Интегральная теорема Муавра-Лапласа
	{
		//n p q m1 m2
		int m1, m2, n;
		cpp_bin_float_100 p, q;

		//Вывод формулы и ввод параметров
		cout << "Pn(m1 <= X <= m2) = F(x2) - F(x1), где x2 = (m2 - n*p)/sqrt(n*p*q),\nx1 = (m1 - n*p)/sqrt(n*p*q), F(x) = (1/sqrt(2*pi)) * интеграл от 0 до x от (e^((-t^2)/2) по dt)" << endl;
		cout << "Введите m1:" << endl;
		cin >> m1;
		cout << "Введите m2:" << endl;
		cin >> m2;
		cout << "Введите n:" << endl;
		cin >> n;
		cout << "Введите p:" << endl;
		cin >> p;
		cout << "Введите q:" << endl;
		cin >> q;

		//Проверка условий для переменных
		if ((m1 > n) || (m2 > n) || (m1 >= m2) || ((p + q) != 1) || (p < 0) || (p > 1) || (q < 0) || (q > 1))
		{
			printf("invalid input data");
			return 0;
		}

		else //основной код
		{
			//Находим x2
			cpp_bin_float_100 x2 = (m2 - n * p) / sqrt(n * p * q);

			//Находим x1
			cpp_bin_float_100 x1 = (m1 - n * p) / sqrt(n * p * q);

			//Предварительный результат
			result = 1 / sqrt(2 * M_PI);

			//Дорасчёт результата
			result *= sqrt(M_PI) * (erf(x2 / sqrt(2.00)) - erf(x1 / sqrt(2.00)))/ sqrt(2.00);
			cout << result << endl;
		}
	}

	else //если выбрана не та задача
	{
		printf("invalid input data");
		return 0;
	}
}

 
 