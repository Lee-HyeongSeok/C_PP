#include <iostream>
using namespace std;

class Gun;
class Bomb;
class Missile;

class Weapon {
public : 
	virtual void load() = 0;
	
	virtual void use() = 0;
	
	
};
class Gun : public Weapon {
public:
	Gun() {

	}
	void load() {
		cout << "���� �����" << endl;
	}
	void use() {
		cout << "���� �߻���" << endl;
	}
	~Gun() {
		
	}
};
class Bomb : public Weapon {
public:
	Bomb() {

	}
	void load() {
		cout << "��ź�� �����" << endl;
	}
	void use() {
		cout << "��ź�� ��Ʈ��" << endl;
	}
	~Bomb() {

	}
};
class Missile : public Weapon {
public:
	Missile() {

	}
	void load() {
		cout << "�̻����� �����" << endl;
	}
	void use() {
		cout << "�̻����� �߻���" << endl;
	}
	~Missile() {

	}
};
class Shop {
public : 
	virtual Weapon* selectMenu() {
		return NULL;
	}
};
class BattleShop : public Shop {
private : 
	int choice;
public : 

	Weapon* selectMenu() {
		
		cout << "=========================" << endl;
		cout << "���� ������ ����" << endl;
		cout << "=========================" << endl;
		cout << "1. ��" << endl;
		cout << "2. ��ź" << endl;
		cout << "3. �̻���" << endl;
		cout << "������ ����(1-3) �׿� ���� : " << endl;
		cin >> choice;
		switch (choice) {
		case 1: {
			Gun  * g = new Gun();
			return g;
			break;
		}
			
		case 2: {
			Bomb  * b = new Bomb();
			return b;
			break;
		}
			
		case 3: {
			Missile * m = new Missile();
			return m;
			break;
		}
			
		default : 
			cout << "���α׷� ����" << endl;
			return 0;
		}
	
	}
};

int main() {
	BattleShop bShop;
	Weapon *weapon;

	while (true) {
		weapon = bShop.selectMenu();
		if (weapon == 0) {
			return 0;
		}
		weapon->load();
		weapon->use();
		delete weapon;
	}
	return 0;
}