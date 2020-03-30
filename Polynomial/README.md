## c++ 자료구조론 다항식   

#### * 사용 함수
		* Add(Polynomial poly)
		* Mult(Polynomial poly)   
		* NewTerms(const float c, const int e)
		* Print();

#### 출력 방법
#### * 연산자 재정의
		* ostream &operator<<(ostream& os, const Polynomial &c);
#### * 클래스 메서드 정의
		* Print();

#### 입력 방법
#### * 연산자 재정의
		* istream &operator>>(istream &is, Polynomial &c);
#### * 클래스 메서드 정의
		* setting();   

## 표현 방법
#### * a(6)=x^(5)+x^(4)+...+x^(1)+x^(0)
#### * b(6)=x^(5)+x^(4)+...+x^(1)+x^(0)
#### * a(x) = 3x^(2) + 2x^(1)-4 에서 (계수, 지수)의 쌍으로 표현한다.
		* 계수 : coef
		* 지수 : exp   


## Term 클래스   
<pre>
<code>
class Term {
	friend Polynomial;

	// <또 다른 출력 및 입력 방법>
	// friend ostream &operator<<(ostream &os, const Polynomial &c);
private :
	// Polynomial 클래스에서 계수와 지수를 쌍으로 가지는 배열을 위해 존재한다.
	float coef; // 계수
	int exp; // 지수
};
</code>
</pre>   

## Polynomial 클래스   
<pre>
<code>
class Polynomial {
private :
	Term *termArray; // 0이 아닌 항의 배열
	int capacity;	// termArray의 크기
	int terms;		// 0이 아닌 항의 수

public:
	Polynomial() {
		capacity = 1;
		terms = 0;
		termArray = new Term[capacity];
	}
	void NewTerms(const float c, const int e) {
		if (terms == capacity) {
			// termArray의 크기를 두 배로 확장한다.
			capacity *= 2;
			Term *temp = new Term[capacity]; // 새로운 배열 동적할당
			copy(termArray, termArray + terms, temp);
			delete[] termArray; // 그 전 메모리를 반환
			termArray = temp;
		}
		termArray[terms].coef = c;
		termArray[terms++].exp = e;
	}
	Polynomial Add(Polynomial poly) {
		Polynomial c; // 더해진 객체를 반환하기 위한 객체
		/*
		 인자로 전달된 객체와 *this를 0이 아닌 항의 수로
		 분석을 수행한다.
		*/

		// aPos : 비교할 대상 객체
		// bPos : 전달된 객체
		int aPos = 0, bPos = 0;

		/*
		 aPos가 *this의 terms와 같거나
		 bPos가 인자로 전달된 객체의 terms와 같을 때 종료
		*/
		while ((aPos < terms) && (bPos < poly.terms)) {
			if ((termArray[aPos].exp == poly.termArray[bPos].exp)) {
				float t = termArray[aPos].coef + poly.termArray[bPos].coef;
				// 반환 목적의 객체에 새로운 항 만들기
				if (t)
					c.NewTerms(t, termArray[aPos].exp);
				aPos++; bPos++;
			}
			// 인자로 전달된 객체의 항이 더 높을 때
			else if ((termArray[aPos].exp < poly.termArray[bPos].exp)) {
				c.NewTerms(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
				bPos++;
			}
			// *this의 항이 더 높을 때
			else {
				c.NewTerms(termArray[aPos].coef, termArray[aPos].exp);
				aPos++;
			}
		}
		//*this의 나머지 항들을 추가한다.
		for (; aPos < terms; aPos++) {
			c.NewTerms(termArray[aPos].coef, termArray[aPos].exp);
		}

		// 인자로 전달된 객체의 나머지 항들을 추가한다.
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
			// 계수와 지수가 다르면 0이 된다.
			else {
				c.NewTerms(0, 0);
			}
		}
		//*this의 나머지 항들을 추가한다.
		for (; aPos < terms; aPos++) {
			c.NewTerms(termArray[aPos].coef, termArray[aPos].exp);
		}

		// 인자로 전달된 객체의 나머지 항들을 추가한다.
		for (; bPos < poly.terms; bPos++) {
			c.NewTerms(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
		}
		return c;
	}
	
	void Print() {
		for (int i = 0; i < terms; i++) {
			if (termArray[i].coef != 0) {
				cout << termArray[i].coef << "x^(" << termArray[i].exp << ") " << "+";
			}
			cout << endl;
		}
	}
	Polynomial setting() {
		float coef;
		int exp;
		int newTerms;
		cout << "입력할 개수 : ";
		cin >> newTerms;

		for (int i = 0; i < newTerms; i++) {
			cout << "계수, 지수 입력 : ";
			cin >> coef >> exp;
			this->NewTerms(coef, exp);
		}
		return *this;
	}
	// <또 다른 출력 방법>
	//friend ostream& operator<<(ostream& os, const Polynomial &c);
	friend istream& operator>>(istream &is, Polynomial &c);
};
</code>
</pre>

## 연산자 재정의(출력)   
<pre>
<code>
ostream &operator<<(ostream &os, const Polynomial &c) {
	for (int i = 0; i < c.terms; i++) {
		if (c.termArray[i].coef != 0) {
			os << c.termArray[i].coef << "x^(" << c.termArray[i].exp << ") " << "+";
		}
		os << endl;
		return os;
	}
}
</code>
</pre>   

## 연산자 재정의(입력)   
<pre>
<code>
istream &operator>>(istream& is, Polynomial &c) {
	float coef;
	int exp;
	int newTerms;

	cout << "입력할 개수 : ";
	is >> newTerms;

	for (int i = 0; i < newTerms; i++) {
		cout << "계수, 지수 입력 : ";
		is >> coef >> exp;
		c.NewTerms(coef, exp);
	}
	return is;
}
</code>
</pre>   

