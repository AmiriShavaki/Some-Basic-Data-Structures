#include <iostream>
#include <string>

using namespace std;

class Node {
	private:
		string* value;
		Node* next;
		Node* prev;
		
	public:
		Node(string& value, Node* next, Node* prev);
		string* getValue() { return value; }
		Node* getNext() { return next; }
		Node* getPrev() { return prev; }
		void setNext(Node* newNext) { next = newNext; }
		void setPrev(Node* newPrev) { prev = newPrev; }
};

Node::Node(string& value, Node* next, Node* prev) {
	this -> value = new string;
	*(this -> value) = value;
	this -> next = next;
	this -> prev = prev;
}

class DLL {
	private:
		int filled;
		int ptr;
		Node* ptrPtr;
		Node* front;
		Node* rear;
		
	public:
		DLL() { front = NULL; rear = NULL; filled = 0; ptr = 0; }
		bool insert_front(string value);
		bool insert_rear(string value);
		bool insert_after_value(string previous, string value);
		bool insert_after_index(int index, string value);
		bool delete_value(string value);
		bool delete_index(int index);
		string next();
		string previous();
		string get(int index);
		string getFront() { return (is_empty() ? "0" : *(front -> getValue())); }
		string getRear() { return (is_empty() ? "0" : *(rear -> getValue())); }
		bool clear();
		bool is_empty() { return filled == 0; }
		int size() { return filled; }
};

bool DLL::clear() {
	if (is_empty()) {
		return false;
	}
	filled = 0;
	ptr = 0;
	front = NULL;
	rear = NULL;
	return true;
}

string DLL::get(int index) {
	Node* tmpPtr = front;
	int i = 0;
	while (tmpPtr != NULL) {
		if (index == i) {
			return *(tmpPtr -> getValue());
		}
		tmpPtr = tmpPtr -> getNext();
		i++;
	}
	return "0";	
}

string DLL::previous() {
	if (0 >= ptr) {
		return "0";
	}
	ptr--;
	ptrPtr = ptrPtr -> getPrev();
	return *(ptrPtr -> getValue());
}

string DLL::next() {
	if (filled - 1 <= ptr) {
		return "0";
	}
	if (ptr == 0) {
		ptrPtr = front;
	}
	ptr++;
	ptrPtr = ptrPtr -> getNext();
	return *(ptrPtr -> getValue());
}

bool DLL::delete_index(int index) {
	Node* tmpPtr = front;
	int i = 0;
	while (tmpPtr != NULL) {
		if (i == index) {
			if (tmpPtr -> getPrev() != NULL) {
				tmpPtr -> getPrev() -> setNext(tmpPtr -> getNext());
			}
			if (tmpPtr -> getNext() != NULL) {
				tmpPtr -> getNext() -> setPrev(tmpPtr -> getPrev());
			}
			if (tmpPtr == front) {
				front = tmpPtr -> getNext();
			}
			if (tmpPtr == rear) {
				rear = tmpPtr -> getPrev();
			}
			filled--;
			return true;
		}
		tmpPtr = tmpPtr -> getNext();
		i++;
	}
	return false;	
}

bool DLL::delete_value(string value) {
	Node* tmpPtr = front;
	while (tmpPtr != NULL && value != "0") {
		if (*(tmpPtr -> getValue())== value) {
			if (tmpPtr -> getPrev() != NULL) {
				tmpPtr -> getPrev() -> setNext(tmpPtr -> getNext());
			}
			if (tmpPtr -> getNext() != NULL) {
				tmpPtr -> getNext() -> setPrev(tmpPtr -> getPrev());
			}
			if (tmpPtr == front) {
				front = tmpPtr -> getNext();
			}
			if (tmpPtr == rear) {
				rear = tmpPtr -> getPrev();
			}
			filled--;
			return true;
		}
		tmpPtr = tmpPtr -> getNext();
	}
	return false;
}

bool DLL::insert_after_index(int index, string value) {
	Node* tmpPtr = front;
	int i = 0;
	while (tmpPtr != NULL && value != "0") {
		if (index == i) {
			Node* newElem = new Node(value, tmpPtr -> getNext(), tmpPtr);
			if (tmpPtr -> getNext() != NULL) {
				tmpPtr -> getNext() -> setPrev(newElem);
			} else {
				rear = newElem;
			}
			tmpPtr -> setNext(newElem);
			filled++;
			return true;
		}
		tmpPtr = tmpPtr -> getNext();
		i++;
	}
	return false;
}

bool DLL::insert_after_value(string previous, string value) {
	Node* tmpPtr = front;
	while (tmpPtr != NULL && value != "0") {
		if (*(tmpPtr -> getValue()) == previous) {
			Node* newElem = new Node(value, tmpPtr -> getNext(), tmpPtr);
			if (tmpPtr -> getNext() != NULL) {
				tmpPtr -> getNext() -> setPrev(newElem);
			} else {
				rear = newElem;
			}
			tmpPtr -> setNext(newElem);
			filled++;
			return true;
		}
		tmpPtr = tmpPtr -> getNext();
	}
	return false;
}

bool DLL::insert_front(string value) {
	if (value == "0") {
		return false;
	}
	Node* newElem = new Node(value, NULL, NULL);
	if (is_empty()) {
		front = newElem;
		rear = newElem;
	} else {
		newElem -> setNext(front);
		front -> setPrev(newElem);
		front = newElem;
	}
	filled++;
	return true;
}

bool DLL::insert_rear(string value) {
	if (value == "0") {
		return false;
	}
	Node* newElem = new Node(value, NULL, NULL);
	if (is_empty()) {
		front = newElem;
		rear = newElem;
	} else {
		newElem -> setPrev(rear);
		rear -> setNext(newElem);
		rear = newElem;
	}
	filled++;
	return true;
}

int main() {
	DLL l;
	string op;
	while (cin >> op) {
		if (op == "insert_front") {
			string newElem;
			cin >> newElem;
			cout << (l.insert_front(newElem) ? "true" : "false") << endl;
		} else if (op == "insert_rear") {
			string newElem;
			cin >> newElem;
			cout << (l.insert_rear(newElem) ? "true" : "false") << endl;
		} else if (op == "front") {
			cout << l.getFront() << endl;
		} else if (op == "rear") {
			cout << l.getRear() << endl;
		} else if (op == "is_empty") {
			cout << (l.is_empty() ? "true" : "false") << endl;
		} else if (op == "size") {
			cout << l.size() << endl;
		} else if (op == "clear") {
			cout << (l.clear() ? "true" : "false") << endl;
		} else if (op == "insert_after_value") {
			string value;
			string previous;
			cin >> previous >> value;
			cout << (l.insert_after_value(previous, value) ? "true" : "false") << endl;
		} else if (op == "insert_after_index") {
			string value;
			int index;
			cin >> index >> value;
			cout << (l.insert_after_index(index, value) ? "true" : "false") << endl;
		} else if (op == "delete_value") {
			string value;
			cin >> value;
			cout << (l.delete_value(value) ? "true" : "false") << endl;
		} else if (op == "delete_index") {
			int index;
			cin >> index;
			cout << (l.delete_index(index) ? "true" : "false") << endl;
		} else if (op == "next") {
			cout << l.next() << endl;
		} else if (op == "previous") {
			cout << l.previous() << endl;
		} else if (op == "get") {
			int index;
			cin >> index;
			cout << l.get(index) << endl;
		} 
	}
	return 0;
}

