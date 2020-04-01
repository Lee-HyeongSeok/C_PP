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
	// 처음에 크기가 stackCapacity인 공백 스택을 생성
	Stack(int stackCapacity = 10) : capacity(stackCapacity) {
		if (capacity < 1) throw "Stack capacity must be > 0";
		stack = new T[capacity];	// 전달된 인자만큼의 배열을 할당
		top = -1;	// 스택의 top 포인터를 -1로 설정한다. 
	}
	// 스택의 원소 수가 0이면 true, 아니면 false를 반환한다.
	bool isEmpty() const {
		return top == -1;
	}
	// 스택의 톱 원소를 반환한다.
	T& Top() const {
		if (isEmpty()) throw "Stack is empty";
		return stack[top];
	}
	// 스택의 톱에 item을 삽입한다.
	void Push(const T& item) {
		if (top == capacity - 1) {
			ChangeSize(stack, capacity, 2 * capacity);
			capacity *= 2;
		}
		stack[++top] = item;
	}
	// 스택의 원소를 삭제한다.
	void pop() {
		if (isEmpty()) throw "Stack is empty. Cannot delete";
		stack[top--].~T(); // T에 대한 소멸자
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

	cout << "입력할 개수를 입력하시오." <<endl;
	cin >> test;

	// 스택에 값을 입력시킨다.
	for (int i = 0; i < test; i++) {
		cin >> item;
		S.Push(item);
		item = 0;
	}

	// 스택의 탑 확인
	cout << "Stack Top : " << S.Top() << endl << endl;
	
	// 스택 출력
	S.Print();
	cout << endl << endl;
	// 스택 삭제
	S.pop();
	S.pop();

	// 원소 n개 삭제 후 스택 출력
	S.Print();
}