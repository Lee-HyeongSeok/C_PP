#pragma once
#ifndef PAY_H
#define PAY_H

#define MOBILE_PHONE_PAYMENT	1
#define BANK_TRANSFER_PAYMENT	2
#define CREDIT_CARD_PAYMENT		3
#define MOBILE_PHONE_INTEREST_RATE	0.2	// ����� ���� ������ ����
#define BANK_TRANSFER_INTEREST_RATE 0.1	// ���� ���� ������
#define CREDIT_CARD_INTEREST_RATE	0.15	// �ſ�ī�� ���� ������

class Pay {
public :
	virtual int charge(int amount) = 0;	
};


class CardPay : public Pay {
	double interest;
public : 
	CardPay(double rate) {
		this->interest = rate;
	}
	// �����ݾ� = Ƽ�� ���� + Ƽ�ϰ��� * ���������
	int charge(int amount);
};
class BankTransfer : public Pay {
	double interest;
public : 
	BankTransfer(double rate) {
		this->interest = rate;
	}
	int charge(int amount);
};
class MobilePay : public Pay {
	double interest;
public : 
	MobilePay(double rate) {
		this->interest = rate;
	}
	int charge(int amount);
};
#endif