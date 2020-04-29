// bkim1790_L2_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Bauer Kristof
511
Írjunk ki egy, a 60-as számrendszerben megadott számot a 10-es számrendszerben! A 60-as számrendszer számjegyei: 0,1, …, 9, (10), (11), …, (59).
*/


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string beolvas()
{
	ifstream file;
	file.open("bkim1790_L2_5.txt");

	string szam60;
	if (file.is_open())
	{
		file >> szam60;
	}

	file.close();
	return szam60;

}



void atalakit(string szam)
{
	int hossz = szam.length() - 1;
	long hatv = 1;
	long sum = 0;
	int szamint = 0;

	while (hossz > -1)
	{
		if (szam[hossz] >= '0' && szam[hossz] <= '9')
		{
			szamint = int(szam[hossz])-48;
		}

		else if (szam[hossz] >= 'A' && szam[hossz] <= 'Z')
		{
			szamint = int(szam[hossz]) - 65+10;
		}

		else if(szam[hossz]>='a' && szam[hossz]<='x') 
		{
			szamint = int(szam[hossz]) - 97+36;
		}

		sum = sum + szamint * hatv;
		hatv = hatv * 60;

		hossz = hossz - 1;

	}	
	cout << sum;
}
int main()
{
	string szam = beolvas();
	atalakit(szam);
}