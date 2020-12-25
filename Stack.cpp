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
};

Node::Node(string& value, Node* next) {
	this -> value = new string;
	*(this -> value) = value;
	this -> next = next;
}

class Stack {
	private:
		int size;
		int filled;
		Node* top;
		
	public:
		Stack(int size) { this -> size = size; filled = 0; top = NULL; }
		bool push(string& value);
		string pop();
		string peek() { return (is_empty() ? "0" : *(top -> getValue())); }
		bool is_empty() { return filled == 0; }
		bool is_full() { return size == filled; }
		int getSize() { return filled; }
		bool clear() { top = NULL; filled = 0; return true; }
};

bool Stack::push(string& value) {
	if (is_full()) {
		return false;
	} 
	Node* newElem = new Node(value, top);
	top = newElem;
	filled++;
	return true;
}

string Stack::pop() {
	//cout << "filled:" << filled << "   is_empty:" << is_empty() << endl;
	if (is_empty()) {
		return "0";
	} 
	string res = *(top -> getValue());
	top = top -> getNext();
	filled--;
	return res;
}

int main() {
	int n, m;
	cin >> n; //Size of the stack
	cin >> m; //Number of lines following (however I ain't use this)
	Stack stk(n);
	string op;
	while (cin >> op) {
		if (op == "push") {
			string newElem;
			cin >> newElem;
			cout << (stk.push(newElem) ? "true" : "false") << endl;
		} else if (op == "pop") {
			cout << stk.pop() << endl;
		} else if (op == "peek") {
			cout << stk.peek() << endl;
		} else if (op == "is_empty") {
			cout << (stk.is_empty() ? "true" : "false") << endl;
		} else if (op == "is_full") {
			cout << (stk.is_full() ? "true" : "false") << endl;
		} else if (op == "size") {
			cout << stk.getSize() << endl;
		} else if (op == "clear") {
			cout << (stk.clear() ? "true" : "false") << endl;
		}
	}
	return 0;
}
