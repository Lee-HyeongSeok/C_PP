#include <algorithm>
#include <list>
#include <iostream>
using namespace std;

int main() {
	list<int> coll;

	for (int i = 20; i <= 40; ++i) {
		coll.push_back(i);
	}

	// pos3 : 3�̶�� int �� ������ ��ġ�� ã�´�.
	// ��Ұ� ������ coll.end()�� �ȴ�.
	auto pos3 = find(coll.begin(), coll.end(), 3);

	// ã�� ��ҿ��� ���� ������ ������
	reverse(pos3, coll.end());

	// list<int>�� �ݺ��� pos25, pos35 ����
	list<int>::iterator pos25, pos35;
	
	pos25 = find(coll.begin(), coll.end(), 25);
	pos35 = find(coll.begin(), coll.end(), 35);

	cout << "max : " << *max_element(pos25, ++pos35) << endl;
	cout << "min : " << *min_element(pos25, pos35) << endl;

	auto pos30 = find(pos25, pos35, 30);
	if (pos30 == pos35) {
		cout << "30 is not in the subrange" << endl;
	}
	else {
		cout << "30 is in the subrange" << endl;
	}

	// ���� ����
	// find_if�� ���ٸ� ���, coll �� �� ��ҿ��� ���� ������ ��������

	list<int>::iterator pos;
	pos = find_if(coll.begin(), coll.end(), [](int i) {
		return i == 25 || i == 35;
	});
	if (pos == coll.end()) {
		cout << "���� 25�� ��Ұ� ����" << endl;
	}
	else if (*pos == 25) {
		pos25 = pos;
		pos35 = find(++pos, coll.end(), 35);
	}
	else {
		pos35 = pos;
		pos25 = find(++pos, coll.end(), 25);
	}
}