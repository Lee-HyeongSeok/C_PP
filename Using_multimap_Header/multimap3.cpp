#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	multimap<int, string> mm;

	mm.insert(pair<int, string>(60, "c"));
	mm.insert(pair<int, string>(30, "C++"));
	mm.insert(pair<int, string>(40, "Linux"));
	mm.insert(pair<int, string>(70, "Java"));
	mm.insert(pair<int, string>(40, "Ubuntu"));
	mm.insert(pair<int, string>(90, "Unix"));
	mm.insert(pair<int, string>(40, "CentOS"));

	multimap<int, string>::iterator iter;

	for (iter = mm.begin(); iter != mm.end(); iter++) {
		cout << "[ " << iter->first << ", " << iter->second << " ] ";
	}
	cout << endl;
	// 중복 키 값이 존재하는 40의 인자 출력
	for (iter = mm.equal_range(40).first; iter != mm.equal_range(40).second; iter++) {
		cout << "[ " << iter->first << ", " << iter->second << " ]";
	}
	cout << endl;

	pair < multimap<int, string>::iterator,
		multimap<int, string>::iterator> pair_iter = mm.equal_range(40);

	// [ fisrt, second ) 개폐구간
	cout << "pair_iter.first : " << (pair_iter.first)->first << ", " << (pair_iter.first)->second << endl;
	cout << "pair_iter.second : " << (pair_iter.second)->first << ", " << (pair_iter.second)->second << endl;

	return 0;

}