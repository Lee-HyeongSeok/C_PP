/*
	* 희소행렬의 연결을 표현(노드의 head 필드는 표시되지 않았다.)

		|H|			->		|H0|			->			|H1|			-> ....
	| 4 | 5 | 6 |		| 0 | 0 | 2 |				| 1 | 0 | 4 |
	|	  |  	|		|	  |		|				|	  |		|
*/

#include <iostream>
#include <algorithm>

using namespace std;

class Matrix;		// 전방 선언

// row필드와 col필드는 행렬의 차수를 저장하는 데 사용된다.
struct Triple {
	int row;
	int col;
	int value;
};

class MatrixNode {
private:
	MatrixNode *down, *right;
	bool head;
	// 이름없는 Union
	union {
		MatrixNode *next;
		Triple triple;
	};
public:
	MatrixNode(){}
	// 생성자
	MatrixNode(bool b, Triple* t) {
		head = b;
		if (head) {
			right = down = this;	// row, col 헤더노드
		}
		else {
			triple = *t; // 헤더 노드 리스트를 위한 원소 노드
		}
	}
	friend class Matrix;
	friend istream& operator>>(istream&, Matrix&);	// 행렬의 판독 
	friend ostream& operator<<(ostream&, Matrix &);
};

class Matrix {
private:
	MatrixNode *headnode;
public:
	Matrix() {

	}
	~Matrix() {
		MatrixNode *av = 0;
		if (!headnode) return;	// 삭제할 노드
		MatrixNode *x = headnode->right;
		headnode->right = av;
		av = headnode;

		// 행별로 삭제한다.
		while (x != headnode) {
			MatrixNode *y = x->right;
			x->right = av;
			av = y;
			x = x->next;
		}
		headnode = 0;
	}
	friend istream& operator>>(istream&, Matrix&);
	friend ostream& operator<<(ostream&, Matrix&);
};

istream& operator>>(istream& is, Matrix& matrix) {
	Triple s;
	is >> s.row >> s.col >> s.value;	// 행렬의 차수 

	int p = max(s.row, s.col);	// max algorithm
	matrix.headnode = new MatrixNode(false, &s);

	if (p == 0) {
		matrix.headnode->right = matrix.headnode;
		return is;
	}

	MatrixNode **head = new MatrixNode*[p];
	for (int i = 0; i < p; i++) {
		head[i] = new MatrixNode(true, 0);
	}
	int currentRow = 0;
	MatrixNode *last = head[0];

	for (int i = 0; i < s.value; i++) {
		Triple t;
		cout << "행, 열, 원소 입력 : " << endl;
		is >> t.row >> t.col >> t.value;

		if (t.row > currentRow) {
			last->right = head[currentRow];
			currentRow = t.row;
			last = head[currentRow];
		}
		// 새로운 노드를 행 리스트에 연결
		last = last->right = new MatrixNode(false, &t);
		// 열 리스트에 연결
		head[t.col]->next = head[t.col]->next->down = last;
	}
	// 마지막 행을 마감한다.
	last->right = head[currentRow];
	for (int i = 0; i < s.col; i++) {
		head[i]->next->down = head[i];	// 모든 열 리스트를 마감한다.
	}
	// headnode와 head연결
	for (int i = 0; i < p - 1; i++) {
		head[i]->next = head[i + 1];
	}
	head[p - 1]->next = matrix.headnode;
	matrix.headnode->right = head[0];
	delete[] head;
	return is;
}
ostream& operator<<(ostream& os, Matrix& m) {
	MatrixNode *head = m.headnode->right;
	while (head != m.headnode) {
		for (MatrixNode *cur = head->right; cur != head; cur = cur->right) {
			os << "(" << cur->triple.row << ", " << cur->triple.col << ", " << cur->triple.value << ")" << endl;
			head = head->next;
		}
		return os;
	}
}
int main() {
	Matrix matrix;
	cin >> matrix;
	cout << endl << endl;
	cout << "희소행렬 출력" << endl;
	cout << "(행, 열, 값)" << endl;
	cout << matrix;
	return 0;
}