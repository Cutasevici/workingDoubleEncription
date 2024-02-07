#include "LinkedList.h"

void LinkedList::insertNode(const string& planeText) {
    Node* newNode = new Node(planeText);
    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    length++;
}

//functia de afisare
void LinkedList::display() {
    Node* current = head;
    int index = 0;
    while (current != nullptr) {
        cout << "Index: " << index << " - Node Info: " << current->planeText << endl;
        current = current->next;
        index++;
    }
}
// aplica vigener
void LinkedList::applyVigenereCipher(int index, const string& key) {
    if (index < 0 || index >= length) {
        cout << "Invalid index. Please provide a valid index within the list." << endl;
        return;
    }

    if (head == nullptr) {
        cout << "List is empty. Cannot apply Vigenere cipher." << endl;
        return;
    }
    Node* current = head;
    int currentIndex = 0;
    while (current != nullptr) {
        if (currentIndex == index) {
            if (current->XOR) {
                cout << "XOR flag is set to true. Cannot apply Vigenere cipher." << endl;
                return;
            }


            string originalText = current->planeText;
            size_t keyIndex = 0;


            for (size_t i = 0; i < current->planeText.length(); i++) {
                char c = current->planeText[i];
                char k = key[keyIndex % key.length()];
                if (isalpha(c)) {
                    char base = islower(c) ? 'a' : 'A';
                    char kBase = islower(k) ? 'a' : 'A';
                    current->planeText[i] = ((c - base + (k - kBase)) % 26) + base;
                    keyIndex++;
                }
            }
            cout << "Vigenere cipher applied successfully." << endl;
            current->vigenere = true; // schimba steagul
            return;
        }
        current = current->next;
        currentIndex++;
    }

    cout << "Node at index " << index << " not found in the list." << endl;
}

// decripteaza vigenere
void LinkedList::decryptVigenereCipher(int index, const string& key) {
    if (index < 0 || index >= length) {
        cout << "Invalid index. Please provide a valid index within the list." << endl;
        return;
    }

    Node* current = head;
    int currentIndex = 0;
    while (current != nullptr) {
        if (currentIndex == index) {
            if (current->XOR) {
                cout << "XOR flag is set to true. Please decrypt XOR first." << endl;
                return;
            }

            if (current->vigenere) {
                string originalText = current->planeText;
                size_t keyIndex = 0;
                for (size_t i = 0; i < current->planeText.length(); i++) {
                    char c = current->planeText[i];
                    char k = key[keyIndex % key.length()];
                    if (isalpha(c)) {
                        char base = islower(c) ? 'a' : 'A';
                        char kBase = islower(k) ? 'a' : 'A';
                        int diff = (c - base) - (k - kBase);
                        if (diff < 0) {
                            diff += 26; // Handle negative results
                        }
                        current->planeText[i] = (diff % 26) + base;
                        keyIndex++;
                    }
                }
                cout << "Vigenere cipher decrypted successfully." << endl;
                current->vigenere = false;
            }
            else {
                cout << "Decryption not possible. Vigenere flag is not set for this node." << endl;
            }
            return;
        }
        current = current->next;
        currentIndex++;
    }

    cout << "Node at index " << index << " not found in the list." << endl;
}
// aplica one time pad
void LinkedList::applyVernamCipher(int index, const string& key) {
    if (index < 0 || index >= length) {
        cout << "Invalid index. Please provide a valid index within the list." << endl;
        return;
    }

    Node* current = head;
    for (int currentIndex = 0; current != nullptr && currentIndex <= index; current = current->next, currentIndex++) {
        if (currentIndex == index) {
            string extendedKey = key;
            while (extendedKey.length() < current->planeText.length()) {
                extendedKey += key.substr(0, min(key.length(), current->planeText.length() - extendedKey.length()));
            }

            for (size_t i = 0; i < current->planeText.length(); i++) {
                current->planeText[i] = current->planeText[i] ^ extendedKey[i];
            }

            cout << "Vernam cipher applied successfully." << endl;
            current->XOR = true;
            return;
        }
    }

    cout << "Node at index " << index << " not found in the list." << endl;
}

void LinkedList::decryptVernamCipher(int index, const string& key) {
    if (index < 0 || index >= length) {
        cout << "Invalid index. Please provide a valid index within the list." << endl;
        return;
    }

    Node* current = head;
    for (int currentIndex = 0; current != nullptr && currentIndex <= index; current = current->next, currentIndex++) {
        if (currentIndex == index) {
            string extendedKey = key;
            while (extendedKey.length() < current->planeText.length()) {
                extendedKey += key.substr(0, min(key.length(), current->planeText.length() - extendedKey.length()));
            }
            for (size_t i = 0; i < current->planeText.length(); i++) {
                current->planeText[i] = current->planeText[i] ^ extendedKey[i];
            }

            cout << "Vernam cipher decrypted successfully." << endl;
            current->XOR = false; // schimba steagul
            return;
        }
    }
    cout << "Node at index " << index << " not found in the list." << endl;
}