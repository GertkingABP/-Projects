
//int main(int argc, char** argv)
//{
//    double start_time, end_time, time_seq, time_par;
//    int rank, size, input_size, local_size, remaining, displacement, local_input_size, times = 0;
//    int requested_mpi_processes = 4;
//    string encrypted_text, decrypted_text, local_input, encrypted_text2, gathered_encrypted_text, decrypted_text2;
//    setlocale(LC_ALL, "Rus");
//    string des_key = "abcdefgh"; // 64-bit ключ DES
//
//    string filename = "input3.txt";
//    string plaintext = readTextFromFile(filename);
//    if (plaintext.empty())
//    {
//        cerr << "The text is empty. Exit..." << endl;
//        //MPI_Finalize();
//        return 1;
//    }
//    
//    //текст на 12 тыс. символов как строка, а не файл
//    //string plaintext = "abcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcdeabcdefghabcabcabcde";
//
//    //cout << "Входной текст: " << plaintext << endl;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    // Копирование ключа DES на все процессы
//    MPI_Bcast((void*)des_key.c_str(), des_key.size(), MPI_CHAR, 0, MPI_COMM_WORLD);
//
//    while (times < 10)
//    {
//        start_time = omp_get_wtime();
//        encrypted_text = des_encrypt(des_key, plaintext);
//        end_time = omp_get_wtime();
//        time_seq = end_time - start_time;
//        //cout << "\n\nЗашифрованный текст: " << encrypted_text << endl;
//        cout << "\nSequential encryption time: " << time_seq << endl;
//        start_time = 0;
//        end_time = 0;
//        start_time = omp_get_wtime();
//        decrypted_text = des_decrypt(des_key, encrypted_text);
//        end_time = omp_get_wtime();
//        time_seq = end_time - start_time;
//        //cout << "\n\nРасшифрованный текст: " << decrypted_text << endl;
//        cout << "\nSequential decryption time: " << time_seq << endl;
//        start_time = 0;
//        end_time = 0;
//        cout << "\n\n-------------------------------------------------\n\n";
//
//        if (argc > 1)
//            requested_mpi_processes = atoi(argv[1]);
//
//        // Проверка количества процессов MPI и установка нового значения, если указано пользователем
//        if (size != requested_mpi_processes)
//        {
//
//            if (rank == 0)
//            {
//                cerr << "\nSpecified number of MPI processes: " << requested_mpi_processes << endl;
//                cerr << "\nRunning a program with " << requested_mpi_processes << " MPI processes." << endl;
//            }
//
//            start_time = omp_get_wtime();
//
//            MPI_Comm new_comm;
//            MPI_Comm_split(MPI_COMM_WORLD, 0, rank % requested_mpi_processes, &new_comm);
//            MPI_Comm_rank(new_comm, &rank);
//            MPI_Comm_size(new_comm, &size);
//        }
//
//        //if (rank == 0)
//            //start_time = omp_get_wtime();
//
//        // Распределение данных между процессами
//        input_size = plaintext.size();
//        local_size = input_size / size;
//        remaining = input_size % size;
//
//        displacement = rank * local_size;
//        local_input_size = (rank == size - 1) ? local_size + remaining : local_size;
//
//        // Распределение входных данных между процессами
//        string local_input_buf(local_input_size, ' ');
//        MPI_Scatter(plaintext.data(), local_size, MPI_CHAR,
//            &local_input_buf[0], local_size, MPI_CHAR,
//            0, MPI_COMM_WORLD);
//
//        // Шифрование локальной порции данных
//        encrypted_text2 = des_encrypt(des_key, local_input_buf);
//
//        // Сбор зашифрованных данных на главном процессе
//        gathered_encrypted_text.resize(input_size);
//        MPI_Gather(encrypted_text2.data(), local_input_size, MPI_CHAR,
//            &gathered_encrypted_text[displacement], local_input_size, MPI_CHAR,
//            0, MPI_COMM_WORLD);
//
//        if (rank == 0)
//        {
//            end_time = omp_get_wtime();
//            time_par = end_time - start_time;
//            //cout << "\n\nЗашифрованный текст: " << encrypted_text2 << endl;
//            cout << "\nParallel encryption time: " << time_par << endl;
//            start_time = 0;
//            end_time = 0;
//
//            start_time = omp_get_wtime();
//            decrypted_text2 = des_decrypt(des_key, gathered_encrypted_text);
//            end_time = omp_get_wtime();
//            time_par = end_time - start_time;
//            //cout << "\n\nРасшифрованный текст: " << decrypted_text2 << endl;
//            cout << "\nParallel decryption time: " << time_par << endl;
//        }
//
//        times++;
//        cout << "\n\n=============================END ITERATION=============================\n\n";
//    }
//
//    MPI_Finalize();
//    return 0;
//}






