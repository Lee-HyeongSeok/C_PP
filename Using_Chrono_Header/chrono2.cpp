#include <iostream>
#include <chrono>
#include <ratio>
#include <string>
#include <ctime>

using namespace std;
using namespace std::chrono;

// time_point Ŭ������ �⺻ �����ڰ� Ŭ���� ���� ��ȯ�ϴ� ��
// ����ð��� Ŭ���� ���� ��� �Լ��� now()�� ��Ÿ����.
// �ּ� �ð� ������ time_point Ŭ������ ���� ��� �Լ��� min()�� Ŭ���� ���� ��ȯ�ϴ� ���̴�.
// �ִ� �ð� ������ time_point Ŭ������ ���� ��� �Լ��� max()�� �� Ŭ���� ���� ��ȯ�ϴ� ���̴�.
template <typename V, typename R>
ostream& operator<<(ostream& os, const chrono::duration<V, R>& d) {
	os << "[ " << d.count() << " of " << R::num << "/" << R::den << " ]";
	return os;
}
string asString(const system_clock::time_point& tp) {

	time_t t = system_clock::to_time_t(tp);	//time_t�� 1970�� 1�� 1�Ͽ��� ���� ���ʰ� �귶������
	string ts = ctime(&t);
	ts.resize(ts.size() - 1);
	return ts;
}
int main() {
	// �� �ý��� Ŭ���� ���� ���
	system_clock::time_point tp;
	cout << "epoch : " << asString(tp) << endl;	//asString()�� �ý��� Ŭ���� �ð������� �޷� �ð����� ��ȯ�ϴ� �Լ�

	//���� �ð� ���
	tp = system_clock::now();
	cout << "now : " << asString(tp) << endl;

	//�� �ý��� Ŭ���� �ּ� �ð� ���
	tp = system_clock::time_point::min();
	cout << "min : " << asString(tp) << endl;

	// �� �ý��� Ŭ���� �ִ� �ð� ���
	tp = system_clock::time_point::max();
	cout << "max : " << asString(tp) << endl;
}