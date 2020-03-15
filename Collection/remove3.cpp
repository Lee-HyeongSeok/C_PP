#include <set>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

int main() {
	set<int> coll = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;

	// ������ ����� ���� ��ȯ�Ѵ�.
	// �ߺ��� ���� ������� �ʴ� �����̳ʶ��, ��ȯ ���� 0 �Ǵ� 1�̴�.
	int num = coll.erase(3);

	cout << "number of removed elements : " << num << endl;

	copy(coll.cbegin(), coll.cend(), ostream_iterator<int>(cout, " "));
	cout << endl;
}