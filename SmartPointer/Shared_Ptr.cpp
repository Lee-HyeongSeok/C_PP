#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

int main() {

	/*
	1. �̸����� ����� Ÿ������ �� ���� ������
	2. �⺻���� : shared_ptr<�ڷ���> �����������̸�();
	3. �̷��� �����ϸ� �� ���� �Ҵ��ϰ� �ȴ�.
	*/
	shared_ptr<string> pNico(new string("nico"));
	shared_ptr<string> pJutta(new string("jutta"));

	/*
	1. �� ���� �Ҵ��ϴ� ���� ���
	2. make_shared<>() �̿�
	// shared_ptr<string> pMake = make_shared<string>("Jessy");
	*/
	
	/*
	1. ������ ����
	2. shared_ptr�� �����ڿ� �� ��° ���ڷ� ���ٸ� �����ߴ�.
	3. ���ڿ��� ������ �����ڰ� ������ �� �����Լ� ȣ��

	shared_ptr<string> pNico(new string("nico"),
		[](string* p) {
		cout << "delete : " << *p << endl;
		delete p;
	});
	*/

	/*
	���� ������ ���� ���� �� ���ο� �����͸� �ڿ� �Ҵ� ����,
	������ �Ҵ� �����ڸ� ����� �� �����Ƿ� .reset()�� ����ؾ� �Ѵ�.
	shared_ptr<string> Sp;
	Sp = new string("New string");	// error
	Sp.reset(new string("New string")); // Ok

	pNico = nullptr;
	// resize ȣ�� �� delete Nicola ȣ��ȴ�.
	vec.resize(2);
	*/

	/*
	1. �̸��� ù ���ڸ� �빮�ڷ� �ٲ۴�.
	2. ���ڸ� �����ϴ� �� ���� ��� 
	3. *�����ڸ� ����� pNico�� ����Ű�� ��ü�� ����� ������ �� �ִ�.
	*/
	(*pNico)[0] = 'N'; // ���� �����͸� �Ϲ� ������ ó�� ���
	pJutta->replace(0, 1, "J");

	/*
	1. �����̳ʿ� ������ ���� �� ����
	2. �����̳ʴ� ���޵� ��Ҹ� �����ؼ� �����Ѵ�.
	3. �����̳ʿ��� ���� ��ü�� ����Ű�� ���� �����Ͱ� ����ȴ�.
	4. pNico ��ü�� pNico ��ü�� ���� Nico���ڿ��� ����Ű�� ������, vector�� ��ҿ� �� �����Ͱ� ����Ǵ� ��
	*/
	vector<shared_ptr<string>> vec;
	vec.push_back(pNico);
	vec.push_back(pJutta);
	vec.push_back(pNico);
	vec.push_back(pJutta);
	vec.push_back(pNico);

	// ��� ��� ��� 
	for (auto ptr : vec) {
		cout << *ptr << " ";
	}
	cout << endl;

	// �̸��� �ٽ� �����.
	// ���ڿ��� �����ϸ� �����̳ʿ� ����� �����͵��� ��� ������ �޴´�.
	// �������� ���纻�鵵 ��� �� ���� ����Ű�� �ȴ�.
	*pNico = "Nicola";

	// �ٽ� ��� ��� ���
	for (auto ptr : vec) {
		cout << *ptr << " ";
	}
	cout << endl;

	// ���� �����ͷ� �����ϴ� ��ü�� ������ �������� ���� ��ȯ�Ѵ�.
	// vector�� ù ��° ��ҷ� �����ǰ� �ִ� ��ü pNico, �����̳ʿ� ���Ե� pNico �� ���� ���纻 ���� �� 4��
	cout << "Use count : " << vec[0].use_count() << endl;

	// ���ٸ� �����Ͽ� delete[]�� �����ϵ��� ������Ѵ�.
	shared_ptr<int> p(new int[10],
		[](int* p) {
		delete[] p;
	});


	
}
