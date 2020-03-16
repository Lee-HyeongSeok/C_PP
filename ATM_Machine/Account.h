#pragma once
#include <iostream>
#include <string>

using namespace std;

#ifndef ACCOUNT_H
#define ACCOUNT_H

#define AUTHENTIFICATION_FAIL -1
#define AUTHENTIFICATION_SUCCESS 1
#define BASE_ACCOUNT_ID 100

class Account {
private : 
	int nID;	//계좌 번호
	int nBalance;	//잔고
	string strAccountName;	//고객 명
	string strPassword;	// 계좌 비밀번호

private :
	inline bool authenticate(int id, string passwd) {
		if (nID != id) {
			cout << "is not your ID..." << endl;
			return false;
		}
		else if(nID == id){
			if (strPassword == passwd) {
				cout << "Authentication successful" << endl;
				return AUTHENTIFICATION_SUCCESS;
			}
			else {
				cout << "is not your password.." << endl;
				return false;
			}
		}
	}
public : 
	Account();
	// 계좌 개설 멤버함수
	void create(int id, int money, string name, string password);
	// 현재 잔고 확인, 인증실패시 -1 반환
	int check(int id, string password);
	int GetBalance() const;
	int GetAccID() const;
	int deposit(int id, string password, int money);
	int withdraw(int id, string password, int money);
	string getAccountName();
};

#endif