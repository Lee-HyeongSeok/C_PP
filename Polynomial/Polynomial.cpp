#include <iostream>

using namespace std;


class Polynomial; // ���� ���� 

class Term {
	friend Polynomial;

	// <�� �ٸ� ��� �� �Է� ���>
	// friend ostream &operator<<(ostream &os, const Polynomial &c);
private :
	float coef; // ���
	int exp; // ����
};
class Polynomial {
private :
	Term *termArray; // 0�� �ƴ� ���� �迭
	int capacity;	// termArray�� ũ��
	int terms;		// 0�� �ƴ� ���� ��

public:
	Polynomial() {
		capacity = 1;
		terms = 0;
		termArray = new Term[capacity];
	}
	void NewTerms(const float c, const int e) {
		if (terms == capacity) {
			// termArray�� ũ�⸦ �� ��� Ȯ���Ѵ�.
			capacity *= 2;
			Term *temp = new Term[capacity]; // ���ο� �迭 �����Ҵ�
			copy(termArray, termArray + terms, temp);
			delete[] termArray; // �� �� �޸𸮸� ��ȯ
			termArray = temp;
		}
		termArray[terms].coef = c;
		termArray[terms++].exp = e;
	}
	Polynomial Add(Polynomial poly) {
		Polynomial c; // ������ ��ü�� ��ȯ�ϱ� ���� ��ü
		/*
		 ���ڷ� ���޵� ��ü�� *this�� 0�� �ƴ� ���� ����
		 �м��� �����Ѵ�.
		*/

		// aPos : ���� ��� ��ü
		// bPos : ���޵� ��ü
		int aPos = 0, bPos = 0;

		/*
		 aPos�� *this�� terms�� ���ų�
		 bPos�� ���ڷ� ���޵� ��ü�� terms�� ���� �� ����
		*/
		while ((aPos < terms) && (bPos < poly.terms)) {
			if ((termArray[aPos].exp == poly.termArray[bPos].exp)) {
				float t = termArray[aPos].coef + poly.termArray[bPos].coef;
				// ��ȯ ������ ��ü�� ���ο� �� �����
				if (t)
					c.NewTerms(t, termArray[aPos].exp);
				aPos++; bPos++;
			}
			// ���ڷ� ���޵� ��ü�� ���� �� ���� ��
			else if ((termArray[aPos].exp < poly.termArray[bPos].exp)) {
				c.NewTerms(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
				bPos++;
			}
			// *this�� ���� �� ���� ��
			else {
				c.NewTerms(termArray[aPos].coef, termArray[aPos].exp);
				aPos++;
			}
		}
		//*this�� ������ �׵��� �߰��Ѵ�.
		for (; aPos < terms; aPos++) {
			c.NewTerms(termArray[aPos].coef, termArray[aPos].exp);
		}

		// ���ڷ� ���޵� ��ü�� ������ �׵��� �߰��Ѵ�.
		for (; bPos < poly.terms; bPos++) {
			c.NewTerms(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
		}
		return c;
	}
	Polynomial Mult(Polynomial poly) {
		Polynomial c;
		
		int aPos = 0, bPos = 0;

		while ((aPos < terms) && (bPos < poly.terms)) {
			if ((termArray[aPos].exp == poly.termArray[bPos].exp)) {
				float t = termArray[aPos].coef * poly.termArray[bPos].coef;
				if (t)
					c.NewTerms(t, termArray[aPos].exp);
				aPos++, bPos++;
			}
			// ����� ������ �ٸ��� 0�� �ȴ�.
			else {
				c.NewTerms(0, 0);
			}
		}
		//*this�� ������ �׵��� �߰��Ѵ�.
		for (; aPos < terms; aPos++) {
			c.NewTerms(termArray[aPos].coef, termArray[aPos].exp);
		}

		// ���ڷ� ���޵� ��ü�� ������ �׵��� �߰��Ѵ�.
		for (; bPos < poly.terms; bPos++) {
			c.NewTerms(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
		}
		return c;
	}
	float Eval(float f) {

	}
	void Print(Polynomial &p) {
		for (int i = 0; i < p.terms; i++) {
			if (p.termArray[i].coef != 0) {
				cout << p.termArray[i].coef << "x^(" << p.termArray[i].exp << ") " << "+";
			}
			cout << endl;
		}
	}
	Polynomial setting(Polynomial p) {
		float coef;
		int exp;
		int newTerms;
		cout << "�Է��� ���� : ";
		cin >> newTerms;

		for (int i = 0; i < newTerms; i++) {
			cout << "���, ���� �Է� : ";
			cin >> coef >> exp;
			p.NewTerms(coef, exp);
		}
		return p;
	}
	// <�� �ٸ� ��� ���>
	//friend ostream& operator<<(ostream& os, const Polynomial &c);
	friend istream& operator>>(istream &is, Polynomial &c);
};

// <�� �ٸ� ��� ���>
// ������ �����Ǹ� ���� ���
/*
ostream &operator<<(ostream &os, const Polynomial &c) {
	for (int i = 0; i < c.terms; i++) {
		if (c.termArray[i].coef != 0) {
			os << c.termArray[i].coef << "x^(" << c.termArray[i].exp << ") " << "+";
		}
		os << endl;
		return os;
	}
}
*/
istream &operator>>(istream& is, Polynomial &c) {
	float coef;
	int exp;
	int newTerms;

	cout << "�Է��� ���� : ";
	is >> newTerms;

	for (int i = 0; i < newTerms; i++) {
		cout << "���, ���� �Է� : ";
		is >> coef >> exp;
		c.NewTerms(coef, exp);
	}
	return is;
}


int main() {
	Polynomial p1, p2, result;
	
	cin >> p1;
	cin >> p2;

	printf("Add===========\n");
	result = p1.Add(p2);
	result.Print(result);

	printf("mult==========\n");
	result = p1.Mult(p2);
	result.Print(result);
}