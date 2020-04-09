## * 영화 티켓박스 프로그램 구현   

#### * 기능
		* Main, TicketBox, Screen(.cpp, .h)
			* 영화 정보 보기
			* 좌석 예약 현황 보기 
			* 좌석 예약 기능   

		* Pay(.cpp, .h)
			* 티켓 결제 기능 
		
		* Statistic(.cpp, .h)
			* 관리 통계 기능   

#### * main.cpp 동작 원리   
		* KpuTicketBox 객체 생성을 통해 각 상영관별 가족, 성인, 프리미엄 객체를 생성한다.
		* TicketBox의 멤버변수인 Initialize() 메서드를 통해 Screen객체로 반환하여 업캐스팅
		* switch문에서 select에서 반환된 상영관 객체를 업캐스팅 한 screen 객체의 멤버함수를 호출함으로써 각 상영관별 멤버함수가 생성

```c
#include <iostream>
#include "Screen.h"
#include "TicketBox.h"

using namespace std;

int main() {
	KpuTicketBox tBox;		// KpuTicketBox 객체 선언 
	Screen *screen = NULL;	// Screen 포인터 객체 선언
	bool bScreenMenu = true;	// 메인 메뉴로 돌아가는 키를 눌렀을 때 true
	int select = 0;

	tBox.Initialize();
	while (1) {
		if (bScreenMenu) {
			screen = tBox.selectMenu();	// tBox를 업캐스팅
			bScreenMenu = false;	// 
			if (!screen)return 0;
		}
		screen->ShowMovieMenu();	// 메뉴 출력
		cout << "메뉴를 선택하세요 : ";
		cin >> select; cout << endl;
		if (select >= 1 && select <= 9) {
			switch (select) {
			case 1:
				// 영화 정보를 출력하는 메서드를 호출
				screen->ShowMovieInfo();
				break;
			case 2:	
				// 좌석 현황을 출력하는 메서드를 호출
				screen->ShowSeatMap();
				break;
			case 3:
				// 좌석 예약 메서드를 호출
				screen->reserveTicket();
				break;
			case 4:
				// 결제 방식을 선택하는 메서드 호출
				screen->Payment();
				break;
			case 5:
				// 메인 메뉴로 돌아가는 기능
				bScreenMenu = true;
				break;
			}
		}
		else {
			cout << "잘못된 값 입력 .." << endl;
		}
		
	}
	return 0;
}
```   

#### * TicketBox 동작 원리
		* main에서 tBox.Initialize()를 통해 아래 모든 구조가 이루어진다.
		* 가족, 성인, 프리미엄 영화별 통계 자료 추출
		* 업 캐스팅을 위한 각 영화별 생성자 호출 기능을 가진다.
```c
// TicketBox.cpp //

void KpuTicketBox::Initialize() { // 생성자 호출 및 동적할당 
	pFamillyScreen = new FamillyScreen("어벤져스", 8000, 10, 10);
	pAdultScreen = new AdultScreen("악인전", 10000, 10, 10);
	pPremiumScreen = new PremiumScreen("그린북", 30000, 5, 5);
}
```   
```c
// Screen.h //

class FamillyScreen : public Screen {
public : 
	FamillyScreen(string name, int price, int r, int c) : Screen(name, price, r, c) {}
	void ShowMovieInfo();
};
class AdultScreen : public Screen {
public : 
	AdultScreen(string name, int price, int r, int c) : Screen(name, price, r, c) {}
	void ShowMovieInfo();
};
class PremiumScreen : public Screen {
public : 
	PremiumScreen(string name, int price, int r, int c) : Screen(name, price, r, c) {}
	void ShowMovieInfo();
};
```   
```c 
// TicketBox.h //

class TicketBox {
public : 
	// 상영관 메뉴 1관 2관 3관
	virtual Screen * selectMenu() {
		return NULL;
	}
	void Initialize(){}	// 함수 오버로딩
};
```   
```c
// TicketBox를 상속받고 있다.
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

```   
		* main에서 screen = tBox.selectMenu()를 통해 아래 모든 구조가 이루어진다.   
		* 이 때 업 캐스팅이 이루어진다.
		* selectMenu() 메서드에서는 선택한 케이스 마다 Screen class를 상속받는 자식 클래스들의 생성자 호출로 인해 main에서 업 캐스팅이 일어난다.


```c
// main.cpp[14~15번 째 줄] //
while (1) {
		if (bScreenMenu) {
			screen = tBox.selectMenu();	// 이 부분 
			bScreenMenu = false;
			if (!screen)return 0;
		}
```   

```c
// TicketBox.cpp //
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
	case 1:	// pFamilyScreen 클래스는 Screen 클래스를 상속받는다.
		return pFamillyScreen;	// 생성자 호출(업캐스팅)
	case 2:	// pAdultScreen 클래스는 Screen 클래스를 상속받는다.
		return pAdultScreen;	// 생성자 호출(업캐스팅)
	case 3:	// pPremiumScreen 클래스는 Screen 클래스를 상속받는다.
		return pPremiumScreen;	// 생성자 호출(업캐스팅)
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

```   
```c
// main.cpp //
// 위에서 screen = tBox.selectMenu()를 통해 업캐스팅되었다.

screen->ShowMovieMenu();	// 메뉴 출력
		cout << "메뉴를 선택하세요 : ";
		cin >> select; cout << endl;
		if (select >= 1 && select <= 9) {
			switch (select) {
			case 1:
				// 가족, 프리미엄, 성인 영화 정보는 다 다르다.
				// 업 캐스팅으로 인해 하나의 코드로 여러 동작을 구현하는 것이 가능해졌다.
				// 밑에서 코드로 자세한 설명을 하겠다.
				screen->ShowMovieInfo();
				break;
			case 2:
				screen->ShowSeatMap();
				break;
			case 3:
				screen->reserveTicket();
				break;
			case 4:
				screen->Payment();
				break;
			case 5:
				bScreenMenu = true;
				break;
			}
		}
```

