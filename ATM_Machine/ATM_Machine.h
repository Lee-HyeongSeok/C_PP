#pragma once
#include <iostream>
#include <string>
#include "Account.h"

using namespace std;

#ifndef ATMACHINE_H
#define ATMACHINE_H

#define NEGATIVE_ATM_BALANCE -10	// ATM �ܾ׺���

class ATMachine {
private : 
	Account * pAcctArray;	// ���� ������ ������ �迭������
	int nMachineBalance;   // ATM �ܰ�
	int nMaxAccountNum;		// ���������� ������ �迭ũ��
	int nCurrentAccountNum;	// ������ �� ���� ��
	string strManagerPassword; // ������ ��й�ȣ
	bool isManager(string password);
	void displayReport();
		
public : 
	ATMachine();
	~ATMachine();
	// ��� ����ȭ��
	void displayMenu();
	//���� �迭ũ��, ATM �ܰ�, ������ ��ȣ �ʱ�ȭ
	void initialisze(int nSize, int nBalance, string password);
	void createAccount();
	void checkMoney();
	void depositMoney();
	void withdrawMoney();
	void managerMode();

};

#endif