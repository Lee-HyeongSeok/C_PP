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
		screen->ShowMovieMenu();	// �޴� ���
		cout << "�޴��� �����ϼ��� : ";
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
			cout << "�߸��� �� �Է� .." << endl;
		}
		
	}
	return 0;
}