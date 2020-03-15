#include <list>
#include <algorithm>
#include <iostream>
#include <cstdlib>
using namespace std;

bool isPrime(int number) {
	// ��ȣ ����, ���� �� �Լ�
	number = abs(number);

	if (number == 0 || number == 1) {
		return false;
	}

	// ������ ���� ������ ������ ã�´�.
	int divisor;
	for (divisor = number / 2; number % divisor != 0; --divisor) {
		;
	}
	return divisor == 1;
}
int main() {
	list<int> coll;
	for (int i = 1; i <= 30; i++)
	{
		coll.push_back(i);
	}

	auto pos = find_if(coll.cbegin(), coll.cend(), isPrime);
		
	
	if (pos != coll.end()) {
		cout << *pos << endl;
		//cout << *pos << " is first prime number found" << endl;
	}
	else {
		cout << "not found" << endl;
	}
	
}