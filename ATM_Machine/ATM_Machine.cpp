#include <iostream>
#include "ATMachine.h"
#include "Statistics.h"
using namespace std;


ATMachine::ATMachine() {

}
void ATMachine::displayMenu() {
	cout << "-------------------------------------" << endl;
	cout << "-" << "   " << "KPU bank" << "   " << "-" << endl;
	cout << " 1. 계좌 개설 " << endl;
	cout << " 2. 계좌 조회 " << endl;
	cout << " 3. 계좌 입금 " << endl;
	cout << " 4. 계좌 출금 " << endl;
	cout << " 5. 고객 관리 " << endl;
	cout << " 9. 업무 종료 " << endl;
	cout << "메뉴를 선택하세요 : ";
}
//계좌 배열크기, ATM 잔고, 관리자 암호 초기화
void ATMachine::initialisze(int nSize, int nBalance, string password) {
	pAcctArray = new Account[nSize];	// 고객 수 동적할당
	nMachineBalance = nBalance;
	strManagerPassword = password;
	nCurrentAccountNum = 0;
	nMaxAccountNum = nSize;
}
void ATMachine::createAccount() {
	string name;
	string passwd;
	cout << "-----------개설-----------" << endl;
	cout << "이름 입력 : ";
	cin >> name;
	cout << endl;
	cout << "암호 입력 : ";
	cin >> passwd;
	cout << endl;
	pAcctArray[nCurrentAccountNum].create(nCurrentAccountNum, 0, name, passwd);	// 개설된 계좌 수 카운트 안잡히면 요기 확인
	cout << name << " 님 " << pAcctArray[nCurrentAccountNum].GetAccID() << " 번 계좌번호가 정상적으로 개설되었습니다." << endl;
	nCurrentAccountNum++;	// 개설될 때 마다 카운트
}
void ATMachine::checkMoney() {
	int ID;
	string passwd;
	cout << "-----------조회-------------" << endl;
	cout << "계좌 번호 입력 : ";
	cin >> ID; cout << endl;
	cout << "비밀번호 입력 : ";
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
		cout << "현재잔액 : " << pAcctArray[index].GetBalance() << endl;
	}
}
void ATMachine::depositMoney() {	// 계좌 입금
	int id;
	string passwd;
	int money;
	cout << "------------입금--------------" << endl;
	cout << "계좌 번호 입력 : ";
	cin >> id;	cout << endl;
	cout << "비밀번호 입력 : ";
	cin >> passwd; cout << endl;
	cout << "입금액 입력 : "; cin >> money;	cout << endl;
	int index = 0;
	for (int i = 0; i < nCurrentAccountNum; i++) {	//nMaxAccountNum 원래거
		if (pAcctArray[i].GetAccID() == id) {
			index = i;
			pAcctArray[index].deposit(id, passwd, money);
			cout << "현재 잔액 : " << pAcctArray[index].check(id, passwd) << endl;
			return;
		}

	}
	cout << "This ID does not exist" << endl;
//	pAcctArray[index].deposit(id, passwd, money); // ID 패스워드 넣을 돈
//	cout << "현재 잔액 : " << pAcctArray[index].check(id, passwd) << endl;
}
void ATMachine::withdrawMoney() {
	int id;
	string passwd;
	int money;
	cout << "----------출금----------" << endl;
	cout << "계좌번호 입력 : "; cin >> id;	cout << endl;
	cout << "비밀번호 입력 : "; cin >> passwd; cout << endl;
	cout << "출금액 입력 : "; cin >> money; cout << endl;
	int index = 0;
	for (int i = 0; i < nCurrentAccountNum; i++) {
		if (pAcctArray[i].GetAccID() == id) {
			index = i;
			pAcctArray[index].withdraw(id, passwd, money);
			cout << "현재 잔액 : " << pAcctArray[index].check(id, passwd) << endl;
			return;
		}

	}
	cout << "This ID does not exist" << endl;
//	pAcctArray[index].withdraw(id, passwd, money);
//	cout << "현재 잔액 : " << pAcctArray[index].check(id, passwd) << endl;
	
}
void ATMachine::managerMode() {
	string ad;
	cout << "-------------관리-----------" << endl;
	cout << "관리자 비밀번호 입력 : "; cin >> ad;
	if (isManager(ad) == true) {
		cout << "관리자 입니다." << endl;
		displayReport();
	}
	else {
		cout << "관리자 비밀번호가 틀렸습니다." << endl;
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
	cout << "총 고객 :" << nCurrentAccountNum << endl;
	int res1, res2, res3;
	res1 = s.sum(pAcctArray, nCurrentAccountNum);
	res2 = s.average(pAcctArray, nCurrentAccountNum);
	res3 = s.max(pAcctArray, nCurrentAccountNum);
	cout << "ATM 현금 잔고 : " << nMachineBalance+res1 << endl;	// ATM
	cout << "고객 잔고 전체 금액 : " << res1 << endl;	// 고객 + ATM
	cout << "고객 잔고 평균 금액 : " << res2 << endl;
	cout << "고객 잔고 최고 금액 : " << res3 << endl;

	cout << "-----------계좌 현황------------" << endl;
	for (int i = 0; i < nCurrentAccountNum; i++) {
		cout << pAcctArray[i].getAccountName() << " " << pAcctArray[i].GetAccID() << ' ' << pAcctArray[i].GetBalance() << endl;
	}
	cout << "--------------------------------" << endl;
}

ATMachine::~ATMachine() {
	delete[]pAcctArray;
}