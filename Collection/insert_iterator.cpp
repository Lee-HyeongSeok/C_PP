#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>
#include <deque>

#include <set>


using namespace std;

int main() {
	list<int> coll1;
	for (int i = 0; i < 9; i++) {
		coll1.push_back(i + 1);
	}

	vector<int> coll2;
	copy(coll1.cbegin(), coll1.cend(), back_inserter(coll2));
	vector<int>::iterator pos;
	for (pos = coll2.begin(); pos != coll2.end(); ++pos) {
		auto elem = *pos;
		cout << elem << ' ';
	}
	cout << endl;
	deque<int> coll3;
	copy(coll1.cbegin(), coll1.cend(), front_inserter(coll3));
	deque<int>::iterator pos1;
	for (pos1 = coll3.begin(); pos1 != coll3.end(); ++pos1) {
		auto elem = *pos1;
		cout << elem << ' ';
	}
	
	set<int> coll4;
	copy(coll1.cbegin(), coll1.cend(), inserter(coll4, coll4.begin()));
}