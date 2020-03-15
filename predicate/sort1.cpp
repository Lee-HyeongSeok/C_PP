#include <algorithm>
#include <deque>
#include <string>
#include <iostream>
#include <iterator>
using namespace std;

class Person {
private :
	string f_name;
	string l_name;
public : 
	void setFName(string f) {
		f_name = f;
	}
	void setLName(string l) {
		l_name = l;
	}
	string firstname() const {
		return f_name;
	}
	string lastname() const {
		return l_name;
	}
	string getF() {
		return f_name;
	}
	string getL() {
		return l_name;
	}
};


// 하나의 Person 객체가 다른 Person 객체보다 작은지 여부 반환
bool personSortCriterion(const Person& p1, const Person& p2) {
	return p1.lastname() < p2.lastname() ||
		(p1.lastname() == p2.lastname() && p1.firstname() < p2.firstname());
}

int main() {
	deque<Person> coll;

	Person P1;
	Person P2;

	P1.setFName("hello");
	P1.setLName("C");

	P2.setFName("hello");
	P2.setLName("java");

	coll.push_back(P1);
	coll.push_back(P2);
	
	/*
	deque<Person>::const_iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos) {
		cout << pos->getF() << endl
	}
	*/
	sort(coll.begin(), coll.end(), personSortCriterion);
}