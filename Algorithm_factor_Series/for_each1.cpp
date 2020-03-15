#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void print(int elem) {
	cout << elem << ' ';
}

int main() {
	vector<int> coll;

	for (int i = 1; i <= 9; i++) {
		coll.push_back(i);
	}
	// for_each 알고리즘
	// cbegin(), cend() 범위 내 모든 요소에 대해 전달받은 print 함수를 호출함
	for_each(coll.cbegin(), coll.cend(), print);
	cout << endl;
}