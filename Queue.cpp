#include <iostream>
#include <string>

using namespace std;

class Node {
	private:
		string* value;
		Node* next;
		
	public:
		Node(string& value, Node* next);
		string* getValue() { return value; }
		Node* getNext() { return next; }
		void setNext(Node* newNext) { next = newNext; }
};

Node::Node(string& value, Node* next) {
	this -> value = new string;
	*(this -> value) = value;
	this -> next = next;
}

class Queue {
	private:
		int size;
		int filled;
		Node* front;
		Node* rear;
		
	public:
		Queue(int size) { this -> size = size; filled = 0; front = NULL; rear = NULL;}
		bool enqueue(string& value);
		string dequeue();
		string getFront() { return (is_empty() ? "0" : *(front -> getValue())); }
		string getRear() { return (is_empty() ? "0" : *(rear -> getValue())); }
		bool is_empty() { return filled == 0; }
		bool is_full() { return size == filled; }
		int getSize() { return filled; }
		int capacity() { return size; }
		bool clear();
};

bool Queue::clear() {
	if (is_empty()) {
		return false;
	}
	filled = 0;
	front = NULL;
	rear = NULL;
	return true;
}

bool Queue::enqueue(string& value) {
	if (is_full() || value == "0") {
		return false;
	} 
	Node* newElem = new Node(value, NULL);
	if (is_empty()) {
		front = newElem;
		rear = newElem;
	} else {
		rear -> setNext(newElem);
		rear = newElem;
	}
	filled++;
	return true;
}

string Queue::dequeue() {
	//cout << "filled:" << filled << "   is_empty:" << is_empty() << endl;
	if (is_empty()) {
		return "0";
	} 
	string res = *(front -> getValue());
	front = front -> getNext();
	filled--;
	return res;
}

int main() {
	int n, m;
	cin >> n; //Size of the stack
	cin >> m; //Number of lines following (however I ain't use this)
	Queue q(n);
	string op;
	while (cin >> op) {
		if (op == "enqueue") {
			string newElem;
			cin >> newElem;
			cout << (q.enqueue(newElem) ? "true" : "false") << endl;
		} else if (op == "dequeue") {
			cout << q.dequeue() << endl;
		} else if (op == "front") {
			cout << q.getFront() << endl;
		} else if (op == "rear") {
			cout << q.getRear() << endl;
		} else if (op == "is_empty") {
			cout << (q.is_empty() ? "true" : "false") << endl;
		} else if (op == "is_full") {
			cout << (q.is_full() ? "true" : "false") << endl;
		} else if (op == "size") {
			cout << q.getSize() << endl;
		} else if (op == "capacity") {
			cout << q.capacity() << endl;
		} else if (op == "clear") {
			cout << (q.clear() ? "true" : "false") << endl;
		}
	}
	return 0;
}
