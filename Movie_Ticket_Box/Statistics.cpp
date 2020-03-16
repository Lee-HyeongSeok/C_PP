#include <iostream>
#include "Statistics.h"
using namespace std;

Statistcis::Statistcis() {

}

int Statistcis::sum(Ticket **pTicket, int nRow, int nCol) {
	int sum = 0;
	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			if(pTicket[i][j].getCheck() == '$')
				sum += pTicket[i][j].getPayAmount();
		}
	}
	return sum;
}
void Statistcis::ShowReservedStatus(Ticket **pTicket, int nRow, int nCol) {
	int SW;
	int cnt = 0;
	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			if (pTicket[i][j].getCheck() == 'R') {
				cnt++;
				cout << endl << "      <������>   " << endl;
				cout << " [���� ��ȣ ] : " << pTicket[i][j].GetID() << endl;		
			}
		}
	}
	
	cout << endl << " <<<< ���� �¼� >>>> : " << (nRow * nCol) - cnt << endl;

	cout << endl << "=======================================" << endl;
	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			if (pTicket[i][j].getCheck() == '$') {
				cout << "       <������>   " << endl;
				SW = pTicket[i][j].getPayMethod();
				switch (SW) {
				case 1:
					cout << "���� ��ȣ : " << pTicket[i][j].GetID() << endl;
					cout << "���� ���� : ����� ����" << endl;
					cout << "�ڵ��� ��ȣ : " << pTicket[i][j].getCard_num() << endl;
					cout << "������ ���� : "; 
					pTicket[i][j].ShowName();
					break;
				case 2:
					cout << "���� ��ȣ : " << pTicket[i][j].GetID() << endl;
					cout << "���� ���� : KPU ���� ����" << endl;
					cout << "ī�� ��ȣ : ";
					pTicket[i][j].ShowName();
					cout << "������ ���� : " << pTicket[i][j].getName() << endl;
					break;
				case 3:
					cout << "���� ��ȣ : " << pTicket[i][j].GetID() << endl;
					cout << "���� ���� : �ſ�ī�� ����" << endl;
					cout << "ī�� ��ȣ : ";
					pTicket[i][j].ShowName();
					cout << "������ ���� : " << pTicket[i][j].getName() << endl;
					break;
				default:
					cout << "�� �� ���� ���� ����.." << endl;
					return;
				}
			}
		}
	}
}

Statistcis::~Statistcis() {}


