#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

int main() {
	multimap<int, int> mm;

	mm.insert(pair<int, int>(60, 6));
	mm.insert(pair<int, int>(30, 3));
	mm.insert(pair<int, int>(70, 7));
	mm.insert(pair<int, int>(90, 9));
	mm.insert(pair<int, int>(40, 4));
	mm.insert(pair<int, int>(20, 3));
	mm.insert(pair<int, int>(50, 5));
	mm.insert(pair<int, int>(80, 8));

	multimap<int, int>::iterator iter;

	cout << "mm.size() : " << mm.size() << endl;
	cout << "mm.count(40) : " << mm.count(40) << endl;

	for (iter = mm.begin(); iter != mm.end(); iter++) {
		cout << "[ " << iter->first << ", " << iter->second << " ]";
	}
	cout << endl << endl;

	mm.insert(pair<int, int>(40, 44));
	mm.insert(pair<int, int>(40, 3));

	cout << "mm.size() : " << mm.size() << endl;
	cout << "mm.count(40) : " << mm.count(40) << endl;

	for (iter = mm.begin(); iter != mm.end(); iter++) {
		cout << " [ " << iter->first << ", " << iter->second << "] ";
	}
	cout << endl;

	return 0;
}