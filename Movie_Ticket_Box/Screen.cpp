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
			pSeatArray[i][j].setCheck(SEAT_EMPTY_MARK);	// 시트 초기화
		}
	}
}

void Screen::managerMode() {
	string passwd;
	Statistcis S;
	int TotalAmount;
	cout << "--------------통계 관리--------------" << endl;
	cout << "관리자 비밀번호 입력 : "; cin >> passwd;
	if (passwd == TICKETBOX_MANAGER_PWD) {
		cout << "관리자 입니다." << endl;
		cout << "--------------------------------" << endl;
		cout << "[" << strMovieName << "]" << " 관" << endl;
		cout << "< 티켓 결제 금액 총액 > : ";
		TotalAmount = S.sum(pSeatArray, nRowMax, nColMax);
		cout << TotalAmount << endl;
		cout << "< 티켓 판매량 > : ";
		cout << nCurrentReservedld << endl;
		cout << " <결제 및 예약 현황> ";
		S.ShowReservedStatus(pSeatArray, nRowMax, nColMax);
	}
	else {
		cout << "관리자 비밀번호가 틀렸습니다. 재접속 요구" << endl;
		return;
	}
	return;
}
void Screen::reserveTicket() {
	int r, c;
	int choice;
	cout << "   [ 좌석 예약 ]   " << endl;
	cout << "좌석 열 번호 입력(1 ~ "<<nRowMax<<")"; cin >> r;
	cout << "좌석 행 번호 입력(1 ~ "<<nColMax<<")"; cin >> c;
	if (r > nRowMax && c > nColMax) {
		cout << nRowMax << "행" << nColMax << "열" << " 이내로 입력하십시오." << endl;
		return;
	}
	if (pSeatArray[r - 1][c - 1].getCheck() == 'R') {
		cout << "이 좌석은 이미 예약된 상태입니다." << endl;
		cout << "다시 입력은 1번, 이전 메뉴로 이동은 2번을 선택 " << endl;
		cout << "메뉴 선택 : ";
		cin >> choice;
		if (choice == 1) {
			cout << "   [ 좌석 예약 ]   " << endl;
			cout << "좌석 행 번호 입력(1 ~ 10) : "; cin >> r;
			cout << "좌석 행 번호 입력(1 ~ 10) : "; cin >> c;
		}
		else if (choice == 2) {
			return;
		}
	}
	pSeatArray[r-1][c-1].setSeat(r, c);
	pSeatArray[r-1][c-1].setCheck(SEAT_RESERVED_MARK);
	pSeatArray[r-1][c-1].setReservedID(100 + nCurrentReservedld++);	// 티켓번호 100으로 초기화
	
	cout << "행 [" << r << "]" << "  " << "열 [" << c << "]" << "  ";
	cout << pSeatArray[r - 1][c - 1].GetID() << "예약 번호로 접수되었습니다." << endl;
}
void Screen::ShowMovieMenu() {
	cout << "--------------------------" << endl;
	cout << "        " << "영화 메뉴 - " << strMovieName << endl;
	cout << "--------------------------" << endl;
	cout << "1. 영화 정보 " << endl;
	cout << "2. 예약 현황 " << endl;
	cout << "3. 예약 하기 " << endl;
	cout << "4. 티켓 결제 " << endl;
	cout << "5. 메인 메뉴 이동 " << endl;
}
void Screen::ShowSeatMap() {
	cout << "       " << "   [ 좌석 예약 현황 ]   " << "         " << endl;
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
	
	cout << " [ 좌석 예약 결제 ] " << endl;
	cout << "예약 번호 입력 : ";	cin >> number;

	cout << "----------------------------------" << endl;
	cout << "         [ 결제 방식 선택 ]       " << endl;
	cout << "----------------------------------" << endl;
	cout << "1. 모바일 결제 " << endl;
	cout << "2. 은행 이체 결제 " << endl;
	cout << "3. 카드 결제 " << endl << endl;
	cout << " 결제 방식(1-3) : ";
	cin >> choice;
	
	switch (choice) {
		// 모바일
	case MOBILE_PHONE_PAYMENT :
		
		cout << " [ 모바일 결제 ]" << endl;
		for (int i = 0; i < nRowMax; i++) {
			for (int j = 0; j < nColMax; j++) {
				if (pSeatArray[i][j].GetID() == number) {
					pSeatArray[i][j].setPayMethod(MOBILE_PHONE_PAYMENT);
					pSeatArray[i][j].setPayAmount(M.charge(nTicketPrice + (nTicketPrice *MOBILE_PHONE_INTEREST_RATE)));
					cout << "핸드폰 번호 입력 : ";
					pSeatArray[i][j].setCard_num(); cout << endl;
					cout << "이름 : "; 
					pSeatArray[i][j].setName(); cout << endl;
					cout << "모바일 결제가 완료되었습니다. : ";
					cout << pSeatArray[i][j].getPayAmount(); cout << endl;
					pSeatArray[i][j].setCheck(SEAT_COMPLETION_MARK);
				}
			}
		}
		break;
		// 은행 이체
	case BANK_TRANSFER_PAYMENT : 
		cout << " [ KPU 은행 결제 ]" << endl;
		for (int i = 0; i < nRowMax; i++) {
			for (int j = 0; j < nColMax; j++) {
				if (pSeatArray[i][j].GetID() == number) {
					pSeatArray[i][j].setPayMethod(BANK_TRANSFER_PAYMENT);
					pSeatArray[i][j].setPayAmount(B.charge(nTicketPrice + (nTicketPrice *BANK_TRANSFER_INTEREST_RATE)));
					cout << " 은행 번호 입력( 12자리수 ) : ";
					pSeatArray[i][j].setCard_num(); cout << endl;
					cout << "이름 : ";
					pSeatArray[i][j].setName(); cout << endl;
					cout << " KPU 은행 결제가 완료되었습니다. ";
					cout << pSeatArray[i][j].getPayAmount(); cout << endl;
					pSeatArray[i][j].setCheck(SEAT_COMPLETION_MARK);
				}
			}
		}
		break;
		// 신용카드
	case CREDIT_CARD_PAYMENT : 
		cout << " [ 신용카드 결제 ]" << endl;
		for (int i = 0; i < nRowMax; i++) {
			for (int j = 0; j < nColMax; j++) {
				if (pSeatArray[i][j].GetID() == number) {
					pSeatArray[i][j].setPayMethod(CREDIT_CARD_PAYMENT);
					pSeatArray[i][j].setPayAmount(C.charge(nTicketPrice + (nTicketPrice *CREDIT_CARD_INTEREST_RATE)));
					cout << "카드 번호 입력(12자리수) : ";
					pSeatArray[i][j].setCard_num(); cout << endl;
					cout << "이름 : ";
					pSeatArray[i][j].setName(); cout << endl;
					cout << "신용카드 결제가 완료되었습니다. : ";
					cout << pSeatArray[i][j].getPayAmount(); cout << endl;
					pSeatArray[i][j].setCheck(SEAT_COMPLETION_MARK);
				}
			}
		}
		break;
	default : 
		cout << "결제 범위에서 벗어난 값을 입력했습니다. \n";
		return;
	}
}
void FamillyScreen::ShowMovieInfo() {
	cout << "------------------------------" << endl;
	cout << "		  [ 어벤져스 ]   	" << endl;
	cout << "------------------------------" << endl;
	cout << "영화관 : 가족 영화 1관 " << endl;
	cout << "주인공 : 로버트 다우니 주니어 " << endl;
	cout << "줄거리 : 인피니티 워 이후 절반만 살아남은 지구..." << endl;
	cout << "가격 : " << FamillyScreen::nTicketPrice << endl << endl;
}
void AdultScreen::ShowMovieInfo() {
	cout << "------------------------------" << endl;
	cout << "          [ 악인전 ]         " << endl;
	cout << "------------------------------" << endl;
	cout << "영화관 : 성인 영화 2관 " << endl;
	cout << "주인공 : 마동석, 김무열 " << endl;
	cout << "줄거리 : 연쇄살인마의 표적이 되었다 살아난 조직 보스..." << endl;
	cout << "가격 : " << AdultScreen::nTicketPrice << endl << endl;
	
}
void PremiumScreen::ShowMovieInfo() {
	cout << "------------------------------" << endl;
	cout << "          [ 그린북 ]         " << endl;
	cout << "------------------------------" << endl;
	cout << "영화관 : 프리미엄 영화 3관 " << endl;
	cout << "주인공 : 비고 모텐슨, 마샬셜라 알리 " << endl;
	cout << "줄거리 : 취향, 성격도 다른 두 남자의 특별한 우정이 시작..." << endl;
	cout << "가격 : " << PremiumScreen::nTicketPrice << endl << endl;
}
Screen::~Screen() {
	for (int i = 0; i < nColMax; i++) {
		delete[] * (pSeatArray + i);
	}
	delete[] pSeatArray;
}