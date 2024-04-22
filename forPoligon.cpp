// forPoligon.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	//Данный ряд по условию
	const int len = 40;
	int arr[len] = { 27, 32, 22, 32, 29, 26, 35, 31, 39, 31,
					 33, 27, 32, 26, 28, 35, 25, 35, 35, 40,
					  27, 34, 29, 30, 32, 25, 30, 31, 39, 25,
					  33, 29, 27, 32, 34, 30, 36, 31, 36, 36 };

	//Делаем вариационный(по порядку)
	sort(arr, arr + len);

	for (int i = 0; i < len; ++i)
		cout << arr[i] << ' ';

	cout << endl;

	//Делаем статистические(без повторений) Xi и Ni

	int a;//для фиксации
	int N = 0;//для счёта размерности статистических рядов
	
	a = arr[0];
	int i = 0;
	
	while (i < len)
	{
		while (a == arr[i] && i < len)
			i++;

		N++;
		a = arr[i];
	}

	printf("%d", N);
	cout << endl;

	int *x_arr = new int[N];//Xi
	int j = 0;//для индексов статистических Xi, Ni

	a = arr[0];
	i = 0;

	while (i < len)
	{
		while (a == arr[i] && i < len)
			i++;

		x_arr[j] = arr[i - 1];
		j++;
		a = arr[i];
	}

	//Ряд Xi
	for (j = 0; j < N; j++)
		cout << x_arr[j] << ' ';

	cout << endl;

	int* n_arr = new int[N];//Ni
	int count = 0;//для частот
	a = arr[0];
	i = 0;
	j = 0;

	while (i < len)
	{
		while (a == arr[i] && i < len)
		{
			i++;
			count++;
		}

		n_arr[j] = count;
		j++;
		count = 0;
		a = arr[i];
	}

	//Ряд Ni
	for (j = 0; j < N; j++)
		cout << n_arr[j] << ' ';
}

 