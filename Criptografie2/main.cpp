#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;





int main() {
    LinkedList list;
    int choice, index;
    string text, key;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert Node\n";
        cout << "2. Apply Vigenere cipher\n";
        cout << "3. Decrypt Vigenere cipher\n";
        cout << "4. Apply one time pad cipher\n";
        cout << "5. Decrypt one time pad cipher\n";
        cout << "6. Display List\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter text for new node: ";
            cin.ignore(); 
            getline(cin, text); 
            list.insertNode(text);
            break;
        case 2:
            cout << "Enter node index and key for Vigenere Cipher: ";
            cin >> index >> key;
            list.applyVigenereCipher(index, key);
            break;
        case 3:
            cout << "Enter node index and key to decrypt Vigenere Cipher: ";
            cin >> index >> key;
            list.decryptVigenereCipher(index, key);
            break;
        case 4:
            cout << "Enter node index and key for One time pad Cipher: ";
            cin >> index >> key;
            list.applyVernamCipher(index, key);
            break;
        case 5:
            cout << "Enter node index and key to decrypt One time pad Cipher: ";
            cin >> index >> key;
            list.decryptVernamCipher(index, key);
            break;
        case 6:
            list.display();
            break;
        case 7:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}