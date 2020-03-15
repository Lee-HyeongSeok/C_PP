#include <set>
#include <deque>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iostream>
#include "D:\C++ stl\Algorithm_factor_Series\print.hpp"

using namespace std;
using namespace std::placeholders;

/*
print.hpp 내용
template <typename T>
inline void PRINT_ELEMENTS(const T& coll, const std::string& optstr=""){
   cout<<optstr;
   for(const auto& elem: coll){
	  cout<<elem<<' ';
   }
   cout<<endl;
}
*/

int main() {
	// 정렬 기준인 greater<>()로 요소는 역순으로 정렬됨
	set<int, greater<int>> coll1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	deque<int> coll2;

	PRINT_ELEMENTS(coll1, "initialized: ");

	// 모든 요소를 coll2로 옮기면서 10을 곱한다.
	// bind() : 하위 계층 함수 객체와 위치소유자로 상위 계층 함수 객체를 만듬
	// 위치 소유자 : 밑줄로 시작하는 숫자 식별자
	transform(coll1.cbegin(), coll1.cend(), back_inserter(coll2), bind(multiplies<int>(), _1, 10));
	PRINT_ELEMENTS(coll2, "tramsformed : ");

	// 범위 : begin()~end()
	// 치환기준 : bind(equal_to<int>(), _1, 70)
	// 새 값 : 42
	// 42로 치환될 요소들을 골라내기 위해 기준으로 사용
	replace_if(coll2.begin(), coll2.end(), bind(equal_to<int>(), _1, 70), 42);
	PRINT_ELEMENTS(coll2, "replaced : ");

	// 50에서 80사이의 값을 갖는 요소를 제거한다.
	// remove_if() : 순서를 바꾼 다음 새로운 끝을 반환할 뿐이다.
	// coll2.erase()가 제거된 요소들을 삭제한다.
	coll2.erase(remove_if(coll2.begin(), coll2.end(),
		bind(logical_and<bool>(),
			bind(greater_equal<int>(), _1, 50),
			bind(less_equal<int>(), _1, 80))),
		coll2.end());
	PRINT_ELEMENTS(coll2, "removed : ");
}