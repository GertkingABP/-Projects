#include <iostream>
#include <Windows.h>
#include <Wincrypt.h>
#include <fstream>

#pragma comment(lib, "crypt32.lib")
using namespace std;

//-----------------------------------Генерация закрытого и открытого ключей-----------------------------------//
BOOL GenerateKeyPair(HCRYPTPROV hCryptProv, HCRYPTKEY& hPrivateKey, HCRYPTKEY& hPublicKey)
{
    BOOL bSuccess = FALSE;

    if (CryptGenKey(hCryptProv, AT_SIGNATURE, CRYPT_EXPORTABLE, &hPrivateKey))
    {
        //Получение открытого ключа из закрытого
        DWORD dwPublicKeyLen = 0;
        if (CryptExportKey(hPrivateKey, 0, PUBLICKEYBLOB, 0, NULL, &dwPublicKeyLen))
        {
            BYTE* pbPublicKeyData = new BYTE[dwPublicKeyLen];
            if (CryptExportKey(hPrivateKey, 0, PUBLICKEYBLOB, 0, pbPublicKeyData, &dwPublicKeyLen))
            {
                if (CryptImportKey(hCryptProv, pbPublicKeyData, dwPublicKeyLen, 0, 0, &hPublicKey))
                {
                    bSuccess = TRUE;
                    // Печать ключей
                    DWORD dwPrivateKeyLen = 0;
                    if (CryptExportKey(hPrivateKey, 0, PRIVATEKEYBLOB, 0, NULL, &dwPrivateKeyLen))
                    {
                        BYTE* pbPrivateKeyData = new BYTE[dwPrivateKeyLen];
                        if (CryptExportKey(hPrivateKey, 0, PRIVATEKEYBLOB, 0, pbPrivateKeyData, &dwPrivateKeyLen))
                        {
                            cout << "\nПолучен закрытый ключ: ";
                            for (DWORD i = 0; i < dwPrivateKeyLen; i++)
                                printf("%02X ", pbPrivateKeyData[i]);

                            cout << endl;
                        }
                        delete[] pbPrivateKeyData;
                    }

                    cout << "\n\nПолучен открытый ключ: ";
                    for (DWORD i = 0; i < dwPublicKeyLen; i++)
                        printf("%02X ", pbPublicKeyData[i]);

                    cout << endl;
                }
            }

            delete[] pbPublicKeyData;
        }
    }

    return bSuccess;
}

//---------------------------------------------Подписывание файла---------------------------------------------//
BOOL SignFile(HCRYPTPROV hCryptProv, const string& filePath, HCRYPTKEY hPrivateKey)
{
    BOOL bSuccess = FALSE;

    ifstream file(filePath, ios::binary);
    if (file)
    {
        //Чтение содержимого
        file.seekg(0, ios::end);
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);

        BYTE* pbFileData = new BYTE[fileSize];
        file.read(reinterpret_cast<char*>(pbFileData), fileSize);

        // Создание хэша файла
        HCRYPTHASH hHash;
        if (CryptCreateHash(hCryptProv, CALG_SHA1, 0, 0, &hHash))
        {
            if (CryptHashData(hHash, pbFileData, fileSize, 0))
            {
                // Получение размера сигнатуры
                DWORD dwSignatureLen = 0;
                if (CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, NULL, &dwSignatureLen))
                {
                    // Выделение памяти под сигнатуру
                    BYTE* pbSignature = new BYTE[dwSignatureLen];
                    if (CryptSignHash(hHash, AT_SIGNATURE, NULL, 0, pbSignature, &dwSignatureLen))
                    {
                        // Сохранение сигнатуры в файл
                        ofstream signatureFile(filePath + ".sig", ios::binary);
                        signatureFile.write(reinterpret_cast<const char*>(pbSignature), dwSignatureLen);
                        signatureFile.close();

                        bSuccess = TRUE;
                    }

                    delete[] pbSignature;
                }
            }

            CryptDestroyHash(hHash);
        }

        delete[] pbFileData;
    }

    return bSuccess;
}

//-------------------------------------------Проверка подписи файла-------------------------------------------//
BOOL VerifySignature(HCRYPTPROV hCryptProv, const string& filePath, HCRYPTKEY hPublicKey)
{
    BOOL bSuccess = FALSE;

    ifstream file(filePath, ios::binary);
    if (file)
    {
        //Чтение содержимого файла
        file.seekg(0, ios::end);
        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);

        BYTE* pbFileData = new BYTE[fileSize];
        file.read(reinterpret_cast<char*>(pbFileData), fileSize);

        //Создание хэша файла
        HCRYPTHASH hHash;
        if (CryptCreateHash(hCryptProv, CALG_SHA1, 0, 0, &hHash))
        {
            if (CryptHashData(hHash, pbFileData, fileSize, 0))
            {
                //Чтение сигнатуры из файла
                ifstream signatureFile(filePath + ".sig", ios::binary);
                signatureFile.seekg(0, ios::end);
                streampos signatureSize = signatureFile.tellg();
                signatureFile.seekg(0, ios::beg);

                BYTE* pbSignature = new BYTE[signatureSize];
                signatureFile.read(reinterpret_cast<char*>(pbSignature), signatureSize);

                // Проверка сигнатуры
                if (CryptVerifySignature(hHash, pbSignature, signatureSize, hPublicKey, NULL, 0))
                {
                    bSuccess = TRUE;
                    cout << "Подпись верна.\n";
                }

                else
                    cout << "Подпись недействительна.\n";

                delete[] pbSignature;
            }

            CryptDestroyHash(hHash);
        }

        delete[] pbFileData;
    }

    return bSuccess;
}

//----------------------------------------------------MAIN----------------------------------------------------//
int main()
{
    setlocale(LC_ALL, "Rus");
    cout << "1.Генерация ключей:" << endl;
    HCRYPTPROV hCryptProv;
    if (CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        HCRYPTKEY hPrivateKey;
        HCRYPTKEY hPublicKey;

        if (GenerateKeyPair(hCryptProv, hPrivateKey, hPublicKey))
        {
            string filePath = "input_text.txt";

            cout << "\n\n\n2.Подписание файла:" << endl;
            if (SignFile(hCryptProv, filePath, hPrivateKey))
                cout << "\nФайл успешно подписан.\n";
            
            else
                cout << "Ошибка подписывания файла.\n";

            cout << "\n\n\n3.Проверка подписи:" << endl;
            if (VerifySignature(hCryptProv, filePath, hPublicKey))
                cout << "Подпись файла успешно проверена.\n";

            cout << "\n\n\n4.Проверка подписи по разным ключам:" << endl;
            cout << "Новые ключи:" << endl;
            HCRYPTKEY hPrivateKey2;
            HCRYPTKEY hPublicKey2;
            if (GenerateKeyPair(hCryptProv, hPrivateKey2, hPublicKey2))
            {
                filePath = "input_text.txt";

                cout << "\n\n\nПроверка подписи:" << endl;
                if (VerifySignature(hCryptProv, filePath, hPublicKey2))
                    cout << "Подпись файла успешно проверена.\n";

            }

            //Освобождение ресурсов
            CryptDestroyKey(hPrivateKey);
            CryptDestroyKey(hPublicKey);
            CryptDestroyKey(hPrivateKey2);
            CryptDestroyKey(hPublicKey2);
        }

        else
            cout << "Ошибка генерации ключевой пары.\n";

        CryptReleaseContext(hCryptProv, 0);
    }

    else
        cout << "Ошибка при получении контекста CryptoAPI.\n";
}