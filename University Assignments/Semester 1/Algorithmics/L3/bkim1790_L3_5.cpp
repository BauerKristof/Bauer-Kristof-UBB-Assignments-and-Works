/*
Bauer Kristof
511

Olvassunk be soronként több karakterláncot.A karakterláncok kisbetűket és számjegyeket tartalmaznak.Írjunk programot, amely kiszámolja minden karakterlánc esetében a bennük esetlegesen előforduló számok összegét!
*/


#include <iostream>
#include <fstream>
#include <string>
#include <cstring> //a compiler miatt

using namespace std;


int szamKeres(string str)
{
	int hossz = str.length();
	int ossz = 0, szam = 0;

	for (int i = 0; i < hossz; i++)
	{
		while (isdigit(str[i]) && (i<hossz))
		{
			int szamjegy = str[i] - '0';
			szam = szam * 10 + szamjegy;
			i++;
		}
		ossz += szam;
		szam = 0;
	}

	return ossz;

}

void beolvas()
{
	ifstream f;
	string s;
	f.open("bkim1790_L3_5.txt");

	if (f.is_open())
	{
		while (f >> s)
		{
			cout << szamKeres(s) << endl;
		}
	}

	f.close();
}


int main()
{
	int tores;

	beolvas();
	cin >> tores;

	return 0;
}