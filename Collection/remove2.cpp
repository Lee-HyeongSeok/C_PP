#include <iostream>
#include <algorithm>
#include <list>
#include <iterator>

using namespace std;

int main() {
	list<int> coll;

	for (int i = 1; i <= 6; i++) {
		coll.push_front(i);
		coll.push_back(i);
	}

	// ���� ����
	copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;

	// ���� 3�� ��� ��� ����
	// �� �� ����
	list<int>::iterator end = remove(coll.begin(), coll.end(), 3);

	// ���� ������ ��� ���
	// ������ ���۰� ���� ���ƾ� �ϱ� ������ begin() ���
	copy(coll.begin(), end, ostream_iterator<int>(cout, " "));
	cout << endl;

	// ���ŵ� ����� ���� ���, �� �� - ���� ������ ��
	cout << "number of removed elements : " << distance(end, coll.end()) << endl;

	// ���ŵ� ��� ����
	// ��Ҹ� �����ϱ� ���� �����̳��� ������ ����Լ� ȣ�� erase() ���
	coll.erase(end, coll.end());

	// ������ ���� ���
	copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;
}