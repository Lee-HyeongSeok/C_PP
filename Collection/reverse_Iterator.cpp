#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
	vector<int> coll;

	for (int i = 1; i <= 9; i++) {
		coll.push_back(i);
	}
	copy(coll.crbegin(), coll.crend(), ostream_iterator<int>(cout, " "));

	cout << endl;
	vector<int>::iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos) {
		auto elem = *pos;
		cout << elem << ' ';
	}
	cout << endl;
}