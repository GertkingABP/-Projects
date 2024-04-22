///////////////////////////////////////////////////////////////////////////1 ЛАБА///////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <omp.h>

using namespace std;

int CountZerosThread(const vector<int>& array, int start, int end, int k)
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
        threads[i] = thread([&, start, end, i]() { int cnt = CountZerosThread(array, start, end, k); counts[i] = cnt; });
    }

    for (auto& th : threads)
        th.join();

    int total_chains = 0;

    for (int i = 0; i < num_threads; i++)
        total_chains += counts[i];

    return total_chains;
}

const int N = 180180000;
const int min_value = 0;
const int max_value = 4;

int main()
{
    double start_time, end_time;
    setlocale(LC_ALL, "Russian");
    vector <int> mas(N);

    int k, num_threads, chains;
    k = 3;
    num_threads = 1;

    for (int t = 0; t < 10; t++)//проверка циклом работы алгоритма
    {
        srand(time(NULL));
        for (int i = 0; i < N; i++)
        {
            //mas[i] = rand() % 4 + 1;
            mas[i] = rand() % (max_value - min_value + 1) + min_value;
            //mas[i] = 0;
            //cout << mas[i] << " ";
        }

        //mas[rand() % N] = 1;

        cout << "\n\nМассив сгенерирован.\nПервые 10 эл-ов: ";

        for (int i = 0; i < 10; i++)//первые 10 чисел
            cout << mas[i] << " ";

        while (num_threads <= 16)
        {
            start_time = omp_get_wtime();
            chains = CountZerosParallel(mas, k, num_threads);
            end_time = omp_get_wtime();
            cout << "\n\nЧисло цепочек, состоящих из " << k << " нулей: " << chains << endl;
            cout << "Время вычислений в " << num_threads << " поток(е/ах): " << end_time - start_time << " секунд(ы)" << endl;
            start_time = 0;
            end_time = 0;
            num_threads++;
        }

        num_threads = 1;
    }
}

///////////////////////////////////////////////////////////////////////////2 ЛАБА///////////////////////////////////////////////////////////////////////////

/*#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <atomic>
#include <omp.h>
#include <mutex>

using namespace std;*/

//////////////////////////////ФУНКЦИИ ТОЛЬКО С АТОМИКОМ(ЧУТЬ ОТЛИЧАЕТСЯ ВРЕМЯ ВЫЧИСЛЕНИЙ 1 ПОТОКА, НА 10-15% БЫСТРЕЕ, МНОГО ПОТОКОВ ТАК ЖЕ ПО ВРЕМЕНИ, КОГДА ВСЕ НУЛИ, РАЗНИЦЫ ОТ 1 ЛАБЫ НЕТ ВООБЩЕ)//////////////////////////////

/*int СountZerosThread(const vector<int>& array, int start, int end, int k)
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

    atomic<int> counter(0);

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
            int cnt = СountZerosThread(array, start, end, k);
        counts[i] = cnt;
        counter += cnt;
            });
    }

    for (auto& th : threads)
        th.join();

    int total_chains = counter;

    return total_chains;
}*/

//////////////////////////////ФУНКЦИИ ТОЛЬКО С МЬЮТЕКСОМ(РАБОТАЕТ НА 10-15 % ДОЛЬШЕ В 1 ПОТОКЕ, В НЕСКОЛЬКИХ ТАК ЖЕ, НО ПРИ ВСЕХ НУЛЯХ РАБОТАЕТ ООООЧЕНЬ ДОЛГО В 1 И НЕСКОЛЬКИХ ПОТОКАХ, БОЛЕЕ 1 СЕКУНДЫ!)//////////////////////////////

/*int СountZerosThread(const vector<int>& array, int start, int end, int k, mutex& m)
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
                m.lock();
                chains++;
                m.unlock();
                zeros = 0;
            }
        }

        else
            zeros = 0;
    }

    //if (zeros == k)
    //{
        //m.lock();
        //chains++;
        //m.unlock();
    //}

    return chains;
}

int CountZerosParallel(const vector<int>& array, int k, int number_of_threads)
{
    int n = array.size();

    vector<int> counts(number_of_threads, 0);

    int total_chains = 0;

    mutex m;

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
            int cnt = СountZerosThread(array, start, end, k, m);
        counts[i] = cnt;
            });
    }

    for (auto& th : threads)
        th.join();

    for (int i = 0; i < num_threads; i++)
    {
        total_chains += counts[i];
    }

    return total_chains;
}

const int N = 180180000;
const int min_value = 0;
const int max_value = 4;

int main()
{
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

    for (int t = 0; t < 100; t++)//проверка циклом работы алгоритма
    {
        srand(time(NULL));
        for (int i = 0; i < N; i++)
        {
            //mas[i] = rand() % (max_value - min_value + 1) + min_value;
            mas[i] = 0;
            //cout << mas[i] << " ";
        }

        cout << "\n\nМассив сгенерирован.\nПервые 10 эл-ов: ";

        for (int i = 0; i < 10; i++)//первые 10 чисел
            cout << mas[i] << " ";

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
        start_time = 0;
        end_time = 0;

        if (chains != chains_p)
            cout << "\n-----------ALARM!-----------" << endl;
    }
}*/