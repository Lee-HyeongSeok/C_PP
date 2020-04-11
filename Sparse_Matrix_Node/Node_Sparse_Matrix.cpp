/*
	* �������� ������ ǥ��(����� head �ʵ�� ǥ�õ��� �ʾҴ�.)

		|H|			->		|H0|			->			|H1|			-> ....
	| 4 | 5 | 6 |		| 0 | 0 | 2 |				| 1 | 0 | 4 |
	|	  |  	|		|	  |		|				|	  |		|
*/

#include <iostream>
#include <algorithm>

using namespace std;

class Matrix;		// ���� ����

// row�ʵ�� col�ʵ�� ����� ������ �����ϴ� �� ���ȴ�.
struct Triple {
	int row;
	int col;
	int value;
};

class MatrixNode {
private:
	MatrixNode *down, *right;
	bool head;
	// �̸����� Union
	union {
		MatrixNode *next;
		Triple triple;
	};
public:
	MatrixNode(){}
	// ������
	MatrixNode(bool b, Triple* t) {
		head = b;
		if (head) {
			right = down = this;	// row, col ������
		}
		else {
			triple = *t; // ��� ��� ����Ʈ�� ���� ���� ���
		}
	}
	friend class Matrix;
	friend istream& operator>>(istream&, Matrix&);	// ����� �ǵ� 
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
		if (!headnode) return;	// ������ ���
		MatrixNode *x = headnode->right;
		headnode->right = av;
		av = headnode;

		// �ະ�� �����Ѵ�.
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
	is >> s.row >> s.col >> s.value;	// ����� ���� 

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
		cout << "��, ��, ���� �Է� : " << endl;
		is >> t.row >> t.col >> t.value;

		if (t.row > currentRow) {
			last->right = head[currentRow];
			currentRow = t.row;
			last = head[currentRow];
		}
		// ���ο� ��带 �� ����Ʈ�� ����
		last = last->right = new MatrixNode(false, &t);
		// �� ����Ʈ�� ����
		head[t.col]->next = head[t.col]->next->down = last;
	}
	// ������ ���� �����Ѵ�.
	last->right = head[currentRow];
	for (int i = 0; i < s.col; i++) {
		head[i]->next->down = head[i];	// ��� �� ����Ʈ�� �����Ѵ�.
	}
	// headnode�� head����
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
	cout << "������ ���" << endl;
	cout << "(��, ��, ��)" << endl;
	cout << matrix;
	return 0;
}