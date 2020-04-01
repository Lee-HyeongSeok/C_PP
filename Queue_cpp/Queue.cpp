#include <iostream>
#include <algorithm>

template <class T>
class Queue {
public :
	Queue(int queueCapacity = 10) : capacity(queueCapacity) {
		if (capacity < 1) throw "Queue capacity must be > 0";
		queue = new T[capacity];
		front = rear = 0;
	}
	bool isEmpty() const {
		return front == rear;
	}
	T& Front() const {
		if (isEmpty()) throw "Queue is empty. No front element";
		return queue[(front + 1) % capacity];
	}
	T& Rear() const {
		if (isEmpty()) throw "Queue is empty. No rear element";
		return queue[rear];
	}
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
	void Pop() {
		if (isEmpty()) throw "Queue is empty. Cannot delete";
		front = (front + 1) % capacity;
		queue[front].~T();	// T를 위한 소멸자
	}

private :
	T *queue; // 큐 원소를 위한 배열
	int front, rear, capacity;
};