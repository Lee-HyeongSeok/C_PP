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
	os << "���� Top : " << s.Top() << endl;
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
----------------- �� ��ġ -----------------
----- W ---------    X    -------- E ------
---[i][j-1]------ [i][j]  ----- [i][j+1] --
-------------------------------------------
----- SW ----------- S ----------- SE -----
- [i+1][j-1] --- [i+1][j] ---- [i+1][j+1] -
-------------------------------------------
*/

/*
1 <= i <= m �̰� 1 <= j <= p�� 2���� �迭 arr[i][j]�� ǥ���Ѵ�.
���� �� 1�� ���� ���, 0�� ��� ���� ��θ� �ǹ��Ѵ�.
��� arr[1][1]���� ����Ѵ�. �ⱸ�� arr[m][p]�� �ִٰ� �����Ѵ�.
*/
typedef struct{
	int a, b;
}offsets;

// ��, �ϵ�, ��, ����, ��, ����, ��, �ϼ�
enum directions{N, NE, E, SE, S, SW, W, NW};

// �̵��� �� �ִ� ������� �̸� �迭 move�� �����Ѵ�.
offsets moveTo[8] = { {-1, 0}, {-1, 1}, {0, 1},
{1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

struct Items{
	int x, y, dir;
	Items() {}; // ������

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


int mark[13][17] = { 0, }; //���� ���� ǥ��
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
	// ��ΰ� �����ϸ� ����Ѵ�.

	mark[1][1] = 1; // (1, 1)���� �����Ѵ�.

	Stack<Items> stack(m*p);

	Items temp(1, 1, E);
	stack.Push(temp); // items ����ü�� ���ÿ� ����

	// ������ ��ȭ���°� �ƴ� ��
	while (!stack.isEmpty()) {
		// ������ �ֻ��� ���Ҹ� temp ����ü ������ ����
		temp = stack.Top(); 
		stack.pop(); // ������ ���Ҹ� ����

		int i = temp.x;
		int j = temp.y;
		int d = temp.dir;

		while (d < 8) {
			int g = i + moveTo[d].a;
			int h = j + moveTo[d].b;

			// �ⱸ ���� ��
			if ((g == m) && (h == p)) {
				cout << stack;
				cout << i << " " << j << endl; // ��� �� ������ �� ��ġ
				cout << m << " " << p << endl; // Ż���� ��ǥ
				return;
			}
			// ���ο� ��ġ�� ��
			if ((!map[g][h]) && (!mark[g][h])) { 
				// ��Ҵٴ� ǥ��
				mark[g][h] = 1;

				// ���� ��ǥ ����, �ٽ� ���ư��� ��츦 ����
				temp.x = i;
				temp.y = j;

				// ���ٸ� ���� ��� ���ƿ��� �� ���ο� ���� ��Ž���� ����
				temp.dir = d + 1;

				stack.Push(temp); // ���ÿ� ����

				// (g, h)�� �̵�
				i = g; j = h; d = N;
			}
			else {
				d++; // �ٸ� ���� �õ�
			}
		}
	}
	cout << "No Path in maze" << endl;
}

int main() {
	cout << "�̷� ���" << endl;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 17; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << endl;
	cout << "��ǥ : (����, ����, ����)" << endl;
	Path(11, 15); // ���� �����ϱ� ������ �� -2�� 
	return 0;
}