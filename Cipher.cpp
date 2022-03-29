//
// Created by David Balian on 26/03/2022.
//

// 03043 142022 32220 41204 13123 03233 01104

#include "Cipher.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

#define SIZE 100

using namespace std;

Cipher::Cipher() {
    cout << "\nEncryption/Decryption System\n" << endl;
}

void Cipher::encrypt() {
    key = "";
    plaintext = "";
    plaintextInNumbers = "";
    ciphertext = "";

    cout << "\nEnter your message: ";
    cin.ignore();
    getline(cin, plaintext);

    formatMessage(0, plaintext);
    plainTextToNumbers(plaintext);
    cout << "\nMessage after formatting: " << plaintext;
    cout << "\nMessage in number form: " << plaintextInNumbers << endl;

    getKey();

    int cols = key.length();
    int rows = floor(((float)plaintextInNumbers.length() / (float)key.length()) + 1);

    char unsortedKeyArray[SIZE][SIZE];
    char sortedKeyArray[SIZE][SIZE];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            unsortedKeyArray[i][j] = plaintextInNumbers[(i * cols) + j];
            sortedKeyArray[i][j] = plaintextInNumbers[(i * cols) + j];
        }
    }

    for (int i = 0; i < key.length(); ++i) {
        cout << left << setw(4) << key[i];
    }

    cout << endl;

    print2DArray(unsortedKeyArray, rows, cols);

    sortKeyAndArrays(sortedKeyArray);

    cout << endl;

    for (int i = 0; i < key.length(); ++i) {
        cout << left << setw(4) << key[i];
    }

    cout << endl;

    print2DArray(sortedKeyArray, rows, cols);

    assignCipherText(sortedKeyArray, rows, cols);

    cout << endl;

    cout << "\nFinal ciphertext: " << ciphertext << endl;

    cout << endl;
}

void Cipher::formatMessage(int keyOrMsg, string msgToFormat) {
    string tempMsg;

    for (int i = 0; i < msgToFormat.length(); ++i) {
        if (isalpha(msgToFormat[i])) {
            tempMsg += toupper(msgToFormat[i]);
        }
    }

    if (keyOrMsg) {
        key = tempMsg;
    } else {
        plaintext = tempMsg;
    }
}

int Cipher::validateKey(string keyToValidate) {
    for (int i = 0; i < keyToValidate.length(); ++i) {
        for (int j = i + 1; j < keyToValidate.length(); ++j) {
            if (keyToValidate[i] == keyToValidate[j]) {
                return 0;
            }
        }
    }

    return 1;
}

void Cipher::getKey() {
    int keyIsValid;

    do {
        cout << "\nEnter key: ";
        cin >> key;

        keyIsValid = validateKey(key);

        if (!keyIsValid) {
            cout << "\nInvalid key. Enter Again\n";
        }
    } while (!keyIsValid);

    formatMessage(1, key);
    cout << "\nFormatted key: " << key << endl << endl;
}

void Cipher::plainTextToNumbers(string plainTextToConvert) {
    for (int x = 0; x < plainTextToConvert.length(); ++x) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (plaintext[x] == alphabetArray[i][j]) {
                    plaintextInNumbers += to_string(i);
                    plaintextInNumbers += to_string(j);
                }
            }
        }

        if (plaintext[x] == 'Z') {
            plaintextInNumbers += "31";
        }
    }
}

void Cipher::print2DArray(char array[SIZE][SIZE], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
                cout << left << setw(4);
                isnumber(array[i][j]) ? cout << array[i][j] : cout << '-';
        }

        cout << "\n";
    }
}

void Cipher::sortKeyAndArrays(char sorted[SIZE][SIZE]) {
    char temp;

    for (int i = 0; i < key.length() - 1; ++i) {
        for (int j = 0; j < key.length() - i - 1; ++j) {
            if (key[j] > key[j + 1]) {
                temp = key[j];
                key[j] = key[j + 1];
                key[j + 1] = temp;

                for (int x = 0; x < SIZE; ++x) {
                    char tempChar = sorted[x][j];
                    sorted[x][j] = sorted[x][j + 1];
                    sorted[x][j + 1] = tempChar;
                }
            }
        }
    }
}

void Cipher::assignCipherText(char sorted[SIZE][SIZE], int rows, int cols) {
//    for (int j = 0; j <= rows; ++j) {
//        for (int i = 0; i < cols; ++i) {
//            if (isnumber(sorted[i][j]))
//                ciphertext += sorted[i][j];
//        }
//    }

    for (int i = 0; i <= rows; ++i) {
        ciphertext += ' ';
        for (int j = 0; j < cols; ++j) {
                if (isnumber(sorted[j][i])) {
                    ciphertext += sorted[j][i];
                }
        }
    }
}

