#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <mutex>
#include <atomic>
#include <omp.h>

using namespace std;

///////////////////////////////////////////ИЗ 1 ЛАБЫ///////////////////////////////////////////
int СountZerosThread(const vector<int>& array, int start, int end, int k)
{
    int chains = 0;
    int zeros = 0;

    if (array[start] == 0)
        zeros = 1;

    for (int i = start + 1; i < end; i++)
    {
        if (array[i] == 0)
        {
            zeros++;

            if (zeros == k)
            {
                chains++;
                zeros = 0;
            }
        }

        else
            zeros = 0;
    }

    if (zeros == k)
        chains++;

    return chains;
}

int CountZerosParallel(const vector<int>& array, int k, int number_of_threads)
{
    int n = array.size();

    vector<int> counts(number_of_threads, 0);

    vector<int> ends_points(number_of_threads + 1, 0);
    ends_points[0] = 0;

    for (int i = 1; i <= number_of_threads; i++)
    {
        ends_points[i] = array.size() * i / number_of_threads;

        if (ends_points[i] >= n)
            ends_points[i] = n;

        int j = ends_points[i] - 1;

        while (j >= ends_points[i - 1] && array[j] != 0)
            j--;

        if (j >= ends_points[i - 1] + k - 1)
            ends_points[i] = j + 1;

        else
            ends_points[i] = ends_points[i - 1];
    }

    int num_threads = ends_points.size() - 1;

    vector<thread> threads(num_threads);

    for (int i = 0; i < num_threads; i++)
    {
        int start = ends_points[i];
        int end = ends_points[i + 1];
        threads[i] = thread([&, start, end, i]() { int cnt = СountZerosThread(array, start, end, k); counts[i] = cnt; });
    }

    for (auto& th : threads)
        th.join();

    int total_chains = 0;

    for (int i = 0; i < num_threads; i++)
        total_chains += counts[i];

    return total_chains;
}

///////////////////////////////////////////1.ЗАПИСЬ В ОБЩИЕ ПЕРЕМЕННЫЕ///////////////////////////////////////////

int СountZerosThread1(const vector<int>& array, int start, int end, int k, int& chains, int& zeros)
{
    if (array[start] == 0)
        zeros = 1;

    for (int i = start + 1; i < end; i++)
    {
        if (array[i] == 0)
        {
            zeros++;

            if (zeros == k)
            {
                chains++;
                zeros = 0;
            }
        }

        else
            zeros = 0;
    }

    if (zeros == k)
        chains++;

    return 0;
}

int CountZerosParallel1(const vector<int>& array, int k, int number_of_threads)
{
    int n = array.size();

    vector<int> counts(number_of_threads, 0);

    vector<int> ends_points(number_of_threads + 1, 0);
    ends_points[0] = 0;

    for (int i = 1; i <= number_of_threads; i++)
    {
        ends_points[i] = array.size() * i / number_of_threads;

        if (ends_points[i] >= n)
            ends_points[i] = n;

        int j = ends_points[i] - 1;

        while (j >= ends_points[i - 1] && array[j] != 0)
            j--;

        if (j >= ends_points[i - 1] + k - 1)
            ends_points[i] = j + 1;

        else
            ends_points[i] = ends_points[i - 1];
    }

    int num_threads = ends_points.size() - 1;

    vector<thread> threads(num_threads);

    for (int i = 0; i < num_threads; i++)
    {
        int start = ends_points[i];
        int end = ends_points[i + 1];
        threads[i] = thread([&, start, end, i]() {
            int chains = 0;
        int zeros = 0;
        СountZerosThread1(array, start, end, k, chains, zeros);
        counts[i] = chains;
            });
    }

    for (auto& th : threads)
        th.join();

    int total_chains = 0;

    for (int i = 0; i < num_threads; i++)
        total_chains += counts[i];

    return total_chains;
}

