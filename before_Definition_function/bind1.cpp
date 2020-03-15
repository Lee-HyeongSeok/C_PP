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
print.hpp ����
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
	// ���� ������ greater<>()�� ��Ҵ� �������� ���ĵ�
	set<int, greater<int>> coll1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	deque<int> coll2;

	PRINT_ELEMENTS(coll1, "initialized: ");

	// ��� ��Ҹ� coll2�� �ű�鼭 10�� ���Ѵ�.
	// bind() : ���� ���� �Լ� ��ü�� ��ġ�����ڷ� ���� ���� �Լ� ��ü�� ����
	// ��ġ ������ : ���ٷ� �����ϴ� ���� �ĺ���
	transform(coll1.cbegin(), coll1.cend(), back_inserter(coll2), bind(multiplies<int>(), _1, 10));
	PRINT_ELEMENTS(coll2, "tramsformed : ");

	// ���� : begin()~end()
	// ġȯ���� : bind(equal_to<int>(), _1, 70)
	// �� �� : 42
	// 42�� ġȯ�� ��ҵ��� ��󳻱� ���� �������� ���
	replace_if(coll2.begin(), coll2.end(), bind(equal_to<int>(), _1, 70), 42);
	PRINT_ELEMENTS(coll2, "replaced : ");

	// 50���� 80������ ���� ���� ��Ҹ� �����Ѵ�.
	// remove_if() : ������ �ٲ� ���� ���ο� ���� ��ȯ�� ���̴�.
	// coll2.erase()�� ���ŵ� ��ҵ��� �����Ѵ�.
	coll2.erase(remove_if(coll2.begin(), coll2.end(),
		bind(logical_and<bool>(),
			bind(greater_equal<int>(), _1, 50),
			bind(less_equal<int>(), _1, 80))),
		coll2.end());
	PRINT_ELEMENTS(coll2, "removed : ");
}