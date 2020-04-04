#define _CRT_SECURE_NO_WARNINS
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 스택의 default 크기인 10을 넘었을 때 사이즈를 2배로 조정
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
	int is_full() {
		return (top == capacity - 1);
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
	os << "스택의 모든 원소 출력" << endl;
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
// 문자열에서 하나씩 문자를 전달하는 함수
char NextToken(Expression &exp) {
	char token;
	token = exp.expression[exp.idx++];
	return token;
}
// 스택 안에 있는 기호 우선순위
int StackPrecedence(char ch) {
	switch (ch) {
	case '#': return 8;
	case '*': case '/': return 2;
	case '+': case '-': return 3;
	}
	return 8;
}
// 다음에 스택에 들어올 우선순위
int IncommingPrecedence(char ch) {
	switch (ch) {
	case '*': case '/': return 2;
	case '+': case '-': return 3;
	}
	return 0;
}
// 전달된 인자가 문자형 숫자인지 구별하는 함수
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
		if (isOperand(ch)) {	// 다음에 받아온 변수가 문자형 숫자일 때
			post.Push(ch);
		}
		else if (ch == ')') {	// 닫히는 괄호일 때
			while (stack.Top() != '(') {	// 스택의 상위 원소가 열린 괄호가 아닐 때
				post.Push(stack.Top());	// 출력할 스택에 상위 원소 삽입
				stack.pop();	// 잠시 저장하는 스택에 상위 원소 삭제
			}
			stack.pop();
		}
		else {	// 괄호나 숫자가 아니면, 연산 기호일 때

			// 다음에 들어올 기호의 우선순위와 현재 임시 스택의 우선순위를 비교한다.
			while (StackPrecedence(stack.Top()) <= IncommingPrecedence(ch)) {	// 연산자 우선순위 확인
				post.Push(stack.Top());
				stack.pop();
			}
			stack.Push(ch);
		}
	}
	// 나머지 스택들을 후위표기식 스택에 삽입
	while (!stack.isEmpty()) {
		if (stack.Top() != '#') {
			post.Push(stack.Top());
		}
		stack.pop();
	}
	// 모든 스택 출력
	cout << post;
}

int main() {
	// 입력의 끝에 '#'을 입력해야 한다.
	// (1+2)*4+5/(6+1*4)+3#

	string str;
	cin >> str;
	Expression exp(str);
	PostFix(exp); // 후위 표기식
}