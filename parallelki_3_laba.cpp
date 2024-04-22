#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <thread>
#include <omp.h>

using namespace std;

/*int hammingDistance(const string& a, const string& b)
{
    if (a.size() != b.size())
        return -1;

    int dist = 0;

#pragma omp parallel for reduction(+:dist)
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            dist++;
    }

    return dist;
}

int findSubstring(const string& text, const string& pattern, int numOfThreads)
{
    const size_t n = text.size();
    const size_t m = pattern.size();

    if (m > n)
        return -1;

    int index = -1;

#pragma omp parallel num_threads(numOfThreads)
    {
#pragma omp for
        for (int i = 0; i <= n - m; ++i)
        {
            const string substring = text.substr(i, m);
            const int dist = hammingDistance(substring, pattern);
            if (dist == 0)
            {
#pragma omp critical
                {
                    index = i;
                }
            }
        }
    }

    return index;
}*/

int hammingDistance(const string& a, const string& b)
{
    if (a.size() != b.size())
        return -1;

    int dist = 0;

    for (size_t i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            dist++;
    }

    return dist;
}

int findSubstring(const string& text, const string& pattern)
{
    const size_t n = text.size();
    const size_t m = pattern.size();

    if (m > n)
        return -1;

    for (size_t i = 0; i <= n - m; ++i)
    {
        const string substring = text.substr(i, m);
        const int dist = hammingDistance(substring, pattern);
        if (dist == 0)
            return i;
    }

    return -1;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    string text;
    char temp;
    ifstream ifs("my_text.txt");

    if (!ifs) {
        cerr << "File error." << endl;
        return 1;
    }

    ifs.unsetf(ios::skipws);
    while (ifs >> temp)
        text += temp;

    string pattern;
    char temp1;
    ifstream ifs1("search.txt");

    if (!ifs1) {
        cerr << "File error." << endl;
        return 1;
    }

    ifs1.unsetf(ios::skipws);
    while (ifs1 >> temp1)
        pattern += temp1;
    
    int max_threads = omp_get_max_threads();
    cout << "Максимальное кол-во доступных потоков: " << max_threads << endl;
    cout << "-------------------------------------------\n" << endl;
    int count = 0;
    int num_threads = 1;
    double start_time = 0;
    double end_time = 0;
    int t = 0;

    while (t < 10)
    {
        while (num_threads <= max_threads)
        {
            //#pragma omp parallel num_threads(num_threads) reduction(+: count)
            start_time = omp_get_wtime();
            int position = findSubstring(text, pattern);

            if (position >= 0)
                cout << "Вхождение найдено на позиции(символе с индексом): " << position << '\n';

            else
                cout << "Вхождение не найдено.\n";

            end_time = omp_get_wtime();
            //cout << "\n\nВсего найдено вхождений: " << count << endl;
            cout << "Время вычислений в " << num_threads << " поток(е/ах): " << end_time - start_time << endl;
            num_threads++;
            count = 0;
            start_time = 0;
            end_time = 0;
        }

        t++;
        num_threads = 1;
    }
}