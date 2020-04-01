#include <iostream>
#include <algorithm>
using namespace std;

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
public : 
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
			cout <<"top"<<"["<<i<<"] : "<< stack[i] << endl;
		}
	}
	~Stack() {
		delete[] stack;
	}

private:
	T *stack;
	int top;
	int capacity;
};

int main() {
	Stack<int> S;
	int test = 0;
	int item = 0;

	cout << "�Է��� ������ �Է��Ͻÿ�." <<endl;
	cin >> test;

	// ���ÿ� ���� �Է½�Ų��.
	for (int i = 0; i < test; i++) {
		cin >> item;
		S.Push(item);
		item = 0;
	}

	// ������ ž Ȯ��
	cout << "Stack Top : " << S.Top() << endl << endl;
	
	// ���� ���
	S.Print();
	cout << endl << endl;
	// ���� ����
	S.pop();
	S.pop();

	// ���� n�� ���� �� ���� ���
	S.Print();
}