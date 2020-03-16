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
	// �󿵰� �޴� 1�� 2�� 3��
	virtual Screen * selectMenu() {
		return NULL;
	}
	void Initialize(){}	// �Լ� �����ε�
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

// ��ũ�� ��ü ����

#endif
