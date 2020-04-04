## 스택을 활용한 c++ 후위표기법   
#### * 출처 : c++ 자료구조론   

#### 후위 표기식이란?   
* 컴파일러가 수식을 처리할 때 사용하는 표기법이다.   


#### * 사용헤더   
	* <iostream>   
	* <string>   
	* <algorithm>   

#### * 주요 메커니즘   
		* 임시 스택에는 괄호의 열림과 닫힘에 따라 잠시 저장되는 문자가 구분된다.   
		* 연산자가 피연산자들 뒤에 온다.
		* 우선순위가 같은 연산자들이 인접해 있을 경우 괄호를 사용하여 구분한다.
		* 스태킹과 언스태킹에 대해 우선순위를 기반으로 하는 기법을 사용한다.
		* 열린 괄호는 스택에 있을 때는 낮은 우선순위의 연산자처럼 동작
		* 닫힌 괄호 이외의 어느 연산자도 이를 스택에서 나오게할 수 없다.

#### * 주요 클래스(Stack class)   
 		* friend 선언을통해 private에 접근시킨다.
		* friend 선언은 정보은닉에 위배되기 때문에 Print()라는 함수를 만들었다.   

```c
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

```   

#### * 입력한 수식을 관리하는 클래스(Expression class)   

```c
class Expression {
public :
	string expression;
	int idx;	// 문자열의 인덱스를 관리하는 변수 

	Expression(const string str) : expression(str) {
		idx = 0;
	}
	
};
```   

#### * 문자열에서 하나씩 문자를 전달하는 함수   
 

```c
char NextToken(Expression &exp) {
	char token;
	token = exp.expression[exp.idx++];
	return token;
}
```

#### * 임시 스택의 최상위 원소인 연산자 우선순위   

```c
int StackPrecedence(char ch) {
	switch (ch) {
	case '#': return 8;
	case '*': case '/': return 2;
	case '+': case '-': return 3;
	}
	return 8;
}
```   

#### * 다음에 스택에 들어올 기호의 우선순위   
		* NextToken()을 통해 다음에 올 문자를 검사한다.   

```c
int IncommingPrecedence(char ch) {
	switch (ch) {
	case '*': case '/': return 2;
	case '+': case '-': return 3;
	}
	return 0;
}
```   
#### * 현 스택의 연산 기호 우선순위와 다음에 스택에 들어올 기호의 우선순위 비교   

```c
// stack : 여태 저장된 연산 기호 및 숫자들이 있는 스택
// ch : NextToken으로 전달받은 문자형 변수 

while (StackPrecedence(stack.Top()) <= IncommingPrecedence(ch)) {	
	post.Push(stack.Top());
	stack.pop();
}
```
#### * 전달된 문자가 숫자인지 구분하는 함수   

```c
bool isOperand(char ch) {
	if (ch >= '0' && ch <= '9')	// 숫자일 때, true
		return true;
	else			// 숫자 이외의 문자일 때, false
		return false;
}
```   

#### * 후위표기식 전환 함수   

```c
void PostFix(Expression exp) {
	Stack<char> stack;	// 잠시 저장할 스택
	Stack<char> post; // 후위표기식 저장 스택 
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
```