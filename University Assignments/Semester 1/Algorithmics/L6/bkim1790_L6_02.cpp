/*
Bauer Kristof
511
Oldjuk meg a királynős feladatot három logikai tömb segítségével. 
Ezen tömbök értékei azt fejezik ki, hogy létezik-e királynő egy bizonyos oszlopban, vagy egy olyan átlón, amely párhuzamos a főátlóval, 
illetve egy olyanon, amely párhuzamos a mellékátlóval.

*/

#include <iostream>
#include <math.h>

using namespace std;

int sorelembenoszlop[100];
bool foatlo[100], mellekatlo[100],oszlop[100];
int m = 0;
int n = 0; 

void kiir(int m) {
	cout << m << ". megoldas:" << endl;
	for (int i = 0; i <n; i++)
	{
		for (int j = 0; j < n; j++) 
		{
			if (sorelembenoszlop[i] == j)
				cout << "Q ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
	cout << endl;
}


bool nemTamad(int i,int j) 
{
	for (int j = 0; j < i ; j++)
	{

		if (sorelembenoszlop[i] == sorelembenoszlop[j])
		{
			return false;
		}
	}



	if (mellekatlo[i + j] == true)
	{
		return false;
	}

	else if (foatlo[n-i+j] == true)
	{
		return false;
	}

	else if (oszlop[j] == true)
	{
		return false;
	}
	else return true;
	
}

void kiralyno(int i,int n) 
{

	for (int j = 0; j < n; j++) 
	{
		sorelembenoszlop[i] = j;
		
		if (nemTamad(i,j) == true) 
		{
			oszlop[j] = true;
			mellekatlo[i+j] = true;
			foatlo[n-i+j] = true;

			if (i < n-1)
			{
				kiralyno(i + 1, n);
			}
			else if(i==n-1)
			{
				m++;
				kiir(m);
			}
			oszlop[j] = false;
			foatlo[n - i + j] = false;
			mellekatlo[i + j] = false;
		}
	}
}

int main()
{
	cout << "Add meg hany kiralyno legyen" << endl;
	cin >> n;
	kiralyno(0,n);
	system("pause");
	return 0;
}
