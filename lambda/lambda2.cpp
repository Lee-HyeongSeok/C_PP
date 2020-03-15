#include <algorithm>
#include <string>
#include <iostream>
#include <deque>

using namespace std;

class Person {
public :
	string firstname() const;
	string lastname() const;

	//����//
};

int main() {
	deque<Person> coll;

	// ����//
	
	// Person�� ���� �̸����� ����
	sort(coll.begin(), coll.end(),
		[](const Person& p1, const Person& p2) {
		return p1.lastname() < p2.lastname() ||
			(p1.lastname() == p2.lastname() &&
				p1.firstname() < p2.firstname());
	});
}