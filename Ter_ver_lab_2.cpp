// Ter_ver_lab_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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

int main()
{
	int number;
	setlocale(LC_ALL, "Russian");

	//Задачи

	//1-я
	cout << "1. Электрическая цепь из пяти элементов составлена по схеме, приведенной на рисунке. Найти вероятность" << endl;
	cout << "разрыва цепи, предполагая, что отказы отдельных элементов независимы и равны q(i) (i = 1, 2, 3, 4, 5)" << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << "                                                         " << endl;
	cout << "           -------------           -------------                                   " << endl;
	cout << "   |-------|     1     |-----------|     4     |-------|                " << endl;
	cout << "   |       -------------           -------------       |                            " << endl;
	cout << "   |                   -------------                   |     " << endl;
	cout << "*----------------------|     3     |---------------------->                                           " << endl;
	cout << "   |                   -------------                   |                " << endl;
	cout << "   |       -------------           -------------       |                            " << endl;
	cout << "   |-------|     2     |-----------|     5     |-------|                " << endl;
	cout << "           -------------           -------------                                   " << endl;
	cout << "                                                         " << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << "\n" << endl;

	//2-я
	cout << "2. Один студент выучил m1 из n вопросов программы, а второй m2." << endl;
	cout << "Каждому из них задают по три вопроса. Найти вероятность того, что " << endl;
	cout << "не менее, чем на два вопроса правильно ответят: a) оба студента;" << endl;
	cout << "b) только первый студент; c) только один из них; d) хотя бы один из студентов." << endl;
	cout << "\n" << endl;

	//Выбор задачи
	cout << "Введите номер задачи, которую хотите решить" << endl;
	cin >> number;

	if ((number < 1) || (number > 2))
	{
		printf("invalid input data");
	}

	//Решение 1 задачи
	else if (number == 1)
	{
		cpp_bin_float_100 p_b; //искомая вероятность разрыва цепи
		cpp_bin_float_100 q1, q2, q3, q4, q5; //элементы

		cout << "Введите q1" << endl;
		cin >> q1;

		cout << "Введите q2" << endl;
		cin >> q2;

		cout << "Введите q3" << endl;
		cin >> q3;

		cout << "Введите q4" << endl;
		cin >> q4;

		cout << "Введите q5" << endl;
		cin >> q5;

		//Проверка элементов
		if ((q1 < 0) || (q1 > 1) || (q2 < 0) || (q2 > 1) || (q3 < 0) || (q3 > 1) || (q4 < 0) || (q4 > 1) || (q5 < 0) || (q5 > 1))
		{
			printf("invalid input data");
		}

		//Основной алгоритм для данной цепи
		else
		{
			cout << "p_b = (1 - (1 - q1) * (1 - q4)) * q3 * (1 - (1 - q2) * (1 - q5))" << endl;
			p_b = (1 - ((1 - q1) * (1 - q4))) * q3 * (1 - ((1 - q2) * (1 - q5)));
			cout << p_b;
		}
	}

	//Решение 2 задачи
	else if (number == 2)
	{
		cpp_bin_float_100 m1, m2, n; //сколько выучил 1 и 2 студенты и общее кол-во вопросов в экзамене
		cpp_bin_float_100 p1, p2; //Вероятность, что ответит 1 и 2 студенты соответственно
		cpp_bin_float_100 pA, pB, pC, pD; //Вероятности событий из пунктов

		cout << "Введите m1" << endl;
		cin >> m1;

		cout << "Введите m2" << endl;
		cin >> m2;

		cout << "Введите n" << endl;
		cin >> n;

		//Проверка значений
		if ((m1 > n) || (m2 > n) || (m1 < 0) || (m2 < 0) || (n < 0))
		{
			printf("invalid input data");
		}

		//Основной алгоритм
		else
		{
			//Счёт вероятностей(они нужны для всех 4-х пунктов)	
			cout << "p1 = (m1^2 / n^2) * (3 - 2*m1 / n)" << endl;
			cout << "p2 = (m2^2 / n^2) * (3 - 2*m2 / n)" << endl;
			p1 = ((m1 * m1) / (n * n)) * (3 - (2 * m1 / n));
			p2 = ((m2 * m2) / (n * n)) * (3 - (2 * m2 / n));
			cout << p1 << endl;
			cout << p2 << endl;

			//Выбор пункта
			number = 0;
			cout << "Введите пункт, который хотите решить(a-1, b-2, c-3, d-4)" << endl;
			cin >> number;

			if (number == 1) //a
			{
				cout << "pA = p1 * p2" << endl;
				pA = p1 * p2;
				cout << pA << endl;
			}

			else if (number == 2) //b
			{
				cout << "pB = p1 * (1 - p2)" << endl;
				pB = p1 * (1 - p2);
				cout << pB << endl;
			}

			else if (number == 3) //c
			{
				cout << "pC = (p1 * (1 - p2)) + (p2 * (1 - p1))" << endl;
				pC = (p1 * (1 - p2)) + (p2 * (1 - p1));
				cout << pC << endl;
			}

			else if (number == 4) //d
			{
				cout << "pD = 1 - ((1 - p1) * (1 - p2))" << endl;
				pD = 1 - ((1 - p1) * (1 - p2));
				cout << pD << endl;
			}

			else if ((number < 1) || (number > 4)) //неверный пункт
			{
				printf("invalid input data");
			}
		}
	}
}







 