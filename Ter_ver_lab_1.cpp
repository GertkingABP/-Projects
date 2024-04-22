// Ter_ver_lab_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
 
#include <iostream>
#include <math.h>
#include <stdio.h> 
#include <conio.h>

//BOOST
#include <boost/variant.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
using namespace boost::multiprecision;

using namespace std;
/*!Функция для вычисления факториала числа
* n[in] – число, факториал которого нужно вычислить
* return - факториал числа
*/
cpp_bin_float_100 Fact(cpp_bin_float_100 n);

int main()
{
	//Ввод переменных
	setlocale(LC_ALL, "Russian");
	int F;
	cpp_bin_float_100 m, n, h, C, C1, C2, A;

	printf("Введите тип комбинации (1 или 2):\n");
	printf("1 - сочетание без повторения, 2 - размещение с повторением\n");
	scanf_s("%d", &F);

	//Завершение программы, если выбрано не 1 или 2
	if ((F > 2) || (F < 1)) {
		printf("Invalid input data");
		return 0;
	}

	//Основной алгоритм
	//1.Сочетание без повторения
	if (F == 1) {
		printf("C = n! / (m! * (n - m)!\n");
		printf("Введите число n:\n");
		cin >> n;
		printf("Введите число m:\n");
		cin >> m;

		h = n - m;
		C1 = Fact(n);
		C2 = Fact(m) * Fact(h);
		C = C1 / C2;
		cout << fixed << "Результат вычислений = " << C;
	}

	//2.Размещение с повторением
	else if (F == 2)
	{
		printf("A` = n^m\n");
		printf("Введите число n:\n");
		cin >> n;
		printf("Введите число m:\n");
		cin >> m;
		A = pow(n, m);
		cout << fixed << "Результат вычислений = " << A;
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