//#include <iostream>
//#include <fstream>
//#include <openssl/des.h>
//#include <cstring>
//#include <string>
//#include <cstdlib>
//#include <cstdio>
//#include <mpi.h>
//#include <omp.h>
//#include <chrono>
//#include <vector>
//#include <stdio.h>
//
//using namespace std;
//string des_encrypt(const string& key, const string& input)
//{
//    //Проверка длины ключа
//    if (key.size() != 8)
//    {
//        cerr << "The key length must be 8 bytes (64 bits)." << endl;
//        return "";
//    }
//
//    DES_cblock des_key;
//    memcpy(des_key, key.c_str(), 8);
//
//    DES_key_schedule schedule;
//    DES_set_key_unchecked(&des_key, &schedule);
//
//    //Выравнивание входного текста до кратности 8 байт (64 бит)
//    string padded_input = input;
//    while (padded_input.size() % 8 != 0)
//        padded_input.push_back(' ');
//
//    string output = "";
//    DES_cblock input_block, output_block;
//    for (size_t i = 0; i < padded_input.size(); i += 8)
//    {
//        std::memcpy(input_block, padded_input.c_str() + i, 8);
//        DES_ecb_encrypt(&input_block, &output_block, &schedule, DES_ENCRYPT);
//        output.append(reinterpret_cast<const char*>(output_block), 8);
//    }
//
//    return output;
//}
//
//string des_decrypt(const string& key, const string& input)
//{
//    //Проверка длины ключа
//    if (key.size() != 8)
//    {
//        cerr << "The key length must be 8 bytes (64 bits)." << endl;
//        return "";
//    }
//
//    DES_cblock des_key;
//    memcpy(des_key, key.c_str(), 8);
//
//    DES_key_schedule schedule;
//    DES_set_key_unchecked(&des_key, &schedule);
//
//    string output = "";
//    DES_cblock input_block, output_block;
//    for (size_t i = 0; i < input.size(); i += 8)
//    {
//        memcpy(input_block, input.c_str() + i, 8);
//        DES_ecb_encrypt(&input_block, &output_block, &schedule, DES_DECRYPT);
//        output.append(reinterpret_cast<const char*>(output_block), 8);
//    }
//
//    size_t padding = output.find_last_not_of(" ");
//    if (padding != string::npos)
//        output = output.substr(0, padding + 1);
//
//    return output;
//}
//
//string readTextFromFile(const string& filename)
//{
//    ifstream file(filename);
//    if (!file.is_open())
//    {
//        cerr << "Could not open the file." << filename << endl;
//        return "";
//    }
//
//    string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
//    file.close();
//
//    return content;
//}
//
//
//// Функция для параллельного шифрования и дешифрования с использованием MPI
//string parallel_des_crypt(const string& key, const string& input, int mode) {
//    int rank, size;
//
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    /*if (size < 2) {
//        cerr << "Need at least 2 processes for encryption/decryption." << endl;
//        return "";
//    }*/
//
//    const int key_size = 8;
//    if (key.size() != key_size) {
//        cerr << "The key length must be 8 bytes (64 bits)." << endl;
//        return "";
//    }
//
//    DES_cblock des_key;
//    memcpy(des_key, key.c_str(), key_size);
//
//    DES_key_schedule schedule;
//    DES_set_key_unchecked(&des_key, &schedule);
//
//    string output = "";
//
//    int input_size = input.size();
//    int chunk_size = input_size / size;
//    int remaining = input_size % size;
//
//    vector<int> send_counts(size, chunk_size);
//    vector<int> displacements(size, 0);
//
//    for (int i = 0; i < remaining; ++i) {
//        send_counts[i]++;
//    }
//
//    for (int i = 1; i < size; ++i) {
//        displacements[i] = displacements[i - 1] + send_counts[i - 1];
//    }
//
//    int local_chunk_size = send_counts[rank];
//    char* local_input = new char[local_chunk_size + 1];
//    MPI_Scatterv(input.c_str(), send_counts.data(), displacements.data(), MPI_CHAR, local_input, local_chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);
//
//    DES_cblock input_block, output_block;
//
//    for (int i = 0; i < local_chunk_size; i += key_size) {
//        memcpy(input_block, local_input + i, key_size);
//
//        if (mode == DES_ENCRYPT) {
//            DES_ecb_encrypt(&input_block, &output_block, &schedule, DES_ENCRYPT);
//        }
//        else if (mode == DES_DECRYPT) {
//            DES_ecb_encrypt(&input_block, &output_block, &schedule, DES_DECRYPT);
//        }
//
//        output.append(reinterpret_cast<const char*>(output_block), key_size);
//    }
//
//    delete[] local_input;
//
//    char* gathered_output = nullptr;
//    int* recv_counts = nullptr;
//    int* displacements_recv = nullptr;
//
//    if (rank == 0) {
//        gathered_output = new char[input_size];
//        recv_counts = send_counts.data();
//        displacements_recv = displacements.data();
//    }
//
//    MPI_Gatherv(output.c_str(), local_chunk_size, MPI_CHAR, gathered_output, recv_counts, displacements_recv, MPI_CHAR, 0, MPI_COMM_WORLD);
//
//    if (rank == 0) {
//        output.assign(gathered_output, input_size);
//        delete[] gathered_output;
//    }
//
//    return output;
//}
//
//
//int main(int argc, char* argv[])
//{
//    //ПОСЛЕДОВАТЕЛЬНО
//    cout << "\n---------------SEQUENTIAL---------------\n";
//    auto start_time_s = chrono::steady_clock::now();
//    string key1 = "abcdefgh"; //8-байтовый ключ
//    string filename1 = "input3.txt";
//
//    //// Чтение текста из файла
//    string inputText1 = readTextFromFile(filename1);
//    std::string output;
//   
//    string encryptedText1 = des_encrypt(key1, inputText1);
//    string decryptedText1 = des_decrypt(key1, encryptedText1);
//    auto end_time_s = chrono::steady_clock::now();
//    cout << "\nTotal time: " << chrono::duration<double, milli>(end_time_s - start_time_s).count() << " ms" << endl;
//
//    // Вывод результатов и времени выполнения
//    //cout << "\nOriginal Text: " << inputText1 << endl;
//    //cout << "\nEncrypted Text: " << encryptedText1 << endl;
//    //cout << "\nDecrypted Text: " << decryptedText1 << endl;
//
//
//    //ПАРАЛЛЕЛЬНО
//    cout << "\n----------------PARALLEL----------------\n";
//
//    int rank;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    const string key = key1; // Замените на ваш ключ
//    string input_text;
//
//    if (rank == 0) {
//        input_text = readTextFromFile("input3.txt"); // Здесь считывается текст из файла
//    }
//
//    // Рассылка размера текста всем процессам
//    int input_size = input_text.size();
//    MPI_Bcast(&input_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
//
//    // Отправка текста всем процессам
//    MPI_Bcast(&input_text[0], input_size, MPI_CHAR, 0, MPI_COMM_WORLD);
//
//    // Шифрование текста
//    auto start_time_p = chrono::steady_clock::now();
//    string encrypted_text = parallel_des_crypt(key1, input_text, DES_ENCRYPT);
//
//    // Вывод зашифрованного текста только из процесса с рангом 0
//    if (rank == 0) {
//        //cout << "\nEncrypted Text: " << encrypted_text << endl;
//    }
//
//    // Дешифрование текста
//    string decrypted_text = parallel_des_crypt(key, encrypted_text, DES_DECRYPT);
//    auto end_time_p = chrono::steady_clock::now();
//
//    // Вывод дешифрованного текста только из процесса с рангом 0
//    if (rank == 0) {
//        //cout << "\nDecrypted Text: " << decrypted_text << endl;
//    }
//
//
//    cout << "\nTotal time: " << chrono::duration<double, milli>(end_time_p - start_time_p).count() << " ms" << endl;
//    MPI_Finalize();
//    return 0;
//}

