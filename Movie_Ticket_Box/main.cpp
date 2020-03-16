#include <iostream>
#include "Screen.h"
#include "TicketBox.h"

using namespace std;

int main() {
	KpuTicketBox tBox;
	Screen *screen = NULL;
	bool bScreenMenu = true;
	int select = 0;

	tBox.Initialize();
	while (1) {
		if (bScreenMenu) {
			screen = tBox.selectMenu();
			bScreenMenu = false;
			if (!screen)return 0;
		}
		screen->ShowMovieMenu();	// 메뉴 출력
		cout << "메뉴를 선택하세요 : ";
		cin >> select; cout << endl;
		if (select >= 1 && select <= 9) {
			switch (select) {
			case 1:
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
		else {
			cout << "잘못된 값 입력 .." << endl;
		}
		
	}
	return 0;
}