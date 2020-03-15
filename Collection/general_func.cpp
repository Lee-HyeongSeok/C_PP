#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "") {
	cout << optstr;
	for (const auto& elem : coll) {
		cout << elem << ' ';
	}
	cout << endl;
}
int main() {
	vector<int> coll;

	for (int i = 1; i <= 9; i++) {
		coll.push_back(i);
	}
	PRINT_ELEMENTS(coll, "all elements: ");
}