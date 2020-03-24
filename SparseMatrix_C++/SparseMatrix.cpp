#include <iostream>

using namespace std;

class SparseMatrix;

class MatrixTerm {
	friend class SparseMatrix;
	friend ostream &operator<<(ostream &os, const SparseMatrix s);
	friend istream &operator>>(istream &is, SparseMatrix s);
private:
	int row, col, value;
};
class SparseMatrix {
private : 
	// row : ���� ��, cols : ���� ��, terms : 0�� �ƴ� ���� �Ѽ�, capacity : smArr�� ũ��
	// smArr�� �ε��� 0~7������ 0�� �ƴ� ���� ��Ÿ���� 3���� ���� �����Ѵ�.
	// 3���� ���� �� �켱���� ����, �� �������� �� ������ ���ĵȴ�.
	int rows, cols, terms, capacity;
	MatrixTerm *smArr;
public : 
	SparseMatrix(int r = 1, int c = 1, int t = 0)
		: rows(r), cols(c), terms(t) {
		if (t > 0)
			capacity = t;
		else
			capacity = 1;
		smArr = new MatrixTerm[capacity];
	}
	int ReturnRows() {
		return rows;
	}
	int ReturnCols() {
		return cols;
	}
	// *this�� ��� 3���� ���� ��� ���� ���� ���� ��ȯ �� ���� ��� ��ȯ
	SparseMatrix Transpose() {
		SparseMatrix b(cols, rows, terms); // b.smArr�� ũ��� terms�̴�.
		if (terms > 0) {
			int cur = 0;
			for (int i = 0; i < cols; i++) { // �� ���� ��ġ
				for (int j = 0; j < terms; j++) { // �� i�� ���� ���Ҹ� ã�� �̵���Ų��.
					if (smArr[i].col == i) {
						b.smArr[cur].row = i;
						b.smArr[cur].col = smArr[j].row;
						b.smArr[cur++].value = smArr[j].value;
					}
				}
			}
		}
		return b;
	}

	// ����� ũ�⸦ newSize�� �����Ѵ�.
	void ChangeSize(const int newSize) {
		if (newSize < terms) {
			throw "New Size must be >= number of terms";
		}
		MatrixTerm *temp = new MatrixTerm[newSize];
		copy(smArr, smArr + terms, temp);
		delete[] smArr; // ���� �޸� ����
		smArr = temp;
		capacity = newSize;
	}

	// ����� ������ ���� �Լ�
	void StoreSum(const int sum, const int r, const int c) {
		if (sum != 0) {
			if (terms == capacity) {
				ChangeSize(2 * capacity);
			}
			smArr[terms].row = r;
			smArr[terms].col = c;
			smArr[terms++].value = sum;
		}
	}
	// *this�� b�� ���� ���� ������ ���Ͽ� ��ȯ
	SparseMatrix Multiply(SparseMatrix b) {
		if (cols != b.rows)
			throw "incompatible matrics";
		SparseMatrix bXpose = b.Transpose();
		SparseMatrix d(rows, b.cols, 0);

		int currRowIndex = 0,
			currRowBegin = 0,
			currRowA = smArr[0].row;

		if (terms == capacity)
			ChangeSize(terms + 1);
		bXpose.ChangeSize(bXpose.terms + 1);
		smArr[terms].row = rows;
		bXpose.smArr[b.terms].row = b.cols;
		bXpose.smArr[b.terms].col = -1;

		int sum = 0;
		while (currRowIndex < terms) {
			int currColB = bXpose.smArr[0].row;
			int currColIndex = 0;
			while (currColIndex <= b.terms) {
				if (smArr[currRowIndex].row != currRowA) {
					d.StoreSum(sum, currRowA, currColB);
					sum = 0;
					currRowIndex = currRowBegin;

					while (bXpose.smArr[currColIndex].row == currColB)
						currColIndex++;
					currColB = bXpose.smArr[currColIndex].row;
				}
				else if (bXpose.smArr[currColIndex].row != currColB) {
					d.StoreSum(sum, currRowA, currColB);
					sum = 0; // sum �缳��

					currRowIndex = currRowBegin; // currRowA���� ���� ���� ���ϵ��� ����
					currColB = bXpose.smArr[currColIndex].row;
				}
				else {
					if (smArr[currRowIndex].col < bXpose.smArr[currColIndex].col)
						currRowIndex++;
					else if (smArr[currRowIndex].col == bXpose.smArr[currColIndex].col) {
						sum += smArr[currRowIndex].value * bXpose.smArr[currColIndex].value;
						currRowIndex++;
						currColIndex++;
					}
					else
						currColIndex++;
				}
			}
			while (smArr[currRowIndex].row == currRowA)
				currRowIndex++;	// ���� ������ ����.
			currRowBegin = currRowIndex;
			currRowA = smArr[currRowIndex].row;
		}
		return d;
	}

	friend ostream &operator<<(ostream &os, const SparseMatrix s);
	friend istream &operator>>(istream &is, SparseMatrix s);
};

ostream &operator<<(ostream &os, const SparseMatrix s) {
	os << "row : " << s.rows << " " << "col : " << s.cols << endl;
	os << "0�� �ƴ� ����� �� : " << s.terms << endl;

	for (int i = 0; i < s.terms; i++) {
		os << "(" << s.smArr[i].row << ", " << s.smArr[i].col << ", " << s.smArr[i].value << ")" << endl;
	}
	return os;
}

istream &operator>>(istream &is, SparseMatrix s) {
	/*
	cout << "��, �� �׸��� 0�� �ƴ� ����� �� �Է� : ";
	cin >> s.rows >> s.cols >> s.terms;

	if (s.terms > s.capacity) {
		cout << "���� �ʰ�";
		exit(1);
	}
	*/
	for (int i = 0; i < s.terms; i++) {
		cout << i + 1 << "-> ��, ��, �� �Է� : " << endl;
		is >> s.smArr[i].row >> s.smArr[i].col >> s.smArr[i].value;
	}
	return is;
}
int main() {
	SparseMatrix M1(3, 3, 3), M2(3, 3, 3);

	cout << "M1 ��� �Է�" << endl;
	cin >> M1;
	cout << "M1 ��� ���" << endl << M1 << endl;

	cout << "M2 ��� �Է�" << endl;
	cin >> M2;
	cout << "M2 ��� ���" << endl << M2 << endl;

	return 0;
}