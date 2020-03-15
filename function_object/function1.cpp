#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class PrintInt {
public :

	// 전달된 인자를 출력하는 함수객체
	void operator()(int elem) const {
		cout << elem << ' ';
	}
};
int main() {
	vector<int> coll;

	for (int i = 1; i <= 9; i++) {

		coll.push_back(i);
	}

	// PrintInt는 operator()를 호출할 수 있는 객체를 정의한다.
	// 이 클래스의 임시 객체를 생성하고, for_each 알고리즘에 인자로 전달됨
	for_each(coll.cbegin(), coll.cend(), PrintInt());

	cout << endl;
}