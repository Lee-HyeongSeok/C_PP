#include <iostream>
#include "Screen.h"
#include "TicketBox.h"
#include "Statistics.h"
using namespace std;

class KpuTicketBox;

void KpuTicketBox::Initialize() {
	pFamillyScreen = new FamillyScreen("�����", 8000, 10, 10);
	pAdultScreen = new AdultScreen("������", 10000, 10, 10);
	pPremiumScreen = new PremiumScreen("�׸���", 30000, 5, 5);
}
Screen * KpuTicketBox::selectMenu() {
	int choice;
	Screen * SCR;
	cout << "----------------------" << endl;
	cout << "�󿵰� ���� �޴�" << endl;
	cout << "----------------------" << endl;
	cout << "1. ���� ��ȭ 1��" << endl;
	cout << "2. ���� ��ȭ 2��" << endl;
	cout << "3. �����̾� ��ȭ 3��" << endl;
	cout << "9. ���� ��� ��� " << endl;
	cout << "����(1 ~ 3) ������ : 9��, �� �� ���� : ";
	cin >> choice;
	switch (choice) {
	case 1:
		return pFamillyScreen;	// ������ ȣ��
	case 2:
		return pAdultScreen;	// ������ ȣ��
	case 3:
		return pPremiumScreen;	// ������ ȣ��
	case 9:
		cout << "1. ���� ��ȭ�� ��� " << endl;
		SCR = pFamillyScreen;
		SCR->managerMode();
		cout << "=================================" << endl;
		cout << "2. ���� ��ȭ�� ���" << endl;
		SCR = pAdultScreen;
		SCR->managerMode();
		cout << "=================================" << endl;
		cout << "3. �����̾� ��ȭ�� ���" << endl;
		SCR = pPremiumScreen;
		SCR->managerMode();
		cout << "=================================" << endl;
		return SCR;
	default :
		cout << "���α׷� ����" << endl;
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