```c
// Screen.cpp // 업캐스팅
// 함수 오버로딩을 통해 위에서 업캐스팅된 screen 객체에 대한 출력 정보가 다르다.
// 업 캐스팅 : 하나의 코드로 여러 동작을 구현하는 것을 말한다.   


// 위에 코드 screen->ShowMovieInfo(); 에서 screen객체에 FamilyScreen이 업캐스팅 되어있을 때 
void FamillyScreen::ShowMovieInfo() {
	cout << "------------------------------" << endl;
	cout << "		  [ 어벤져스 ]   	" << endl;
	cout << "------------------------------" << endl;
	cout << "영화관 : 가족 영화 1관 " << endl;
	cout << "주인공 : 로버트 다우니 주니어 " << endl;
	cout << "줄거리 : 인피니티 워 이후 절반만 살아남은 지구..." << endl;
	cout << "가격 : " << FamillyScreen::nTicketPrice << endl << endl;
}

// 위에 코드 screen->ShowMovieInfo(); 에서 screen객체에 AdultScreen이 업캐스팅 되어있을 때 
void AdultScreen::ShowMovieInfo() {
	cout << "------------------------------" << endl;
	cout << "          [ 악인전 ]         " << endl;
	cout << "------------------------------" << endl;
	cout << "영화관 : 성인 영화 2관 " << endl;
	cout << "주인공 : 마동석, 김무열 " << endl;
	cout << "줄거리 : 연쇄살인마의 표적이 되었다 살아난 조직 보스..." << endl;
	cout << "가격 : " << AdultScreen::nTicketPrice << endl << endl;
	
}

// 위에 코드 screen->ShowMovieInfo(); 에서 screen객체에 PremiumScreen이 업캐스팅 되어있을 때 
void PremiumScreen::ShowMovieInfo() {
	cout << "------------------------------" << endl;
	cout << "          [ 그린북 ]         " << endl;
	cout << "------------------------------" << endl;
	cout << "영화관 : 프리미엄 영화 3관 " << endl;
	cout << "주인공 : 비고 모텐슨, 마샬셜라 알리 " << endl;
	cout << "줄거리 : 취향, 성격도 다른 두 남자의 특별한 우정이 시작..." << endl;
	cout << "가격 : " << PremiumScreen::nTicketPrice << endl << endl;
}
```   

#### * 통계 및 관리
		* TicketBox.cpp의 case 9번에 진입
		* 가족, 성인, 프리미엄 영화관 통계 마다 Screen 객체인 SCR 객체에 각 영화별 생성자를 호출하여 업 캐스팅을 이룬다.
		* 남은 좌석 현황 출력   

```c
// TicketBox.cpp //
		cout << "1. 가족 영화관 통계 " << endl;
		SCR = pFamillyScreen;	// 업 캐스팅
		SCR->managerMode();
		cout << "=================================" << endl;
		cout << "2. 성인 영화관 통계" << endl;
		SCR = pAdultScreen;	// 업 캐스팅
		SCR->managerMode();
		cout << "=================================" << endl;
		cout << "3. 프리미엄 영화관 통계" << endl;
		SCR = pPremiumScreen;	// 업 캐스팅 
		SCR->managerMode();
		cout << "=================================" << endl;
		return SCR;
```   

#### * 결제 기능   
		* 결제 방식이 모바일, 은행, 카드 결제로 나뉜다.
```c
// Screen.cpp //

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
					pSeatArray[i][j].setPayMethod(MOBILE_PHONE_PAYMENT); // 결제 방식 지정 
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
					pSeatArray[i][j].setPayMethod(BANK_TRANSFER_PAYMENT); // 결제 방식 지정 
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
					pSeatArray[i][j].setPayMethod(CREDIT_CARD_PAYMENT); // 결제 방식 지정
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
```

```c
// Pay.h //
class Pay {
public :
	virtual int charge(int amount) = 0;	
};

// Pay class를 상속받고 있다.
class CardPay : public Pay {
	double interest;
public : 
	CardPay(double rate) {
		this->interest = rate;
	}
	// 결제금액 = 티켓 가격 + 티켓가격 * 수수료비율
	int charge(int amount);
};
class BankTransfer : public Pay {
	double interest;
public : 
	BankTransfer(double rate) {
		this->interest = rate;
	}
	int charge(int amount);
};
class MobilePay : public Pay {
	double interest;
public : 
	MobilePay(double rate) {
		this->interest = rate;
	}
	int charge(int amount);
};
```   

#### * Screen.cpp
		* 영화 장르별 정보, 결제 방식, 좌석 초기화, 좌석 예약 및 예약완료 좌석 마킹 기능이 있다.
		* 가족, 성인, 프리미엄 영화는 업 캐스팅을 위해 Screen 객체를 상속받고 있다.   

```c
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
	void ShowSeatMap();	// 좌석 현황 
	virtual void ShowMovieMenu();	// 영화 메뉴 출력, 업캐스팅을 위한 가상함수
	virtual void ShowMovieInfo() = 0;	// 업캐스팅을 위한 가상 함수
	void reserveTicket();	// 좌석예약
	void Payment();		// 결제방식
	void managerMode();	// 관리자 모드 전환 
	int getTicketPrice() {
		return nTicketPrice;
	}
};
```