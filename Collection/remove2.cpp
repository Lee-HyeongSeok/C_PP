#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>

using namespace std;

int main() {
	list<int> coll;

	for (int i = 1; i <= 6; i++) {
		coll.push_front(i);
		coll.push_back(i);
	}

	// 삭제 이전
	copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;

	// 값이 3인 모든 요소 제거
	// 새 끝 유지
	list<int>::iterator end = remove(coll.begin(), coll.end(), 3);

	// 얻은 모음의 요소 출력
	// 범위의 시작과 끝이 같아야 하기 때문에 begin() 사용
	copy(coll.begin(), end, ostream_iterator<int>(cout, " "));
	cout << endl;

	// 제거된 요소의 개수 출력, 새 끝 - 제거 이후의 끝
	cout << "number of removed elements : " << distance(end, coll.end()) << endl;

	// 제거된 요소 삭제
	// 요소를 제거하기 위한 컨테이너의 적절한 멤버함수 호출 erase() 멤버
	coll.erase(end, coll.end());

	// 수정된 모음 출력
	copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;
}