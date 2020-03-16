#pragma once
#ifndef TICKET_H
#define TICKET_H
#include <string>
#include "Screen.h"
#include "TicketBox.h"

#define SEAT_EMPTY_MARK	'-'
#define SEAT_RESERVED_MARK	'R'
#define SEAT_COMPLETION_MARK	'$'

class Ticket {
	int nRow;	// �¼� ��
	int nCol;	// �¼� ��
	char charCheck;	// ���� ����
	int nReservedID;	// ���� ��ȣ
	int nPayAmount;		// ���� �ݾ�
	int nPayMethod;		// ���� ����
	string name;
	string Card_num;
public : 
	Ticket() {

	}
	Ticket(Ticket &copy) {
		nRow = copy.nRow;
		nCol = copy.nCol;
		charCheck = copy.charCheck;
		nReservedID = copy.nReservedID;
		nPayAmount = copy.nPayAmount;
		nPayMethod = copy.nPayMethod;
		name = copy.name;
		Card_num = copy.Card_num;
	}
	void setSeat(int r, int c) {
		nRow = r;
		nCol = c;
	}
	int GetID() {
		return nReservedID;
	}
	void setReservedID(int reserved) {
		nReservedID = reserved;
	}
	void setCheck(char check) {
		charCheck = check;
	}
	char getCheck() {
		return charCheck;
	}
	int getReservedID() {
		return nReservedID;
	}
	void setPayAmount(int amount) {	// Ƽ�ϰ���+Ƽ�ϰ���*������
		nPayAmount = amount;
	}
	int getPayAmount() {
		return nPayAmount;
	}
	void setPayMethod(int method) {
		nPayMethod = method;
	}
	int getPayMethod() const {
		return nPayMethod;
	}
	void setName() {
		string N;
		cin >> N;
		name = N;
	}
	string getName() {
		return name;
	}
	void ShowName() {
		cout << name << endl;
	}
	void setCard_num() {
		string str;
		cin >> str;
		Card_num = str;
	}
	string getCard_num() {
		return Card_num;
	}
	~Ticket() {
		
	}
};

#endif
