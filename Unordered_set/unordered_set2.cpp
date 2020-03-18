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

	cout << "������� ���ĵǼ� ���´�. " << endl;
	Print_set(s);

	cout << "20�� s �� �����ΰ��� ? ";
	auto iter = s.find(20);
	if (iter != s.end()) {
		cout << "��" << endl;
	}
	else {
		cout << "����" << endl;
	}

	cout << "25�� s �� ������ ? ";
	iter = s.find(25);
	if (iter != s.end()) {
		cout << "�� " << endl;
	}
	else {
		cout << "����" << endl;
	}
}