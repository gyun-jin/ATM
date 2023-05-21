#include<iostream>
#include "ATMachine.h"
#include "Account.h"
#include"Statistics.h"
using namespace std;

int main() {
	int select;
	// 고객 수(100명), ATM 잔금 초기화, 관리자 암호
	ATMachine atm(100, 50000, "admin");
	while (1) {
		atm.displayMenu();
		cout << "메뉴를 선택하세요 : ";
		cin >> select;
		cout << endl;
		switch (select) {
		case 1:
			atm.createAccount();	// 계좌 개설
			break;
		case 2:
			atm.checkMoney();		// 계좌 조회
			break;
		case 3:
			atm.depositMoney();		// 계좌 입금
			break;
		case 4:
			atm.widrawMoney();		// 계좌 출금
			break;
		case 5:
			atm.transfer();			// 계좌 이체
			break;
		case 6:
			atm.managerMode();		// 고객 관리
			break;
		case 9:
			cout << "안녕히 가세요." << endl;
			return 0;
		default:
			cout << "번호 확인 후 다시 입력하세요." << endl;
		}
	}
}