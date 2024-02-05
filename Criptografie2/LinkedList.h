#include <iostream>
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

	void insertNode(const string& planeText);
	void display();
	void applyVigenereCipher(int index, const string& key);
	void decryptVigenereCipher(int index, const string& key);
	void applyVernamCipher(int index, const string& key);
	void decryptVernamCipher(int index, const string& key);
};