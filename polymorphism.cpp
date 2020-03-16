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
		cout << "ÃÑÀÌ ÀûÀçµÊ" << endl;
	}
	void use() {
		cout << "ÃÑÀ» ¹ß»çÇÔ" << endl;
	}
	~Gun() {
		
	}
};
class Bomb : public Weapon {
public:
	Bomb() {

	}
	void load() {
		cout << "ÆøÅºÀÌ ÀûÀçµÊ" << endl;
	}
	void use() {
		cout << "ÆøÅºÀ» ÅÍÆ®¸²" << endl;
	}
	~Bomb() {

	}
};
class Missile : public Weapon {
public:
	Missile() {

	}
	void load() {
		cout << "¹Ì»çÀÏÀÌ ÀûÀçµÊ" << endl;
	}
	void use() {
		cout << "¹Ì»çÀÏÀ» ¹ß»çÇÔ" << endl;
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
		cout << "¹«±â ¾ÆÀÌÅÛ ¼±ÅÃ" << endl;
		cout << "=========================" << endl;
		cout << "1. ÃÑ" << endl;
		cout << "2. ÆøÅº" << endl;
		cout << "3. ¹Ì»çÀÏ" << endl;
		cout << "¾ÆÀÌÅÛ ¼±ÅÃ(1-3) ±×¿Ü Á¾·á : " << endl;
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
			cout << "ÇÁ·Î±×·¥ Á¾·á" << endl;
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