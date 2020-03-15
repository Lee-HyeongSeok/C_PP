#include <algorithm>
#include <string>
#include <iostream>
#include <deque>

using namespace std;

class Person {
public :
	string firstname() const;
	string lastname() const;

	//생략//
};

int main() {
	deque<Person> coll;

	// 생략//
	
	// Person을 성과 이름으로 정렬
	sort(coll.begin(), coll.end(),
		[](const Person& p1, const Person& p2) {
		return p1.lastname() < p2.lastname() ||
			(p1.lastname() == p2.lastname() &&
				p1.firstname() < p2.firstname());
	});
}