void Cipher::decrypt() {
    key = "";
    plaintext = "";
    plaintextInNumbers = "";
    cipherToDecrypt = "";

    getMsgToDecrypt();
    getCiphertextLength();

    cout << "\nYour message is: " << cipherToDecrypt << endl;

    getKey();
    sortKey();

    int cols = key.length();
    int rows = floor(((float)actualCiphertextLength / (float)key.length()) + 1);

    char unsortedKeyArray[SIZE][SIZE];
    char sortedKeyArray[SIZE][SIZE];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int currIndex = (j * rows) + i;

            sortedKeyArray[i][j] = cipherToDecrypt[currIndex];
            unsortedKeyArray[i][j] = cipherToDecrypt[currIndex];
        }
    }


    cout << endl;

    for (int i = 0; i < sortedKey.length(); ++i) {
        cout << left << setw(4) << sortedKey[i];
    }

    cout << endl;

    print2DArray(sortedKeyArray, rows, cols);

    sortBackKeyArray(key, sortedKey, unsortedKeyArray);


    cout << endl;
    for (int i = 0; i < cols; ++i) {
        if (isspace(unsortedKeyArray[0][i])) {
            for (int j = 0; j < rows; ++j) {
                cout << unsortedKeyArray[j][i] << endl;

                char temp = unsortedKeyArray[j][i];
                unsortedKeyArray[j][i] = unsortedKeyArray[j + 1][i];
                unsortedKeyArray[j + 1][i] = temp;
            }
        }
    }
    cout << endl;

    cout << endl;

    for (int i = 0; i < key.length(); ++i) {
        cout << left << setw(4) << key[i];
    }

    cout << endl;

    print2DArray(unsortedKeyArray, rows, cols);

    cipherToPlain(unsortedKeyArray, rows, cols);
}

void Cipher::getMsgToDecrypt() {
    int msgIsValid;

    do {
        cout << "\nEnter encrypted message: ";
        cin.ignore();
        getline(cin, cipherToDecrypt);

        msgIsValid = validateMsgToDecrypt(cipherToDecrypt);

        if (!msgIsValid) {
            cout << "\nWrong Input. Try Again." << endl;
        }
    } while(!msgIsValid);
}

int Cipher::validateMsgToDecrypt(string msgToValidate) {
    for (int i = 0; i < msgToValidate.length(); ++i) {
        if (isalpha(msgToValidate[i]))
            return 0;
    }

    return 1;
}

void Cipher::sortKey() {
    char temp;
    sortedKey = key;

    for (int i = 0; i < sortedKey.length() - 1; ++i) {
        for (int j = 0; j < sortedKey.length() - i - 1; ++j) {
            if (sortedKey[j] > sortedKey[j + 1]) {
                temp = sortedKey[j];
                sortedKey[j] = sortedKey[j + 1];
                sortedKey[j + 1] = temp;
            }
        }
    }
}

void Cipher::getCiphertextLength() {
    int length = 0;

    for (int i = 0; i < cipherToDecrypt.length(); ++i)
        if (isnumber(cipherToDecrypt[i]))
            length++;

    actualCiphertextLength = length;
}

void Cipher::sortBackKeyArray(string unsortKey, string sKey, char sorted[][SIZE]) {
    for (int i = 0; i < unsortKey.length(); ++i) {
        for (int j = 0; j < unsortKey.length(); ++j) {
            if (unsortKey[i] == sKey[j]) {
                char temp = sKey[i];
                sKey[i] = sKey[j];
                sKey[j] = temp;

                for (int x = 0; x < SIZE; ++x) {
                    char tempChar = sorted[x][j];
                    sorted[x][j] = sorted[x][i];
                    sorted[x][i] = tempChar;
                }
            }
        }
    }
}

void Cipher::cipherToPlain(char unsortedArray[][SIZE], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (isnumber(unsortedArray[i][j])) {
                plaintextInNumbers += unsortedArray[i][j];
            }
        }
    }

    for (int i = 0; i < plaintextInNumbers.length() - 1; i += 2) {
        char rowItem = plaintextInNumbers[i];
        char colItem = plaintextInNumbers[i + 1];

        plaintext += alphabetArray[rowItem - '0'][colItem - '0'];
    }

    cout << "\n" << plaintextInNumbers << endl;
    cout << "\nFinal decrypted message: " << plaintext << endl;
}

