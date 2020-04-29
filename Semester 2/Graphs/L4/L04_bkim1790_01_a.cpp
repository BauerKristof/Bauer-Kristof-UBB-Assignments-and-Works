/*
Nev:Bauer Kristof
Csoport:511
*/

#include<iostream>
#include <fstream>
#include <limits>

using namespace std;

class Prufer
{
	int csp[20][20], fok[20] = { 0 };
	int csSzam, elSzam;


public:
	Prufer();
	void pruferKod();
};

Prufer::Prufer()
{
	ifstream file;
	file.open("graf.txt");
	if (file.is_open())
	{
		file >> csSzam;
		elSzam = csSzam - 1;
	
		for (int i = 0; i < elSzam; i++)
		{
			file >> csp[i][0];
			file >> csp[i][1];

			fok[csp[i][0]]++;
			fok[csp[i][1]]++;
		}
	}
}

void Prufer::pruferKod()
{
	int seged, min;

	cout << "PRUFER: { ";
	for (int i = 0; i < csSzam - 2; i++)
	{
		min = INT_MAX;

		for (int j = 0; j < elSzam; j++)
		{
			if (fok[csp[j][0]] == 1)
			{
				if (min > csp[j][0])
				{
					min = csp[j][0];
					seged = j;
				}
			}
			
			if (fok[csp[j][1]] == 1)
			{
				if (min > csp[j][1])
				{
					min = csp[j][1];
					seged = j;
				}
			}
		}

		fok[csp[seged][0]]--;
		fok[csp[seged][1]]--;

		if (fok[csp[seged][0]] == 0)
		{
			cout << csp[seged][1] << " ";
		}
		else
		{
			cout << csp[seged][0] << " ";
		}
	}
	cout << "}" << endl;
}

int main()
{
	Prufer teszt;
	teszt.pruferKod();
	
	system("pause");
	return 0;
}