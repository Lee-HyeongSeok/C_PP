#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "print.hpp"

using namespace std;

int square(int value) {
	return value * value;
}

int main() {
	set<int> coll1;
	vector<int> coll2;
	for (int i = 1; i <= 9; i++) {
		coll1.insert(i);
	}
	PRINT_ELEMENTS(coll1, "initialized: ");

	transform(coll1.cbegin(), coll1.cend(), back_inserter(coll2), square);
	PRINT_ELEMENTS(coll2, "square: ");
}