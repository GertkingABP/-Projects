#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>

// CUDA header
#include <cuda_runtime.h>

using namespace std;

struct RsaPublicKey {
    long long e, m;
};

struct RsaPrivateKey {
    long long d, m;
};

// Нахождение общего делителя
long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

// Решение Диофантова уравнения a*x + b*y = 1
void DiophantEquation(long long a, long long b, long long& x, long long& y) {
    long long a11 = 1, a12 = 0, a21 = 0, a22 = 1;

    while (true) {
        long long r = a % b;
        if (r == 0) {
            x = a12;
            y = a22;
            return;
        }
        else {
            long long q = a / b;
            long long save12 = a12;
            long long save22 = a22;
            a12 = a11 - save12 * q;
            a22 = a21 - save22 * q;
            a11 = save12;
            a21 = save22;
            a = b;
            b = r;
        }
    }
}

// Поиск числа y, такого что (x*y)%m == 1
long long FindNumber(long long x, long long m) {
    long long y, sux;
    DiophantEquation(x, m, y, sux);

    while (y < 0)
        y += m;

    return y;
}

// Вычисление (a в степени b)%m
long long Power(long long a, long long b, long long m) {
    a %= m;
    long long res = a;
    for (long long i = 1; i < b; i++)
        res = (res * a) % m;

    return res;
}

// Генерация пары ключей
void GenerateKeyPair(long long p, long long q, long long e, RsaPublicKey& pub, RsaPrivateKey& pri) {
    if ((gcd(e, p - 1) != 1) || (gcd(e, q - 1) != 1)) {
        printf("GenerateKeyPair: Incorrect parameters\n");
        exit(1);
    }

    pub.m = p * q;
    pub.e = e;
    pri.m = p * q;

    // Функция Эйлера
    long long phi_m = (p - 1) * (q - 1);
    pri.d = FindNumber(e, phi_m);
}

// Сообщение должно быть < key. m
long long Encode(long long source, RsaPublicKey& key) {
    return Power(source, key.e, key.m);
}

long long Decode(long long source, RsaPrivateKey& key) {
    return Power(source, key.d, key.m);
}

// Ядро CUDA для параллельного кодирования
__global__ void parallelEncode(long long* arr, long long* result, long long e, long long m, int l) { //  функция-ядро CUDA, которая будет выполняться на GPU. global это значит
    /* индекс текущей потоковой области, вычисляемый на основе сетки блоков и размера блока.

    blockIdx.x представляет индекс блока, 
    blockDim.x - количество потоков в блоке,
    threadIdx.x - индекс потока внутри блока. 

    Это вычисление индекса помогает определить конкретный элемент массива, который будет обработан текущим потоком. */
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < l) {
        result[i] = 1; // initialize result
        for (long long j = 0; j < e; j++) {
            result[i] = (result[i] * arr[i]) % m;
        }
    }
}

// Ядро CUDA для параллельного декодирования
__global__ void parallelDecode(long long* arr, long long* result, long long d, long long m, int l) {

    // смотреть код выше
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < l) {
        result[i] = 1; // initialize result
        for (long long j = 0; j < d; j++) {
            result[i] = (result[i] * arr[i]) % m;
        }
    }
}

int main() {
    setlocale(LC_CTYPE, "Russian_Russia.1251");
    long long p = 29;
    long long q = 19;
    long long e = 47;
    long long arr[] = { 19, 13, 30, 350, 500, 19, 13, 30, 350, 500 };
    long long l = 10;

    RsaPublicKey pub_key;
    RsaPrivateKey pri_key;

    GenerateKeyPair(p, q, e, pub_key, pri_key);
    long long enc;
    long long dec = 0;
    long long i = 0;

    // Последовательная версия
    clock_t start_time = clock();
    for (i = 0; i < l; i++) {
        long long source = arr[i] % pub_key.m;
        enc = Encode(source, pub_key);
        dec = Decode(enc, pri_key);
        cout << "Последовательный: Оригинальный: " << source << " Зашифрованный: " << enc << " Расшифрованный: " << dec << endl;
    }

    clock_t end_time = clock();
    double sequential_time = double(end_time - start_time) / CLOCKS_PER_SEC;


    // Параллельная версия с использованием куды
    // размечаем память
    long long* d_arr;
    long long* d_enc_result;
    long long* d_dec_result;
    cudaMalloc((void**)&d_arr, l * sizeof(long long));
    cudaMalloc((void**)&d_enc_result, l * sizeof(long long));
    cudaMalloc((void**)&d_dec_result, l * sizeof(long long));

    // копируем данные в девайс
    cudaMemcpy(d_arr, arr, l * sizeof(long long), cudaMemcpyHostToDevice);

    // устанавливаем сетку и размер блоков
    int block_size = 256;
    int grid_size = (l + block_size - 1) / block_size;

    // запускаем ядра куда
    start_time = clock();
    parallelEncode << <grid_size, block_size >> > (d_arr, d_enc_result, pub_key.e, pub_key.m, l);
    cudaDeviceSynchronize(); // Wait for the GPU to finish


    parallelDecode << <grid_size, block_size >> > (d_enc_result, d_dec_result, pri_key.d, pri_key.m, l);

    // измерим скорость выполнения параллельной версии
    end_time = clock();
    double cuda_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    // рассчитаем ускорение
    double speedup_cuda = sequential_time / cuda_time;

    // окончание измерения


    cudaDeviceSynchronize(); // Wait for the GPU to finish

    // скопируем результат обратно в хост
    long long* h_enc_result = new long long[l];
    long long* h_dec_result = new long long[l];
    cudaMemcpy(h_enc_result, d_enc_result, l * sizeof(long long), cudaMemcpyDeviceToHost);
    cudaMemcpy(h_dec_result, d_dec_result, l * sizeof(long long), cudaMemcpyDeviceToHost);

    // вывод параллельных результатов
    for (i = 0; i < l; i++) {
        long long source = arr[i] % pub_key.m;
        cout << "Параллельный (CUDA): Оригинальный: " << source << " Зашифрованный: " << h_enc_result[i] << " Расшифрованный: "
            << h_dec_result[i] << endl;
    }


    cout << "Ускорение (CUDA): " << speedup_cuda << endl;
    // освобождаем
    cudaFree(d_arr);
    cudaFree(d_enc_result);
    cudaFree(d_dec_result);

    // очищаем
    delete[] h_enc_result;
    delete[] h_dec_result;
}