#include <iostream>
#include "Screen.h"
#include "TicketBox.h"
#include "Ticket.h"
#include "Pay.h"
#include "Statistics.h"
#include <string>
using namespace std;

#define SEAT_NUMBER 100

Screen::Screen(string name, int price, int r, int c) {
	strMovieName = name;
	nRowMax = r;
	nColMax = c;
	nTicketPrice = price;
	nCurrentReservedld = 0;
	pSeatArray = new Ticket*[nColMax];
	for (int r = 0; r < nRowMax; r++) {
		pSeatArray[r] = new Ticket[nColMax];
	}
	for (int i = 0; i < nRowMax; i++) {
		for (int j = 0; j < nColMax; j++) {
			pSeatArray[i][j].setCheck(SEAT_EMPTY_MARK);	// ��Ʈ �ʱ�ȭ
		}
	}
}

void Screen::managerMode() {
	string passwd;
	Statistcis S;
	int TotalAmount;
	cout << "--------------��� ����--------------" << endl;
	cout << "������ ��й�ȣ �Է� : "; cin >> passwd;
	if (passwd == TICKETBOX_MANAGER_PWD) {
		cout << "������ �Դϴ�." << endl;
		cout << "--------------------------------" << endl;
		cout << "[" << strMovieName << "]" << " ��" << endl;
		cout << "< Ƽ�� ���� �ݾ� �Ѿ� > : ";
		TotalAmount = S.sum(pSeatArray, nRowMax, nColMax);
		cout << TotalAmount << endl;
		cout << "< Ƽ�� �Ǹŷ� > : ";
		cout << nCurrentReservedld << endl;
		cout << " <���� �� ���� ��Ȳ> ";
		S.ShowReservedStatus(pSeatArray, nRowMax, nColMax);
	}
	else {
		cout << "������ ��й�ȣ�� Ʋ�Ƚ��ϴ�. ������ �䱸" << endl;
		return;
	}
	return;
}
void Screen::reserveTicket() {
	int r, c;
	int choice;
	cout << "   [ �¼� ���� ]   " << endl;
	cout << "�¼� �� ��ȣ �Է�(1 ~ "<<nRowMax<<")"; cin >> r;
	cout << "�¼� �� ��ȣ �Է�(1 ~ "<<nColMax<<")"; cin >> c;
	if (r > nRowMax && c > nColMax) {
		cout << nRowMax << "��" << nColMax << "��" << " �̳��� �Է��Ͻʽÿ�." << endl;
		return;
	}
	if (pSeatArray[r - 1][c - 1].getCheck() == 'R') {
		cout << "�� �¼��� �̹� ����� �����Դϴ�." << endl;
		cout << "�ٽ� �Է��� 1��, ���� �޴��� �̵��� 2���� ���� " << endl;
		cout << "�޴� ���� : ";
		cin >> choice;
		if (choice == 1) {
			cout << "   [ �¼� ���� ]   " << endl;
			cout << "�¼� �� ��ȣ �Է�(1 ~ 10) : "; cin >> r;
			cout << "�¼� �� ��ȣ �Է�(1 ~ 10) : "; cin >> c;
		}
		else if (choice == 2) {
			return;
		}
	}
	pSeatArray[r-1][c-1].setSeat(r, c);
	pSeatArray[r-1][c-1].setCheck(SEAT_RESERVED_MARK);
	pSeatArray[r-1][c-1].setReservedID(100 + nCurrentReservedld++);	// Ƽ�Ϲ�ȣ 100���� �ʱ�ȭ
	
	cout << "�� [" << r << "]" << "  " << "�� [" << c << "]" << "  ";
	cout << pSeatArray[r - 1][c - 1].GetID() << "���� ��ȣ�� �����Ǿ����ϴ�." << endl;
}
void Screen::ShowMovieMenu() {
	cout << "--------------------------" << endl;
	cout << "        " << "��ȭ �޴� - " << strMovieName << endl;
	cout << "--------------------------" << endl;
	cout << "1. ��ȭ ���� " << endl;
	cout << "2. ���� ��Ȳ " << endl;
	cout << "3. ���� �ϱ� " << endl;
	cout << "4. Ƽ�� ���� " << endl;
	cout << "5. ���� �޴� �̵� " << endl;
}
void Screen::ShowSeatMap() {
	cout << "       " << "   [ �¼� ���� ��Ȳ ]   " << "         " << endl;
	cout << "         ";
	if (nRowMax == 5) {
		for (int i = 0; i < nRowMax; i++) {
			cout << " [" << i + 1 << "]" << "   ";
		}
		cout << endl;

		for (int i = 0; i < nRowMax; i++) {
			cout << "[" << i + 1 << "]" << "      ";
			for (int j = 0; j < nColMax; j++) {
				if (i == nRowMax - 1)
					cout << " [" << pSeatArray[i][j].getCheck() << "]" << "   ";
				else {
					cout << " [" << pSeatArray[i][j].getCheck() << "]" << "   ";
				}
			}
			cout << endl;
		}
	}
	else if (nRowMax == 10) {
		for (int i = 0; i < nRowMax; i++) {
			cout << " [" << i + 1 << "]" << "   ";
		}
		cout << endl;

		for (int i = 0; i < nRowMax; i++) {
			cout << "[" << i + 1 << "]" << "      ";
			for (int j = 0; j < nColMax; j++) {
				if (i == nRowMax - 1)
					cout << "[" << pSeatArray[i][j].getCheck() << "]" << "    ";
				else {
					cout << " [" << pSeatArray[i][j].getCheck() << "]" << "   ";
				}
			}
			cout << endl;
		}
	}
}

