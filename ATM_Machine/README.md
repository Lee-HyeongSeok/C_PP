## * ATM 프로그램 작성   
#### * 사용환경 : visual studio 2017   

#### * 사용 소스 파일
1. Main.cpp
2. Account.cpp / Account.h
3. ATMachine.cpp / ATMachine.h
4. Statistics.cpp / Statistics.h   

#### * 메커니즘 : main -> ATMachine(사용자 명령 수행) -> Account(저장)   

#### * 기능 설명   

* Main, Account, ATMachine
	* 계좌 개설, 조회, 업무 종료 기능
	* 계좌 입금, 출금 기능   

* Statistics
	* 고객 관리 기능   

#### * 주요 소스 설명   

		* ATMachine
			* 고객의 계좌 정보를 저장하는 pAcctArray가 존재한다.
			* ATMachine에서 고객의 정보를 저장하지 않는다.
			* pAcctArray 포인터는 주로 Account 소스의 입, 출금 메서드에 접근한다.
			* createAccount 메서드를 통해 계좌를 개설할 수 있다.
	
		* void initialisze(int nSize, int nBalance, string password); 메서드 
			* 최대 고객수, ATM잔고, 관리자 암호로 구성되어있다.
			* 고객의 정보는 Account에서 갖지만 ATM 관리자 암호는 ATMachine에서 갖는다.
```c
class ATMachine {
private : 
	Account * pAcctArray;	// 동적 생성된 고객계좌 포인터 
	int nMachineBalance;   	// ATM 잔고
	int nMaxAccountNum;	// 동적생성된 고객계좌 배열크기
	int nCurrentAccountNum;	// 개설된 고객 계좌 수
	string strManagerPassword; // 관리자 비밀번호
	bool isManager(string password); // 관리자 모드 전환을 위한 메서드 
	void displayReport();	// 일반 사용자가 볼 수 없는 전체 계좌 현황, 아이디를 출력한다. 
		
public : 
	ATMachine();
	~ATMachine();
	// 기능 선택화면
	void displayMenu();	
	//계좌 배열크기, ATM 잔고, 관리자 암호 초기화
	void initialisze(int nSize, int nBalance, string password);	// ATM기계를 초기화할 때 사용한다.
	void createAccount();	// 계좌 개설 메서드
	void checkMoney();		// 계좌 조회 메서드 
	void depositMoney();	// 입금 메서드 
	void withdrawMoney();	// 출금 메서드
	void managerMode();		// 관리자 모드 진입 

};
```   
		* Account 
			* ATMachine을 통해 들어온 정보를 저장하는 객체이다.
			* ATMachine에서 선언한 pAcctArray라는 Account형 포인터 객체를 통해 관리된다.
			* 주로 고객의 이름, 계좌정보 및 비밀번호를 저장한다.
```c
class Account {
private : 
	int nID;	//계좌 번호
	int nBalance;	//잔고
	string strAccountName;	//고객 명
	string strPassword;	// 계좌 비밀번호

private :
	inline bool authenticate(int id, string passwd) {
		if (nID != id) {
			cout << "is not your ID..." << endl;
			return false;
		}
		else if(nID == id){
			if (strPassword == passwd) {
				cout << "Authentication successful" << endl;
				return AUTHENTIFICATION_SUCCESS;
			}
			else {
				cout << "is not your password.." << endl;
				return false;
			}
		}
	}
public : 
	Account();
	// 계좌 개설 멤버함수
	void create(int id, int money, string name, string password);
	// 현재 잔고 확인, 인증실패시 -1 반환
	int check(int id, string password);
	int GetBalance() const;
	int GetAccID() const;
	int deposit(int id, string password, int money);
	int withdraw(int id, string password, int money);
	string getAccountName();
};
```   

		* main   
			* ATMachine 객체를 생성하여 사용자가 입력한 case대로 기능을 실행한다.   
			* 사용 가능한 기능을 displayMenu 메서드를 통해 출력한다.