//#include <iostream>
//#include <openssl/dh.h>
//#include <openssl/evp.h>
//#include <openssl/rand.h>
//
//void generateKeyAndExchange() {
//    DH* dh = DH_new();
//    if (!dh) {
//        std::cerr << "Error creating DH parameters." << std::endl;
//        return;
//    }
//
//    int primeLength = 23; // Длина ключа (можно изменить)
//    int generator = 5;    // Примитивный корень g (замените на своё значение)
//
//    // Генерация параметров DH
//    if (DH_generate_parameters_ex(dh, primeLength, generator, nullptr) != 1) {
//        std::cerr << "Error generating DH parameters." << std::endl;
//        DH_free(dh);
//        return;
//    }
//
//    // Генерация ключей Алисы и Боба
//    if (DH_generate_key(dh) != 1) {
//        std::cerr << "Error generating DH keys." << std::endl;
//        DH_free(dh);
//        return;
//    }
//
//    // Преобразование ключа DH к типу EVP_PKEY
//    EVP_PKEY* evpKey = EVP_PKEY_new();
//    if (!evpKey) {
//        std::cerr << "Error creating EVP_PKEY." << std::endl;
//        DH_free(dh);
//        return;
//    }
//    if (EVP_PKEY_set1_DH(evpKey, dh) != 1) {
//        std::cerr << "Error setting EVP_PKEY." << std::endl;
//        EVP_PKEY_free(evpKey);
//        DH_free(dh);
//        return;
//    }
//
//    // Получение открытого ключа Боба от стороны Боба и наоборот
//    const BIGNUM* alice_pub_key;
//    DH_get0_key(dh, &alice_pub_key, nullptr);
//
//    // Преобразование открытого ключа Боба к типу EVP_PKEY
//    EVP_PKEY* bobPubKey = EVP_PKEY_new();
//    if (!bobPubKey) {
//        std::cerr << "Error creating Bob's EVP_PKEY." << std::endl;
//        EVP_PKEY_free(evpKey);
//        DH_free(dh);
//        return;
//    }
//    if (EVP_PKEY_set1_DH(bobPubKey, dh) != 1) {
//        std::cerr << "Error setting Bob's EVP_PKEY." << std::endl;
//        EVP_PKEY_free(bobPubKey);
//        EVP_PKEY_free(evpKey);
//        DH_free(dh);
//        return;
//    }
//
//    // Создание контекста для вычисления общего секретного ключа на стороне Алисы
//    EVP_PKEY_CTX* ctxA = EVP_PKEY_CTX_new(evpKey, nullptr);
//    if (!ctxA) {
//        std::cerr << "Error creating Alice's EVP_PKEY_CTX." << std::endl;
//        EVP_PKEY_free(bobPubKey);
//        EVP_PKEY_free(evpKey);
//        DH_free(dh);
//        return;
//    }
//
//    // Получение длины общего секретного ключа
//    size_t sharedSecretLenA;
//    if (EVP_PKEY_derive_init(ctxA) != 1 || EVP_PKEY_derive_set_peer(ctxA, bobPubKey) != 1 ||
//        EVP_PKEY_derive(ctxA, nullptr, &sharedSecretLenA) != 1) {
//        std::cerr << "Error computing shared secret length for Alice." << std::endl;
//        EVP_PKEY_CTX_free(ctxA);
//        EVP_PKEY_free(bobPubKey);
//        EVP_PKEY_free(evpKey);
//        DH_free(dh);
//        return;
//    }
//
//    // Выделение памяти для общего секретного ключа Алисы
//    unsigned char* sharedSecretA = (unsigned char*)malloc(sharedSecretLenA);
//    if (!sharedSecretA) {
//        std::cerr << "Error allocating memory." << std::endl;
//        EVP_PKEY_CTX_free(ctxA);
//        EVP_PKEY_free(bobPubKey);
//        EVP_PKEY_free(evpKey);
//        DH_free(dh);
//        return;
//    }
//
//    // Вычисление общего секретного ключа на стороне Алисы
//    if (EVP_PKEY_derive(ctxA, sharedSecretA, &sharedSecretLenA) != 1) {
//        std::cerr << "Error computing shared secret key for Alice." << std::endl;
//        free(sharedSecretA);
//        EVP_PKEY_CTX_free(ctxA);
//        EVP_PKEY_free(bobPubKey);
//        EVP_PKEY_free(evpKey);
//        DH_free(dh);
//        return;
//    }
//
//    // Использование общего секретного ключа для шифрования сообщений между Алисой и Бобом
//
//    // Очистка памяти и освобождение ресурсов
//    free(sharedSecretA);
//    EVP_PKEY_CTX_free(ctxA);
//    EVP_PKEY_free(bobPubKey);
//    EVP_PKEY_free(evpKey);
//    DH_free(dh);
//}
//
//int main() {
//    generateKeyAndExchange();
//    return 0;
//}

