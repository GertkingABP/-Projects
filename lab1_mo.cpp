//ВАРИАНТ 5 (МЕТОДЫ: ДЕЛЕНИЯ ПОПОЛАМ, ПАУЭЛЛА)
/*УРАВНЕНИЯ:  1  (x − 1)^2
			  2  4*x^3 - 8*x^2 - 11*x + 5
			  3  x + (3/x^2)
			  4  (x + 2.5) / (4 - x^2)
			  5  -sin(x) - (sin(3*x) / 3)
			  6  -2*sin(x) - sin(2*x) - (2*sin(3*x) / 3))  */

#include <iomanip>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <algorithm>

//BOOST
#include <boost/variant.hpp>
#include <boost\any.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
using namespace boost::multiprecision;

cpp_bin_float_100 function_6_ex(int num, cpp_bin_float_100 x)//функция вычисления 1 из 6 функции от заданного x
{
	cpp_bin_float_100 answer = 0;//ответ

	if (num == 1)
		answer = pow((x - 1), 2);

	else if (num == 2)
		answer = (4 * pow(x, 3)) - (8 * pow(x, 2)) - (11 * x) + 5;

	else if (num == 3)
	{
		if (x == 0)
		{
			x = 0.00001;
		}

		answer = x + (3 / (pow(x, 2)));
	}

	else if (num == 4)
	{
		if (x == -2)
			x = -1.99999;

		else if (x == 2)
			x = 1.99999;
		
		else
			;

		answer = (x + 2.5) / (4 - (pow(x, 2)));
	}

	else if (num == 5)
		answer = -sin(x) - (sin(3 * x) / 3);

	else if (num == 6)
		answer = -2 * sin(x) - sin(2 * x) - (2 * sin(3 * x) / 3);
	
	else
		;

	return answer;
}

