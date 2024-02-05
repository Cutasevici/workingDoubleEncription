#include <iostream>
#include <string>
using namespace std;


class Node {
public:
	string planeText;
	string key;
	Node* next;
	bool vigenere;
	bool XOR;
	Node(string planeText) {
		this->planeText = planeText;
		next = nullptr;
	}

};

class LinkedList {
private:
	Node* head;
	Node* tail;
	int length;
public:
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		length = 0;
	}
	~LinkedList() {
		Node* current = head;
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}

	void insertNode(const string& planeText) {
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


	void display() {
		Node* current = head;
		int index = 0; // Start the index at 0
		while (current != nullptr) {
			cout << "Index: " << index << " - PlainText: " << current->planeText << endl;		
			current = current->next;
			index++;
		}
	}

    void applyVigenereCipher(int index,const string& key) {
        if (index < 0 || index >= length) {
            cout << "Invalid index. Please provide a valid index within the list." << endl;
            return;
        }

        if (head == nullptr) {
            cout << "List is empty. Cannot apply Vigenere cipher." << endl;
            return;
        }

        // Check if XOR is set to true for the current node
        Node* current = head;
        int currentIndex = 0;
        while (current != nullptr) {
            if (currentIndex == index) {
                if (current->XOR) {
                    cout << "XOR flag is set to true. Cannot apply Vigenere cipher." << endl;
                    return;
                }


                string originalText = current->planeText; // Store the original text
                size_t keyIndex = 0; // Keep track of the key index

                // Apply Vigenere cipher to the plainText in this node
                for (size_t i = 0; i < current->planeText.length(); i++) {
                    char c = current->planeText[i];
                    char k = key[keyIndex % key.length()]; // Repeating key
                    if (isalpha(c)) {
                        // Determine the base based on the character case
                        char base = islower(c) ? 'a' : 'A';
                        char kBase = islower(k) ? 'a' : 'A';
                        current->planeText[i] = ((c - base + (k - kBase)) % 26) + base;
                        keyIndex++; // Move to the next character in the key
                    }
                    // Skip non-alphabetic characters
                }
                cout << "Vigenere cipher applied successfully." << endl;
                current->vigenere = true; // Set the vigenere variable for this node to true
                return;
            }
            current = current->next;
            currentIndex++;
        }

        cout << "Node at index " << index << " not found in the list." << endl;
    }


    void decryptVigenereCipher(int index, const string& key) {
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
                    

                    string originalText = current->planeText; // Store the original text
                    size_t keyIndex = 0; // Keep track of the key index

                    // Apply Vigenere decryption to the plainText in this node
                    for (size_t i = 0; i < current->planeText.length(); i++) {
                        char c = current->planeText[i];
                        char k = key[keyIndex % key.length()]; // Repeating key
                        if (isalpha(c)) {
                            // Determine the base based on the character case
                            char base = islower(c) ? 'a' : 'A';
                            char kBase = islower(k) ? 'a' : 'A';
                            int diff = (c - base) - (k - kBase);
                            if (diff < 0) {
                                diff += 26; // Handle negative results
                            }
                            current->planeText[i] = (diff % 26) + base;
                            keyIndex++; // Move to the next character in the key
                        }
                        // Skip non-alphabetic characters
                    }
                    cout << "Vigenere cipher decrypted successfully." << endl;

                    // Reset the vigenere flag to its default value (false)
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

    void applyVernamCipher(int index, const string& key) {
        if (index < 0 || index >= length) {
            cout << "Invalid index. Please provide a valid index within the list." << endl;
            return;
        }

        Node* current = head;
        for (int currentIndex = 0; current != nullptr && currentIndex <= index; current = current->next, currentIndex++) {
            if (currentIndex == index) {
                // Extend the key to match the length of the planeText, if necessary
                string extendedKey = key;
                while (extendedKey.length() < current->planeText.length()) {
                    extendedKey += key.substr(0, min(key.length(), current->planeText.length() - extendedKey.length()));
                }

                // Apply the Vernam cipher
                for (size_t i = 0; i < current->planeText.length(); i++) {
                    // XOR the current character with the corresponding key character
                    current->planeText[i] = current->planeText[i] ^ extendedKey[i];
                }

                cout << "Vernam cipher applied successfully." << endl;
                // Optionally, set a flag to indicate that this node is encrypted with the Vernam cipher
                current->XOR = true; // Assuming you want to use this flag for indicating Vernam cipher application
                return;
            }
        }

        cout << "Node at index " << index << " not found in the list." << endl;
    }

    void decryptVernamCipher(int index, const string& key) {
        if (index < 0 || index >= length) {
            cout << "Invalid index. Please provide a valid index within the list." << endl;
            return;
        }

        Node* current = head;
        for (int currentIndex = 0; current != nullptr && currentIndex <= index; current = current->next, currentIndex++) {
            if (currentIndex == index) {
                // Extend the key to match the length of the planeText, if necessary
                string extendedKey = key;
                while (extendedKey.length() < current->planeText.length()) {
                    extendedKey += key.substr(0, min(key.length(), current->planeText.length() - extendedKey.length()));
                }

                // Apply the Vernam cipher for decryption
                for (size_t i = 0; i < current->planeText.length(); i++) {
                    // XOR the current character with the corresponding key character again to decrypt
                    current->planeText[i] = current->planeText[i] ^ extendedKey[i];
                }

                cout << "Vernam cipher decrypted successfully." << endl;
                // Reset the XOR flag to indicate decryption, if appropriate
                current->XOR = false; // This line is optional, depending on how you want to manage the encryption state
                return;
            }
        }

        cout << "Node at index " << index << " not found in the list." << endl;
    }


    











};


int main() {
    LinkedList list;
    int choice, index;
    string text, key;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert Node\n";
        cout << "2. Apply Vigenere Cipher\n";
        cout << "3. Decrypt Vigenere Cipher\n";
        cout << "4. Apply Vernam Cipher\n";
        cout << "5. Decrypt Vernam Cipher\n";
        cout << "6. Display List\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter text for new node: ";
            cin.ignore(); // Ignore newline from previous input
            getline(cin, text); // Use getline to allow spaces in input
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
            cout << "Enter node index and key for Vernam Cipher: ";
            cin >> index >> key;
            list.applyVernamCipher(index, key);
            break;
        case 5:
            cout << "Enter node index and key to decrypt Vernam Cipher: ";
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
   







	return 0;
}