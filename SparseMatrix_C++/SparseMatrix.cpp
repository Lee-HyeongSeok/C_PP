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
	// row : 행위 수, cols : 열의 수, terms : 0이 아닌 항의 총수, capacity : smArr의 크기
	// smArr의 인덱스 0~7까지는 0이 아닌 항을 나타내는 3원소 쌍을 저장한다.
	// 3원소 쌍은 행 우선으로 정렬, 행 내에서는 열 순서로 정렬된다.
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
	// *this의 모든 3원소 쌍의 행과 열의 값을 서로 교환 후 얻은 행렬 반환
	SparseMatrix Transpose() {
		SparseMatrix b(cols, rows, terms); // b.smArr의 크기는 terms이다.
		if (terms > 0) {
			int cur = 0;
			for (int i = 0; i < cols; i++) { // 열 기준 전치
				for (int j = 0; j < terms; j++) { // 열 i로 부터 원소를 찾아 이동시킨다.
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

	// 행렬의 크기를 newSize로 변경한다.
	void ChangeSize(const int newSize) {
		if (newSize < terms) {
			throw "New Size must be >= number of terms";
		}
		MatrixTerm *temp = new MatrixTerm[newSize];
		copy(smArr, smArr + terms, temp);
		delete[] smArr; // 이전 메모리 제거
		smArr = temp;
		capacity = newSize;
	}

	// 행렬의 곱셈을 위한 함수
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
	// *this와 b의 행의 수가 같으면 곱하여 반환
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
					sum = 0; // sum 재설정

					currRowIndex = currRowBegin; // currRowA행을 다음 열과 곱하도록 설정
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
				currRowIndex++;	// 다음 행으로 간다.
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
	os << "0이 아닌 요소의 수 : " << s.terms << endl;

	for (int i = 0; i < s.terms; i++) {
		os << "(" << s.smArr[i].row << ", " << s.smArr[i].col << ", " << s.smArr[i].value << ")" << endl;
	}
	return os;
}

istream &operator>>(istream &is, SparseMatrix s) {
	/*
	cout << "열, 행 그리고 0이 아닌 요소의 수 입력 : ";
	cin >> s.rows >> s.cols >> s.terms;

	if (s.terms > s.capacity) {
		cout << "범위 초과";
		exit(1);
	}
	*/
	for (int i = 0; i < s.terms; i++) {
		cout << i + 1 << "-> 열, 행, 값 입력 : " << endl;
		is >> s.smArr[i].row >> s.smArr[i].col >> s.smArr[i].value;
	}
	return is;
}
int main() {
	SparseMatrix M1(3, 3, 3), M2(3, 3, 3);

	cout << "M1 행렬 입력" << endl;
	cin >> M1;
	cout << "M1 희소 행렬" << endl << M1 << endl;

	cout << "M2 행렬 입력" << endl;
	cin >> M2;
	cout << "M2 희소 행렬" << endl << M2 << endl;

	return 0;
}