#include <iostream>
#include "ATMachine.h"
#include "Statistics.h"
using namespace std;


ATMachine::ATMachine() {

}
void ATMachine::displayMenu() {
	cout << "-------------------------------------" << endl;
	cout << "-" << "   " << "KPU bank" << "   " << "-" << endl;
	cout << " 1. ���� ���� " << endl;
	cout << " 2. ���� ��ȸ " << endl;
	cout << " 3. ���� �Ա� " << endl;
	cout << " 4. ���� ��� " << endl;
	cout << " 5. �� ���� " << endl;
	cout << " 9. ���� ���� " << endl;
	cout << "�޴��� �����ϼ��� : ";
}
//���� �迭ũ��, ATM �ܰ�, ������ ��ȣ �ʱ�ȭ
void ATMachine::initialisze(int nSize, int nBalance, string password) {
	pAcctArray = new Account[nSize];	// �� �� �����Ҵ�
	nMachineBalance = nBalance;
	strManagerPassword = password;
	nCurrentAccountNum = 0;
	nMaxAccountNum = nSize;
}
void ATMachine::createAccount() {
	string name;
	string passwd;
	cout << "-----------����-----------" << endl;
	cout << "�̸� �Է� : ";
	cin >> name;
	cout << endl;
	cout << "��ȣ �Է� : ";
	cin >> passwd;
	cout << endl;
	pAcctArray[nCurrentAccountNum].create(nCurrentAccountNum, 0, name, passwd);	// ������ ���� �� ī��Ʈ �������� ��� Ȯ��
	cout << name << " �� " << pAcctArray[nCurrentAccountNum].GetAccID() << " �� ���¹�ȣ�� ���������� �����Ǿ����ϴ�." << endl;
	nCurrentAccountNum++;	// ������ �� ���� ī��Ʈ
}
void ATMachine::checkMoney() {
	int ID;
	string passwd;
	cout << "-----------��ȸ-------------" << endl;
	cout << "���� ��ȣ �Է� : ";
	cin >> ID; cout << endl;
	cout << "��й�ȣ �Է� : ";
	cin >> passwd; cout << endl;
	int index = 0;
	for (int i = 0; i < nMaxAccountNum; i++) {
		if (pAcctArray[i].GetAccID() == ID) {
			index = i;
		}
	}
	if (pAcctArray[index].check(ID, passwd) == -1) {
		cout << "is not your ID or doesn't exist" << endl;
		return;
	}
	else {
		cout << "�����ܾ� : " << pAcctArray[index].GetBalance() << endl;
	}
}
void ATMachine::depositMoney() {	// ���� �Ա�
	int id;
	string passwd;
	int money;
	cout << "------------�Ա�--------------" << endl;
	cout << "���� ��ȣ �Է� : ";
	cin >> id;	cout << endl;
	cout << "��й�ȣ �Է� : ";
	cin >> passwd; cout << endl;
	cout << "�Աݾ� �Է� : "; cin >> money;	cout << endl;
	int index = 0;
	for (int i = 0; i < nCurrentAccountNum; i++) {	//nMaxAccountNum ������
		if (pAcctArray[i].GetAccID() == id) {
			index = i;
			pAcctArray[index].deposit(id, passwd, money);
			cout << "���� �ܾ� : " << pAcctArray[index].check(id, passwd) << endl;
			return;
		}

	}
	cout << "This ID does not exist" << endl;
//	pAcctArray[index].deposit(id, passwd, money); // ID �н����� ���� ��
//	cout << "���� �ܾ� : " << pAcctArray[index].check(id, passwd) << endl;
}
void ATMachine::withdrawMoney() {
	int id;
	string passwd;
	int money;
	cout << "----------���----------" << endl;
	cout << "���¹�ȣ �Է� : "; cin >> id;	cout << endl;
	cout << "��й�ȣ �Է� : "; cin >> passwd; cout << endl;
	cout << "��ݾ� �Է� : "; cin >> money; cout << endl;
	int index = 0;
	for (int i = 0; i < nCurrentAccountNum; i++) {
		if (pAcctArray[i].GetAccID() == id) {
			index = i;
			pAcctArray[index].withdraw(id, passwd, money);
			cout << "���� �ܾ� : " << pAcctArray[index].check(id, passwd) << endl;
			return;
		}

	}
	cout << "This ID does not exist" << endl;
//	pAcctArray[index].withdraw(id, passwd, money);
//	cout << "���� �ܾ� : " << pAcctArray[index].check(id, passwd) << endl;
	
}
void ATMachine::managerMode() {
	string ad;
	cout << "-------------����-----------" << endl;
	cout << "������ ��й�ȣ �Է� : "; cin >> ad;
	if (isManager(ad) == true) {
		cout << "������ �Դϴ�." << endl;
		displayReport();
	}
	else {
		cout << "������ ��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
		return;
	}
}
bool ATMachine::isManager(string password) {
	if (password == strManagerPassword) {
		return true;
	}
	else {
		return false;
	}

}
void ATMachine::displayReport() {
	Statistics s;
	cout << "�� �� :" << nCurrentAccountNum << endl;
	int res1, res2, res3;
	res1 = s.sum(pAcctArray, nCurrentAccountNum);
	res2 = s.average(pAcctArray, nCurrentAccountNum);
	res3 = s.max(pAcctArray, nCurrentAccountNum);
	cout << "ATM ���� �ܰ� : " << nMachineBalance+res1 << endl;	// ATM
	cout << "�� �ܰ� ��ü �ݾ� : " << res1 << endl;	// �� + ATM
	cout << "�� �ܰ� ��� �ݾ� : " << res2 << endl;
	cout << "�� �ܰ� �ְ� �ݾ� : " << res3 << endl;

	cout << "-----------���� ��Ȳ------------" << endl;
	for (int i = 0; i < nCurrentAccountNum; i++) {
		cout << pAcctArray[i].getAccountName() << " " << pAcctArray[i].GetAccID() << ' ' << pAcctArray[i].GetBalance() << endl;
	}
	cout << "--------------------------------" << endl;
}

ATMachine::~ATMachine() {
	delete[]pAcctArray;
}