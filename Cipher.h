//
// Created by David Balian on 26/03/2022.
//

#ifndef FINAL_ERG_CLION_CIPHER_H
#define FINAL_ERG_CLION_CIPHER_H

#define SIZE 100

#include <string>
using namespace std;


class Cipher {
private:
    string key;
    string plaintext;
    string plaintextInNumbers;
    string ciphertext;
    string cipherToDecrypt;
    string sortedKey;
    int actualCiphertextLength;

    char alphabetArray[5][5] = {
            {'A', 'B', 'C', 'D', 'E'},
            {'F', 'G', 'H', 'I', 'J'},
            {'K', 'L', 'M', 'N', 'O'},
            {'P', 'Q', 'R', 'S', 'T'},
            {'U', 'V', 'W', 'X', 'Y'},
    };
public:
    Cipher();

    // member functions for encryption process
    void encrypt();
    void formatMessage(int, string);
    void getKey();
    void plainTextToNumbers(string);
    static void print2DArray(char [][SIZE], int, int);
    void sortKeyAndArrays(char [][SIZE]);
    void assignCipherText(char [][SIZE], int, int);
    static int validateKey(string);

    // member functions for decryption process
    void decrypt();
    void getMsgToDecrypt();
    void sortKey();
    static int validateMsgToDecrypt(string);
    void getCiphertextLength();
    static void sortBackKeyArray(string, string, char [][SIZE]);
    void cipherToPlain(char [][SIZE], int, int);
};


#endif //FINAL_ERG_CLION_CIPHER_H
