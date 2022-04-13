//
// Created by David Balian on 26/03/2022.
//

#include "Cipher.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

#define SIZE 100

using namespace std;

Cipher::Cipher() {
    cout << "\nEncryption/Decryption System" << endl;
    actualCiphertextLength = 0;
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

    // initializes both sorted and unsorted arrays with plain text in numbers
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            unsortedKeyArray[i][j] = plaintextInNumbers[(i * cols) + j];
            sortedKeyArray[i][j] = plaintextInNumbers[(i * cols) + j];
        }
    }

    // prints unsorted key array
    for (int i = 0; i < key.length(); ++i) {
        cout << left << setw(4) << key[i];
    }

    cout << endl;

    print2DArray(unsortedKeyArray, rows, cols);

    sortKeyAndArrays(sortedKeyArray);

    cout << endl;

    // prints sorted key array
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

// capitalizes all letters and removes numbers/symbols from message or key
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

// validates key - checks if it contains each letter only once
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

// gets key from user
void Cipher::getKey() {
    int keyIsValid;

    do {
        cout << "\nEnter key: ";
        cin >> key;

        formatMessage(1, key);

        keyIsValid = validateKey(key);

        if (!keyIsValid) {
            cout << "\nInvalid key. Enter Again\n";
        }
    } while (!keyIsValid);

    formatMessage(1, key);
    cout << "\nFormatted key: " << key << endl << endl;
}

// converts plaintext message to numbers using alphabet array
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

// prints a 2d array
void Cipher::print2DArray(char array[SIZE][SIZE], int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << left << setw(4);
            isnumber(array[i][j]) ? cout << array[i][j] : cout << '-';
        }

        cout << "\n";
    }
}

// sorts characters of key and array columns based on key
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

// assigns value to ciphertext using sorted key array
void Cipher::assignCipherText(char sorted[SIZE][SIZE], int rows, int cols) {
    for (int i = 0; i < cols; ++i) {
        ciphertext += ' ';
        for (int j = 0; j < rows; ++j) {
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

    // removes spaces from cipher that might interfere with array
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            int currIndex = (j * rows) + i;

            if (isspace(cipherToDecrypt[currIndex + 1]) && isnumber(cipherToDecrypt[currIndex]) && i >= rows - 1) {
                cipherToDecrypt.erase(currIndex + 1, 1);
            }

            sortedKeyArray[i][j] = cipherToDecrypt[currIndex];
            unsortedKeyArray[i][j] = cipherToDecrypt[currIndex];
        }
    }


    cout << endl;

    // prints key and sorted array
    for (int i = 0; i < sortedKey.length(); ++i) {
        cout << left << setw(4) << sortedKey[i];
    }

    cout << endl;

    print2DArray(sortedKeyArray, rows, cols);

    // gets unsorted key array and sorts it back to match original  key
    sortBackKeyArray(key, sortedKey, unsortedKeyArray);


    cout << endl;

    // prints original key array
    for (int i = 0; i < key.length(); ++i) {
        cout << left << setw(4) << key[i];
    }

    cout << endl;

    print2DArray(unsortedKeyArray, rows, cols);

    cipherToPlain(unsortedKeyArray, rows, cols);
}

// gets message to decrypt from user
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

// validates message to decrypt - only accepts numbers and spaces
int Cipher::validateMsgToDecrypt(string msgToValidate) {
    for (int i = 0; i < msgToValidate.length(); ++i) {
        if (!isnumber(msgToValidate[i]) && !isspace(msgToValidate[i]))
            return 0;
    }

    return 1;
}

// sorts key alphabetically
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

// gets actual length of cipher without the spaces
void Cipher::getCiphertextLength() {
    int length = 0;

    for (int i = 0; i < cipherToDecrypt.length(); ++i)
        if (isnumber(cipherToDecrypt[i]))
            length++;

    actualCiphertextLength = length;
}

// sorts array to match original key
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

// converts from cipher to plaintext based on alphabet array
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

