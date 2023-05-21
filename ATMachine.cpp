#include <iostream>
#include "ATMachine.h"
using namespace std;

ATMachine::ATMachine(int size, int balance, string password)
{
	pAcctArray = new Account[size];
	nMaxAccountNum = size;
	nMachineBalance = balance;
	strManagerPassword = password;
}

ATMachine::~ATMachine()
{
	if (pAcctArray) delete[] pAcctArray;
}

// 화면
void ATMachine::displayMenu() {
	cout << "\n--------------------" << endl;
	cout << "-   TUKOREA BANK   -" << endl;
	cout << "--------------------" << endl;
	cout << " 1. 개좌 개설\n" 
		" 2. 개좌 조회\n"
		" 3. 계좌 입금\n" 
		" 4. 계좌 출금\n"
		" 5. 계좌 입금\n" 
		" 6. 고객 관리\n" 
		" 9. 업무 종료" << endl;
}

// 개설
void ATMachine::createAccount()
{
	string Aname, Apassword;
	if (nCurrentAccountNum < nMaxAccountNum) {
		cout << " ------ 개설 ------ " << endl;
		cout << "이름 입력 : "; cin >> Aname;
		cout << "암호 입력 : "; cin >> Apassword;

		srand(unsigned(time(0)));  // 시드값 설정

		int randNum = rand() % 901 + 100;  // 100부터 1000까지의 랜덤 번호 생성

		pAcctArray[nCurrentAccountNum++].create(randNum, 0, Aname, Apassword);
		cout << Aname << "님" << randNum << "번 계좌번호가 정상적으로 개설되었습니다. 감사합니다." << endl;
	}
	else
		cout << "계좌 개설 불가.";
}

// 조회
void ATMachine::checkMoney()
{
	int Id, check;
	string pass;

	cout << " ------ 조회 ------ " << endl;
	cout << "계좌번호 입력 : "; cin >> Id;
	cout << "비밀번호 입력 : "; cin >> pass;

	for (int i = 0; i < nMaxAccountNum; i++) {
		check = pAcctArray[i].check(Id, pass);
		if (check != -1) {
			cout << "현재 잔액  : " << check << endl;
			return;
		}
	}
	cout << "계좌가 존재하지 않습니다. " << endl;
	cout << endl;

}

// 해지
void ATMachine::closeAccount()
{
	cout << " ------ 해지 ------ " << endl;
	cout << "이름 입력 : ";
	cout << "암호 입력 : ";
}

// 입금
void ATMachine::depositMoney()
{
	int Id, money;
	string pass;

	cout << " ------ 입금 ------ " << endl;
	cout << "계좌번호 입력 : "; cin >> Id;
	cout << "비밀번호 입력 : "; cin >> pass;

	for (int i = 0; i < nMaxAccountNum; i++) {
		if (pAcctArray[i].check(Id, pass) != -1) {
			cout << "입금액   입력 : "; cin >> money;

			cout << "현재 잔액  : " << pAcctArray[i].deposit(Id, pass, money) << endl;	// 입금
			cout << "입금 완료" << endl;
			return;
		}
	}
	cout << "계좌가 존재하지 않습니다. " << endl;
}

// 출금
void ATMachine::widrawMoney()
{
	int Id, money, balance;
	string pass;

	cout << " ------ 출금 ------ " << endl;
	cout << "계좌번호 입력 : "; cin >> Id;
	cout << "비밀번호 입력 : "; cin >> pass;

	for (int i = 0; i < nMaxAccountNum; i++) {

		if (pAcctArray[i].check(Id, pass) != -1) {
			cout << "출금액   입력 : "; cin >> money;
			balance = pAcctArray[i].widraw(Id, pass, money);	// 출금
			if (balance != -1) {
				cout << "현재 잔액  : " << balance << endl;
				cout << "출금 완료" << endl;
				return;
			}
			else {
				cout << "잔액 부족" << endl;
				return;
			}
		}
	}
	cout << "계좌가 존재하지 않습니다. " << endl;
}

// 계좌이체
void ATMachine::transfer()
{
	int Id1, Id2, money, balance, flag;
	string pass;

	cout << "------ 이체 ------" << endl;
	cout << "계좌번호 입력 : "; cin >> Id1;
	cout << "비밀번호 입력 : "; cin >> pass;
	cout << "이체계좌 입력 : "; cin >> Id2;
	cout << "이체금액 입력 : "; cin >> money;
	for (int i = 0; i < nMaxAccountNum; i++) {

		if (pAcctArray[i].check(Id1, pass) != -1) {
			balance = pAcctArray[i].widraw(Id1, pass, money);   // 출금
			if (balance != -1) 
			{
				for (int j = 0; j < nCurrentAccountNum; j++) 
				{
					flag = pAcctArray[j].deposit(Id2, money);	// 이체
					if (flag != -1) break;						// 
					else if (j == nCurrentAccountNum - 1)		// 생성된 계좌 수만큼 반복했지만 이체계좌가 없을 때
					{		
						pAcctArray[i].deposit(Id1, pass, money);
						cout << "이체 계좌가 존재하지 않습니다. " << endl;
						return;
					}
				}
				cout << "현재 잔액  : " << balance << endl;		// 이체 후 잔액
				cout << "이체 완료" << endl;
				return;
			}
			else {
				cout << "잔액 부족" << endl;
				return;
			}
		}
	}
	cout << "계좌가 존재하지 않습니다. " << endl;
}

// 매니저 암호 확인
bool ATMachine::isManager(string password)
{
	if (strManagerPassword == password) return true;
	return false;
}

// 통계 화면 처리
void ATMachine::displayReport()
{
	cout << "--------------------" << endl;
	int sum = stat.sum(pAcctArray, nCurrentAccountNum);
	cout << "ATM  현재 잔고 : 	 " << nMachineBalance + sum << "원" << endl;
	cout << "고객 잔고 총액 :	 " << sum << "원(총 " << nCurrentAccountNum << "명)" << endl;
	cout << "고객 잔고 평균 :	 " << stat.average(pAcctArray, nCurrentAccountNum) << "원" << endl;
	cout << "고객 잔고 최고 :	 " << stat.max(pAcctArray, nCurrentAccountNum) << "원" << endl;
	cout << "--------------------" << endl;
	cout << "-  고객 계좌 목록  -" << endl;
	cout << "--------------------" << endl;
	stat.sort(pAcctArray, nCurrentAccountNum);

}

// 고객 관리
void ATMachine::managerMode()
{
	string password;
	cout << "------ 관리 ------" << endl;
	cout << "관리자 비밀번호 입력 : "; cin >> password;
	if (isManager(password)) {
		cout << "\n관리자입니다. \n" << endl;
		displayReport();
	}
	else cout << "비밀번호가 틀렸습니다. " << endl;
}