```c
int main() {
	int select;
	ATMachine atm;
	
	// ATM 기계 설정
	atm.initialisze(100, 50000, "admin");

	while (1) {
		atm.displayMenu();
		cin >> select;
		cout << endl;

		switch (select) {
		case 1:
			atm.createAccount();	// 계좌 개설
			break;
		case 2:
			atm.checkMoney();		// 계좌 확인
			break;
		case 3:
			atm.depositMoney();	// 입금
			break;
		case 4:
			atm.withdrawMoney();	// 출금
			break;
		case 5:
			atm.managerMode();	// 관리자 모드
			break;
		case 9:				// 취소를 눌렀을 때 
			cout << "안녕히 가세요!!!!" << endl;
			return 0;
		default:
			cout << "번호 확인 후 다시 입력하세요" << endl;
			break;
		}
	}
	return 0;
}
```

#### * 계좌 입금 
		* 성공 시 최종잔고 출력, 실패 시 인증 실패 상수 반환(AUTHENTIFICATION_FAIL)
		* ATMachine.cpp
				* deposit() 메서드는 Account 객체의 메서드이다.
				* pAcctArray는 Account객체의 배열이므로 접근이 가능하다.   

```c
void ATMachine::depositMoney() {	// 계좌 입금
	int id;
	string passwd;
	int money;
	cout << "------------입금--------------" << endl;
	cout << "계좌 번호 입력 : ";
	cin >> id;	cout << endl;
	cout << "비밀번호 입력 : ";
	cin >> passwd; cout << endl;
	cout << "입금액 입력 : "; cin >> money;	cout << endl;
	int index = 0;

	// pAcctArray[i] 배열은 Account 객체이다.
	for (int i = 0; i < nCurrentAccountNum; i++) {	//nMaxAccountNum 원래거
		if (pAcctArray[i].GetAccID() == id) {
			index = i;
			pAcctArray[index].deposit(id, passwd, money);
			cout << "현재 잔액 : " << pAcctArray[index].check(id, passwd) << endl;
			return;
		}

	}
	cout << "This ID does not exist" << endl;
//	pAcctArray[index].deposit(id, passwd, money); // ID 패스워드 넣을 돈
//	cout << "현재 잔액 : " << pAcctArray[index].check(id, passwd) << endl;
}
```
		* Account.cpp   

				* ATMachine에서 입금 기능에 사용되는 메서드이다.
				* 입금 후 잔고를 반환해주고 있다.   
				* 주로 고객의 이름, 계좌명, 계좌 비밀번호를 저장한다.
```c
int Account::deposit(int id, string password, int money) {
	if (authenticate(id, password) == true) {	// id와 패스워드가 맞을 때
		nBalance += money;
	}
	else {
		return 0;
	}
	return nBalance;
}
```   

#### * 계좌 출금   
		* 성공 시 최종잔고, 실패 시 인증 실패 상수반환(AUTHENTIFICATION_FAIL)
		* ATMachine.cpp   
				* withdraw() 메서드는 Account 객체의 메서드이다.
				* pAcctArray는 Account객체의 배열이므로 접근이 가능하다.   

```c
void ATMachine::withdrawMoney() {
	int id;
	string passwd;
	int money;
	cout << "----------출금----------" << endl;
	cout << "계좌번호 입력 : "; cin >> id;	cout << endl;
	cout << "비밀번호 입력 : "; cin >> passwd; cout << endl;
	cout << "출금액 입력 : "; cin >> money; cout << endl;
	int index = 0;
	for (int i = 0; i < nCurrentAccountNum; i++) {
		if (pAcctArray[i].GetAccID() == id) { // 사용자 인증 부분 
			index = i;

			// withdraw() 메서드는 Account.cpp에 있다.
			pAcctArray[index].withdraw(id, passwd, money);
			cout << "현재 잔액 : " << pAcctArray[index].check(id, passwd) << endl;
			return;
		}

	}
	// 인증 실패 시 메시지 출력 
	cout << "This ID does not exist" << endl;
	
}
```   

		* Account.cpp   
				* ATMachine에서 출금 기능에 사용되는 메서드이다.
				* 출금 후 잔고를 반환해주고 있다.   
				* 주로 고객의 이름, 계좌명, 계좌 비밀번호를 저장한다.   

