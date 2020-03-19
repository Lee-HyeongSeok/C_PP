#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename T>
void dump(const char *desc, T t) {
	cout.width(12);
	cout << left << desc << " => ";
	copy(t.begin(), t.end(), ostream_iterator<typename T::value_type>(cout, " "));
	cout << endl;
}
int main() {
	vector<int> coll;

	for (int i = 0; i < 8; i++) {
		coll.push_back(i + 1);
	}

	vector<int>::const_iterator minpos = min_element(coll.begin(), coll.end());
	cout << "min : " << *minpos << endl;

	vector<int>::const_iterator maxpos = max_element(coll.begin(), coll.end());
	cout << "max : " << *maxpos << endl;

	dump("vector element ", coll);
}