/*
Bauer Kristof
511
Adva van egy n db egész számot tartalmazó sorozat (2  n < 10). Helyezzünk az adott számok közé n – 1 aritmetikai műveleti jelt 
(+, –, *, /), úgy, hogy a kifejezés értéke legyen egyenlő egy adott K számmal! Amennyiben lehetetlen megoldást találni, 
írjunk ki megfelelő üzenetet! A kifejezés értéke minden lépésben legyen egész szám! A műveleteket nem a matematikából ismert 
operátorprecedencia szerint végezzük, hanem megjelenésük sorrendjében.
*/

#include <iostream>
#include <fstream>

using namespace std;

int n = 0;
int szamok[10], x[9];
int k = 0;

void beolvas()
{
	ifstream file;
	file.open("bkim1790_L6_03.txt");

	if (file.is_open())
	{
		file >> n;
		for (int i = 1; i <= n; i++) 
		{
			file >> szamok[i];
		}
		file >> k;
	}
}



void kiiras()
{
	cout << k << "= " << szamok[1];
	for (int i = 1; i <n; i++)
	{
		if (x[i] == 1) cout << " + "<<szamok[i+1];
		else if (x[i] == 2) cout << " - "<<szamok[i + 1];
		else if (x[i] == 3) cout << " * "<< szamok[i + 1];
		else if (x[i] == 4) cout << " / "<< szamok[i + 1];
	}
	cout << endl;

}

void back(int osszeg, int i, int m)
{
	if (m == 1)
	{
		if (osszeg == k)
		{
			kiiras();
		}
	}
	else
	{
		while (i <= n)
		{
			x[i-1] = 1;
			back(osszeg + szamok[i], i + 1, m - 1);
			x[i-1] = 2;
			back(osszeg - szamok[i], i + 1, m - 1);
			x[i-1] = 3;
			back(osszeg * szamok[i], i + 1, m - 1);
			x[i-1] = 4;
			back(osszeg / szamok[i], i + 1, m - 1);

			i++;
		}
	}

}

int main()
{
	beolvas();
	back(szamok[1],	2, n);
	system("pause");
	return 0;
}