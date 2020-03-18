#include <iostream>
#include <unordered_set>	// ������ ��
#include <string>
#include <unordered_map>	// ������ ���� ��
using namespace std;

int main() {
	// ������ ��
	unordered_multiset<string> cities{
		"Braunschweig", "Hanover", "Frankfurt", "New York",
		"Chicago", "Toronto", "Paris", "Frankfurt"
	};
	for (const auto& elem : cities) {
		cout << elem << ' ';
	}
	cout << endl;

	cities.insert({ "London", "Munich", "Hanover", "Branschweig" });
	for (const auto& elem : cities) {
		cout << elem << " ";
	}
	cout << endl;
	unordered_map<string, double> coll{ {"tim", 9.9}, {"struppi", 11.77} };

	// �� ����� �� ����
	for (pair < const string, double >& elem : coll){
		elem.second *= elem.second;
	}
	for (const auto& elem : coll) {
		cout << elem.first << " : " << elem.second << endl;
	}
}