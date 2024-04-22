
#include <iostream>
#include <omp.h>

using namespace std;
const int N = 200000000;
int mas[N];
int mas2[N];

void quicksort(int* a, int left, int right) {
    int i = left, j = right, tmp;
    int pivot = a[(left + right) / 2];
    
    while (i <= j) 
    {
        while (a[i] < pivot)
            i++;
    
        while (a[j] > pivot)
            j--;
        
        if (i <= j)
        {
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    };

    if (left < j)
        quicksort(a, left, j);

    if (i < right)
        quicksort(a, i, right);
}

void quicksort_parallel(int* mas, int left, int right)
{
    //omp_set_num_threads(number_threads);
    int i = left, j = right, tmp;
    int pivot = mas[(left + right) / 2];

    while (i <= j) 
    {
        while (mas[i] < pivot)
            i++;
        
        while (mas[j] > pivot)
            j--;
        
        if (i <= j)
        {
            tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
            i++;
            j--;
        }
    };

    if (right - left >= N / 8)
    {
#pragma omp parallel sections 
        {
#pragma omp section
            {
                if (left < j)
                    quicksort_parallel(mas, left, j);
            }

#pragma omp section
            {
                if (i < right)
                    quicksort_parallel(mas, i, right);
            }
        }
    }

    else 
    {
        if (left < j)
            quicksort_parallel(mas, left, j);

        if (i < right)
            quicksort_parallel(mas, i, right);
    }
}

int main()
{
    int t = 0;
    while (t < 10)
    {
        //int num_threads = 16;
        setlocale(LC_ALL, "Russian");
        double start_time;
        double end_time;

        srand(time(NULL));
        for (int i = 0; i < N; i++) //рандомный массив и копирование во второй
            mas[i] = rand() % 1000 + 1;

        for (int i = 0; i < N; i++)
            mas2[i] = mas[i];

        cout << "------------------------------------------\n";

        cout << "\nМассив сгенерирован.\nДо сортировки:\n";

        for (int i = 0; i < 10; i++)//первые 10 чисел до сортировки
            cout << mas[i] << " ";

        cout << "\n\n";

        cout << "Последовательная версия:" << endl;
        //omp_set_nested(0);
        start_time = omp_get_wtime();
        quicksort(mas, 0, N - 1);
        end_time = omp_get_wtime();
        
        cout << "После сортировки:\n";
        for (int i = 0; i < 10; i++)//первые 10 чисел после сортировки
            cout << mas[i] << " ";

        cout << "\n\n";
        cout << "\nВремя вычислений: " << end_time - start_time << " сек." << endl;

        cout << "\n\n";

        cout << "\n\n\nПараллельная версия:" << endl;
        omp_set_nested(1);
        start_time = omp_get_wtime();
        quicksort_parallel(mas2, 0, N - 1);
        end_time = omp_get_wtime();

        cout << "После сортировки:\n";
        for (int i = 0; i < 10; i++)//первые 10 чисел после сортировки
            cout << mas2[i] << " ";

        cout << "\n\n";
        cout << "\nВремя вычислений: " << end_time - start_time << " сек." << endl;

        bool results_of_versions = true;
        for (int i = 0; i < N; i++)
        {
            if (mas[i] != mas2[i])
            {
                results_of_versions = false;
                break;
            }
        }

        if (results_of_versions == false)
            cout << "\nРезультаты не совпадают!" << endl;

        else
            cout << "\nРезультаты совпадают." << endl;
    }

    cout << "\n\n";
    t++;
}