///////////////////////////////////////////2.АТОМАРНЫЕ ОПЕРАЦИИ///////////////////////////////////////////
int СountZerosThread2(const vector<int>& array, atomic<int>& total_zeros, int start, int end, int k)
{
    int chains = 0;
    int zeros = 0;

    if (array[start] == 0)
    {
        zeros = 1;
        total_zeros.fetch_add(zeros); //увеличиваем общее количество нулей
    }

    for (int i = start + 1; i < end; i++)
    {
        if (array[i] == 0)
        {
            zeros++;

            if (zeros == k)
            {
                chains++;
                zeros = 0;
                total_zeros.fetch_add(-k); //уменьшаем общее количество нулей на k
            }
        }
        else
            zeros = 0;
    }

    if (zeros == k)
    {
        chains++;
        total_zeros.fetch_add(-k); //уменьшаем общее количество нулей на k
    }

    return chains;
}

int CountZerosParallel2(const vector<int>& array, int k, int number_of_threads)
{
    int n = array.size();
    atomic<int> total_zeros(0); //общее количество нулей (инициализируем атомарно)

    vector<int> counts(number_of_threads, 0);
    vector<int> ends_points(number_of_threads + 1, 0);
    ends_points[0] = 0;

    for (int i = 1; i <= number_of_threads; i++)
    {
        ends_points[i] = array.size() * i / number_of_threads;

        if (ends_points[i] >= n)
            ends_points[i] = n;

        int j = ends_points[i] - 1;

        while (j >= ends_points[i - 1] && array[j] != 0)
            j--;

        if (j >= ends_points[i - 1] + k - 1)
            ends_points[i] = j + 1;

        else
            ends_points[i] = ends_points[i - 1];
    }

    int num_threads = ends_points.size() - 1;
    vector<thread> threads(num_threads);

    for (int i = 0; i < num_threads; i++)
    {
        int start = ends_points[i];
        int end = ends_points[i + 1];
        threads[i] = thread([&, start, end, i]() { int cnt = СountZerosThread2(array, total_zeros, start, end, k); counts[i] = cnt; });
    }

    for (auto& th : threads)
        th.join();

    int total_chains = 0;

    if (total_zeros % k == 0) //если общее количество нулей кратно k, то мы добавляем дополнительную цепочку
        total_chains++;

    for (int i = 0; i < num_threads; i++)
        total_chains += counts[i];

    return total_chains;
}

///////////////////////////////////////////3.1.СИНХРОНИЗАЦИЯ МЬЮТЕКСАМИ///////////////////////////////////////////
int СountZerosThread_m(const vector<int>& array, int start, int end, int k, mutex& mtx, int& total_zeros)
{
    int chains = 0;
    int zeros = 0;

    if (array[start] == 0)
    {
        mtx.lock();
        total_zeros++;
        mtx.unlock();
        zeros = 1;
    }

    for (int i = start + 1; i < end; i++)
    {
        if (array[i] == 0)
        {
            zeros++;

            if (zeros == k)
            {
                chains++;
                zeros = 0;

                mtx.lock();
                total_zeros -= k;
                mtx.unlock();
            }
        }

        else
            zeros = 0;
    }

    if (zeros == k)
    {
        chains++;

        mtx.lock();
        total_zeros -= k;
        mtx.unlock();
    }

    return chains;
}

int CountZerosParallel_m(const vector<int>& array, int k, int number_of_threads)
{
    int n = array.size();
    int total_zeros = 0;
    mutex mtx;

    vector<int> counts(number_of_threads, 0);

    vector<int> ends_points(number_of_threads + 1, 0);
    ends_points[0] = 0;

    for (int i = 1; i <= number_of_threads; i++)
    {
        ends_points[i] = array.size() * i / number_of_threads;

        if (ends_points[i] >= n)
            ends_points[i] = n;

        int j = ends_points[i] - 1;

        while (j >= ends_points[i - 1] && array[j] != 0)
            j--;

        if (j >= ends_points[i - 1] + k - 1)
            ends_points[i] = j + 1;

        else
            ends_points[i] = ends_points[i - 1];
    }

    int num_threads = ends_points.size() - 1;

    vector<thread> threads(num_threads);

    for (int i = 0; i < num_threads; i++)
    {
        int start = ends_points[i];
        int end = ends_points[i + 1];
        threads[i] = thread([&, start, end, i]() { int cnt = СountZerosThread_m(array, start, end, k, mtx, total_zeros); counts[i] = cnt; });
    }

    for (auto& th : threads)
        th.join();

    int total_chains = 0;

    if (total_zeros % k == 0)
        total_chains++;

    for (int i = 0; i < num_threads; i++)
        total_chains += counts[i];

    return total_chains;
}

