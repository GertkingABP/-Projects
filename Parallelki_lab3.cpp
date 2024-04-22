#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include <omp.h>
#include <thread>

using namespace std;

int LevenshteinDistance1(string str1, string str2)
{
    int n = str1.length();
    int m = str2.length();

    if (n == 0) 
        return m;
    
    if (m == 0)
        return n;

    vector<int> last_row(m + 1);

    for (int i = 0; i <= m; i++)
        last_row[i] = i;

    for (int i = 1; i <= n; i++)
    {
        int old_diag = last_row[0];
        last_row[0] = i;

        for (int j = 1; j <= m; j++)
        {
            int temp = last_row[j];
            
            if (str1[i - 1] == str2[j - 1])
                last_row[j] = old_diag;
            
            else
                last_row[j] = min({ last_row[j - 1], last_row[j], old_diag }) + 1;
            
            old_diag = temp;
        }
    }

    return last_row[m];
}

int main()
{
    setlocale(LC_ALL, "Russian");

    string text;
    char temp;
    ifstream ifs("text4.txt");

    if (!ifs) {
        cerr << "Ошибка файла!!!" << endl;
        return 1;
    }

    ifs.unsetf(ios::skipws);
    while (ifs >> temp)
        text += temp;

    string search_string;
    char temp1;
    ifstream ifs1("search.txt");

    if (!ifs1) {
        cerr << "Ошибка файла!!!" << endl;
        return 1;
    }

    ifs1.unsetf(ios::skipws);
    while (ifs1 >> temp1)
        search_string += temp1;

    int m = search_string.length();

    int max_threads = omp_get_max_threads();
    cout << "Максимальное кол-во доступных потоков: " << max_threads << endl;
    cout << "-------------------------------------------\n" << endl;
    int count = 0; //кол-во вхождений с расстоянием = 0
    int num_threads = 1;
    double start_time = 0;
    double end_time = 0;
    int t = 1;
    int min_dist = 10000000;
    int new_dist = 0;
    string min_str;

    while (t <= 10)
    {
        cout << "\n\n----------------------------------------------\nИтерация " << t << endl;
        while (num_threads <= max_threads)
        {
            start_time = omp_get_wtime();
            #pragma omp parallel for num_threads(num_threads) /*reduction(+: count)*/
            for (int i = 0; i <= text.length() - m; i++)
            {
                string substr = text.substr(i, m);
                new_dist = LevenshteinDistance1(search_string, substr);
                
                if (new_dist < min_dist)
                {
                    min_dist = new_dist;
                    min_str = substr;
                }

                /*if (new_dist == 0)
                {
                    count++;
                    //cout << "Вхождение найдено на символе с индексом " << i << endl;
                }*/
            }
            
            end_time = omp_get_wtime();
            cout << "\n\nНаиболее похожая строка: " << min_str << endl;
            cout << "\nНаименьшее расстояние: " << min_dist << endl;
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