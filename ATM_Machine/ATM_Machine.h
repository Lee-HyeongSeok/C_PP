#pragma once
#include <iostream>
#include <string>
#include "Account.h"

using namespace std;

#ifndef ATMACHINE_H
#define ATMACHINE_H

#define NEGATIVE_ATM_BALANCE -10	// ATM 잔액부족

class ATMachine {
private : 
	Account * pAcctArray;	// 동적 생성된 고객계좌 배열포인터
	int nMachineBalance;   // ATM 잔고
	int nMaxAccountNum;		// 동적생성된 고객계좌 배열크기
	int nCurrentAccountNum;	// 개설된 고객 계좌 수
	string strManagerPassword; // 관리자 비밀번호
	bool isManager(string password);
	void displayReport();
		
public : 
	ATMachine();
	~ATMachine();
	// 기능 선택화면
	void displayMenu();
	//계좌 배열크기, ATM 잔고, 관리자 암호 초기화
	void initialisze(int nSize, int nBalance, string password);
	void createAccount();
	void checkMoney();
	void depositMoney();
	void withdrawMoney();
	void managerMode();

};

#endif