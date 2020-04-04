#define _CRT_SECURE_NO_WARNINS
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// ������ default ũ���� 10�� �Ѿ��� �� ����� 2��� ����
template <class T>
void ChangeSize(T*& a, const int oldSize, const int newSize) {
	if (newSize < 0) throw "New length must be >= 0";

	T* temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete[]a;
	a = temp;
}
template <class T>
class Stack {
public:
	// ó���� ũ�Ⱑ stackCapacity�� ���� ������ ����
	Stack(int stackCapacity = 10) : capacity(stackCapacity) {
		if (capacity < 1) throw "Stack capacity must be > 0";
		stack = new T[capacity];	// ���޵� ���ڸ�ŭ�� �迭�� �Ҵ�
		top = -1;	// ������ top �����͸� -1�� �����Ѵ�. 
	}
	// ������ ���� ���� 0�̸� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	bool isEmpty() const {
		return top == -1;
	}
	int is_full() {
		return (top == capacity - 1);
	}
	// ������ �� ���Ҹ� ��ȯ�Ѵ�.
	T& Top() const {
		if (isEmpty()) throw "Stack is empty";
		return stack[top];
	}
	// ������ �鿡 item�� �����Ѵ�.
	void Push(const T& item) {
		if (top == capacity - 1) {
			ChangeSize(stack, capacity, 2 * capacity);
			capacity *= 2;
		}
		stack[++top] = item;
	}
	// ������ ���Ҹ� �����Ѵ�.
	void pop() {
		if (isEmpty()) throw "Stack is empty. Cannot delete";
		stack[top--].~T(); // T�� ���� �Ҹ���
	}
	void Print() {
		for (int i = top; i >= 0; i--) {
			cout << "top" << "[" << i << "] : " << stack[i] << endl;
		}
	}
	~Stack() {
		delete[] stack;
	}
	template <typename T>
	friend ostream &operator<<(ostream &os, Stack<T> &s);

private:
	T *stack;
	int top;
	int capacity;
};

template <typename T>
ostream &operator<<(ostream &os, Stack<T> &s) {
	os << "������ ��� ���� ���" << endl;
	for (int i = 0; i <= s.top; i++) {
		os << s.stack[i] << " ";
	}
	return os;
}

class Expression {
public :
	string expression;
	int idx;

	Expression(const string str) : expression(str) {
		idx = 0;
	}
	
};
// ���ڿ����� �ϳ��� ���ڸ� �����ϴ� �Լ�
char NextToken(Expression &exp) {
	char token;
	token = exp.expression[exp.idx++];
	return token;
}
// ���� �ȿ� �ִ� ��ȣ �켱����
int StackPrecedence(char ch) {
	switch (ch) {
	case '#': return 8;
	case '*': case '/': return 2;
	case '+': case '-': return 3;
	}
	return 8;
}
// ������ ���ÿ� ���� �켱����
int IncommingPrecedence(char ch) {
	switch (ch) {
	case '*': case '/': return 2;
	case '+': case '-': return 3;
	}
	return 0;
}
// ���޵� ���ڰ� ������ �������� �����ϴ� �Լ�
bool isOperand(char ch) {
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}
void PostFix(Expression exp) {
	Stack<char> stack;
	Stack<char> post;
	stack.Push('#');

	for (char ch = NextToken(exp); ch != '#'; ch = NextToken(exp)) {
		if (isOperand(ch)) {	// ������ �޾ƿ� ������ ������ ������ ��
			post.Push(ch);
		}
		else if (ch == ')') {	// ������ ��ȣ�� ��
			while (stack.Top() != '(') {	// ������ ���� ���Ұ� ���� ��ȣ�� �ƴ� ��
				post.Push(stack.Top());	// ����� ���ÿ� ���� ���� ����
				stack.pop();	// ��� �����ϴ� ���ÿ� ���� ���� ����
			}
			stack.pop();
		}
		else {	// ��ȣ�� ���ڰ� �ƴϸ�, ���� ��ȣ�� ��

			// ������ ���� ��ȣ�� �켱������ ���� �ӽ� ������ �켱������ ���Ѵ�.
			while (StackPrecedence(stack.Top()) <= IncommingPrecedence(ch)) {	// ������ �켱���� Ȯ��
				post.Push(stack.Top());
				stack.pop();
			}
			stack.Push(ch);
		}
	}
	// ������ ���õ��� ����ǥ��� ���ÿ� ����
	while (!stack.isEmpty()) {
		if (stack.Top() != '#') {
			post.Push(stack.Top());
		}
		stack.pop();
	}
	// ��� ���� ���
	cout << post;
}

int main() {
	// �Է��� ���� '#'�� �Է��ؾ� �Ѵ�.
	// (1+2)*4+5/(6+1*4)+3#

	string str;
	cin >> str;
	Expression exp(str);
	PostFix(exp); // ���� ǥ���
}