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
				cout << endl << "      <예약자>   " << endl;
				cout << " [예약 번호 ] : " << pTicket[i][j].GetID() << endl;		
			}
		}
	}
	
	cout << endl << " <<<< 남은 좌석 >>>> : " << (nRow * nCol) - cnt << endl;

	cout << endl << "=======================================" << endl;
	for (int i = 0; i < nRow; i++) {
		for (int j = 0; j < nCol; j++) {
			if (pTicket[i][j].getCheck() == '$') {
				cout << "       <결제자>   " << endl;
				SW = pTicket[i][j].getPayMethod();
				switch (SW) {
				case 1:
					cout << "예약 번호 : " << pTicket[i][j].GetID() << endl;
					cout << "결제 수단 : 모바일 결제" << endl;
					cout << "핸드폰 번호 : " << pTicket[i][j].getCard_num() << endl;
					cout << "결제자 성함 : "; 
					pTicket[i][j].ShowName();
					break;
				case 2:
					cout << "예약 번호 : " << pTicket[i][j].GetID() << endl;
					cout << "결제 수단 : KPU 은행 결제" << endl;
					cout << "카드 번호 : ";
					pTicket[i][j].ShowName();
					cout << "결제자 성함 : " << pTicket[i][j].getName() << endl;
					break;
				case 3:
					cout << "예약 번호 : " << pTicket[i][j].GetID() << endl;
					cout << "결제 수단 : 신용카드 결제" << endl;
					cout << "카드 번호 : ";
					pTicket[i][j].ShowName();
					cout << "결제자 성함 : " << pTicket[i][j].getName() << endl;
					break;
				default:
					cout << "알 수 없는 값이 들어옴.." << endl;
					return;
				}
			}
		}
	}
}

Statistcis::~Statistcis() {}


