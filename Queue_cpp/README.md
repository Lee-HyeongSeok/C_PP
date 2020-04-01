## c++ 배열을 사용한 큐 구현   
#### 출처 : c++ 자료구조론   

## Queue의 개념   
* 컴퓨터의 기본적인 자료 구조의 한 가지로, 먼저 삽입된 데이터가 먼저 나오는
(First In First Out) 구조로 저장하는 방식이다.   

#### * 주 메서드   
		* isEmpty() : 큐의 원소 수가 0이면 true, 아니면 false를 반환한다.
		* Front() : 큐의 앞에 있는 원소를 반환한다.
		* Rear() : 큐의 뒤에 있는 원소를 반환한다.
		* Push() : 큐의 뒤에 데이터를 삽입한다.
		* Pop() : 데이터를 삭제하는 메서드   

#### * 사용되는 변수   
		* T *queue : 큐 원소를 위한 배열   
		* int front : 첫 번째 원소의 위치   
		* int rear : 마지막 원소의 위치   
		* int capacity : 큐 배열의 크기   

#### isEmpty() 메서드   
```c
bool isEmpty() const {
	// 앞과 뒤의 위치를 가리키는 원소가 서로 같으면 비어있는 큐
	return front == rear;
}
```   

#### Front() 메서드   
```c
T& Front() const {
	// 큐가 비었을 때
	if (isEmpty()) throw "Queue is empty. No front element";
	// 큐의 앞에있는 원소를 반환한다.
	return queue[(front + 1) % capacity];
}
```   

#### Rear() 메서드
```c
T& Rear() const {
	if (isEmpty()) throw "Queue is empty. No rear element";
	// 큐의 뒤에 있는 원소를 반환한다.
	return queue[rear];
}
```   

#### Push() 메서드   
```c
void Push(const T& item) {
		// 큐가 꽉 찼으면 두 배로 만든다.

		if ((rear + 1) % capacity == front) {
			T* newQueue = new T[2 * capacity];

			// queue를 newQueue로 복사한다.
			int start = (front + 1) % capacity;
			if (start < 2)
				copy(queue + start, queue + start + capacity - 1, newQueue);
			else {	// 둘러싸서 큐를 만든다.
				copy(queue + start, queue + capacity, newQueue);
				copy(queue, queue + rear + 1, newQueue + capacity - start);
			}
		}
		// newQueue로 전환한다.
		front = 2 * capacity - 1;
		rear = capacity - 2;
		capacity *= 2;
		delete[] queue;
		queue = newQueue;
	}
```   

#### Pop() 메서드
```c
void Pop() {
	if (isEmpty()) throw "Queue is empty. Cannot delete";
	
	// 큐의 앞에 있는 원소부터 삭제한다.
	front = (front + 1) % capacity;
	queue[front].~T();	// T를 위한 소멸자
}
```