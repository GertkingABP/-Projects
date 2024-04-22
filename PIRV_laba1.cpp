#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <omp.h>
using namespace std;

const int N = 1000000; // количество чисел в массиве
const int MIN_VALUE = 1; // минимальное значение для генерации случайных чисел
const int MAX_VALUE = 1000; // максимальное значение для генерации случайных чисел
/*
Цикл, создающий конкуренцию между потоками, создаёт только замедление, если диапазон элементов слишком маленький.
возможно есть смысл разделить поток поровну между потоками, чтобы они все работали параллельно, на своих участках, а не конкурировали
*/

void pushElementsInArray(vector <int>& arr, int element, int N) {
    for (int i = 0; i < N; i++) {
        arr.push_back(element);
    }
}

void pushInBackOfArray(vector <int>& arr, int element, int N) {
    for (int i = 0; i < N; i++) {
        arr.push_back(element);
    }
}

void pushInFrontOfArray(vector <int>& arr, int element, int N) {
    for (int i = 0; i < N; i++) {
        arr.insert(arr.begin(), element);
    }
}


void countOccurences(vector <int> arr, vector <int>& count_of_occurences) {
    // every thread try to find digit to count
    for (int j = 0; j < MAX_VALUE - MIN_VALUE + 1; j++) {
        // available number tagged with -1 occurences
        if (count_of_occurences[j] == -1) {
            // when available number found, thread tags this number as processing, by changing occurences of this digit to -2
            count_of_occurences[j] = -2;
            // count actual number of occurences of this element in array
            count_of_occurences[j] = count(arr.begin(), arr.end(), j + MIN_VALUE);
            //cout << "Number of " << j + MIN_VALUE << " in array: " << count_of_occurences[j]<<" thread: " << this_thread::get_id() << "\n";
        }
    }
}

void arrayCountSort(vector<int> array, int thread_number) {
    // save start time
    double start_time = omp_get_wtime();
    // array of occurences for each possible number in array
    vector <int> count_of_occurences(MAX_VALUE - MIN_VALUE + 1, -1);
    // array with threads
    vector <thread> th(thread_number);

    // initializing threads
    for (int i = 0; i < thread_number; i++) {
        th[i] = thread([array, &count_of_occurences]() {
            countOccurences(array, count_of_occurences);
            });
        cout << "\nthread #" << th[i].get_id() << " open";
    }
    // waiting for all threads to end before continue
    for (int i = 0; i < thread_number; i++) th[i].join();

    // init result array
    vector <int> result_array = {};

    // building result array 
    //cout << "\nCount_of_occurences: ";
    for (int i = 0; i < MAX_VALUE - MIN_VALUE + 1; i++) {
        //cout << count_of_occurences[i] << " (" << i + MIN_VALUE << ") ";
        pushElementsInArray(result_array, i + MIN_VALUE, count_of_occurences[i]);
    }

    // save end time
    double end_time = omp_get_wtime();

    // Output of result array and time for operation
    //cout << "\nResult array:\n";
    //for (int i = 0; i < N; i++) {
    //    cout << result_array[i] << " ";
    //}
    cout << "\nTime: " << end_time - start_time;
}

int main()
{
    cout << "Distributed and Parallel Computing\nLaboratory work #1, variant #7\n"
        << "Hello!\n";
    int number_of_threads = 0;
    while (number_of_threads < 2 || number_of_threads>4) {
        cout << "\nInput number of threads (1<t<5): ";
        cin >> number_of_threads;
        if (number_of_threads < 2) cout << "It doesn't make sense. Input digit more than 1.\n";
        if (number_of_threads > 4) cout << "There are only 4 threads on this processor, try again.\n";
    }


    // Creating of original array
    vector <int> original_array(N);
    //cout << "Original Array:\n";

    // Filling original array with random numbers
    srand(time(NULL)); // assign start point for rand()
    for (int i = 0; i < N; i++) {
        original_array[i] = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
        //cout << original_array[i] << " "; // array output
    }

    cout << "\n\nSingle thread.";
    arrayCountSort(original_array, 1);

    cout << "\n\n" << number_of_threads << " threads.";
    arrayCountSort(original_array, number_of_threads);


    cout << "\nGoodbye!\n";
}

