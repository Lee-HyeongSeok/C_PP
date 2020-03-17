#include <iostream>
#include <chrono>
#include <ratio>
#include <string>
#include <ctime>

using namespace std;
using namespace std::chrono;

// time_point 클래스의 기본 생성자가 클럭에 따라 반환하는 값
// 현재시간은 클럭의 정적 멤버 함수인 now()를 나타낸다.
// 최소 시간 지점은 time_point 클래스의 정적 멤버 함수인 min()이 클럭에 따라 반환하는 값이다.
// 최대 시간 지점은 time_point 클래스의 정적 멤버 함수인 max()가 각 클럭을 위해 반환하는 값이다.
template <typename V, typename R>
ostream& operator<<(ostream& os, const chrono::duration<V, R>& d) {
	os << "[ " << d.count() << " of " << R::num << "/" << R::den << " ]";
	return os;
}
string asString(const system_clock::time_point& tp) {

	time_t t = system_clock::to_time_t(tp);	//time_t는 1970년 1월 1일에서 부터 몇초가 흘렀는지ㅠ
	string ts = ctime(&t);
	ts.resize(ts.size() - 1);
	return ts;
}
int main() {
	// 이 시스템 클럭의 기초 출력
	system_clock::time_point tp;
	cout << "epoch : " << asString(tp) << endl;	//asString()은 시스템 클럭의 시간지점을 달력 시간으로 변환하는 함수

	//현재 시간 출력
	tp = system_clock::now();
	cout << "now : " << asString(tp) << endl;

	//이 시스템 클럭의 최소 시간 출력
	tp = system_clock::time_point::min();
	cout << "min : " << asString(tp) << endl;

	// 이 시스템 클럭의 최대 시간 출력
	tp = system_clock::time_point::max();
	cout << "max : " << asString(tp) << endl;
}