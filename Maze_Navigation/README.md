## C++ 자료구조론 미로 탐색   
#### * 출처 : c++ 자료구조론   

## 문제   
-----------------------------------------------
----- NW ----------- N ----------- NE -----
- [i-1][j-1] -------- [i-1][j] ----- [i-1][j+1] --
-----------------------------------------------
----------------- 현 위치 --------------------
------ W ---------    X    ----------- E ------
-----[i][j-1]-------- [i][j]   --------- [i][j+1] --
-----------------------------------------------
----- SW ----------- S ------------- SE -----
-- [i+1][j-1] ----- [i+1][j] ------ [i+1][j+1] -
------------------------------------------------

#### * Map의 형식   
		* 1 <= i <= m, 1 <= j <= p인 2차원 배열 map[i][j]로 표현한다.
		* 출구는 map[m][p]에 있다고 가정한다.
		* 맵의 각 1은 막힌 통로, 0은 통과 가능한 통로를 의미한다.   


#### offsets 구조체   
* 미로 문제를 단순화하는 장치   
* 이동할 수 있는 방향들을 배열 moveTo에 미리 정의한다.   
```c
typedef struct{
	int a, b;
}offsets;

// 북, 북동, 동, 남동, 남, 남서, 서, 북서
enum directions{N, NE, E, SE, S, SW, W, NW};

/*
N = (a, b) = (-1, 0)
NE = (a, b) = (-1, 1)
E = (a, b) = (0, 1)
SE = (a, b) = (1, 1)
S = (a, b) = (1, 0)
SW = (a, b) = (1, -1)
W = (a, b) = (0, -1)
NW = (a, b) = (-1, -1)
*/

// 이동할 수 있는 방향들을 미리 배열 move에 정의한다.
offsets moveTo[8] = { {-1, 0}, {-1, 1}, {0, 1},
{1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

```   

#### Stack Class   
* 미로 이동 경로를 저장하기 위해 사용   

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
	os << "현재 Top : " << s.Top() << endl;
	for (int i = 0; i <= s.top; i++) {
		os << i + 1 << ": " << s.stack[i] << endl;
	}
	return os;
}
```   

#### Items 구조체   
* 3원소 쌍(i, j, dir)의 표현을 위해 사용
* 이 알고리즘에서는 가장 최근에 입력된 3원소 쌍을 먼저 제거하므로 스택에 저장되어야 한다.   
* 스택에는 최대 m*p개의 원소가 들어갈 수 있다.   

```c
struct Items{
	int x, y, dir;

	// 생성자, 스택 템플릿 함수의 자료형으로 사용하기 위해 필요하다.
	// Stack<Items> stack(m*p); 코드에서 사용.
	Items() {}; 

	Items(int a, int b, int d) {
		x = a;
		y = b;
		dir = d;
	}
};
```   

#### 이동 방향을 출력하기 위한 함수 오버로딩   
```c
ostream &operator<<(ostream &os, Items &item){
	os << item.x << ", " << item.y << ", ";

	switch (item.dir)
	{
	case 1:
		cout << "N";
		break;
	case 2:
		cout << "NE";
		break;
	case 3:
		cout << "E";
		break;
	case 4:
		cout << "SE";
		break;
	case 5:
		cout << "S";
		break;
	case 6:
		cout << "SW";
		break;
	case 7:
		cout << "W";
		break;
	case 8:
		cout << "NW";
	}
	return os;
}
```   
