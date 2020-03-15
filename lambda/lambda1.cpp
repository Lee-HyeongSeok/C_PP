#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;

int main() {
	deque<int> coll = { 1, 3, 19, 5, 13, 7, 11, 2, 17 };
	int x = 5;
	int y = 12;

	// 람다는 정수 i를 받아 x보다 크고 y보다 작은지를 반환하는 함수 객체다.
	/* 캡쳐인 [=]로 명시하면 람다가 선언되는 곳에서 사용할 수 있는 변수를
		람다의 내부에 값으로 전달 가능
		때문에 람다 내부에서도 x, y를 읽을 수 있던 것이다.

		[&] 사용시 참고로 전달되기 때문에 람다 내부에서 x, y값을 수정할 수 있다.
	*/
	auto pos = find_if(coll.cbegin(), coll.cend(), // 범위
		[=](int i) {	// 정렬 기준
		return i > x && i < y;
	});

	//비교//

	/*
	직접 작성한 루프를 사용
	vector<int>::iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos) {
		if (*pos > x && *pos < y)
			break;
	}
	*/

	/*
	bool pred(int i){
		return i > x && i < y;
	}
	... 생략
	int main(){
		... 생략
		pos = find_if(coll.begin(), coll.end(), pred);
	}
	*/
	cout << "first elem > 5 and < 12 : " << *pos << endl;
}