/*
Bauer Kristof
511
Írjunk rekurzív algoritmust, amely kiír egy n természetes számot törzstényezőkre bontva!
*/



#include <iostream>
#include <fstream>

using namespace std;

void beolvas(int &szam)
{
	ifstream file;
	file.open("bkim1790_L5_1.txt");
	if (file.is_open())
	{
		file >> szam;
	}

}

void torzstenyezo(int szam, int hanyados, int db)
{
	if (szam == 1)
	{
		cout << hanyados << "^" << db;
			return;

	}

	else
	{
		if ((szam%hanyados) == 0)
		{
			return torzstenyezo(szam / hanyados, hanyados, db + 1);
		}

		else
		{
			if (db != 0)
			{
				cout << hanyados << "^" << db;
				db = 0;
				cout << "*";
			}
			return torzstenyezo(szam, hanyados + 1, db);

		}
	}
}

int main()
{
	int szam, hanyados=2;
	int db = 0;
	beolvas(szam);
	torzstenyezo(szam, hanyados, db);
	cout << endl;
	system("PAUSE");
	return 0;

}