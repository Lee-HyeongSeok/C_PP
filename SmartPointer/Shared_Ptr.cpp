#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

int main() {

	/*
	1. 이름으로 사람을 타나내는 두 공유 포인터
	2. 기본형식 : shared_ptr<자료형> 공유포인터이름();
	3. 이렇게 생성하면 두 번을 할당하게 된다.
	*/
	shared_ptr<string> pNico(new string("nico"));
	shared_ptr<string> pJutta(new string("jutta"));

	/*
	1. 한 번만 할당하는 선언 방식
	2. make_shared<>() 이용
	// shared_ptr<string> pMake = make_shared<string>("Jessy");
	*/
	
	/*
	1. 삭제자 정의
	2. shared_ptr의 생성자에 두 번째 인자로 람다를 전달했다.
	3. 문자열의 마지막 소유자가 삭제될 때 람다함수 호출

	shared_ptr<string> pNico(new string("nico"),
		[](string* p) {
		cout << "delete : " << *p << endl;
		delete p;
	});
	*/

	/*
	공유 포인터 먼저 선언 후 새로운 포인터를 뒤에 할당 가능,
	하지만 할당 연산자를 사용할 수 없으므로 .reset()을 사용해야 한다.
	shared_ptr<string> Sp;
	Sp = new string("New string");	// error
	Sp.reset(new string("New string")); // Ok

	pNico = nullptr;
	// resize 호출 시 delete Nicola 호출된다.
	vec.resize(2);
	*/

	/*
	1. 이름의 첫 문자를 대문자로 바꾼다.
	2. 문자를 변경하는 두 가지 방식 
	3. *연산자를 사용해 pNico가 가리키는 객체의 멤버에 접근할 수 있다.
	*/
	(*pNico)[0] = 'N'; // 공유 포인터를 일반 포인터 처럼 사용
	pJutta->replace(0, 1, "J");

	/*
	1. 컨테이너에 각각을 여러 번 삽입
	2. 컨테이너는 전달된 요소를 복사해서 저장한다.
	3. 컨테이너에는 같은 객체를 가리키는 여러 포인터가 저장된다.
	4. pNico 객체는 pNico 객체의 값인 Nico문자열을 가리키는 포인터, vector의 요소에 그 포인터가 저장되는 것
	*/
	vector<shared_ptr<string>> vec;
	vec.push_back(pNico);
	vec.push_back(pJutta);
	vec.push_back(pNico);
	vec.push_back(pJutta);
	vec.push_back(pNico);

	// 모든 요소 출력 
	for (auto ptr : vec) {
		cout << *ptr << " ";
	}
	cout << endl;

	// 이름을 다시 덮어쓴다.
	// 문자열을 조작하면 컨테이너에 저장된 포인터들이 모두 영향을 받는다.
	// 포인터의 복사본들도 모두 새 값을 가리키게 된다.
	*pNico = "Nicola";

	// 다시 모든 요소 출력
	for (auto ptr : vec) {
		cout << *ptr << " ";
	}
	cout << endl;

	// 공유 포인터로 참조하는 객체를 소유한 포인터의 수를 반환한다.
	// vector의 첫 번째 요소로 참조되고 있는 객체 pNico, 컨테이너에 삽입된 pNico 세 개의 복사본 까지 총 4개
	cout << "Use count : " << vec[0].use_count() << endl;

	// 람다를 전달하여 delete[]를 삭제하도록 해줘야한다.
	shared_ptr<int> p(new int[10],
		[](int* p) {
		delete[] p;
	});


	
}
