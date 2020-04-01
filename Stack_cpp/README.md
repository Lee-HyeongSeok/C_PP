## c++ 배열을 사용한 스택 구현   
#### 출처 : c++ 자료구조론   

## Stack의 개념   
* 한 쪽 끝에서만 자료를 삽입하고 삭제할 수 있는 LIFO(Last In First Out) 형식의 자료 구조이다.   


#### * 주 메서드   
		* isEmpty() : 스택이 비었는지 확인하는 메서드   
		* Top() : 스택의 최상위 값을 알려주는 메서드   
		* Push(int item) : 스택에 값을 삽입하는 메서드   
		* Pop() : 최상위 스택부터 값을 삭제하는 메서드
		* ChangeSize() : 스택의 크기를 변경하는 메서드   
		* Print() : 모든 스택 출력

#### * 사용되는 변수   
		* T *stack : 스택 원소를 위한 배열   
		* int top : 원소의 위치를 위한 변수   
		* int capacity : 스택 배열의 크기   


#### ChangeSize() : 클래스 외부 메서드   

```c
template <class T>
void ChangeSize(T*& a, const int oldSize, const int newSize) {
	if (newSize < 0) throw "New length must be >= 0";

	T* temp = new T[newSize];
	int number = min(oldSize, newSize);
	copy(a, a + number, temp);
	delete[]a;
	a = temp;
}
```   

#### isEmpty() 메서드, 클래스 내부 선언   
```c
// top은 스택의 높이를 뜻한다.
// 스택의 원소 수가 0이면 true, 아니면 false를 반환한다.
bool isEmpty() const {
	return top == -1;
}
```   

#### Top() 메서드, 클래스 내부 선언   
```c
T& Top() const {
	// 스택이 비었으면 메시지 출력
	if (isEmpty()) throw "Stack is empty";

	// 스택의 최상위 원소를 반환한다.
	return stack[top];
}
```   

#### Push() 메서드, 클래스 내부 선언   
```c
void Push(const T& item) {
	// 스택이 포화상태일 때
	if (top == capacity - 1) {
		// 사이즈를 2배로 재할당한다.
		ChangeSize(stack, capacity, 2 * capacity);
		capacity *= 2;
	}
	stack[++top] = item; // 인자로 전달된 값을 스택에 삽입
}
```   

#### pop() 메서드, 클래스 내부 선언   
```c
void pop() {
	// 스택이 비었으면 메시지 출력
	if (isEmpty()) throw "Stack is empty. Cannot delete";
	// 최상위 스택에서부터 감소하며 소멸자 호출
	stack[top--].~T(); // T에 대한 소멸자
}
```   

#### Print() 메서드, 클래스 내부 선언
```c
void Print() {
	// 최상위 값을 시작으로 마지막 원소까지 출력
	for (int i = top; i >= 0; i--) {
		cout <<"top"<<"["<<i<<"] : "<< stack[i] << endl;
	}
}
```