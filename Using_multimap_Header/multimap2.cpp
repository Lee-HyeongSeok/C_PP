#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

int main() {
	multimap<int, string> mm;

	mm.insert(pair<int, string>(60, "C"));
	mm.insert(pair<int, string>(30, "C++"));
	mm.insert(pair<int, string>(40, "CentOs"));
	mm.insert(pair<int, string>(40, "Linux"));
	mm.insert(pair<int, string>(70, "Java"));
	mm.insert(pair<int, string>(90, "Unix"));
	mm.insert(pair<int, string>(40, "Kali linux"));
	mm.insert(pair<int, string>(40, "Fedora"));

	multimap<int, string>::iterator iter;

	for (iter = mm.begin(); iter != mm.end(); iter++) {
		cout << "[ " << iter->first << ", " << iter->second << "] ";
	}
	cout << endl << endl;

	//�ߺ� Ű ���� �����ϴ� 40�� ���� ���
	for (iter = mm.lower_bound(40); iter != mm.upper_bound(40); iter++) {
		cout << "[ " << iter->first << ", " << iter->second << "] ";
	}
	cout << endl;

	// ���� >= lower_bound
	// ���� < upper_bound
	// [ lower_iter, upper_bound )	���󱸰�.
	multimap<int, string>::iterator lower_iter = mm.lower_bound(40);
	multimap<int, string>::iterator upper_iter = mm.upper_bound(40);

	cout << "lower_iter : " << lower_iter->first << ", " << lower_iter->second << endl;
	cout << "upper_iter : " << upper_iter->first << ", " << upper_iter->second << endl;

	cout << "mm.size() : " << mm.size() << endl;

	return 0;
}