void Screen::Payment() {
	int choice;
	int number;
	CardPay C(CREDIT_CARD_INTEREST_RATE);
	MobilePay M(MOBILE_PHONE_INTEREST_RATE);
	BankTransfer B(BANK_TRANSFER_INTEREST_RATE);
	
	cout << " [ �¼� ���� ���� ] " << endl;
	cout << "���� ��ȣ �Է� : ";	cin >> number;

	cout << "----------------------------------" << endl;
	cout << "         [ ���� ��� ���� ]       " << endl;
	cout << "----------------------------------" << endl;
	cout << "1. ����� ���� " << endl;
	cout << "2. ���� ��ü ���� " << endl;
	cout << "3. ī�� ���� " << endl << endl;
	cout << " ���� ���(1-3) : ";
	cin >> choice;
	
	switch (choice) {
		// �����
	case MOBILE_PHONE_PAYMENT :
		
		cout << " [ ����� ���� ]" << endl;
		for (int i = 0; i < nRowMax; i++) {
			for (int j = 0; j < nColMax; j++) {
				if (pSeatArray[i][j].GetID() == number) {
					pSeatArray[i][j].setPayMethod(MOBILE_PHONE_PAYMENT);
					pSeatArray[i][j].setPayAmount(M.charge(nTicketPrice + (nTicketPrice *MOBILE_PHONE_INTEREST_RATE)));
					cout << "�ڵ��� ��ȣ �Է� : ";
					pSeatArray[i][j].setCard_num(); cout << endl;
					cout << "�̸� : "; 
					pSeatArray[i][j].setName(); cout << endl;
					cout << "����� ������ �Ϸ�Ǿ����ϴ�. : ";
					cout << pSeatArray[i][j].getPayAmount(); cout << endl;
					pSeatArray[i][j].setCheck(SEAT_COMPLETION_MARK);
				}
			}
		}
		break;
		// ���� ��ü
	case BANK_TRANSFER_PAYMENT : 
		cout << " [ KPU ���� ���� ]" << endl;
		for (int i = 0; i < nRowMax; i++) {
			for (int j = 0; j < nColMax; j++) {
				if (pSeatArray[i][j].GetID() == number) {
					pSeatArray[i][j].setPayMethod(BANK_TRANSFER_PAYMENT);
					pSeatArray[i][j].setPayAmount(B.charge(nTicketPrice + (nTicketPrice *BANK_TRANSFER_INTEREST_RATE)));
					cout << " ���� ��ȣ �Է�( 12�ڸ��� ) : ";
					pSeatArray[i][j].setCard_num(); cout << endl;
					cout << "�̸� : ";
					pSeatArray[i][j].setName(); cout << endl;
					cout << " KPU ���� ������ �Ϸ�Ǿ����ϴ�. ";
					cout << pSeatArray[i][j].getPayAmount(); cout << endl;
					pSeatArray[i][j].setCheck(SEAT_COMPLETION_MARK);
				}
			}
		}
		break;
		// �ſ�ī��
	case CREDIT_CARD_PAYMENT : 
		cout << " [ �ſ�ī�� ���� ]" << endl;
		for (int i = 0; i < nRowMax; i++) {
			for (int j = 0; j < nColMax; j++) {
				if (pSeatArray[i][j].GetID() == number) {
					pSeatArray[i][j].setPayMethod(CREDIT_CARD_PAYMENT);
					pSeatArray[i][j].setPayAmount(C.charge(nTicketPrice + (nTicketPrice *CREDIT_CARD_INTEREST_RATE)));
					cout << "ī�� ��ȣ �Է�(12�ڸ���) : ";
					pSeatArray[i][j].setCard_num(); cout << endl;
					cout << "�̸� : ";
					pSeatArray[i][j].setName(); cout << endl;
					cout << "�ſ�ī�� ������ �Ϸ�Ǿ����ϴ�. : ";
					cout << pSeatArray[i][j].getPayAmount(); cout << endl;
					pSeatArray[i][j].setCheck(SEAT_COMPLETION_MARK);
				}
			}
		}
		break;
	default : 
		cout << "���� �������� ��� ���� �Է��߽��ϴ�. \n";
		return;
	}
}
void FamillyScreen::ShowMovieInfo() {
	cout << "------------------------------" << endl;
	cout << "		  [ ����� ]   	" << endl;
	cout << "------------------------------" << endl;
	cout << "��ȭ�� : ���� ��ȭ 1�� " << endl;
	cout << "���ΰ� : �ι�Ʈ �ٿ�� �ִϾ� " << endl;
	cout << "�ٰŸ� : ���Ǵ�Ƽ �� ���� ���ݸ� ��Ƴ��� ����..." << endl;
	cout << "���� : " << FamillyScreen::nTicketPrice << endl << endl;
}
void AdultScreen::ShowMovieInfo() {
	cout << "------------------------------" << endl;
	cout << "          [ ������ ]         " << endl;
	cout << "------------------------------" << endl;
	cout << "��ȭ�� : ���� ��ȭ 2�� " << endl;
	cout << "���ΰ� : ������, �蹫�� " << endl;
	cout << "�ٰŸ� : ������θ��� ǥ���� �Ǿ��� ��Ƴ� ���� ����..." << endl;
	cout << "���� : " << AdultScreen::nTicketPrice << endl << endl;
	
}
void PremiumScreen::ShowMovieInfo() {
	cout << "------------------------------" << endl;
	cout << "          [ �׸��� ]         " << endl;
	cout << "------------------------------" << endl;
	cout << "��ȭ�� : �����̾� ��ȭ 3�� " << endl;
	cout << "���ΰ� : ��� ���ٽ�, �����ȶ� �˸� " << endl;
	cout << "�ٰŸ� : ����, ���ݵ� �ٸ� �� ������ Ư���� ������ ����..." << endl;
	cout << "���� : " << PremiumScreen::nTicketPrice << endl << endl;
}
Screen::~Screen() {
	for (int i = 0; i < nColMax; i++) {
		delete[] * (pSeatArray + i);
	}
	delete[] pSeatArray;
}