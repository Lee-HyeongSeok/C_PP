#pragma once
#ifndef TICKETBOX_H
#define TICKETBOX_H

#include "Statistics.h"
#include "Screen.h"
using namespace std;

class KpuTicketBox;
class FamillyScreen;
class AdultScreen;
class PremiumScreen;
class Screen;

#define TICKETBOX_MANAGER_PWD "admin"

class TicketBox {
public : 
	// 상영관 메뉴 1관 2관 3관
	virtual Screen * selectMenu() {
		return NULL;
	}
	void Initialize(){}	// 함수 오버로딩
};
class KpuTicketBox : public TicketBox {
	FamillyScreen * pFamillyScreen;
	AdultScreen * pAdultScreen;
	PremiumScreen * pPremiumScreen;
public : 
	KpuTicketBox();
	~KpuTicketBox();
	Screen * selectMenu();
	void Initialize();
};

// 스크린 객체 생성

#endif
