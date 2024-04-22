// Ter_ver_3_part1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//ПРОГРАММА ДЛЯ ВЫЧИСЛЕНИЯ 1 ИЗ 5 ФОРМУЛ ВСЕЙ ЛАБЫ
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

int main()
{
	setlocale(LC_ALL, "Russian");
	cpp_bin_float_100 result;//результат программы
	int number;//переменная на определение того, какую задачу Бернулли решить

	cpp_bin_float_100 p, q;//вероятность события и обратная
	int n, m, m1, m2;//число испытаний и кол-во раз, когда произойдёт событие с p 

	cout << "ФОРМУЛА БЕРНУЛЛИ: Pn(m) = (C из n по m) * p^m * (1 - p)^n - m\n" << endl;

	//1 задача(при k = m)
	cout << "1.Вероятность выигрыша по любой облигации займа за всё время его действия равна 0.25.\nКакова вероятность того, что человек, приобретя 8 облигаций, выиграет по 6 из них?\n" << endl;
	
	//2 задача(посложнее, для всех типов Бернулли)
	cout << "2.Монету бросают 5 раз. Найти вероятность того, что герб выпадет:\nа)менее 2 раз, б)не менее 2 раз, в)ровно 2 раза, г)от 0 до 1 раза.\n" << endl;

	cout << "Введите задачу (по Бернулли), которую хотите решить:" << endl;
	cin >> number;

	if (number == 1)//простая при k = m
	{
		p = 0.25;
		q = 1 - p;
		n = 8;
		m = 6;
	    m1 = 0;
		m2 = m1;
		result = Bernully(m, n, p);
		cout << result << endl;
	}

	else if (number == 2)//для всех случаев
	{
		p = 0.5;
		q = 1 - p;
		n = 5;
		m = 2;
		m1 = 0;
		m2 = 1;

		//а)k < m
		//Вычисление суммы нужных исходов
		cpp_bin_float_100 sum = 0;

		for (int i = 0; i < m; i++)
		{
			sum += Bernully(i, n, p);
		}

		//Счёт нужной вероятности
		result = sum;
		cout << "а)";
		cout << result << endl;


		//б)k >= m
		//Вычисление суммы ненужных исходов
		sum = 0;

		for (int i = 0; i < m; i++)
		{
			sum += Bernully(i, n, p);
		}

		//Счёт нужной вероятности
		result = 1 - sum;
		cout << "б)";
		cout << result << endl;

		//в)k = m
		result = Bernully(m, n, p);
		cout << "в)";
		cout << result << endl;

		//г)m1 <= k <= m2
		result = 0;
		for (int i = m1; i <= m2; i++)
		{
			result += Bernully(i, n, p);
		}

		cout << "г)";
		cout << result << endl;
	}

	else
	{
		printf("invalid input data");
		return 0;
	}
}

 