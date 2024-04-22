// Ter_ver_3_part3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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


//ФУНКЦИЯ ДЛЯ ИНТЕГРАЛЬНОЙ ТЕОРЕМЫ
cpp_bin_float_100 Integr(int m1, int m2, int n, cpp_bin_float_100 p, cpp_bin_float_100 q)
{
	cpp_bin_float_100 resIntegr;

	//Находим x2
	cpp_bin_float_100 x2 = (m2 - n * p) / sqrt(n * p * q);

	//Находим x1
	cpp_bin_float_100 x1 = (m1 - n * p) / sqrt(n * p * q);

	//Предварительный результат
	resIntegr = 1 / sqrt(2 * M_PI);

	//Дорасчёт результата
	resIntegr *= sqrt(M_PI) * (erf(x2 / sqrt(2.00)) - erf(x1 / sqrt(2.00))) / sqrt(2.00);
	return resIntegr;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cpp_bin_float_100 result;//результат программы
	int number;//переменная на определение того, какую задачу по интегральной решить
	//n p q m1 m2
	int m1, m2, n;
	cpp_bin_float_100 p, q;

	//Вывод формулы для задач по интегральной
	cout << "ФОРМУЛА ИНТЕГРАЛЬНОЙ ТЕОРЕМЫ:Pn(m1 <= X <= m2) = F(x2) - F(x1), где x2 = (m2 - n*p)/sqrt(n*p*q),\nx1 = (m1 - n*p)/sqrt(n*p*q), F(x) = (1/sqrt(2*pi)) * интеграл от 0 до x от (e^((-t^2)/2) по dt)\n" << endl;


	cout << "1.Вероятность поражения стрелком мишени равна 0.7.\nНайти вероятность того, что при 100 выстрелах\nмишень будет поражена от 65 до 80 раз.\n" << endl;

	cout << "2.В институте обучается 1000 студентов. В столовой имеется 105 посадочных мест. Каждый студент отправляется в столовую на большой перемене с вероятностью 0,1. Какова вероятность того, что в обычный учебный день:\nа) столовая будет заполнена не более чем на две трети; б)посадочных мест на всех не хватит.\n" << endl;

	cout << "Введите задачу которую хотите решить:" << endl;

	cin >> number;

	if (number == 1)//простая
	{
		p = 0.7;
		q = 0.3;
		n = 100;
		m1 = 65;
		m2 = 80;

		result = Integr(m1, m2, n, p, q);
		cout << result << endl;
	}


	else if (number == 2)//посложнее
	{
		p = 0.1;
		q = 0.9;
		n = 1000;
		//2/3 мест
		int places = 105 * 2 / 3;

		//Пункт а
		m1 = 0;
		m2 = places;
		result = Integr(m1, m2, n, p, q);
		cout << "а)";
		cout << result << endl;

		//Пункт б
		m1 = 106;
		m2 = n;
		result = Integr(m1, m2, n, p, q);
		cout << "б)";
		cout << result << endl;
	}

	else
	{
		printf("invalid input data");
		return 0;
	}
}

 