#include <iostream>
#include "Screen.h"
#include "TicketBox.h"
#include "Statistics.h"
using namespace std;

class KpuTicketBox;

void KpuTicketBox::Initialize() {
	pFamillyScreen = new FamillyScreen("어벤져스", 8000, 10, 10);
	pAdultScreen = new AdultScreen("악인전", 10000, 10, 10);
	pPremiumScreen = new PremiumScreen("그린북", 30000, 5, 5);
}
Screen * KpuTicketBox::selectMenu() {
	int choice;
	Screen * SCR;
	cout << "----------------------" << endl;
	cout << "상영관 메인 메뉴" << endl;
	cout << "----------------------" << endl;
	cout << "1. 가족 영화 1관" << endl;
	cout << "2. 성인 영화 2관" << endl;
	cout << "3. 프리미엄 영화 3관" << endl;
	cout << "9. 관리 통계 기능 " << endl;
	cout << "선택(1 ~ 3) 관리자 : 9번, 그 외 종료 : ";
	cin >> choice;
	switch (choice) {
	case 1:
		return pFamillyScreen;	// 생성자 호출
	case 2:
		return pAdultScreen;	// 생성자 호출
	case 3:
		return pPremiumScreen;	// 생성자 호출
	case 9:
		cout << "1. 가족 영화관 통계 " << endl;
		SCR = pFamillyScreen;
		SCR->managerMode();
		cout << "=================================" << endl;
		cout << "2. 성인 영화관 통계" << endl;
		SCR = pAdultScreen;
		SCR->managerMode();
		cout << "=================================" << endl;
		cout << "3. 프리미엄 영화관 통계" << endl;
		SCR = pPremiumScreen;
		SCR->managerMode();
		cout << "=================================" << endl;
		return SCR;
	default :
		cout << "프로그램 종료" << endl;
		return 0;
	}

}
KpuTicketBox::KpuTicketBox() {
	Initialize();
}
KpuTicketBox::~KpuTicketBox() {
	delete pFamillyScreen;
	delete pAdultScreen;
	delete pPremiumScreen;
}