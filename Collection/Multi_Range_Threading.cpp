#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
	list<int> coll1;
	for (int i = 0; i < 9; i++) {
		coll1.push_back(i + 1);
	}
	vector<int> coll2;

	coll2.resize(coll1.size());
	// coll2�� �������� ����
	// ���� coll1�� ������, ���� ����
	copy(coll1.cbegin(), coll1.cend(), coll2.begin());
	
	deque<int> coll3(coll1.size());

	copy(coll1.cbegin(), coll1.cend(), coll3.begin());
	
}