////////////////////////////////////////////////////////////3.2.СИНХРОНИЗАЦИЯ КРИТИЧЕСКИМИ СЕКЦИЯМИ////////////////////////////////////////////////////////////
int СountZerosThread_cr(const vector<int>& array, int start, int end, int k)
{
    int chains = 0;
    int zeros = 0;

    if (array[start] == 0)
        zeros = 1;

    for (int i = start + 1; i < end; i++)
    {
        if (array[i] == 0)
        {
            zeros++;

            if (zeros == k)
            {

#pragma omp critical
                chains++;

                zeros = 0;
            }
        }

        else
            zeros = 0;
    }


#pragma omp critical
    {
        if (zeros == k)
            chains++;
    }

    return chains;
}

int CountZerosParallel_cr(const vector<int>& array, int k, int number_of_threads)
{
    int n = array.size();

    vector<int> counts(number_of_threads, 0);

    vector<int> ends_points(number_of_threads + 1, 0);
    ends_points[0] = 0;

    for (int i = 1; i <= number_of_threads; i++)
    {
        ends_points[i] = array.size() * i / number_of_threads;

        if (ends_points[i] >= n)
            ends_points[i] = n;

        int j = ends_points[i] - 1;

        while (j >= ends_points[i - 1] && array[j] != 0)
            j--;

        if (j >= ends_points[i - 1] + k - 1)
            ends_points[i] = j + 1;

        else
            ends_points[i] = ends_points[i - 1];
    }

    int num_threads = ends_points.size() - 1;

    vector<thread> threads(num_threads);

#pragma omp parallel num_threads(number_of_threads)
    {
#pragma omp for
        for (int i = 0; i < num_threads; i++)
        {
            int start = ends_points[i];
            int end = ends_points[i + 1];
            int cnt = СountZerosThread_cr(array, start, end, k);
            counts[i] = cnt;
        }
    }

    int total_chains = 0;

    for (int i = 0; i < num_threads; i++)
        total_chains += counts[i];

    return total_chains;
}

////////////////////////////////////////4.ИНДИВИДУАЛЬНЫЕ ПЕРЕМЕННЫЕ ДЛЯ ВЫЧИСЛЕНИЯ В КАЖДОМ ПОТОКЕ(ЗАМЕНЕНА ТОЛЬКО 2 ФУНКЦИЯ)////////////////////////////////////////

int CountZerosParallel4(const vector<int>& array, int k, int number_of_threads)
{
    int n = array.size();

    vector<vector<int>> counts(number_of_threads, vector<int>(1, 0)); //вектор векторов

    vector<int> ends_points(number_of_threads + 1, 0);
    ends_points[0] = 0;

    for (int i = 1; i <= number_of_threads; i++)
    {
        ends_points[i] = array.size() * i / number_of_threads;

        if (ends_points[i] >= n)
            ends_points[i] = n;

        int j = ends_points[i] - 1;

        while (j >= ends_points[i - 1] && array[j] != 0)
            j--;

        if (j >= ends_points[i - 1] + k - 1)
            ends_points[i] = j + 1;

        else
            ends_points[i] = ends_points[i - 1];
    }

    int num_threads = ends_points.size() - 1;

    vector<thread> threads(num_threads);

    for (int i = 0; i < num_threads; i++)
    {
        int start = ends_points[i];
        int end = ends_points[i + 1];
        threads[i] = thread([&, start, end, i]() { int cnt = СountZerosThread(array, start, end, k); counts[i][0] = cnt; }); // записываем результат вычислений в вектор векторов
    }

    for (auto& th : threads)
        th.join();

    int total_chains = 0;

    for (int i = 0; i < num_threads; i++)
        total_chains += counts[i][0]; //суммируем результаты вычислений по каждому потоку

    return total_chains;
}

