#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include <string>
using namespace std;

class Ticket;

class Screen {
protected : 
	int nTicketPrice;	// 티켓 가격
	int nRowMax, nColMax;	// 좌석 행과 열 최대 값
	int nCurrentReservedld;	// 발급된 마지막 예약 번호
	Ticket **pSeatArray;	// 스크린 좌석에 대한 티켓 배열
	string strMovieName;	// 스크린 상영중인 영화 제목
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
	// 관리통계 이쪽에 넣어야될걸~
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

