#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;

int main() {
	deque<int> coll = { 1, 3, 19, 5, 13, 7, 11, 2, 17 };
	int x = 5;
	int y = 12;

	// ���ٴ� ���� i�� �޾� x���� ũ�� y���� �������� ��ȯ�ϴ� �Լ� ��ü��.
	/* ĸ���� [=]�� ����ϸ� ���ٰ� ����Ǵ� ������ ����� �� �ִ� ������
		������ ���ο� ������ ���� ����
		������ ���� ���ο����� x, y�� ���� �� �ִ� ���̴�.

		[&] ���� ����� ���޵Ǳ� ������ ���� ���ο��� x, y���� ������ �� �ִ�.
	*/
	auto pos = find_if(coll.cbegin(), coll.cend(), // ����
		[=](int i) {	// ���� ����
		return i > x && i < y;
	});

	//��//

	/*
	���� �ۼ��� ������ ���
	vector<int>::iterator pos;
	for (pos = coll.begin(); pos != coll.end(); ++pos) {
		if (*pos > x && *pos < y)
			break;
	}
	*/

	/*
	bool pred(int i){
		return i > x && i < y;
	}
	... ����
	int main(){
		... ����
		pos = find_if(coll.begin(), coll.end(), pred);
	}
	*/
	cout << "first elem > 5 and < 12 : " << *pos << endl;
}