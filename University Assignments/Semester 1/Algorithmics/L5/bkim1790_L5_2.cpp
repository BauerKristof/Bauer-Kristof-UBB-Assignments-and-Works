/*
Bauer Kristof
511
Írjunk rekurzív algoritmust, amely ellenőrzi, hogy egy beolvasott szám tökéletes szám-e (egyenlő-e a nála kisebb osztóinak összegével)!

*/



#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int &szam)
{
	ifstream file;
	file.open("bkim1790_L5_2.txt");
	if (file.is_open())
	{
		file >> szam;
	}

}

int tokeletes(int szam, int oszto)
{
	if (oszto == 1)
	{
		return 1;
	}
	else
	{
		if (szam % oszto == 0)
		{
			return oszto + tokeletes(szam, oszto-1);
		}
		else
		{
			return tokeletes(szam, oszto-1);
		}
	}
}


int main()
{
	int szam, oszto;
	beolvas(szam);
	oszto = szam / 2;
	if (tokeletes(szam, oszto) == szam) cout << "igen" << endl;
	else cout << "nem" << endl;
	system("PAUSE");
	return 0;

}