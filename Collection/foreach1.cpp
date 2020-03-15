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

}