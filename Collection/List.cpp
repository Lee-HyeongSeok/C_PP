#include <algorithm>
#include <list>
#include <iostream>
using namespace std;

int main() {
	list<int> coll;

	for (int i = 20; i <= 40; ++i) {
		coll.push_back(i);
	}

	// pos3 : 3이라는 int 형 정수의 위치를 찾는다.
	// 요소가 없으면 coll.end()가 된다.
	auto pos3 = find(coll.begin(), coll.end(), 3);

	// 찾은 요소에서 부터 순서를 뒤집음
	reverse(pos3, coll.end());

	// list<int>형 반복자 pos25, pos35 선언
	list<int>::iterator pos25, pos35;
	
	pos25 = find(coll.begin(), coll.end(), 25);
	pos35 = find(coll.begin(), coll.end(), 35);

	cout << "max : " << *max_element(pos25, ++pos35) << endl;
	cout << "min : " << *min_element(pos25, pos35) << endl;

	auto pos30 = find(pos25, pos35, 30);
	if (pos30 == pos35) {
		cout << "30 is not in the subrange" << endl;
	}
	else {
		cout << "30 is in the subrange" << endl;
	}

	// 범위 구현
	// find_if와 람다를 사용, coll 내 각 요소에서 평가할 기준을 정의해줌

	list<int>::iterator pos;
	pos = find_if(coll.begin(), coll.end(), [](int i) {
		return i == 25 || i == 35;
	});
	if (pos == coll.end()) {
		cout << "값이 25인 요소가 없음" << endl;
	}
	else if (*pos == 25) {
		pos25 = pos;
		pos35 = find(++pos, coll.end(), 35);
	}
	else {
		pos35 = pos;
		pos25 = find(++pos, coll.end(), 25);
	}
}