int main()
{
	cpp_bin_float_100 x0, x1, x2, x3, x4, xl, xk, xkm, mas4x[4], mas3x[3], func_x0, func_x1, func_x2, func_x3, func_x4, func_x0hp, func_x0hm, func_xk, func_xkm, h, e, a, b, d, answer_x, answer_fx;
	int choosen_alg, num_function, k;
	setlocale(LC_ALL, "RUS");

	//Ввод данных и проверка их корректности
	cout << "Выберите алгоритм: 1 - деление пополам, 2 - Пауэлл." << endl;
	cin >> choosen_alg;

	if (choosen_alg == 1)
	{
		cout << endl << "Выбран метод деления пополам." << endl << endl;
	}

	else if (choosen_alg == 2)
	{
		cout << endl << "Выбран метод Пауэлла." << endl << endl;
	}

	else
	{
		cout << endl << "Вы ввели что-то другое..." << endl << endl;
		return 0;
	}

	cout << "Введите начальную точку x0 и шаг h:" << endl;
	cin >> x0 >> h;

	if (h < 0.5 || h > 1)
	{
		cout << endl << "Шаг h должен быть от 0.5 до 1." << endl;
		return 0;
	}

	cout << endl << "Введите точность e:" << endl;
	cin >> e;

	if (e < 0 || e > 1)
	{
		cout << endl << "Точность e должна быть от 0 до 1." << endl;
		return 0;
	}

	//Алгоритм Дэвиса-Свенна-Кэмпи для нахождения точек а и б
	cout << endl << "Выберите функцию: (1) (x - 1)^2;\t(2) 4*x^3 - 8*x^2 - 11*x + 5;\t(3) x + (3 / x ^ 2);" << endl << "(4) (x + 2.5) / (4 - x^2);\t(5) - sin(x) - (sin(3 * x) / 3);\t(6) - 2*sin(x) - sin(2*x) - (2*sin(3*x) / 3)" << endl;
	cin >> num_function;

	if (num_function != 1 && num_function != 2 && num_function != 3 && num_function != 4 && num_function != 5 && num_function != 6)
	{
		cout << endl << "Вы ввели что-то другое..." << endl << endl;
		return 0;
	}

	else//сам дск
	{
		func_x0 = function_6_ex(num_function, x0);
		func_x0hp = function_6_ex(num_function, x0 + h);
		func_x0hm = function_6_ex(num_function, x0 - h);

		if (func_x0 > func_x0hp)
		{
			a = x0;
			k = 2;

		point1:
			xk = x0 + (pow(2, k - 1) * h);
			xkm = x0 + (pow(2, k - 1 - 1) * h);
			func_xk = function_6_ex(num_function, xk);
			func_xkm = function_6_ex(num_function, xkm);

			if (func_xkm <= func_xk)
			{
				if (h > 0)
					b = xk;
				else
					a = xk;
			}

			else
			{
				if (h > 0)
					a = xkm;
				else
					b = xkm;

				k++;
				goto point1;
			}
		}

		else
		{
			if (func_x0hm >= func_x0)
			{
				a = x0 - h;
				b = x0 + h;
			}

			else
			{
				b = x0;
				h = -h;
				k = 2;
				goto point1;
			}
		}
	}

	cout << endl << "До решения одним из методов по алгоритму ДСК: a = " << a << "; b = " << b << endl;

	if (choosen_alg == 1)//решение 1 методом
	{
		cout << endl << "Деление пополам:" << endl << endl;
		cout << "Введите d:" << endl;
		cin >> d;

		if (d <= 0 || d >= e)
		{
			cout << "Значение константы d вышло за пределы." << endl;
			return 0;
		}

		else
		{
		point2:
			x1 = 0.5 * (a + b) - d;
			x2 = 0.5 * (a + b) + d;
			func_x1 = function_6_ex(num_function, x1);
			func_x2 = function_6_ex(num_function, x2);

			if (func_x1 <= func_x2)
				b = x2;

			else
				a = x1;

			if (e > ((b - a) / 2))
			{
				answer_x = (a + b) / 2;
			}

			else
				goto point2;
		}
	}

	else if (choosen_alg == 2)//решение 2 методом(+)
	{
		cout << endl << "Метод Пауэлла:" << endl;

		if (e > 0)
		{
			x1 = a;
			x2 = 0.5 * (a + b);
			x3 = b;

		point3:
			func_x1 = function_6_ex(num_function, x1);
			func_x2 = function_6_ex(num_function, x2);
			func_x3 = function_6_ex(num_function, x3);

			x4 = 0.5 * (((pow(x2, 2) - pow(x3, 2)) * func_x1 + ((pow(x3, 2) - pow(x1, 2)) * func_x2) + ((pow(x1, 2) - pow(x2, 2)) * func_x3)) / (((x2 - x3) * func_x1) + ((x3 - x1) * func_x2) + ((x1 - x2) * func_x3)));
			func_x4 = function_6_ex(num_function, x4);

			if (func_x1 < func_x2 && func_x1 < func_x3)
				xl = x1;

			else if (func_x2 < func_x1 && func_x2 < func_x3)
				xl = x2;

			else if (func_x3 < func_x1 && func_x3 < func_x2)
				xl = x3;

			else
				;

			if (abs(x4 - xl) <= e)
				answer_x = x4;

			else
			{
				mas4x[0] = x1; //перенумерация, не по возрастанию
				mas4x[1] = x2;
				mas4x[2] = x3;
				mas4x[3] = x4;

				if (func_x4 > func_x1 && func_x4 > func_x2 && func_x4 > func_x3) //max - f(x4)
				{
					mas3x[0] = mas4x[0];
					mas3x[1] = mas4x[1];
					mas3x[2] = mas4x[2];

					sort(begin(mas3x), end(mas3x));

					x1 = mas3x[0];
					x2 = mas3x[1];
					x3 = mas3x[2];
				}

				else if (func_x3 > func_x1 && func_x3 > func_x2 && func_x3 > func_x4) //max - f(x3)
				{
					mas3x[0] = mas4x[0];
					mas3x[1] = mas4x[1];
					mas3x[2] = mas4x[3];

					sort(begin(mas3x), end(mas3x));

					x1 = mas3x[0];
					x2 = mas3x[1];
					x3 = mas3x[2];
				}

				else if (func_x2 > func_x1 && func_x2 > func_x3 && func_x2 > func_x4) //max - f(x2)
				{
					mas3x[0] = mas4x[0];
					mas3x[1] = mas4x[2];
					mas3x[2] = mas4x[3];

					sort(begin(mas3x), end(mas3x));

					x1 = mas3x[0];
					x2 = mas3x[1];
					x3 = mas3x[2];
				}

				else if (func_x1 > func_x2 && func_x1 > func_x3 && func_x1 > func_x4) //max - f(x1)
				{
					mas3x[0] = mas4x[1];
					mas3x[1] = mas4x[2];
					mas3x[2] = mas4x[3];

					sort(begin(mas3x), end(mas3x));

					x1 = mas3x[0];
					x2 = mas3x[1];
					x3 = mas3x[2];
				}

				else
					;

				goto point3;
			}
		}

		else
		{
			cout << "Для данного метода е должна быть больше 0." << endl;
			return 0;
		}
	}

	answer_fx = function_6_ex(num_function, answer_x);
	cout << setprecision(4);
	cout << endl << "Ответ: x = " << answer_x << "; f(x) = " << answer_fx << endl;
}
