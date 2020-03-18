#include <iostream>
#include <set>

using namespace std;

template <typename T>
void Print_set(set<T>& s) {
	cout << "[ ";
	for (typename set<T>::iterator iter = s.begin(); iter != s.end(); iter++) {
		cout << *iter << ' ';
	}
	cout << " ]" << endl;
}
int main() {
	set<int> s;
	s.insert(10);
	s.insert(50);
	s.insert(20);
	s.insert(40);
	s.insert(30);

	cout << "순서대로 정렬되서 나온다. " << endl;
	Print_set(s);

	cout << "20이 s 의 원소인가요 ? ";
	auto iter = s.find(20);
	if (iter != s.end()) {
		cout << "네" << endl;
	}
	else {
		cout << "ㄴㄴ" << endl;
	}

	cout << "25가 s 의 원소임 ? ";
	iter = s.find(25);
	if (iter != s.end()) {
		cout << "네 " << endl;
	}
	else {
		cout << "ㄴㄴ" << endl;
	}
}