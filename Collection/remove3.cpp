#include <set>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

int main() {
	set<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;

	// 삭제된 요소의 수를 반환한다.
	// 중복된 값을 허용하지 않는 컨테이너라면, 반환 값은 0 또는 1이다.
	int num = coll.erase(3);

	cout << "number of removed elements : " << num << endl;

	copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;
}