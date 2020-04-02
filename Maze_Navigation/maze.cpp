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
/*
-------------------------------------------
----- NW ----------- N ----------- NE -----
- [i-1][j-1] --- [i-1][j] ---- [i-1][j+1] -
-------------------------------------------
----------------- 현 위치 -----------------
----- W ---------    X    -------- E ------
---[i][j-1]------ [i][j]  ----- [i][j+1] --
-------------------------------------------
----- SW ----------- S ----------- SE -----
- [i+1][j-1] --- [i+1][j] ---- [i+1][j+1] -
-------------------------------------------
*/

/*
1 <= i <= m 이고 1 <= j <= p인 2차원 배열 arr[i][j]로 표현한다.
맵의 각 1은 막힌 통로, 0은 통과 가능 통로를 의미한다.
쥐는 arr[1][1]에서 출발한다. 출구는 arr[m][p]에 있다고 가정한다.
*/
typedef struct{
	int a, b;
}offsets;

// 북, 북동, 동, 남동, 남, 남서, 서, 북서
enum directions{N, NE, E, SE, S, SW, W, NW};

// 이동할 수 있는 방향들을 미리 배열 move에 정의한다.
offsets moveTo[8] = { {-1, 0}, {-1, 1}, {0, 1},
{1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

struct Items{
	int x, y, dir;
	Items() {}; // 생성자

	Items(int a, int b, int d) {
		x = a;
		y = b;
		dir = d;
	}
};
/*
ostream &operator<<(ostream &os, Items &item) {
	return os << item.x << ", " << item.y << ", " << item.dir;
}
*/
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


int mark[13][17] = { 0, }; //갔던 지점 표기
int map[13][17] = { 

		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1 },
		{ 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },

};



void Path(const int m, const int p) {
	// 경로가 존재하면 출력한다.

	mark[1][1] = 1; // (1, 1)에서 시작한다.

	Stack<Items> stack(m*p);

	Items temp(1, 1, E);
	stack.Push(temp); // items 구조체를 스택에 삽입

	// 스택이 포화상태가 아닐 때
	while (!stack.isEmpty()) {
		// 스택의 최상위 원소를 temp 구조체 변수에 삽입
		temp = stack.Top(); 
		stack.pop(); // 스택의 원소를 삭제

		int i = temp.x;
		int j = temp.y;
		int d = temp.dir;

		while (d < 8) {
			int g = i + moveTo[d].a;
			int h = j + moveTo[d].b;

			// 출구 도착 시
			if ((g == m) && (h == p)) {
				cout << stack;
				cout << i << " " << j << endl; // 경로 상 마지막 두 위치
				cout << m << " " << p << endl; // 탈출한 좌표
				return;
			}
			// 새로운 위치일 때
			if ((!map[g][h]) && (!mark[g][h])) { 
				// 밟았다는 표시
				mark[g][h] = 1;

				// 이전 좌표 저장, 다시 돌아가는 경우를 위해
				temp.x = i;
				temp.y = j;

				// 막다른 길일 경우 돌아왔을 때 새로운 방향 재탐색을 위해
				temp.dir = d + 1;

				stack.Push(temp); // 스택에 삽입

				// (g, h)로 이동
				i = g; j = h; d = N;
			}
			else {
				d++; // 다른 방향 시도
			}
		}
	}
	cout << "No Path in maze" << endl;
}

int main() {
	cout << "미로 출력" << endl;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << endl;
	cout << "좌표 : (가로, 세로, 방향)" << endl;
	Path(11, 15); // 벽은 제외하기 때문에 각 -2씩 
	return 0;
}