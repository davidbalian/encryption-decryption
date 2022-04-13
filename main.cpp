#include <iostream>
#include <string>
#include "Cipher.h"

using namespace std;

int main() {
    Cipher cipher;
    string choice = "0";

    do {
        cout << "\n1. Encode a message";
        cout << "\n2. Decode a message";
        cout << "\n3. Exit";

        cout << "\n\nYour choice: ";
        cin >> choice;
        cout << endl;

       if (choice == "1") {
           cipher.encrypt();
       } else if (choice == "2") {
           cipher.decrypt();
       } else if (choice == "3") {
           cout << "\nExiting.";
       } else {
           cout << "\nWrong input. Try again.";
       }
    } while (choice != "3");

    return 0;
}