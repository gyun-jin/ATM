#include <iostream>
#include "Statistics.h"
using namespace std;

// ∞≥º≥µ» ∞Ë¡¬ ¿‹∞Ì «’
int Statistics::sum(Account* pArray, int size)
{
	int total = 0;
	for (int i = 0; i < size; i++) {
		total += pArray[i].getBalance();
	}
	return total;
}

// ∞≥º≥µ» ∞Ë¡¬ ¿‹∞Ì ∆Ú±’
int Statistics::average(Account* pArray, int size)
{
	int average;
	average = sum(pArray, size) / size;
	return average;
}

// ∞≥º≥µ» ∞Ë¡¬ ¿‹∞Ì √÷∞Ì
int Statistics::max(Account* pArray, int size)
{
	int max = pArray[0].getBalance();
	for (int i = 0; i < size; i++) {
		if (max < pArray[i].getBalance())
			max = pArray[i].getBalance();
	}
	return max;
}

// ¿‹∞Ì ≥ª∏≤¬˜º¯
void Statistics::sort(Account* pArray, int size)
{
	Account temp;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pArray[i].getBalance() > pArray[j].getBalance())
			{
				temp = pArray[i];
				pArray[i] = pArray[j];
				pArray[j] = temp;
			}
		}
	}
	for (int k = 0; k < size; k++) {
		cout << k << ". " << pArray[k].getAccountName() << "\t\t" << pArray[k].getAcctID() << "\t\t" << pArray[k].getBalance() << endl;
	}
}
