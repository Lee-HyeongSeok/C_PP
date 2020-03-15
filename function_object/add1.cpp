#include <list>
#include <algorithm>
#include <iostream>
#include "D:\C++ stl\Algorithm_factor_Series\print.hpp"

using namespace std;

/*
template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr = "") {
	cout << optstr;
	for (const auto& elem : coll) {
		cout << elem << ' ';
	}
	cout << endl;
}
*/
class AddValue {
private:
	int theValue;
public:
	// ���� ���� �ʱ�ȭ�ϴ� ������
	AddValue(int v) :theValue(v) {

	}
	// �� Ŭ������ �ӽ� ��ü�� ������
	void operator() (int& elem) const {
		elem += theValue;
	}
};

int main() {
	list<int> coll;

	for (int i = 1; i <= 9; i++) {
		coll.push_back(i);
	}
	PRINT_ELEMENTS(coll, "initialized : ");

	for_each(coll.begin(), coll.end(), AddValue(10));
	PRINT_ELEMENTS(coll, "after adding 10 : ");

	for_each(coll.begin(), coll.end(), AddValue(*coll.begin()));
	PRINT_ELEMENTS(coll, "after adding first element : ");
}