////////////////////////////////////////////////////////////////////////////////////MAIN////////////////////////////////////////////////////////////////////////////////////

const int N = 180180000;
const int min_value = 0;
const int max_value = 4;

int main()
{
    int counts;
    double start_time, end_time;
    setlocale(LC_ALL, "Russian");
    vector <int> mas(N);

    int k, num_threads;
    cout << "\nВведите k(сколько нулей в цепочке):" << endl;
    cin >> k;
    cout << "\nВведите число потоков:" << endl;
    cin >> num_threads;

    while (k < 1 || k > 16)
    {
        cout << "\nВведите k от 1 до 16:" << endl;
        cin >> num_threads;
    }

    while (num_threads < 1 || num_threads > 16)
    {
        cout << "\nВведите число потоков от 1 до 16:" << endl;
        cin >> num_threads;
    }

    for (int t = 0; t < 105; t++)//проверка циклом работы алгоритма
    {
        srand(time(NULL));
        for (int i = 0; i < N; i++)
        {
            mas[i] = rand() % (max_value - min_value + 1) + min_value;
            //mas[i] = 0;
            //cout << mas[i] << " ";
        }

        //mas[rand() % N] = 1;

        cout << "\n\n\nИтерация " << t + 1 <<":\n\n>>>>>>>Массив сгенерирован.\nПервые 10 эл-ов: ";

        for (int i = 0; i < 10; i++)//первые 10 чисел
            cout << mas[i] << " ";

        cout << "\n---------------------------------------------------------------\n1. Обычная версия (1 л/р):" << endl;

        start_time = 0;
        end_time = 0;

        start_time = omp_get_wtime();
        int chains = CountZerosParallel(mas, k, 1);
        end_time = omp_get_wtime();
        cout << "\n\nЧисло цепочек, состоящих из " << k << " нулей: " << chains << endl;
        cout << "Время вычислений в 1 потоке: " << end_time - start_time << " секунд(ы)" << endl;
        
        start_time = 0;
        end_time = 0;

        start_time = omp_get_wtime();
        int chains_p = CountZerosParallel(mas, k, num_threads);
        end_time = omp_get_wtime();

        cout << "\nЧисло цепочек из " << k << " нулей: " << chains_p << endl;
        cout << "Время вычислений в " << num_threads << " поток(е/ах): " << end_time - start_time << " секунд(ы)" << endl;

        if (chains != chains_p)
            cout << "\n-----------ALARM!-----------" << endl;
        
        start_time = 0;
        end_time = 0;

        cout << "\n---------------------------------------------------------------\n2. Запись в общие переменные:" << endl;

        start_time = omp_get_wtime();
        chains = CountZerosParallel1(mas, k, 1);
        end_time = omp_get_wtime();
        cout << "\n\nЧисло цепочек, состоящих из " << k << " нулей: " << chains << endl;
        cout << "Время вычислений в 1 потоке: " << end_time - start_time << " секунд(ы)" << endl;

        start_time = 0;
        end_time = 0;

        start_time = omp_get_wtime();
        chains_p = CountZerosParallel1(mas, k, num_threads);
        end_time = omp_get_wtime();

        cout << "\nЧисло цепочек из " << k << " нулей: " << chains_p << endl;
        cout << "Время вычислений в " << num_threads << " поток(е/ах): " << end_time - start_time << " секунд(ы)" << endl;

        if (chains != chains_p)
            cout << "\n-----------ALARM!-----------" << endl;
        
        start_time = 0;
        end_time = 0;

        cout << "\n---------------------------------------------------------------\n3. Атомарные операции:" << endl;

        start_time = omp_get_wtime();
        chains = CountZerosParallel2(mas, k, 1);
        end_time = omp_get_wtime();
        cout << "\n\nЧисло цепочек, состоящих из " << k << " нулей: " << chains << endl;
        cout << "Время вычислений в 1 потоке: " << end_time - start_time << " секунд(ы)" << endl;

        start_time = 0;
        end_time = 0;

        start_time = omp_get_wtime();
        chains_p = CountZerosParallel2(mas, k, num_threads);
        end_time = omp_get_wtime();

        cout << "\nЧисло цепочек из " << k << " нулей: " << chains_p << endl;
        cout << "Время вычислений в " << num_threads << " поток(е/ах): " << end_time - start_time << " секунд(ы)" << endl;

        if (chains != chains_p)
            cout << "\n-----------ALARM!-----------" << endl;

        start_time = 0;
        end_time = 0;

        cout << "\n---------------------------------------------------------------\n4.1. Синхронизация мьютексами:" << endl;

        start_time = omp_get_wtime();
        chains = CountZerosParallel_m(mas, k, 1);
        end_time = omp_get_wtime();
        cout << "\n\nЧисло цепочек, состоящих из " << k << " нулей: " << chains << endl;
        cout << "Время вычислений в 1 потоке: " << end_time - start_time << " секунд(ы)" << endl;

        start_time = 0;
        end_time = 0;

        start_time = omp_get_wtime();
        chains_p = CountZerosParallel_m(mas, k, num_threads);
        end_time = omp_get_wtime();

        cout << "\nЧисло цепочек из " << k << " нулей: " << chains_p << endl;
        cout << "Время вычислений в " << num_threads << " поток(е/ах): " << end_time - start_time << " секунд(ы)" << endl;

        if (chains != chains_p)
            cout << "\n-----------ALARM!-----------" << endl;

        start_time = 0;
        end_time = 0;

        cout << "\n---------------------------------------------------------------\n4.2. Синхронизация критическими секциями:" << endl;

        start_time = omp_get_wtime();
        chains = CountZerosParallel_cr(mas, k, 1);
        end_time = omp_get_wtime();
        cout << "\n\nЧисло цепочек, состоящих из " << k << " нулей: " << chains << endl;
        cout << "Время вычислений в 1 потоке: " << end_time - start_time << " секунд(ы)" << endl;

        start_time = 0;
        end_time = 0;

        start_time = omp_get_wtime();
        chains_p = CountZerosParallel_cr(mas, k, num_threads);
        end_time = omp_get_wtime();

        cout << "\nЧисло цепочек из " << k << " нулей: " << chains_p << endl;
        cout << "Время вычислений в " << num_threads << " поток(е/ах): " << end_time - start_time << " секунд(ы)" << endl;

        if (chains != chains_p)
            cout << "\n-----------ALARM!-----------" << endl;

        start_time = 0;
        end_time = 0;

        cout << "\n---------------------------------------------------------------\n5. Индивидуальные переменные для вычислений в каждом потоке:" << endl;

        start_time = omp_get_wtime();
        chains = CountZerosParallel4(mas, k, 1);
        end_time = omp_get_wtime();
        cout << "\n\nЧисло цепочек, состоящих из " << k << " нулей: " << chains << endl;
        cout << "Время вычислений в 1 потоке: " << end_time - start_time << " секунд(ы)" << endl;

        start_time = 0;
        end_time = 0;

        start_time = omp_get_wtime();
        chains_p = CountZerosParallel4(mas, k, num_threads);
        end_time = omp_get_wtime();

        cout << "\nЧисло цепочек из " << k << " нулей: " << chains_p << endl;
        cout << "Время вычислений в " << num_threads << " поток(е/ах): " << end_time - start_time << " секунд(ы)" << endl;

        if (chains != chains_p)
            cout << "\n-----------ALARM!-----------" << endl;
    }
}