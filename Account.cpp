#include<iostream>
#include <string>
using namespace std;
#include "Account.h"

inline bool Account::authenticate(int id, string passwd)
{
	if ((id == nID) && (passwd == strPassword))	return true;
	else	return false;	// Ω«∆–
}


Account::Account()
{
	nID = -1;
	nBalance = 0;
}

void Account::create(int id, int money, string name, string password)
{
	nID = id;
	nBalance = money;
	strAccountName = name;
	strPassword = password;
}

void Account::close()
{
}

int Account::check(int id, string password)
{
	if (authenticate(id, password) == 1) return nBalance;		// ¿‹∞Ì
	else return AUTHENTIFICATION_FAIL;	// -1
}

int Account::deposit(int id, string password, int money)
{
	if (authenticate(id, password) == 1) {
		nBalance = nBalance + money;
		return nBalance;		// ¿‹∞Ì
	}
	else return AUTHENTIFICATION_FAIL;	// -1
}

int Account::widraw(int id, string password, int money)
{
	if (authenticate(id, password) == 1) {
		if (nBalance < money) return -1;

		else {
			nBalance -= money;
			return nBalance;		// ¿‹∞Ì
		}
	}
	else return AUTHENTIFICATION_FAIL;	// -1
}

int Account::deposit(int id, int money)
{

	if (id == nID) {
		nBalance += money;
		return nBalance;
	}
	else return AUTHENTIFICATION_FAIL;
}