```c
int Account::withdraw(int id, string password, int money) {
	if (authenticate(id, password) == true) {
		if (nBalance < money) {
			cout << "lack of your balance.." << endl;
			return nBalance;
		}
			// if (nBalance >= money) 
		nBalance -= money;
		
	}
	else {
		return AUTHENTIFICATION_FAIL;	// 실패 시 상수 반환 
	}
	return nBalance;
}
```   

#### * 관리자 모드 
		* ATMachine.cpp
			* managerMode() : 관리자 인증 확인 후 성공 시 displayReport() 메서드를 호출한다.
		
		* displayReport() : Statistics 객체를 선언 후 모든 고객의 잔고 현황을 출력한다.
		
		* Statistics.cpp 
			* 모든 메서드의 인자로 Account 객체에 접근하고 있다.
			* Account 객체는 고객의 정보를 저장하는 객체이다.
			* ATMachine에 있는 displayReport() 메서드에서 Account 형 포인터인 pAcctArray를 인자로 전달받는다.   

** ATMachine.cpp / 매니저 모드 진입 
```c
void ATMachine::managerMode() {
	string ad;
	cout << "-------------관리-----------" << endl;
	cout << "관리자 비밀번호 입력 : "; cin >> ad;
	if (isManager(ad) == true) {
		cout << "관리자 입니다." << endl;
		displayReport();	// 총 고객 현황 메서드 호출, Statistics 객체가 영향을 준다.
	}
	else {
		cout << "관리자 비밀번호가 틀렸습니다." << endl;
		return;
	}
}
```   

** ATMachine.cpp / displayReport() 메서드 호출  
```c
void ATMachine::displayReport() {
	Statistics s;
	cout << "총 고객 :" << nCurrentAccountNum << endl;
	int res1, res2, res3;
	
	// pAcctArray에는 고객들의 정보가 저장되어있다.
	res1 = s.sum(pAcctArray, nCurrentAccountNum);	
	res2 = s.average(pAcctArray, nCurrentAccountNum);
	res3 = s.max(pAcctArray, nCurrentAccountNum);
	cout << "ATM 현금 잔고 : " << nMachineBalance+res1 << endl;	// ATM
	cout << "고객 잔고 전체 금액 : " << res1 << endl;	// 고객 + ATM
	cout << "고객 잔고 평균 금액 : " << res2 << endl;
	cout << "고객 잔고 최고 금액 : " << res3 << endl;

	cout << "-----------계좌 현황------------" << endl;
	for (int i = 0; i < nCurrentAccountNum; i++) {
		cout << pAcctArray[i].getAccountName() << " " << pAcctArray[i].GetAccID() << ' ' << pAcctArray[i].GetBalance() << endl;
	}
	cout << "--------------------------------" << endl;
}
```   

** Statistics.cpp / ATMachine에서 선언한 Account형 포인터를 인자로 받는다.
```c
int Statistics::sum(Account * pArray, int size) {
	int total_b = 0;
	for (int i = 0; i < size; i++) {
		total_b += pArray[i].GetBalance();
	}
	return total_b;
}
int Statistics::average(Account* pArray, int size) {
	int total_b = 0;
	for (int i = 0; i < size; i++) {
		total_b += pArray[i].GetBalance();
	}
	if (total_b == 0) {
		return 0;
	}
	return total_b / size;
}
int Statistics::max(Account* pArray, int size) {
	int *temp = new int[size];

	for (int i = 0; i < size; i++) {
		temp[i] = pArray[i].GetBalance();
	}
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (temp[j] < temp[j+1]) {
				SWAP(temp[j], temp[j + 1]);
			}
		}
	}
	if (size == 0) {
		temp[0] = 0;
	}

	return temp[0];
	delete[]temp;
}
```