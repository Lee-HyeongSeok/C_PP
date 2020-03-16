#include <iostream>
#include "Account.h"
using namespace std;

Account::Account() {

}
void Account::create(int id, int money, string name, string password) {
	nID = id + BASE_ACCOUNT_ID;
	nBalance = money;
	int len = name.size();
	strAccountName = name;
	strPassword = password;
}
// 현재 잔고 확인, 인증실패시 -1 반환
int Account::check(int id, string password) {
	if (nID != id) {
		return AUTHENTIFICATION_FAIL;
	}
	else {
		if (strPassword == password)
			return nBalance;
		else {
			cout << "password error..." << endl;
			nBalance = 0;
			return nBalance;
			//return -1;
		}
			
		
	}
}
int Account::GetBalance() const {
	return nBalance;
}
int Account::GetAccID() const {
	return nID;
}
int Account::deposit(int id, string password, int money) {
	if (authenticate(id, password) == true) {	// id와 패스워드가 맞을 때
		nBalance += money;
	}
	else {
		return 0;
	}
	return nBalance;
}
int Account::withdraw(int id, string password, int money) {
	if (authenticate(id, password) == true) {
		if (nBalance < money) {
			cout << "lack of your balance.." << endl;
			return nBalance;
		}
			// if (nBalance >= money) 
		nBalance -= money;
		
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
	return nBalance;
}
string Account::getAccountName() {
	return strAccountName;
}