#include <iostream>
#include <openssl/dh.h>
#include <openssl/engine.h>
#include <openssl/rand.h>

void printError(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    exit(EXIT_FAILURE);
}

void printKey(const std::string& name, const BIGNUM* key) {
    char* hexKey = BN_bn2hex(key);
    std::cout << name << " key: " << hexKey << std::endl;
    OPENSSL_free(hexKey);
}

int main() {
    // Инициализация OpenSSL
    OpenSSL_add_all_algorithms();

    // Создание параметров обмена ключами для первого участника
    DH* dh1 = DH_new();
    if (!dh1) {
        printError("Failed to create DH parameters for participant 1");
    }

    // Генерация параметров для первого участника
    if (DH_generate_parameters_ex(dh1, 256, DH_GENERATOR_2, nullptr) != 1) {
        printError("Failed to generate DH parameters for participant 1");
    }

    // Генерация ключей для первого участника
    if (DH_generate_key(dh1) != 1) {
        printError("Failed to generate DH key for participant 1");
    }

    // Получение открытого ключа для первого участника
    const BIGNUM* pubKey1;
    DH_get0_key(dh1, &pubKey1, nullptr);
    printKey("Participant 1 Public", pubKey1);

    // Создание параметров обмена ключами для второго участника
    DH* dh2 = DH_new();
    if (!dh2) {
        printError("Failed to create DH parameters for participant 2");
    }

    // Копирование параметров первого участника для второго участника
    BIGNUM* p1 = BN_dup(DH_get0_p(dh1));
    BIGNUM* q1 = BN_dup(DH_get0_q(dh1));
    BIGNUM* g1 = BN_dup(DH_get0_g(dh1));
    if (!p1 || !q1 || !g1) {
        printError("Failed to duplicate DH parameters for participant 2");
    }

    if (!DH_set0_pqg(dh2, p1, q1, g1)) {
        printError("Failed to set DH parameters for participant 2");
    }

    // Освобождение ресурсов параметров первого участника, так как они больше не нужны
    BN_free(p1);
    BN_free(q1);
    BN_free(g1);

    // Генерация ключей для второго участника
    if (DH_generate_key(dh2) != 1) {
        printError("Failed to generate DH key for participant 2");
    }

    // Получение открытого ключа для второго участника
    const BIGNUM* pubKey2;
    DH_get0_key(dh2, &pubKey2, nullptr);
    printKey("Participant 2 Public", pubKey2);

    // Вычисление общего секрета для первого участника
    unsigned char* secret1 = new unsigned char[DH_size(dh1)];
    int secretLen1 = DH_compute_key(secret1, pubKey2, dh1);
    if (secretLen1 < 0) {
        printError("Failed to compute shared secret for participant 1");
    }

    // Вычисление общего секрета для второго участника
    unsigned char* secret2 = new unsigned char[DH_size(dh2)];
    int secretLen2 = DH_compute_key(secret2, pubKey1, dh2);
    if (secretLen2 < 0) {
        printError("Failed to compute shared secret for participant 2");
    }

    std::cout << "Shared secret 1: ";
    for (int i = 0; i < secretLen1; ++i) {
        printf("%02x", secret1[i]);
    }
    std::cout << std::endl;

    std::cout << "Shared secret 2: ";
    for (int i = 0; i < secretLen2; ++i) {
        printf("%02x", secret2[i]);
    }
    std::cout << std::endl;

    // Освобождение ресурсов
    delete[] secret1;
    delete[] secret2;
    DH_free(dh1);
    DH_free(dh2);

    // Очистка и выход из OpenSSL
    ENGINE_cleanup();
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
    ERR_free_strings();

    return 0;
}
