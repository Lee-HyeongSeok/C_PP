#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include <string>
using namespace std;

class Ticket;

class Screen {
protected : 
	int nTicketPrice;	// Ƽ�� ����
	int nRowMax, nColMax;	// �¼� ��� �� �ִ� ��
	int nCurrentReservedld;	// �߱޵� ������ ���� ��ȣ
	Ticket **pSeatArray;	// ��ũ�� �¼��� ���� Ƽ�� �迭
	string strMovieName;	// ��ũ�� ������ ��ȭ ����
	int Ticket_count;
public : 
	Screen(string name, int price, int r, int c);
	~Screen();
	void ShowSeatMap();
	virtual void ShowMovieMenu();
	virtual void ShowMovieInfo() = 0;
	void reserveTicket();
	void Payment();
	void managerMode();
	// ������� ���ʿ� �־�ߵɰ�~
	int getTicketPrice() {
		return nTicketPrice;
	}
};

class FamillyScreen : public Screen {
public : 
	FamillyScreen(string name, int price, int r, int c) : Screen(name, price, r, c) {

	}
	void ShowMovieInfo();
};
class AdultScreen : public Screen {
public : 
	AdultScreen(string name, int price, int r, int c) : Screen(name, price, r, c) {}
	void ShowMovieInfo();
};
class PremiumScreen : public Screen {
public : 
	PremiumScreen(string name, int price, int r, int c) : Screen(name, price, r, c) {

	}
	void ShowMovieInfo();
};

#endif

